/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 06:56:44 by sudaniel          #+#    #+#             */
/*   Updated: 2024/11/15 10:02:49 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "ft_printf/ft_printf.h"

static void	send_signal(char *message, int pid)
{
	int	signum;
	int	i;

	while (*message)
	{
		i = 8;
		while (i)
		{
			signum = (*message >> --i) & 1;
			if (signum)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			pause();
			usleep(50);
		}
		message++;
	}
}

static void	acknowledge(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR1)
		write(1, "Bit 1 received.\n", 16);
	else if (signum == SIGUSR2)
		write(1, "Bit 0 received.\n", 16);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sigact;

	pid = ft_atoi(argv[1]);
	if (argc != 3 || pid <= 0)
	{
		ft_printf("Error!\nCheck Inputs, PID and arguments count\n");
		return (0);
	}
	sigact.sa_sigaction = acknowledge;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
	{
		ft_printf("Error: failed to install signal\n");
		return (0);
	}
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
	{
		ft_printf("Error: failed to install signal\n");
		return (0);
	}
	send_signal(argv[2], pid);
	send_signal("\n", pid);
	return (0);
}
