/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:06:22 by iatilla-          #+#    #+#             */
/*   Updated: 2025/06/02 16:45:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Extracts the variable name from input string
 * and retrieves its value from envp
 *
 * @param input: The input string containing the variable
 * @param start: Starting position of the variable name
 * @param end: Ending position of the variable name
 * @param envp: Array of environment variables
 * @return: The environment variable value, or NULL if not found
 */
char	*get_char_envvar(char *input, int start, int end, char **envp)
{
	char	*env_name;
	char	*env_value;

	env_name = extract_string(input, start, end);
	if (!env_name)
		return (NULL);
	env_value = extract_env_value(env_name, envp);
	free(env_name);
	return (env_value);
}

/**
 * Add an environment variable token to the parser state
 * Creates a new token with the environment 
 * variable value and updates parser state
 *
 * @param state: Current parsing state
 * @param env_value: The resolved environment variable value
 * @param j: Position to update the parser to
 * @return: Always returns 1 (success)
 */
int	add_env_token(t_parse_state *state, char *env_value, int j)
{
	t_token_type	token_type;

	token_type = ENV_VAR;
	if (state->expect_filename)
		state->expect_filename = 0;
	add_token(state->tokens, env_value, token_type, NULL);
	state->i = j;
	state->start = j;
	state->in_word = 0;
	return (1);
}

/**
 * Processes an environment variable token from the input string
 * Main function that handles the complete
   environment variable processing workflow
 *
 * @param input: The input string being parsed
 * @param state: Current parsing state
 * @param envp: Array of environment variables
 * @param j: End position of the environment variable
 * @return: 1 if successful, 0 if variable not found or error occurred
 */
int	process_env_token(char *input, t_parse_state *state, char **envp, int j)
{
	char	*env_value;

	env_value = get_char_envvar(input, state->start, j, envp);
	if (!env_value)
		return (0);
	return (add_env_token(state, env_value, j));
}

/**
 * Find the end of an environment variable name
 * Scans forward to determine where the variable name terminates
 *
 * @param input: The input string being scanned
 * @param start: Starting position (should be at '$' character)
 * @return: Position where the variable name ends
 */
int	find_env_var_end(char *input, int start)
{
	int	j;

	j = start + 1;
	while (input[j] && !ft_is_whitespace(input[j]) && !is_operator(input, j)
		&& input[j] != '\'' && input[j] != '"' && input[j] != '('
		&& input[j] != ')')
		j++;
	return (j);
}

/**
 * Process the current word if needed before handling an env var

 * Ensures any pending word token is processed
  before starting environment variable parsing
 *
 * @param input: The input string being parsed
 * @param state: Current parsing state
 * @param envp: Array of environment variables
 * @return: Always returns 1 (success)
 */
int	prepare_for_env_var(char *input, t_parse_state *state, char **envp)
{
	if (state->in_word && state->start < state->i)
	{
		process_token(input, state, envp);
		state->in_word = 0;
	}
	state->start = state->i;
	return (1);
}
