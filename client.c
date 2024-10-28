/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:14:08 by cschnath          #+#    #+#             */
/*   Updated: 2024/10/27 19:30:41 by cschnath         ###   ########.fr       */
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

int g_flag = 0; // Global variable, always resets flag to 0

// Finish this, not sure how
void    ft_handler(int signum)
{
    g_flag = 1;
    
}

// Work on this! Sends a single bit
void	ft_send_bit(int pid, int bit)
{
	int	signal;
	
	if (bit == 1)
		signal = SIGUSR1; // Basically only 1s are important
	else
		signal = SIGUSR2; // Other one is 0s
}

// Almost done, sends a char bit by bit
void	ft_send_char(int pid, unsigned char c)
{
	int	i;

	i = 8;
	while (i > 0)
	{
		ft_send_bit(pid, c >> i); // Change bitwise stuff
		usleep(); // If it works it should return 0
		i--;
	}
}

// This one should be done, sends a whole string char by char
void	ft_send_string(int pid, const char *str)
{
	while (*str)
		ft_send_char(pid, *str++);
	ft_send_char(pid, '\0'); // Null-terminate the string
}

int	main(int argc, char *argv[])
{
	__pid_t pid; // Predefined struct, not sure if I'm using it right

	// Check the command line arguments
	// Has to be name of program, process id and the message to be sent
	if (argc != 3)
	{
		ft_putstr("Usage: ./client [PID] [string]\n");
		exit(EXIT_FAILURE);
	}
}