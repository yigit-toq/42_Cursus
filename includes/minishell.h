/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:08:52 by ytop              #+#    #+#             */
/*   Updated: 2024/09/27 01:43:23 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define TRUE		1
# define FALSE		0

# define FAILURE	1
# define SUCCESS	0

# define STD_OUTPUT 1
# define STD_INPUT  0

# define SEMICOLON	';'
# define REDIRECT	'>'
# define INPUT		'<'
# define PIPE		'|'

# define BLACK		"\033[1;90m"
# define RED		"\033[1;91m"

# define GREEN		"\033[1;92m"

# define RESET		"\033[0m"

# define SYNTAX_ERR	"syntax error near unexpected token"
# define PROMPT		"minishell> "

extern int	g_signal;

typedef enum e_token
{
	SEMICOLON_T = SEMICOLON,
	REDIRECT_T = REDIRECT,
	INPUT_T = INPUT,
	PIPE_T = PIPE,
}			t_token;

typedef struct s_fd
{
	int		change;
	int		std_in;
	int		std_out;
}			t_fd;

typedef struct s_parser
{
	char			**args;
	struct s_parser	*next;
}			t_parser;

typedef struct s_minishell
{
	t_fd	fd;
	t_list	*env;
	t_list	*token;
	char	*line;
	char	*path;
	int		*pid;
	int		pipe_count;
	int		exit_code;
	int		status;
}			t_minishell;

t_minishell	*get_minishell(void);

void		handle_signals(void);

void		env_to_list(char *env[]);

#endif