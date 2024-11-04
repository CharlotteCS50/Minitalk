/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:42:06 by cschnath          #+#    #+#             */
/*   Updated: 2024/11/04 20:09:37 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_handler_b(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (((c & 1 << i)) == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		usleep(100);
	}
}

void	ft_acknowledgement(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("Server acknowledged the message\n");
}

int	main(int argc, char *argv[])
{
	__pid_t		pid;
	const char	*string;
	int			flag;

	signal(SIGUSR1, ft_acknowledgement);
	if (argc != 3)
	{
		ft_printf("Usage: ./client [PID] [string]\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	string = argv[2];
	flag = 0;
	while (string[flag])
		ft_handler_b(pid, string[flag++]);
	ft_handler_b(pid, '\0');
}
