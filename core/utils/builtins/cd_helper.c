/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:46:25 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/17 16:56:39 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	move_back(t_env **env, char *old_pwd)
{
	t_env	*curr;

	curr = *env;
	if (chdir("..") == -1)
		return ;
	new_pwd(&curr, old_pwd);
}

void	move_to_relative_path(t_env **env, char *old_pwd, char *new_dir)
{
	t_env	*curr;
	char	*relative_path;

	(void)new_dir;
	curr = *env;
	relative_path = return_value(*env, "HOME");
	if (chdir(relative_path) == -1)
		return ;
	new_pwd(&curr, old_pwd);
}

void	move_to_previous_dir(t_env **env, char *old_pwd)
{
	t_env	*curr;

	curr = *env;
	if (chdir(old_pwd) == -1)
		return ;
	new_pwd(&curr, old_pwd);
}
