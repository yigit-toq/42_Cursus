/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:06 by ytop              #+#    #+#             */
/*   Updated: 2024/03/18 14:32:56 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "../ft_printf/includes/ft_printf.h"

static void	handler_bit(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
		i |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}

int	main(void)
{
	ft_printf("\033[0;32mServer Connected!\033[0m\n");
	ft_printf("Server PID -> %d\n", getpid());
	while (1)
	{
		signal(SIGUSR1, handler_bit);
		signal(SIGUSR2, handler_bit);
		pause();
	}
	return (0);
}
