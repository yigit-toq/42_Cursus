/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:32:09 by ytop              #+#    #+#             */
/*   Updated: 2024/09/29 21:32:09 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// indexes[0]: string_index, indexes[1]: word_start, indexes[2]: word_count, indexes[3]: quote_flag

// Ana fonksiyon: String'i ayırıcıya göre böler ve tırnak içerisini ayrı değerlendirir

static int	get_word_start(char *str, char delimiter, int *index, int *quote_flag);
static int	count_words(char *str, char delimiter);

static void	init_indexes(int indexes[], int size);

char	**parser_split(char *str, char delimiter)
{
	int		indexes[4];
	char	**result;
	char	*substr;

	init_indexes(indexes, 4);
	result = calloc(count_words(str, delimiter) + 1, sizeof(char *));
	if (!result)
		return (0);
	while (str[indexes[0]])
	{
		indexes[1] = get_word_start(str, delimiter, &indexes[0], &indexes[3]);
		if (indexes[0] > indexes[1])
		{
			substr = ft_substr(str, indexes[1], indexes[0] - indexes[1]);
			if (substr)
			{
				replace_arg(substr);
				result[indexes[2]++] = substr;
			}
		}
	}
	result[indexes[2]] = 0;
	return (result);
}

static void	init_indexes(int indexes[], int size)
{
	int	i;

	i = 0;
	while (i < size)
		indexes[i++] = 0;
}

// indexes[0]: word_count, indexes[1]: in_word, indexes[2]: quote_flag

static int	is_quote(char c);

static int	count_words(char *str, char delimiter)
{
	int	indexes[3];

	init_indexes(indexes, 3);
	while (*str)
	{
		if (is_quote(*str))
		{
			if (indexes[2] == 0)
				indexes[2] = *str;
			else if (indexes[2] == *str)
				indexes[2] = 0;
		}
		if (*str != delimiter || indexes[2])
		{
			if (!indexes[1] && indexes[0]++)
				indexes[1] = 1;
		}
		else
			indexes[1] = 0;
		str++;
	}
	return (indexes[0]);
}

// Fonksiyon: Tırnak içerisini dikkate alarak, string'den bir kelime alır

static void	update_quote(char current_char, int *quote_flag);

static int	get_word_start(char *str, char delimiter, int *index, int *quote_flag)
{
	int	start;

	while (str[*index] && (str[*index] == delimiter && *quote_flag == 0))
		(*index)++;
	start = *index;
	while (str[*index] && (str[*index] != delimiter || *quote_flag))
	{
		update_quote(str[*index], quote_flag);
		(*index)++;
	}
	return (start);
}

// Fonksiyon: Bulunan konum tırnak içindeyse, true döner

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

// Fonksiyon: Tırnak durumunu günceller

static void	update_quote(char current_char, int *quote_flag)
{
	if (is_quote(current_char))
	{
		if (*quote_flag == 0)
			*quote_flag = current_char;
		else if (*quote_flag == current_char)
			*quote_flag = 0;
	}
}
