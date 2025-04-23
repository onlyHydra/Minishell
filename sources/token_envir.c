/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_envir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:54:23 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/23 23:09:25 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:10:50 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/23 23:50:00 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Checks if a character is valid for environment variable names
 * (alphanumeric or underscore)
 */
static int	is_env_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/**
 * Gets environment variable value from envp array
 * @param var_name: Name of the environment variable without the $
 * @param envp: Environment variables array
 * @return Value of the variable or empty string if not found
 */
static char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	int		var_len;
	char	*var_with_equals;

	if (!var_name || !envp)
		return (ft_strdup(""));
	
	var_len = ft_strlen(var_name);
	var_with_equals = ft_calloc(var_len + 2, sizeof(char));
	if (!var_with_equals)
		return (ft_strdup(""));
	
	ft_strcpy(var_with_equals, var_name);
	var_with_equals[var_len] = '=';
	var_with_equals[var_len + 1] = '\0';
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_with_equals, var_len + 1) == 0)
		{
			free(var_with_equals);
			return (ft_strdup(envp[i] + var_len + 1));
		}
		i++;
	}
	free(var_with_equals);
	return (ft_strdup(""));
}

/**
 * Extracts the variable name from input starting at position i
 * Handles both $VAR and ${VAR} formats
 * @return malloc'd string containing variable name without $ or {}
 */
static char	*extract_var_name(char *input, int *i)
{
	int		start;
	int		end;

	(*i)++; // Skip the '$'
	
	// Handle ${VAR} format
	if (input[*i] == '{')
	{
		(*i)++; // Skip the '{'
		start = *i;
		while (input[*i] && input[*i] != '}')
			(*i)++;
		
		if (input[*i] != '}') // Unclosed brace
			return (NULL);
		
		end = *i;
		(*i)++; // Skip the '}'
		return (extract_token(input, start, end));
	}
	
	// Handle $? special variable
	if (input[*i] == '?')
	{
		(*i)++; // Skip the '?'
		return (ft_strdup("?"));
	}
	
	// Handle regular $VAR format
	start = *i;
	while (input[*i] && is_env_var_char(input[*i]))
		(*i)++;
	
	end = *i;
	return (extract_token(input, start, end));
}

/**
 * Expands a single environment variable in the token
 * @param token: Original token string
 * @param pos: Position of the $ character
 * @param envp: Environment variables array
 * @param exit_status: Last command exit status
 * @return New token with variable expanded
 */
static char	*expand_single_var(char *token, int *pos, char **envp, int exit_status)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	char	*temp;
	int		i;
	int		j;
	
	i = *pos;
	var_name = extract_var_name(token, &i);
	if (!var_name)
		return (token);
	
	// Handle special $? variable
	if (ft_strncmp(var_name, "?",ft_strlen(var_name)) == 0)
	{
		free(var_name);
		var_value = ft_itoa(exit_status);
	}
	else
	{
		var_value = get_env_value(var_name, envp);
		free(var_name);
	}
	
	// Create new token with expanded variable
	result = ft_calloc(ft_strlen(token) - (i - *pos) + ft_strlen(var_value) + 1, sizeof(char));
	if (!result)
	{
		free(var_value);
		return (token);
	}
	
	// Copy part before variable
	j = 0;
	while (j < *pos)
	{
		result[j] = token[j];
		j++;
	}
	
	// Copy variable value
	ft_strcat(result, var_value);
	
	// Copy part after variable
	ft_strcat(result, token + i);
	free(var_value);
	
	// Update position to point after the expanded value
	*pos = j + ft_strlen(var_value) - 1;
	
	temp = token;
	token = result;
	free(temp);
	
	return (token);
}

/**
 * Expands all environment variables in a token
 * Handles different behavior based on quotes
 * @param token: Original token string
 * @param envp: Environment variables array
 * @param exit_status: Last command exit status
 * @return New token with all variables expanded
 */
char	*expand_env_vars(char *token, char **envp, int exit_status)
{
	int		i;
	char	in_quotes;
	
	if (!token || !envp)
		return (token);
	
	i = 0;
	in_quotes = 0;
	while (token[i])
	{
		// Track quote state
		if (token[i] == '\'' && (i == 0 || token[i - 1] != '\\'))
		{
			if (in_quotes == 0)
				in_quotes = '\'';
			else if (in_quotes == '\'')
				in_quotes = 0;
		}
		else if (token[i] == '"' && (i == 0 || token[i - 1] != '\\'))
		{
			if (in_quotes == 0)
				in_quotes = '"';
			else if (in_quotes == '"')
				in_quotes = 0;
		}
		
		// Expand variables outside quotes or inside double quotes only
		if (token[i] == '$' && in_quotes != '\'')
		{
			token = expand_single_var(token, &i, envp, exit_status);
		}
		
		i++;
	}
	
	return (token);
}

/**
 * Handles environment variable expansion during token processing
 * To be integrated in your process_token function
 */
char	*process_env_vars(char *token, char **envp, int exit_status)
{
	return (expand_env_vars(token, envp, exit_status));
}

/**
 * Detects if string contains environment variables that need expansion
 * @return 1 if string contains $ (except in single quotes), 0 otherwise
 */
int	has_env_vars(char *str)
{
	int		i;
	char	in_quotes;
	
	i = 0;
	in_quotes = 0;
	while (str && str[i])
	{
		// Track quote state
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		{
			if (in_quotes == 0)
				in_quotes = '\'';
			else if (in_quotes == '\'')
				in_quotes = 0;
		}
		else if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
		{
			if (in_quotes == 0)
				in_quotes = '"';
			else if (in_quotes == '"')
				in_quotes = 0;
		}
		
		// Check for $ outside single quotes
		if (str[i] == '$' && in_quotes != '\'')
		{
			// Verify it's a valid variable reference
			if (str[i + 1] == '?' || str[i + 1] == '{' || is_env_var_char(str[i + 1]))
				return (1);
		}
		
		i++;
	}
	
	return (0);
}
