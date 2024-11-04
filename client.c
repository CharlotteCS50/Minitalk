/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:14:08 by cschnath          #+#    #+#             */
/*   Updated: 2024/11/04 14:12:41 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The client reads the server’s PID and the message from the command-line
arguments. It iterates over each character in the message.
For each character, it calls the send_signal function, which will convert the
character into 8 bits and sends each bit as a signal to the server.
It uses SIGUSR1 to represent a 1 bit and SIGUSR2 to represent a 0 bit.
After sending each bit, the client waits for a short duration
using the usleep function. This delay allows the server
to process the received signals.
*/

#include "minitalk.h"

void	ft_handler(int pid, char c)
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
		usleep(420);
	}
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
	string = argv[2];
	flag = 0;
	while (string[flag])
		ft_handler(pid, string[flag++]);
	ft_handler(pid, '\0');
}
