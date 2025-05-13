/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_regular.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:06:22 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/13 16:10:19 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Extract environment variable name and get its value
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
 * @brief Processes an environment variable token from the input string.
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
