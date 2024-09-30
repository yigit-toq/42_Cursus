/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:40:41 by ytop              #+#    #+#             */
/*   Updated: 2024/09/29 18:40:41 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

char	*get_pwd(void)
{
	char	pwd[4096];
	char	*path;

	path = getcwd(pwd, 4096);
	if (!path)
		return (perror("minishell: pwd: "), NULL);
	return (ft_printf("%s\n", path), path);
}
