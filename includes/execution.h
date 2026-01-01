/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:32:47 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/19 16:20:36 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <utils.h>
# include <lexer.h>

typedef enum e_identify
{
	IN,
	OUT,
	APPEND,
	HEREDOC,
}	t_identify;

typedef struct	s_command
{
	bool				is_builtin;
	int					status;
	t_identify			identity;
	char				*cmd;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void		execute(void);
char		*get_pwd(void);
void		order_env(char **env);
void		free_list(t_env *env);
void		print_pwd(t_env *env);
t_env		*init_env(char **envp);
void		print_all_env(t_env *env);
char		*get_key(const char *envp);
void		update_new_pwd(t_env *env);
void		create_new_pwd(t_env *env);
t_env		*free_head_node(t_env *env);
char		*get_value(const char *envp);
void		free_envp(char **envp, int i);
t_command	*command_line(t_token *token);
void		free_list_and_exit(t_env *env);
bool		repeated(t_env *env, char *key);
size_t		strlen_double_array(char **env);
char		**list_to_array(const t_env *env);
void		new_pwd(t_env **env, char *old_pwd);
void		old_pwd(t_env **env, char *old_pwd);
void		push_back(t_env **head, t_env *new);
char		*return_value(t_env *env, char *key);
void		move_back(t_env **env, char *old_pwd);
int			full_length_of_list(const t_env *env);
void		update_old_pwd(t_env *env, char *og_pwd);
void		create_old_pwd(t_env *env, char *og_pwd);
void		destroy_and_copy(char **dest, const char *src);
void		move_to_previous_dir(t_env **env, char *old_pwd);
char		*join_key_value(const char *key, const char *value);
void		set_value(t_env **env, const char *key, const char *value);
void		move_to_relative_path(t_env **env, char *old_pwd, char *new_dir);

#endif