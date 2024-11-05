/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:42:06 by cschnath          #+#    #+#             */
/*   Updated: 2024/11/05 23:48:53 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Run with make bonus

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
		usleep(500);
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

	if (argc != 3)
	{
		ft_printf("Usage: ./client [PID] [string]\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, ft_acknowledgement);
	string = argv[2];
	flag = 0;
	while (string[flag])
		ft_handler_b(pid, string[flag++]);
	ft_handler_b(pid, '\0');
}
