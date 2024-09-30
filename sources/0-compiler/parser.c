/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:07:10 by ytop              #+#    #+#             */
/*   Updated: 2024/09/28 01:07:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	*allocate_parser(int count);
static int		process_tokens(t_minishell *minishell, t_parser **parser);

int	parser(t_minishell *minishell)
{
	t_parser	*parser;
	int			t_count;

	t_count = ft_lstsize(minishell->token);
	parser = allocate_parser(t_count);
	if (!parser)
		return (FAILURE);
	if (process_tokens(minishell, &parser))
		return (FAILURE);
	minishell->parser = parser;
	return (SUCCESS);
}

static t_parser	*allocate_parser(int count)
{
	t_parser	*head;
	t_parser	*new;
	int			i;

	i = 0;
	head = NULL;
	while (i < count)
	{
		new = ft_parser_new(NULL, NULL);
		if (!new)
			return (perror("ft_calloc"), NULL);
		ft_parser_addback(&head, new);
		i++;
	}
	return (head);
}

static int	handle_token(t_parser *node, t_list *token);

static int	process_tokens(t_minishell *minishell, t_parser **parser)
{
	t_parser	*current_parser;
	t_list		*token;

	current_parser = *parser;
	token = minishell->token;
	while (current_parser && token)
	{
		if (handle_token(current_parser, token))
			return (FAILURE);
		current_parser = current_parser->next;
		token = token->next;
	}
	return (SUCCESS);
}

static int	handle_token(t_parser *node, t_list *token)
{
	char	*token_content;

	token_content = ft_strdup(token->content);
	if (!token_content)
		return (perror("ft_strdup"), FAILURE);
	if (replace_arg(token_content))
		return (FAILURE);
	node->args = parser_split(token_content, ' ');
	if (!node->args)
		return (perror("ft_split"), FAILURE);
	node->args_quote = parser_split(token_content, ' ');
	if (!node->args_quote)
		return (perror("ft_split"), FAILURE);
	gfree(token_content);
	return (SUCCESS);
}
