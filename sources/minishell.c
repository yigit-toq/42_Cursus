/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:41:40 by ytop              #+#    #+#             */
/*   Updated: 2024/09/27 01:59:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	g_signal;

static int	minishell_loop(t_minishell *minishell, char *env[]);

static void	starting(void);

t_minishell	*get_minishell(void)
{
	static t_minishell	minishell;

	return (&minishell);
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	starting();
	handle_signals();
	minishell = get_minishell();
	minishell_loop(minishell, env);
	return (SUCCESS);
}

static void	init_data(void);

static int	minishell_routine(t_minishell *minishell);

static int	minishell_loop(t_minishell *minishell, char *env[])
{
	int	value;

	ft_bzero(minishell, sizeof(t_minishell));
	env_to_list(env);
	while (TRUE)
	{
		value = 0;
		init_data();
		minishell->line = readline(GREEN PROMPT RESET);
		if (!minishell->line)
		{
			ft_putstr_fd("exit\n", 0);
			rl_clear_history();
			exit(0);
		}
		if (ft_strlen(minishell->line) != 0)
		{
			value = minishell_routine(minishell);
			if (value == 1)
				return (FAILURE);
			else if (value == 2)
				continue ;
		}
		if (minishell->line)
			free(minishell->line);
	}
	return (SUCCESS);
}

static int	minishell_routine(t_minishell *minishell)
{
	add_history(minishell->line);
	return (0);
}

static void	init_data(void)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	minishell->pipe_count = 0;
}

static void	starting(void)
{
	ft_printf(GREEN "\033[H\033[J");
	ft_printf("   _____   __        __        __            __   __\n");
	usleep(100000);
	ft_printf("  /     \\ |__| ____ |__| _____|  |__   ____ |  | |  |\n");
	usleep(100000);
	ft_printf(" /  \\ /  \\|  |/    \\|  |/  ___/  |  \\_/ __ \\|  | |  |\n");
	usleep(100000);
	ft_printf("/    Y    \\  |   |  \\  |\\___ \\|   Y  \\  ___/|  |_|  |__\n");
	usleep(100000);
	ft_printf("\\____|__  /__|___|  /__/____  >___|  /\\___  >____/____/\n");
	usleep(100000);
	ft_printf("        \\/        \\/        \\/     \\/     \\/\n" RESET);
	usleep(500000);
	ft_printf(BLACK "\nCREATED BY:\n");
	usleep(500000);
	ft_printf("\t\t _________________");
	ft_printf("\n\t\t/                 \\\n");
	ft_printf("\t\t| ytop & abakirca |\n");
	ft_printf("\t\t\\_________________/\n");
	ft_printf("\n\n" RESET);
}
