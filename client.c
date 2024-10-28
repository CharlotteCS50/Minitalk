/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:14:08 by cschnath          #+#    #+#             */
/*   Updated: 2024/10/28 23:33:36 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The client reads the server’s PID and the message from the command-line
arguments. It iterates over each character in the message.
For each character, it calls the send_signal function, which will convert the
character into 8 bits and sends each bit as a signal to the server.
It uses SIGUSR1 to represent a 1 bit and SIGUSR2 to represent a 0 bit.
After sending each bit, the client waits for a short duration
(42 microseconds) using the usleep function. This delay allows the server
to process the received signals.
*/

#include "minitalk.h"

// Global variable, always resets flag to 0
// Lets client know when the server has received & processed a bit
int		g_flag = 0;

// Detect acknowledgement signals from the server
void	ft_handler(int signum)
{
	if (signum == SIGUSR1 || signum == SIGUSR2)
		g_flag = 1;
}

// Sends a single bit, should be done
void	ft_send_bit(int pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1; // Basically only 1s are important
	else
		signal = SIGUSR2; // Other one is 0s
	if (kill(pid, signal) == -1) // Send the signal
	{
		// If it doesn't work, sennd error message
		perror("Error sending signal");
		exit(EXIT_FAILURE);
	}
	g_flag = 0;
	while (!g_flag)
		; // Apparently this waits until the signal is processed
}

// Sends a char bit by bit, should be done
void	ft_send_char(int pid, unsigned char c)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		bit = (c >> (7 - i)) & 1; // Get the i-th bit from the left
		ft_send_bit(pid, bit);
		usleep(200); // Short delay to make sure signal is being processed
		i++;
	}
}

// This one should be done, sends a whole string char by char
void	ft_send_string(int pid, const char *str)
{
	while (*str)
		ft_send_char(pid, *str++);
	ft_send_char(pid, '\0'); // Null-terminate the string
}

// Sends a string to a PID of the server
int	main(int argc, char *argv[])
{
	__pid_t pid;
	struct sigaction sa;
	// Check the command line arguments
	// Has to be name of program and the message to be sent
	if (argc != 3)
	{
		ft_printf("Usage: ./client [PID] [string]\n");
		exit(EXIT_FAILURE);
	}
	pid = atoi(argv[1]);
	if (pid <= 0) // Make sure pid is valid
	{
		ft_printf("Error: Invalid PID\n");
		exit(EXIT_FAILURE);
	}
	sa.sa_handler = ft_handler;
	sigemptyset(&sa.sa_mask); // Mask signals that should be blocked
	sa.sa_flags = 0;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		{
			perror("Error setting up signal");
			exit(EXIT_FAILURE);
		}
	ft_send_string(pid, argv[2]);
	return (0);
}