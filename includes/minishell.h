/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:08:52 by ytop              #+#    #+#             */
/*   Updated: 2024/09/26 18:20:03 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include "libft.h"

# define TRUE		1
# define FALSE		0

# define FAILURE	1
# define SUCCESS	0

# define STD_OUTPUT 1
# define STD_INPUT  0

# define SYNTAX_ERR	"syntax error near unexpected token"
# define PROMPT		"minishell$ "

# define SEMICOLON	';'
# define REDIRECT	'>'
# define INPUT		'<'
# define PIPE		'|'

# define BLACK		"\033[1;90m"
# define RED		"\033[1;91m"

# define GREEN		"\033[1;92m"

# define RESET		"\033[0m"

extern int	g_signal;

typedef struct s_fd
{
	int		change;
	int		std_in;
	int		std_out;
}			t_fd;

typedef struct s_mlist
{
	void			*data;
	struct s_mlist	*next;
	struct s_mlist	*prev;
}			t_mlist;

typedef struct s_minishell
{
	t_fd	fd;
	t_mlist	*env;
	t_mlist	*token;
	char	*line;
	char	*path;
	int		*pid;
	int		pipe_count;
	int		exit_code;
	int		status;
	int		sign;
}			t_minishell;

t_mlist	*env_to_list(char *env[]);

#endif