/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:28:38 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 14:51:08 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Prepare token for processing with type determination
 * @param input: Input string
 * @param state: Parsing state
 * @param end: End position of token
 * @param envp: Environment variables
 * @return: Processed token value or NULL if extraction failed
 */
static char	*prepare_token(char *input, t_parse_state *state,
		t_token_type *type, char **envp)
{
	char			*token_value;
	t_token_type	token_type;
	int				is_env;
	char			*expanded_value;

	token_value = extract_string(input, state->start, state->i);
	if (!token_value)
		return (NULL);
	token_type = decide_token_type(token_value, envp, state);
	*type = token_type;
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
 * @param end: state->i
 * @param envp: Environment variables
 */
void	process_token(char *input, t_parse_state *state, char **envp)
{
	char			*token_value;
	char			*free_me;
	t_token_type	token_type;

	free_me = NULL;
	token_value = prepare_token(input, state, &token_type, envp);
	if (!token_value)
		return ;
	if (state->is_first_token && is_string_command(token_value, envp, &free_me))
		token_type = CMD;
	else if (state->expect_filename && token_type != ENV_VAR
		&& !is_redir_token_type(token_type) && !is_operator_token(token_type))
	{
		token_type = FILENAME;
		state->expect_filename = 0;
	}
	else if (state->expect_filename)
		state->expect_filename = 0;
	free(free_me);
	state->is_first_token = 0;
	add_token(state->tokens, token_value, token_type, state->filepath);
	free(state->filepath);
	state->filepath = NULL;
	state->in_word = 0;
}
