/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:24:31 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/24 21:24:44 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static void	toggle_quote(char c, char *state)
{
	if (*state == 0 && (c == '\'' || c == '"'))
		*state = c;
	else if (*state == c)
		*state = 0;
}

static size_t	count_result_len(const char *str)
{
	size_t	len;
	size_t	i;
	char	state;

	len = 0;
	i = 0;
	state = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && state == 0)
			state = str[i];
		else if (str[i] == state)
			state = 0;
		else
			len++;
		i++;
	}
	return (len);
}

static void	copy_without_quotes(char *dst, const char *src)
{
	size_t	i;
	size_t	j;
	char	state;

	i = 0;
	j = 0;
	state = 0;
	while (src[i])
	{
		toggle_quote(src[i], &state);
		if (!((src[i] == '\'' || src[i] == '"')
			&& (state == src[i] || state == 0)))
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
}

char	*remove_quotes(const char *str)
{
	char	*result;
	size_t	len;

	if (!str)
		return (NULL);
	len = count_result_len(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	copy_without_quotes(result, str);
	return (result);
}
