/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 00:32:47 by ytop              #+#    #+#             */
/*   Updated: 2024/09/30 00:32:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_minishell *minishell)
{
	if (minishell->pipe_count == 0)
		return (single_command(minishell));
	else
		return (multiple_command(minishell));
	return (FAILURE);
}
