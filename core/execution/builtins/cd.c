/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 21:15:34 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/17 16:49:57 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	change_dir(t_env **env, char *new_dir)
{
	char	*old_pwd;

	old_pwd = get_pwd();
	if (!old_pwd)
		return (free(old_pwd));
	if ((ft_strcmp(new_dir, "..") == 0))
	{
		move_back(env, old_pwd);
		return (free(old_pwd));
	}
	if (new_dir[0] == '\0')
	{
		move_to_relative_path(env, old_pwd, new_dir);
		return (free(old_pwd));
	}
	if (new_dir[0] == '-')
	{
		move_to_previous_dir(env, old_pwd);
		return (free(old_pwd));
	}
	if (chdir(new_dir) == -1)
		return (free(old_pwd));
	new_pwd(env, old_pwd);
}
