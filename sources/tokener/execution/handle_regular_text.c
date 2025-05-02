/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_regular_text.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:34:41 by schiper           #+#    #+#             */
/*   Updated: 2025/05/02 14:25:37 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * @brief Processes an environment variable token from the input string.
 *
 * Extracts a substring from the input representing an environment variable,
 * retrieves its value from the environment, and adds it as a token to the
 * parser state. Always preserves ENV_VAR type even when a filename is expected.
 *
 * @param input The full input string being parsed.
 * @param state The current parsing state, tracking position and token list.
 * @param envp The environment variable array.
 * @param j The current index in the input
 * where the environment variable ends.
 * @return int Returns 1 on success, 0 on failure (e.g.,
	memory allocation error).
 */
static int	process_env_token(char *input, t_parse_state *state, char **envp,
		int j)
{
	char			*env_name;
	char			*env_value;
	t_token_type	token_type;

	env_name = extract_string(input, state->start, j);
	if (!env_name)
		return (0);
	env_value = extract_env_value(env_name, envp);
	free(env_name);
	token_type = ENV_VAR;
	if (state->expect_filename)
		state->expect_filename = 0;
	add_token(state->tokens, env_value, token_type);
	state->i = j;
	state->start = j;
	state->in_word = 0;
	return (1);
}

/**
 * Handle environment variables specifically
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
static int	handle_env_var(char *input, t_parse_state *state, char **envp)
{
	int	j;

	if (is_environment_variable(input))
	{
		if (state->in_word && state->start < state->i)
		{
			process_token(input, state, state->i, envp);
			state->in_word = 0;
		}
		state->start = state->i;
		j = state->i + 1;
		while (input[j] && !ft_is_whitespace(input[j]) && !is_operator(input, j)
			&& input[j] != '\'' && input[j] != '"' && input[j] != '('
			&& input[j] != ')')
			j++;
		return (process_env_token(input, state, envp, j));
	}
	return (0);
}

/**
 * Handle regular text (without quotes or special characters)
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
int	handle_regular_text(char *input, t_parse_state *state, char **envp)
{
	int	j;

	if (handle_env_var(input, state, envp))
		return (1);
	if (is_operator(input, state->i) || input[state->i] == '\''
		|| input[state->i] == '"' || input[state->i] == '('
		|| input[state->i] == ')')
		return (0);
	if (!state->in_word)
	{
		state->in_word = 1;
		state->start = state->i;
	}
	j = state->i;
	while (input[j] && !is_operator(input, j) && input[j] != ' '
		&& input[j] != '\t' && input[j] != '\'' && input[j] != '"'
		&& input[j] != '(' && input[j] != ')' && input[j] != '$')
		j++;
	if (j > state->i)
	{
		process_token(input, state, j, envp);
		state->i = j;
		return (1);
	}
	return (0);
}

/**
 *@param input: string
 *@param i: index
 @return: true if its a operator, false if not
 */
int	is_operator(char *input, int i)
{
	if (!input || i < 0 || i >= (int)ft_strlen(input))
		return (0);
	if (input[i] == '&' && input[i + 1] == '&')
		return (1);
	if (input[i] == '|' && input[i + 1] == '|')
		return (1);
	if (input[i] == '>' && input[i + 1] == '>')
		return (1);
	if (input[i] == '<' && input[i + 1] == '<')
		return (1);
	if (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == '&'
		|| input[i] == ';')
		return (1);
	return (0);
}
