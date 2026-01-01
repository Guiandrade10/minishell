/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:14:14 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/23 14:51:51 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_cmd	*cmd_create(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->redirs = NULL;
	return (cmd);
}

bool	cmd_add_arg(t_cmd *cmd, char *arg)
{
	char	**new_argv;
	int		i;

	if (!cmd || !arg)
		return (false);
	new_argv = malloc(sizeof(char *) * (cmd->argc + 2));
	if (!new_argv)
		return (false);
	i = 0;
	while (i < cmd->argc)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(arg);
	if (!new_argv[i])
	{
		free(new_argv);
		return (false);
	}
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	cmd->argc++;
	return (true);
}

void	cmd_free(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (i < cmd->argc)
		{
			free(cmd->argv[i]);
			i++;
		}
		free(cmd->argv);
	}
	if (cmd->redirs)
		redir_free(cmd->redirs);
	free(cmd);
}

t_ast_node	*parse_command(t_parser *p)
{
	t_cmd	*cmd;

	cmd = cmd_create();
	if (!cmd)
		return (NULL);
	if (!parse_command_loop(p, cmd))
	{
		cmd_free(cmd);
		return (NULL);
	}
	return (ast_new_cmd(cmd));
}

bool	parse_command_loop(t_parser *p, t_cmd *cmd)
{
	char	*unquoted;

	while (p->current && p->current->type != TOKEN_PIPE
		&& p->current->type != TOKEN_EOF)
	{
		if (p->current->type == TOKEN_WORD)
		{
			unquoted = remove_outer_quotes(p->current->value);
			if (!unquoted || !cmd_add_arg(cmd, unquoted))
			{
				free(unquoted);
				return (false);
			}
			free(unquoted);
			parser_advance(p);
		}
		else if (!parse_redirections(p, cmd))
			return (false);
	}
	return (true);
}
