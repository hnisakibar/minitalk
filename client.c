/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisa <nisa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:52:58 by hakibar           #+#    #+#             */
/*   Updated: 2025/04/05 04:23:27 by nisa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdatomic.h>

sig_atomic_t	g_ack = 0;

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	ack_handler(int signal_type)
{
	(void)signal_type;
	g_ack = 1;
}

void	send_message(char *argv, int server_pid)
{
	int	i;
	int j;
	char c;

	i = 0;
	while (argv[i] != '\0')
	{
		c =	argv[i];
		j = 0;
		while (j < 8)
		{
			g_ack = 0;
			if ((c << j) & 128)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			while (!g_ack)
				pause();
			usleep(SLEEP_TIME);
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	server_pid;

	server_pid = -1;
	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		if (server_pid <= 0 || kill(server_pid, 0) == -1)
		{
			write(2, "Error: Invalid PID\n", 18);
			exit(1);
		}
		signal(SIGUSR1, ack_handler);
		send_message(argv[2], server_pid);
	}
	else
		write(2, "Error: ./client <Server_Pid> <Message>\n", 39);
	return (0);
}
