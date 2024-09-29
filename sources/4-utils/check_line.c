/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:42:03 by ytop              #+#    #+#             */
/*   Updated: 2024/09/27 14:42:03 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_line(void)
{
	t_minishell	*minishell;
	char		*line;
	int			quote;

	minishell = get_minishell();
	line = ft_strtrim(minishell->line, " ");
	if (ft_strcmp(line, "") == 0)
		return (gfree(line), FAILURE);
	quote = check_quote(line, ft_strlen(line));
	if (quote)
	{
		gfree(line);
		minishell->value.exit_code = 2;
		return (ft_dprintf(STD_ERROR, SYNTAX_ERR " `%c\'\n", quote), FAILURE);
	}
	return (SUCCESS);
}

//pipe_control eklenecek

int	check_quote(char *line, int value)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (i < value)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		i++;
	}
	return ((int)quote);
}

static void	process_char(char *in, char *buf, int *i, int *j);

// Yeniden düzenlenecek

int	replace_arg(char *args)
{
	char	*input;
	char	*buffer;
	int		src_index;
	int		dst_index;
	int		in_len;

	input = args;
	in_len = ft_strlen(input);
	buffer = ft_calloc((in_len * 2) + 1, sizeof(char));
	if (!buffer)
		return (perror("ft_calloc"), FAILURE);
	src_index = 0;
	dst_index = 0;
	while (src_index < in_len)
		process_char(input, buffer, &src_index, &dst_index);
	buffer[dst_index] = '\0';
	args = buffer;
	return (SUCCESS);
}

// gfree(args); line : 80

static void	process_char(char *in, char *buf, int *i, int *j)
{
	if ((in[*i] == '>' || in[*i] == '<') && !check_quote(in, *i))
	{
		if (*i > 0 && in[*i - 1] != ' ' && in[*i - 1] != '>' && in[*i - 1] != '<')
			buf[(*j)++] = ' ';
		if (in[*i] == '>' && in[*i + 1] == '>')
		{
			buf[(*j)++] = '>';
			buf[(*j)++] = '>';
			(*i) += 2;
		}
		else if (in[*i] == '<' && in[*i + 1] == '<')
		{
			buf[(*j)++] = '<';
			buf[(*j)++] = '<';
			(*i) += 2;
		}
		else
			buf[(*j)++] = in[(*i)++];
		if (*i < (int)ft_strlen(in) && in[*i] != ' ' && in[*i] != '>' && in[*i] != '<')
			buf[(*j)++] = ' ';
	}
	else
	{
		buf[(*j)++] = in[(*i)++];
	}
}
