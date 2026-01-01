/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:53:48 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/23 14:50:12 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void	lexer_init(t_lexer *lex, const char *input)
{
	lex->input = input;
	lex->pos = 0;
	lex->len = ft_strlen(input);
	lex->tokens = NULL;
}

char	current_char(t_lexer *lex)
{
	if (lex->pos >= lex->len)
		return ('\0');
	return (lex->input[lex->pos]);
}

char	peek_char(t_lexer *lex)
{
	if (lex->pos + 1 >= lex->len)
		return ('\0');
	return (lex->input[lex->pos + 1]);
}

bool	lexer_tokenize(t_lexer *lex)
{
	char	c;

	while (lex->pos < lex->len)
	{
		skip_whitespace(lex);
		c = current_char(lex);
		if (c == '\0')
			break ;
		if (is_operator_char(c))
		{
			if (! tokenize_operator(lex))
				return (false);
		}
		else
		{
			if (!tokenize_word(lex))
				return (false);
		}
	}
	return (true);
}

t_token	*lexer(const char *input)
{
	t_lexer	lex;
	t_token	*eof_token;

	if (!input)
		return (NULL);
	lexer_init(&lex, input);
	if (! lexer_tokenize(&lex))
	{
		token_list_free(lex.tokens);
		return (NULL);
	}
	eof_token = token_create(TOKEN_EOF, NULL, false);
	if (!eof_token || !token_add(&lex, eof_token))
	{
		token_list_free(lex.tokens);
		return (NULL);
	}
	return (lex.tokens);
}
