/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:30:00 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/23 14:53:35 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

char	*extract_var_name(const char *str, size_t *len)
{
	size_t	i;

	if (!str || !len)
		return (NULL);
	if (str[0] == '?' || str[0] == '$' || str[0] == '@' || str[0] == '*'
		|| str[0] == '-' || str[0] == '#' || str[0] == '!')
	{
		*len = 1;
		return (ft_substr(str, 0, 1));
	}
	if (str[0] >= '0' && str[0] <= '9')
	{
		*len = 1;
		return (ft_substr(str, 0, 1));
	}
	i = 0;
	if (!is_var_char(str[i], true))
	{
		*len = 0;
		return (NULL);
	}
	while (str[i] && is_var_char(str[i], i == 0))
		i++;
	*len = i;
	return (ft_substr(str, 0, i));
}

char	*get_env_value(const char *name, char **env)
{
	size_t	i;
	size_t	name_len;
	char	*value;

	if (!name || !env)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			value = ft_strdup(env[i] + name_len + 1);
			return (value);
		}
		i++;
	}
	return (ft_strdup(""));
}

static char	*expand_special_var(t_expander *exp, char *var_name, size_t var_len)
{
	if (var_name[0] == '?')
	{
		exp->pos += 1;
		return (ft_itoa(exp->exit_status));
	}
	if (var_name[0] == '$' && var_len == 1)
	{
		exp->pos += 1;
		return (ft_itoa(getpid()));
	}
	if (var_name[0] >= '0' && var_name[0] <= '9' && var_len == 1)
	{
		exp->pos += 1;
		return (ft_strdup(""));
	}
	if (var_name[0] == '@' || var_name[0] == '*' || var_name[0] == '-'
		|| var_name[0] == '#' || var_name[0] == '!')
	{
		exp->pos += 1;
		return (ft_strdup(""));
	}
	exp->pos += var_len;
	return (get_env_value(var_name, exp->env));
}

char	*expand_variable(t_expander *exp)
{
	size_t	var_len;
	char	*var_name;
	char	*value;

	var_name = extract_var_name(exp->input + exp->pos, &var_len);
	if (!var_name || var_len == 0)
	{
		if (var_name)
			free(var_name);
		return (ft_strdup("$"));
	}
	value = expand_special_var(exp, var_name, var_len);
	free(var_name);
	return (value);
}
