/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:14:13 by cschnath          #+#    #+#             */
/*   Updated: 2024/11/06 00:29:44 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_signal_handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bit;

	(void)context;
	c |= (signal == SIGUSR1);
	bit++;
	if (bit == 8)
	{
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
			usleep(5000);
		}
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &ft_signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
