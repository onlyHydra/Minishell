/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviromental_expansion_helper.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 02:26:34 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 02:27:42 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * Handle special variables like $? and $$
 */
static int	handle_special_var_len(char special, int exit_status)
{
	char	*var_value;
	int		len;

	var_value = handle_special_var(special, exit_status);
	len = 0;
	if (var_value)
	{
		len = ft_strlen(var_value);
		free(var_value);
	}
	return (len);
}

/**
 * Handle the expansion of regular environment variables
 */
static int	handle_env_var_len(char *input, int *i, t_env_var *env_vars)
{
	char	*var_name;
	char	*var_value;
	int		len;

	var_name = extract_var_name(&input[*i]);
	len = 0;
	if (var_name)
	{
		var_value = get_env_value(env_vars, var_name);
		if (var_value)
			len = ft_strlen(var_value);
		free(var_name);
		*i += ft_strlen(var_name);
	}
	return (len);
}

/**
 * Get the length of expanded variable in the input string
 */
int	get_expanded_len(char *input, t_env_var *env_vars, int exit_status)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1])
		{
			i++;
			if (input[i] == '?' || input[i] == '$')
				len += handle_special_var_len(input[i], exit_status);
			else if (ft_isalpha(input[i]))
				len += handle_env_var_len(input, &i, env_vars);
			else
				len++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
