/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/23 15:19:14 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

char	*append_char(char *str, char c)
{
	char	*new_str;
	size_t	len;

	if (!str)
	{
		new_str = malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}

char	*append_str(char *s1, const char *s2)
{
	char	*result;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

void	update_quote_state(t_expander *exp, char c)
{
	if (exp->state == STATE_NORMAL)
	{
		if (c == '\'')
			exp->state = STATE_SINGLE;
		else if (c == '"')
			exp->state = STATE_DOUBLE;
	}
	else if (exp->state == STATE_SINGLE && c == '\'')
		exp->state = STATE_NORMAL;
	else if (exp->state == STATE_DOUBLE && c == '"')
		exp->state = STATE_NORMAL;
}
