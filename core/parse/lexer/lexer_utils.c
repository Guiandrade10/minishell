/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/23 15:11:05 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

const char	*token_type_to_printable(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("|");
	if (type == TOKEN_REDIR_IN)
		return ("<");
	if (type == TOKEN_REDIR_OUT)
		return (">");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	if (type == TOKEN_APPEND)
		return (">>");
	if (type == TOKEN_EOF)
		return ("newline");
	return (NULL);
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_whitespace(t_lexer *lex)
{
	while (lex->pos < lex->len && is_whitespace(lex->input[lex->pos]))
		lex->pos++;
}

void	advance(t_lexer *lex)
{
	if (lex->pos < lex->len)
		lex->pos++;
}
