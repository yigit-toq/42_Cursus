/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:18:53 by ytop              #+#    #+#             */
/*   Updated: 2024/09/30 00:18:53 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	err_msg(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd(ERR_TITLE, STDERR_FILENO);
	if (cmd)
		ft_dprintf(STDERR_FILENO, "%s", cmd);
	if (arg)
		ft_dprintf(STDERR_FILENO, "`%s'", arg);
	if (msg)
		ft_dprintf(STDERR_FILENO, ": %s", msg);
	ft_dprintf(STDERR_FILENO, "\n");
	return (SUCCESS);
}
