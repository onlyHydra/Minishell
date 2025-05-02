/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:28:38 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/02 17:16:43 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"
/**
 * Prepare token for processing with type determination
 * @param input: Input string
 * @param state: Parsing state
 * @param end: End position of token
 * @param envp: Environment variables
 * @return: Processed token value or NULL if extraction failed
 */
static char	*prepare_token(char *input, t_parse_state *state, int end,
		char **envp)
{
	char			*token_value;
	t_token_type	token_type;
	int				is_env;
	char			*expanded_value;

	token_value = extract_string(input, state->start, end);
	if (!token_value)
		return (NULL);
	token_type = decide_token_type(token_value, envp,state);
	is_env = (token_type == ENV_VAR || is_environment_variable(token_value));
	if (is_env)
	{
		expanded_value = extract_env_value(token_value, envp);
		free(token_value);
		token_value = expanded_value;
	}
	return (token_value);
}

/**
 * Process a token with awareness of filename expectations
 * @param input: Input string
 * @param state: Parsing state
 * @param end: End position of token
 * @param envp: Environment variables
 */
void	process_token(char *input, t_parse_state *state, int end, char **envp)
{
	char			*token_value;
	t_token_type	token_type;
	t_token         *new_token;

	token_value = prepare_token(input, state, end, envp);
	if (!token_value)
		return ;
	token_type = decide_token_type(token_value, envp, state);
	if (state->is_first_token && is_string_command(token_value, envp, &state->filepath))
		token_type = CMD;
	else if (state->expect_filename && token_type != ENV_VAR)
	{
		token_type = FILENAME;
		state->expect_filename = 0;
	}
	else if (state->expect_filename)
		state->expect_filename = 0;
	state->is_first_token = 0;
	new_token = add_token(state->tokens, token_value, token_type);
	new_token->filepath = state->filepath;
	if (!new_token)
		free(token_value);
	else if (token_type == CMD && state->filepath)
		new_token->filepath = ft_strdup(state->filepath);
	state->in_word = 0;
}
