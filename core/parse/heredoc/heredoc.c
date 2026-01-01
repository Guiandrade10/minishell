/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 13:59:56 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 14:00:06 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

char	*read_heredoc(const char *delim, bool expand, int exit_status, char **env)
{
	char	*line;
	char	*content;
	char	*expanded;
	char	*temp;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
			expanded = expand_heredoc_line(line, exit_status, env);
		else
			expanded = ft_strdup(line);
		free(line);
		if (!expanded)
		{
			free(content);
			return (NULL);
		}
		temp = ft_strjoin(content, expanded);
		free(content);
		free(expanded);
		if (!temp)
			return (NULL);
		content = temp;
		temp = ft_strjoin(content, "\n");
		free(content);
		if (!temp)
			return (NULL);
		content = temp;
	}
	return (content);
}

static bool	process_cmd_heredocs(t_cmd *cmd, int exit_status, char **env)
{
	t_redir	*redir;
	char	*content;

	if (!cmd)
		return (true);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			content = read_heredoc(redir->file, !redir->quoted,
					exit_status, env);
			if (!content)
				return (false);
			redir->heredoc_content = content;
		}
		redir = redir->next;
	}
	return (true);
}

bool	process_heredocs(t_ast_node *ast, int exit_status, char **env)
{
	if (!ast)
		return (true);
	if (ast->type == NODE_CMD)
		return (process_cmd_heredocs(ast->cmd, exit_status, env));
	if (ast->type == NODE_PIPE)
	{
		if (!process_heredocs(ast->left, exit_status, env))
			return (false);
		if (!process_heredocs(ast->right, exit_status, env))
			return (false);
	}
	return (true);
}
