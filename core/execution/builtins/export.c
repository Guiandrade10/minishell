/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:02:41 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/17 16:49:57 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	export_with_arguments(t_env **env, const char *args)
{
	char	*key;
	char	*value;

	key = get_key(args);
	if (!key)
		return ;
	value = get_value(args);
	if (!value)
		return (free(key));
	set_value(env, key, value);
	free(key);
	free(value);
}

void	export_with_no_arguments(const t_env *env)
{
	int		i;
	char	**array_env;

	array_env = list_to_array(env);
	if (!array_env)
		return ;
	order_env(array_env);
	i = 0;
	while (array_env[i])
	{
		ft_putstr(array_env[i]);
		i++;
	}
}

void	export(t_env *env, const char *args)
{
	if (!env)
		return ;
	if (args)
		return (export_with_arguments(&env, args));
	export_with_no_arguments(env);
}
