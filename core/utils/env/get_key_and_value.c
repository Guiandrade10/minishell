/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key_and_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 21:32:13 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/17 15:24:11 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

char	*get_key(const char *envp)
{
	char		*key;
	char		*temp;

	if (!envp)
		return (NULL);
	temp = ft_strchr(envp, '=');
	if (!temp)
		return (NULL);
	key = ft_substr(envp, 0, temp - envp);
	if (!key)
		return (NULL);
	return (key);
}

char	*get_value(const char *envp)
{
	char	*equals;
	char	*string;

	equals = ft_strchr(envp, '=');
	if (!equals)
		return (NULL);
	string = ft_strdup(equals + 1);
	if (!string)
		return (NULL);
	return (string);
}
