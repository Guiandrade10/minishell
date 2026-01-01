/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 01:59:17 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/17 16:49:57 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**list_to_array(const t_env *env)
{
	char	**envp;
	size_t	i;

	envp = ft_calloc(full_length_of_list(env) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		envp[i] = join_key_value(env->key, env->value);
		if (!envp[i])
			return (free_envp(envp, i), NULL);
		i++;
		env = env->next;
	}
	return (envp);
}
