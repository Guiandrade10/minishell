/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 14:03:49 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <lexer.h>

typedef struct s_quote_state
{
	char	in_quote;
	size_t	i;
	char	*result;
}	t_quote_state;

typedef enum e_expand_state
{
	STATE_NORMAL,
	STATE_SINGLE,
	STATE_DOUBLE
}	t_expand_state;

typedef struct s_expander
{
	const char		*input;
	char			*result;
	size_t			pos;
	t_expand_state	state;
	int				exit_status;
	char			**env;
}	t_expander;

bool	is_var_char(char c, bool first);
char	*append_char(char *str, char c);
char	*expand_variable(t_expander *exp);
char	*process_expansion(t_expander *exp);
bool	process_char(t_expander *exp, char c);
void	handle_quote_toggle(t_expander *exp, char c);
char	*remove_outer_quotes(const char *str);
char	*append_str(char *s1, const char *s2);
void	update_quote_state(t_expander *exp, char c);
char	*get_env_value(const char *name, char **env);
char	*extract_var_name(const char *str, size_t *len);
char	*expand_token(const char *token, int exit_status, char **env);
bool	expand_tokens(t_token *tokens, int exit_status, char **env);

#endif
