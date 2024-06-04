/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:09 by ytop              #+#    #+#             */
/*   Updated: 2024/03/18 15:03:51 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "../ft_printf/includes/ft_printf.h"

static void	send_bit(int pid, char *string, int length)
{
	int	bit;
	int	index;

	index = 0;
	while (index < length)
	{
		bit = 0;
		while (bit < 8)
		{
			if ((string[index] >> bit) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit++;
			usleep(100);
		}
		index++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
	{
		send_bit(ft_atoi(argv[1]), argv[2], ft_strlen(argv[2]));
		send_bit(ft_atoi(argv[1]), "\n", 2);
	}
	else
		ft_printf("%s", "\033[0;31mplease enter [PID] and [Message]\033[0m\n");
	return (0);
}
