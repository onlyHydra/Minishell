/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmental_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:19:10 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/30 20:27:42 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "envir.h"

// /**
//  * Check if a character is valid for a variable name
//  * Valid chars: alphanumeric and underscore
//  */
// static int	is_valid_var_char(char c)
// {
// 	return (ft_isalnum(c) || c == '_');
// }

// /**
//  * Extract variable name from input string
//  */
// static char	*extract_var_name(const char *str)
// {
// 	int		i;
// 	char	*name;

// 	i = 0;
// 	while (str[i] && is_valid_var_char(str[i]))
// 		i++;
// 	name = (char *)malloc(i + 1);
// 	if (!name)
// 		return (NULL);
// 	ft_strlcpy(name, str, i + 1);
// 	return (name);
// }

// /**
//  * Handle special variables like $? and $$
//  */
// static char	*handle_special_var(char var_char, int exit_status)
// {
// 	char	*value;

// 	if (var_char == '?')
// 		return (ft_itoa(exit_status));
// 	else if (var_char == '$')
// 		return (ft_itoa(getpid()));
// 	else
// 	{
// 		value = (char *)malloc(1);
// 		if (value)
// 			value[0] = '\0';
// 		return (value);
// 	}
// }

// /**
//  * Get the length of expanded variable
//  */
// static int	get_expanded_len(char *input, t_env_var *env_vars, int exit_status)
// {
// 	int		i;
// 	int		len;
// 	char	*var_name;
// 	char	*var_value;

// 	i = 0;
// 	len = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '$' && input[i + 1])
// 		{
// 			i++;
// 			if (input[i] == '?' || input[i] == '$')
// 			{
// 				var_value = handle_special_var(input[i], exit_status);
// 				if (var_value)
// 				{
// 					len += ft_strlen(var_value);
// 					free(var_value);
// 				}
// 				i++;
// 			}
// 			else if (is_valid_var_char(input[i]))
// 			{
// 				var_name = extract_var_name(&input[i]);
// 				if (var_name)
// 				{
// 					var_value = get_env_value(env_vars, var_name);
// 					if (var_value)
// 						len += ft_strlen(var_value);
// 					free(var_name);
// 					i += ft_strlen(var_name);
// 				}
// 			}
// 			else
// 				len++;
// 		}
// 		else
// 		{
// 			len++;
// 			i++;
// 		}
// 	}
// 	return (len);
// }

// /**
//  * Expand environment variables in command input
//  */
// char	*expand_env_vars(char *input, t_env_var *env_vars, int exit_status)
// {
// 	int		i;
// 	int		j;
// 	char	*expanded;
// 	char	*var_name;
// 	char	*var_value;
// 	int		in_single_quote;

// 	if (!input)
// 		return (NULL);
// 	expanded = (char *)malloc(get_expanded_len(input, env_vars, exit_status) + 1);
// 	if (!expanded)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	in_single_quote = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'')
// 			in_single_quote = !in_single_quote;
// 		if (input[i] == '$' && input[i + 1] && !in_single_quote)
// 		{
// 			i++;
// 			if (input[i] == '?' || input[i] == '$')
// 			{
// 				var_value = handle_special_var(input[i], exit_status);
// 				if (var_value)
// 				{
// 					ft_strlcpy(&expanded[j], var_value, ft_strlen(var_value) + 1);
// 					j += ft_strlen(var_value);
// 					free(var_value);
// 				}
// 				i++;
// 			}
// 			else if (is_valid_var_char(input[i]))
// 			{
// 				var_name = extract_var_name(&input[i]);
// 				if (var_name)
// 				{
// 					var_value = get_env_value(env_vars, var_name);
// 					if (var_value)
// 					{
// 						ft_strlcpy(&expanded[j], var_value, ft_strlen(var_value) + 1);
// 						j += ft_strlen(var_value);
// 					}
// 					i += ft_strlen(var_name);
// 					free(var_name);
// 				}
// 			}
// 			else
// 				expanded[j++] = '$';
// 		}
// 		else
// 		{
// 			expanded[j++] = input[i++];
// 		}
// 	}
// 	expanded[j] = '\0';
// 	return (expanded);
// }
