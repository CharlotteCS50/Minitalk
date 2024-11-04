/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:14:13 by cschnath          #+#    #+#             */
/*   Updated: 2024/11/04 19:46:51 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The server starts by displaying its PID on the console.
It sets up signal handlers for SIGUSR1 and SIGUSR2 signals using the signal
function. The server enters an infinite loop and waits for signals using the
pause function. When a signal is received, the corresponding signal handler
(handle_signal) is called. The handle_signal function extracts the bit value
(0 or 1) from the received signal and appends it to the current character
being received. If the character is fully received (8 bits), it is displayed
on the console using ft_printf. The bit index and current character are reset
to prepare for the next character.
(Bonus only) After processing the received signal, the server sends a signal
back to the client. If the received signal was SIGUSR1, it sends SIGUSR1 to
acknowledge the received bit. If the received signal was SIGUSR2, it sends
SIGUSR2 back.
*/

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
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	return (0);
}
