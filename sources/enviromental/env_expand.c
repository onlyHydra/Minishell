/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:34:00 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/02 14:50:20 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:35:22 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/02 10:35:22 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "libft.h"

/**
 * Check if a character is a special variable character
 * Special variables: $? (exit status), $$ (process ID)
 */
static int	is_special_var_char(char c)
{
	return (c == '?' || c == '$');
}

/**
 * Extract the name of an environment variable from a string
 * @param str: String containing the variable (starts with $)
 * @param len: Pointer to store the length of the variable name
 * @return: Allocated string with the variable name (without $)
 */
static char	*extract_env_var_name(const char *str, int *len)
{
	int		i;
	char	*var_name;

	if (!str || str[0] != '$' || !str[1])
		return (NULL);
	
	// Handle special variables like $? and $$
	if (is_special_var_char(str[1]))
	{
		var_name = ft_substr(str, 1, 1);
		*len = 2; // $ + special char
		return (var_name);
	}
	
	// Handle regular variables
	i = 1;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	
	var_name = ft_substr(str, 1, i - 1);
	*len = i;
	return (var_name);
}

/**
 * Build a new string with the expanded variable
 * @param prefix: Part of the string before the variable
 * @param value: Value of the variable
 * @param suffix: Part of the string after the variable
 * @return: New allocated string with the expanded variable
 */
static char	*build_expanded_string(char *prefix, char *value, char *suffix)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(prefix, value);
	if (!temp)
		return (NULL);
	
	result = ft_strjoin(temp, suffix);
	free(temp);
	return (result);
}

/**
 * Expand environment and special variables in a string
 * @param str: Input string potentially containing variables
 * @param envp: Environment variables array
 * @param exit_status: Exit status for $? expansion
 * @return: New string with expanded variables, or NULL on error
 */
char	*expand_variables(char *str, char **envp, int exit_status)
{
	int		i;
	char	*var_name;
	char	*var_value;
	char	*result;
	int		var_len;

	if (!str)
		return (NULL);
	
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1])
		{
			var_name = extract_env_var_name(result + i, &var_len);
			if (var_name)
			{
				// Check for special variables
				if (is_special_var_char(var_name[0]))
					var_value = handle_special_var(var_name[0], exit_status);
				else
					var_value = extract_env_value(var_name, envp);
				
				if (var_value)
				{
					char *prefix = ft_substr(result, 0, i);
					char *suffix = ft_strdup(result + i + var_len);
					char *new_result = build_expanded_string(prefix, var_value, suffix);
					
					free(prefix);
					free(suffix);
					free(var_value);
					free(result);
					result = new_result;
					i = 0; // Restart to catch nested variables
				}
				free(var_name);
			}
			else
				i++;
		}
		else
			i++;
	}
	return (result);
}
