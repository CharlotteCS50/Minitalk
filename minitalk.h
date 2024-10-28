/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:01:21 by cschnath          #+#    #+#             */
/*   Updated: 2024/10/28 21:35:41 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "Libft/libft.h"

// Client
void    ft_handler(int signum);
void	ft_send_bit(int pid, int bit);
void	ft_send_char(int pid, unsigned char c);
void	ft_send_string(int pid, const char *str);

// Server
void	ft_signal_handler(int signum, siginfo_t *info, void *context);

#endif