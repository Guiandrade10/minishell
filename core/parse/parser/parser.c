/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 20:47:02 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 14:02:32 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void	parser_init(t_parser *p, t_token *tokens, int exit, char **env)
{
	p->tokens = tokens;
	p->current = tokens;
	p->exit_status = exit;
	p->env = env;
	p->error = false;
}

bool	parser_advance(t_parser *p)
{
	if (!p || !p->current)
		return (false);
	if (p->current->type == TOKEN_EOF)
		return (false);
	p->current = p->current->next;
	return (true);
}

bool	parser_expect(t_parser *p, t_token_type type)
{
	if (!p || !p->current)
		return (false);
	return (p->current->type == type);
}

t_ast_node	*parse(const char *input, int exit_status, char **env)
{
	t_token		*tokens;
	t_parser	parser;
	t_ast_node	*ast;

	tokens = lexer(input);
	if (!tokens)
		return (NULL);
	if (!syntax_check(tokens))
	{
		token_list_free(tokens);
		return (NULL);
	}
	if (!expand_tokens(tokens, exit_status, env))
	{
		token_list_free(tokens);
		return (NULL);
	}
	parser_init(&parser, tokens, exit_status, env);
	ast = parse_pipeline(&parser);
	token_list_free(tokens);
	if (ast && !process_heredocs(ast, exit_status, env))
	{
		ast_free(ast);
		return (NULL);
	}
	return (ast);
}
