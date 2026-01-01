/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:55:47 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/23 15:14:31 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void	token_free(t_token *token)
{
	if (! token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	token_list_free(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		token_free(current);
		current = next;
	}
}

t_token	*token_last(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

int	token_list_size(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

bool	advance_to_word_end(t_lexer *lex)
{
	char	c;
	ssize_t	new_pos;

	while (lex->pos < lex->len)
	{
		c = current_char(lex);
		if (is_whitespace(c) || is_operator_char(c))
			break ;
		if (is_quote(c))
		{
			new_pos = skip_quoted_section(lex->input, lex->pos);
			if (new_pos == -1)
				return (false);
			lex->pos = new_pos;
		}
		else
			advance(lex);
	}
	return (true);
}
