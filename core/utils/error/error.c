/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 21:04:26 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/19 16:09:51 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_list(t_env *env)
{
	t_env	*head;
	t_env	*next;

	if (env)
	{
		head = env;
		while (head != NULL)
		{
			next = head->next;
			if (head->key)
				free(head->key);
			if (head->value)
				free(head->value);
			free(head);
			head = next;
		}
	}
}

void	free_list_and_exit(t_env *env)
{
	t_env	*head;
	t_env	*next;

	if (env)
	{
		head = env;
		while (head != NULL)
		{
			next = head->next;
			if (head->key)
				free(head->key);
			if (head->value)
				free(head->value);
			free(head);
			head = next;
		}
	}
	printf("exit\n");
	exit(EXIT_FAILURE);
}

void	free_envp(char **envp, int i)
{
	while (i--)
		free(envp[i]);
	free(envp);
}
