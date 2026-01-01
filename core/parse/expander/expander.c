/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 13:58:22 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

static void	expander_init(t_expander *exp, const char *input,
	int exit_status, char **env)
{
	exp->input = input;
	exp->result = NULL;
	exp->pos = 0;
	exp->state = STATE_NORMAL;
	exp->exit_status = exit_status;
	exp->env = env;
}

char	*process_expansion(t_expander *exp)
{
	char	*var_value;

	exp->pos++;
	var_value = expand_variable(exp);
	if (!var_value)
		return (NULL);
	exp->result = append_str(exp->result, var_value);
	free(var_value);
	return (exp->result);
}

void	handle_quote_toggle(t_expander *exp, char c)
{
	if (exp->state == STATE_NORMAL)
	{
		if (c == '\'')
			exp->state = STATE_SINGLE;
		else if (c == '"')
			exp->state = STATE_DOUBLE;
	}
	else if (exp->state == STATE_SINGLE && c == '\'')
		exp->state = STATE_NORMAL;
	else if (exp->state == STATE_DOUBLE && c == '"')
		exp->state = STATE_NORMAL;
}

char	*expand_token(const char *token, int exit_status, char **env)
{
	t_expander	exp;

	if (!token)
		return (NULL);
	expander_init(&exp, token, exit_status, env);
	while (token[exp.pos])
	{
		if (!process_char(&exp, token[exp.pos]))
			return (NULL);
	}
	return (exp.result);
}

bool	expand_tokens(t_token *tokens, int exit_status, char **env)
{
	t_token	*current;
	t_token	*prev;
	char	*expanded;

	current = tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == TOKEN_WORD && current->value)
		{
			if (prev && prev->type == TOKEN_HEREDOC)
			{
				prev = current;
				current = current->next;
				continue ;
			}
			expanded = expand_token(current->value, exit_status, env);
			if (!expanded)
				return (false);
			free(current->value);
			current->value = expanded;
		}
		prev = current;
		current = current->next;
	}
	return (true);
}
