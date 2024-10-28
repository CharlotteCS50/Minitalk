/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:14:13 by cschnath          #+#    #+#             */
/*   Updated: 2024/10/28 23:09:50 by cschnath         ###   ########.fr       */
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

// Signum specifies signal, can be anything except sigkill and sigstop
// No idea how to do this one
void	ft_signal_handler(int signum, siginfo_t *info, void *context)
{
	static int bit_count = 0;
	static __pid_t	client_pid = 0;
	static unsigned char c = 0;
	
	(void)context; // Set user context to void bc it's unused
	if (client_pid == 0) // If it's the first signal
		client_pid = info->si_pid; // Set client pid 
	if (signum == SIGUSR1) // SIGUSR1 represents 1
		c = (c << 1) | 1; // Move bit ("1") by 1
	else if (signum == SIGUSR2) // SIGUSR2 represents 0
		c = (c << 1); // Just move on to the next bit
	ft_printf("\nSignal handler function called %d\n", signum); // Test
	bit_count++;
	if (bit_count == 8) // A full byte has been received
	{
		if (c == '\0') // End of message
		{
			kill(client_pid, SIGUSR2); // Send stuff with signal 2
			client_pid = 0;
		}
		else
		{
			write(1, &c, 1);
			kill(client_pid, SIGUSR1); // Send stuff with signal 1
		}
		bit_count = 0; // Reset count back to 0
		c = 0;
	}
	ft_printf("Received SIGINT!\n", signum); // Test
}

// Waits to receive signals and processes them in ft_signal_handler
int	main(void)
{
	// Sigaction examines and changes a signal action
	struct sigaction	sa;
	
	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = ft_signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause(); // Wait for signal; returns -1
	return (0);
}