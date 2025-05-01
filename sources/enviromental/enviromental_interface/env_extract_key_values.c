/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_extract_key_values.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:37:17 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 13:53:57 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * UTILS FOR OTHER POURPOSE
 * Extract the VALUE part from an environment variable array
 * @param key: The environment variable key to look for
 * @param envp: Array of environment variables in the format KEY=VALUE
 * @return: The value part of the matching env var, or empty string if not found
 */
char	*extract_env_value_part(char *key, char **envp)
{
	char	*value;
	int		i;
	int		len;

	value = NULL;
	if (!key || !envp)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
		{
			value = ft_strdup(envp[i] + len + 1);
			return (value);
		}
		i++;
	}
	return (ft_strdup(""));
}

/**
 * Extract the KEY part from an environment variable string
 * @param str: The environment variable string (possibly with $ prefix)
 * @return: The extracted key, or NULL if failed
 */
static char	*extract_env_key(char *str)
{
	char	*key;

	key = NULL;
	if (!str)
		return (NULL);
	if (str[0] == '$')
		str++;
	key = ft_strdup(str);
	return (key);
}

/**
 * This function returns the KEY=VALUE pair of an environmental variable
 * @param str: The environment variable key to look for (possibly with $ sign)
 * @param envp: Array of environment variables in the format KEY=VALUE
 * @return: The full KEY=VALUE string, with empty value if not found
 */

static char	*join_key_value(char *key, char *value)
{
	char	*token_value;
	int		key_len;
	int		value_len;
	int		total_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	total_len = key_len + value_len + 2;
	token_value = (char *)malloc(total_len);
	if (!token_value)
		return (NULL);
	ft_memcpy(token_value, key, key_len);
	token_value[key_len] = '=';
	ft_memcpy(token_value + key_len + 1, value, value_len);
	token_value[total_len - 1] = '\0';
	return (token_value);
}

/**
 * MAIN extractor function for env
 */
char	*extract_env_value(char *str, char **envp)
{
	char	*key;
	char	*value;
	char	*result;

	if (!str || !envp)
		return (NULL);
	key = extract_env_key(str);
	if (!key)
		return (NULL);
	value = extract_env_value_part(key, envp);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	result = join_key_value(key, value);
	free(key);
	free(value);
	return (result);
}
