/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 21:57:14 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 14:02:00 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

bool	parse_heredoc_redir(t_cmd *cmd, t_redir_type redir_type, char *value)
{
	char	*delim;
	bool	quoted;
	bool	ok;

	delim = NULL;
	quoted = strip_quotes_if_any(value, &delim);
	ok = parse_add_redir(cmd, redir_type, delim, quoted);
	free(delim);
	return (ok);
}

static bool	parse_redir_value(t_parser *p, t_cmd *cmd, t_redir_type redir_type)
{
	char	*unquoted;

	if (redir_type == REDIR_HEREDOC)
		return (parse_heredoc_redir(cmd, redir_type, p->current->value));
	unquoted = remove_outer_quotes(p->current->value);
	if (!unquoted || !parse_add_redir(cmd, redir_type, unquoted, false))
	{
		free(unquoted);
		return (false);
	}
	free(unquoted);
	return (true);
}

bool	parse_redir_one(t_parser *p, t_cmd *cmd)
{
	t_redir_type	redir_type;

	redir_type = token_to_redir_type(p->current->type);
	if (!parser_advance(p))
		return (false);
	if (!p->current || p->current->type != TOKEN_WORD)
	{
		parser_error(p, "syntax error: expected filename");
		return (false);
	}
	if (!parse_redir_value(p, cmd, redir_type))
		return (false);
	parser_advance(p);
	return (true);
}

bool	strip_quotes_if_any(const char *str, char **out)
{
	size_t	i;
	bool	has_quotes;

	i = 0;
	has_quotes = false;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			has_quotes = true;
		i++;
	}
	*out = remove_outer_quotes(str);
	return (has_quotes);
}

bool	parse_add_redir(t_cmd *cmd, t_redir_type type, char *value, bool quoted)
{
	t_redir	*redir;

	redir = redir_create(type, value, quoted);
	if (!redir || !redir_add(cmd, redir))
	{
		if (redir)
			redir_free(redir);
		return (false);
	}
	return (true);
}
