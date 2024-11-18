/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 07:40:15 by sudaniel          #+#    #+#             */
/*   Updated: 2024/11/15 10:24:43 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "ft_printf/ft_printf.h"

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char	buffer = 0;
	static int	bit_index = 0;

	(void)context;
	if (signum == SIGUSR1)
		buffer = (buffer << 1) | 1;
	else if (signum == SIGUSR2)
		buffer = (buffer << 1) | 0;
	bit_index++;
	if (bit_index == 8)
	{
		write(1, &buffer, 1);
		buffer = 0;
		bit_index = 0;
	}
	usleep(50);
	if (signum == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (signum == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sigact;

	ft_printf("%d\n", getpid());
	sigact.sa_sigaction = signal_handler;
	sigact.sa_flags = SA_SIGINFO;
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
	while (1)
		pause();
}
