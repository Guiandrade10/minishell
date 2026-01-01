/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:55:51 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/23 15:16:41 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static bool	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND);
}

bool	check_pipe_syntax(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (true);
	if (tokens->type == TOKEN_PIPE)
	{
		syntax_error("|");
		return (false);
	}
	current = tokens;
	while (current && current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_EOF
				|| current->next->type == TOKEN_PIPE)
			{
				syntax_error("|");
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}

bool	check_redir_syntax(t_token *tokens)
{
	t_token		*current;
	const char	*printable;

	current = tokens;
	while (current && current->type != TOKEN_EOF)
	{
		if (is_redir_token(current->type))
		{
			if (!current->next || current->next->type == TOKEN_EOF)
			{
				syntax_error_newline();
				return (false);
			}
			if (current->next->type != TOKEN_WORD)
			{
				printable = current->next->value;
				if (!printable)
					printable = token_type_to_printable(current->next->type);
				syntax_error(printable);
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}

bool	syntax_check(t_token *tokens)
{
	if (!tokens)
		return (false);
	if (!check_pipe_syntax(tokens))
		return (false);
	if (!check_redir_syntax(tokens))
		return (false);
	return (true);
}
