/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:30:37 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/23 15:08:34 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

static void	init_quote_state(t_quote_state *qs)
{
	qs->in_quote = '\0';
	qs->i = 0;
	qs->result = NULL;
}

static bool	handle_quote_char(t_quote_state *qs, char c)
{
	if (qs->in_quote == '\0')
	{
		if (c == '\'' || c == '"')
		{
			qs->in_quote = c;
			return (true);
		}
	}
	else if (c == qs->in_quote)
	{
		qs->in_quote = '\0';
		return (true);
	}
	return (false);
}

static char	*process_quotes(const char *str)
{
	t_quote_state	qs;
	char			*tmp;

	init_quote_state(&qs);
	while (str[qs.i])
	{
		if (!handle_quote_char(&qs, str[qs.i]))
		{
			tmp = append_char(qs.result, str[qs.i]);
			if (!tmp)
				return (free(qs.result), NULL);
			qs.result = tmp;
		}
		qs.i++;
	}
	return (qs.result);
}

char	*remove_outer_quotes(const char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	result = process_quotes(str);
	if (!result)
		return (ft_strdup(""));
	return (result);
}
