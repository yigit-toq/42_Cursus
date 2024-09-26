/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:41:40 by ytop              #+#    #+#             */
/*   Updated: 2024/09/26 18:18:45 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	starting(void);

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	starting();
	handle_signal();
	ft_bzero(&minishell, sizeof(t_minishell));
	minishell.env = env_to_list(env);
	return (SUCCESS);
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
