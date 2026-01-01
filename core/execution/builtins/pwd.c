/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:09:08 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/17 16:49:57 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_pwd(t_env *env)
{
	t_env	*head;
	char	*pwd;

	if (!env)
		return ;
	pwd = get_pwd();
	if (!pwd)
		return ;
	head = env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, "PWD") == 0)
		{
			destroy_and_copy(&head->value, pwd);
			ft_putstr(head->value);
			return ;
		}
		if (head->next == NULL)
		{
			create_new_pwd(head);
			ft_putstr(head->value);
			return ;
		}
		head = head->next;
	}
}

void	new_pwd(t_env **env, char *og_pwd)
{
	t_env	*head;

	if (!env)
		return ;
	old_pwd(env, og_pwd);
	head = *env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, "PWD") == 0)
		{
			update_new_pwd(head);
			return ;
		}
		if (head->next == NULL)
		{
			create_new_pwd(head);
			return ;
		}
		head = head->next;
	}
}

void	old_pwd(t_env **env, char *og_pwd)
{
	t_env	*head;

	if (!env)
		return ;
	head = *env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, "OLDPWD") == 0)
		{
			update_old_pwd(head, og_pwd);
			return ;
		}
		if (head->next == NULL)
		{
			create_old_pwd(head, og_pwd);
			return ;
		}
		head = head->next;
	}
}
