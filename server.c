/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisa <nisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:52:23 by hakibar           #+#    #+#             */
/*   Updated: 2025/04/05 04:41:47 by nisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr(int number)
{
	char	character;

	if (number >= 10)
		ft_putnbr(number / 10);
	character = (number % 10) + '0';
	write(1, &character, 1);
}

void	write_message(int signal_type, siginfo_t *info, void *context)
{
	static int	index;
	static char	a;

	(void)context;
	a = a << 1;
	if (signal_type == SIGUSR1)
		a = a | 1;
	index++;
	if (index == 8)
	{
		write(1, &a, 1);
		a = 0;
		index = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	int					server_pid;

	sa.sa_sigaction = write_message;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	server_pid = getpid();
	if (server_pid <= 0)
	{
		write(2, "Error: PID Error\n", 17);
		exit(1);
	}
	write(1, "Server PID: ", 12);
	ft_putnbr(server_pid);
	write(1, "\n", 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error: SIGNAL Error\n", 20);
		exit(1);
	}
	while (1)
		pause();
}
