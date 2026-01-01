/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_updates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:41:38 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/17 16:49:57 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_value(t_env **env, const char *key, const char *value)
{
	t_env	*curr;

	if (!env)
		return ;
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (destroy_and_copy(&curr->value, value));
		curr = curr->next;
	}
	curr = ft_calloc(1, sizeof(t_env));
	if (!curr)
		return ;
	curr->key = ft_strdup(key);
	if (!curr->key)
		return (free(curr));
	curr->value = (char *)value;
	push_back(env, curr);
}

void	destroy_and_copy(char **dest, const char *src)
{
	char	*new;

	if (!dest)
		return ;
	new = ft_strdup(src);
	if (!new)
		return ;
	free(*dest);
	*dest = new;
}

char	*return_value(t_env *env, char *key)
{
	t_env	*head;

	if (!env || !key)
		return (NULL);
	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

t_env	*unset_node(t_env *env, char *key)
{
	t_env	*prev;
	t_env	*curr;

	if (!env || !key)
		return (env);
	if (ft_strcmp(env->key, key) == 0)
		return (free_head_node(env));
	prev = env;
	curr = env->next;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			prev->next = curr->next;
			if (curr->key)
				free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	return (env);
}

char	*join_key_value(const char *key, const char *value)
{
	size_t		i;
	size_t		size;
	char		*string;

	if (!key)
		return (NULL);
	size = ft_strlen(key);
	i = size;
	if (value)
		size += ft_strlen(value);
	string = ft_calloc(size + 2, sizeof(char));
	if (!string)
		return (NULL);
	ft_strcpy(string, key);
	string[i++] = '=';
	ft_strcpy(&string[i], value);
	return (string);
}
