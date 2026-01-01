/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:15 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/01 13:56:32 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	push_back(t_env **head, t_env *new)
{
	t_env	*temp;

	new->next = NULL;
	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new;
	char	*key;
	int		i;

	i = 0;
	head = NULL;
	while (envp && envp[i])
	{
		key = get_key(envp[i]);
		if (!key)
			return (free_list(head), NULL);
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			return (free_list(head), NULL);
		new->key = key;
		new->value = get_value(envp[i]);
		push_back(&head, new);
		i++;
	}
	return (head);
}
