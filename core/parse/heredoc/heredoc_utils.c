/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 14:00:30 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 14:00:37 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

char	*expand_heredoc_line(const char *line, int exit_status, char **env)
{
	t_expander	exp;
	char		c;

	if (!line)
		return (NULL);
	exp.input = line;
	exp.result = NULL;
	exp.pos = 0;
	exp.state = STATE_NORMAL;
	exp.exit_status = exit_status;
	exp.env = env;
	while (line[exp.pos])
	{
		c = line[exp.pos];
		if (c == '$' && line[exp.pos + 1] != '\0')
		{
			if (!process_expansion(&exp))
				return (NULL);
		}
		else
		{
			exp.result = append_char(exp.result, c);
			if (!exp.result)
				return (NULL);
			exp.pos++;
		}
	}
	return (exp.result);
}
