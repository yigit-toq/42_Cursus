/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:54:23 by ytop              #+#    #+#             */
/*   Updated: 2024/09/27 00:32:19 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>
#include <signal.h>

static void	ctrl_c(int signal);
static void	ctrl_d(int signal);

void	handle_signals(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_d);
}

static void	ctrl_c(int signal)
{
	(void)signal;
	if (g_signal == 2)
	{
		printf("\033[A");
		ioctl(0, TIOCSTI, "\n");
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_signal = 1;
}

static void	ctrl_d(int signal)
{
	(void)signal;
	rl_on_new_line();
	printf("\033[K");
	rl_redisplay();
	g_signal = 0;
}

//tcseta fonksiyonu eklenecek