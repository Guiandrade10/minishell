/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:23:33 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/23 15:03:34 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	program_loop(t_env *env)
{
	const char	*input;

	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			free_list_and_exit(env);
		command_line(lexer(input));
		execute();
	}
}
