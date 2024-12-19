/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:21:07 by ytop              #+#    #+#             */
/*   Updated: 2024/10/16 16:52:11 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
	struct s_parser	*next;
	char			**args;
}					t_parser;

t_parser	*ft_parser_new(char **args);

void		ft_parser_clear(t_parser **lst, void (*del)(void *));

void		ft_parser_delone(t_parser *lst, void (*del)(void *));

void		ft_parser_addback(t_parser **lst, t_parser *new);
#endif
