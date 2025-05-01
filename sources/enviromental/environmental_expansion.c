/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmental_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:19:10 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 18:16:25 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

// /**
//  * Handle the special cases `$?` and `$$`
//  */
// static int	handle_special_expansion(char **expanded, int *j, char special)
// {
// 	char	*var_value;

// 	var_value = handle_special_var(special, 3);
// 	if (var_value)
// 	{
// 		ft_strlcpy(&(*expanded)[*j], var_value, ft_strlen(var_value) + 1);
// 		*j += ft_strlen(var_value);
// 		free(var_value);
// 		return (1);
// 	}
// 	return (0);
// }

// /**
//  * Expand environment variables in the command input
//  */
// char	*expand_env_vars(char *input, t_env_var *env_vars)
// {
// 	char	*expanded;
// 	int		i;
// 	int		j;
// 	int		in_single_quote;

// 	i = 0;
// 	j = 0;
// 	if (!input)
// 		return (NULL);
// 	expanded = malloc(get_expanded_len(input, env_vars) + 1);
// 	if (!expanded)
// 		return (NULL);
// 	i = 0, j = 0, in_single_quote = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'')
// 		{
// 			in_single_quote = !in_single_quote;
// 			expanded[j++] = input[i++];
// 		}
// 		else if (input[i] == '$' && input[i + 1] && !in_single_quote)
// 		{
// 			i++;
// 			if (handle_var_expansion(expanded, &j, input, &i, env_vars) == 0)
// 				return (NULL);
// 		}
// 		else
// 		{
// 			expanded[j++] = input[i++];
// 		}
// 	}
// 	expanded[j] = '\0';
// 	return (expanded);
// }

// /**
//  * Handle variable expansion for $?, $$ and named variables
//  */
// static int	handle_var_expansion(char *expanded, int *j, char *input,
		// int *i,
// 		t_env_var *env_vars)
// {
// 	char	*value;
// 	char	*name;
// 	char	*value;

// 	if (input[*i] == '?' || input[*i] == '$')
// 	{
// 		value = handle_special_var(input[*i], 3);
// 		if (!value)
// 			return (0);
// 		copy_and_free(&expanded[*j], value, j);
// 		(*i)++;
// 	}
// 	else if (is_valid_var_char(input[*i]))
// 	{
// 		name = extract_var_name(&input[*i]);
// 		if (!name)
// 			return (0);
// 		value = get_env_value(env_vars, name);
// 		if (value)
// 			ft_strlcpy(&expanded[*j], value, ft_strlen(value) + 1);
// 		*j += value ? ft_strlen(value) : 0;
// 		*i += ft_strlen(name);
// 		free(name);
// 	}
// 	else
// 	{
// 		expanded[(*j)++] = '$';
// 	}
// 	return (1);
// }

// /**
//  * Helper to copy string value and update position
//  */
// static void	copy_and_free(char *dest, char *src, int *pos)
// {
// 	ft_strlcpy(dest, src, ft_strlen(src) + 1);
// 	*pos += ft_strlen(src);
// 	free(src);
// }

// /**
//  * Expand environment variables in the command input
//  */
// char	*expand_env_vars(char *input, t_env_var *env_vars)
// {
// 	int		i;
// 	int		j;
// 	int		in_single_quote;
// 	char	*expanded;

// 	i = 0;
// 	j = 0;
// 	in_single_quote = 0;
// 	if (!input)
// 		return (NULL);
// 	expanded = (char *)malloc(get_expanded_len(input, env_vars) + 1);
// 	if (!expanded)
// 		return (NULL);
// 	while (input[i])
// 	{
// 		if (!handle_char_expansion(&expanded, &j, input, &i, &in_single_quote,
// 				env_vars))
// 			return (NULL);
// 		i++;
// 	}
// 	expanded[j] = '\0';
// 	return (expanded);
// }
