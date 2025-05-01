/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmental_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:19:10 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 12:48:29 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * Handle the special cases `$?` and `$$`
 */
static int	handle_special_expansion(char **expanded, int *j, char special,
		int exit_status)
{
	char	*var_value;

	var_value = handle_special_var(special, exit_status);
	if (var_value)
	{
		ft_strlcpy(&(*expanded)[*j], var_value, ft_strlen(var_value) + 1);
		*j += ft_strlen(var_value);
		free(var_value);
		return (1);
	}
	return (0);
}

/**
 * Handle environment variable expansion
 */
static int	copy_var_value_name(char **expanded, int *j, char *input,
		int *i, t_env_var *env_vars)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_var_name(&input[*i]);
	if (var_name)
	{
		var_value = get_env_value(env_vars, var_name);
		if (var_value)
		{
			ft_strlcpy(&(*expanded)[*j], var_value, ft_strlen(var_value) + 1);
			*j += ft_strlen(var_value);
		}
		*i += ft_strlen(var_name);
		free(var_name);
		return (1);
	}
	return (0);
}

/**

	* Handle a single character in the input string for environment variable expansion
 */
static int	handle_char_expansion(char **expanded, int *j, char *input, int *i,
		int *in_single_quote, t_env_var *env_vars, int exit_status)
{
	if (input[*i] == '\'')
		*in_single_quote = !*in_single_quote;
	if (input[*i] == '$' && input[*i + 1] && !*in_single_quote)
	{
		(*i)++;
		if (input[*i] == '?' || input[*i] == '$')
		{
			if (!handle_special_expansion(expanded, j, input[*i], exit_status))
				return (0);
			(*i)++;
		}
		else if (is_valid_var_char(input[*i]))
		{
			if (!copy_var_value_name(expanded, j, input, i, env_vars))
				return (0);
		}
		else
			(*expanded)[*j] = '$';
	}
	else
		(*expanded)[*j] = input[*i];
	(*j)++;
	return (1);
}

/**
 * Expand environment variables in the command input
 */
char	*expand_env_vars(char *input, t_env_var *env_vars, int exit_status)
{
	int		i;
	int		j;
	int		in_single_quote;
	char	*expanded;

	i = 0;
	j = 0;
	in_single_quote = 0;
	if (!input)
		return (NULL);
	expanded = (char *)malloc(get_expanded_len(input, env_vars, exit_status)
			+ 1);
	if (!expanded)
		return (NULL);
	while (input[i])
	{
		if (!handle_char_expansion(&expanded, &j, input, &i, &in_single_quote,
				env_vars, exit_status))
			return (NULL);
		i++;
	}
	expanded[j] = '\0';
	return (expanded);
}
