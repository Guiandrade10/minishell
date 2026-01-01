/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:57:02 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/17 16:49:57 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_pwd(void)
{
	char	buffer[9999];

	return (ft_strdup(getcwd(buffer, 9999)));
}

void	update_new_pwd(t_env *env)
{
	char	*pwd;

	pwd = get_pwd();
	if (!pwd)
		return ;
	destroy_and_copy(&env->value, pwd);
	if (!env->value)
		return (free(pwd));
	free(pwd);
}

void	update_old_pwd(t_env *env, char *og_pwd)
{
	t_env	*curr;

	curr = env;
	destroy_and_copy(&curr->value, og_pwd);
	if (!og_pwd)
		return ;
	if (!curr->value)
	{
		free(og_pwd);
		return ;
	}
	free(og_pwd);
}

void	create_new_pwd(t_env *env)
{
	char	*pwd;
	t_env	*new;
	t_env	*head;

	pwd = get_pwd();
	if (!pwd)
		return ;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
	{
		free_list(env);
		return ;
	}
	head = env;
	new->key = "PWD";
	new->value = pwd;
	push_back(&head, new);
	free(pwd);
}

void	create_old_pwd(t_env *env, char *og_pwd)
{
	t_env	*new;
	t_env	*head;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
	{
		free_list(env);
		return ;
	}
	head = env;
	new->key = "OLDPWD";
	new->value = og_pwd;
	push_back(&head, new);
}
