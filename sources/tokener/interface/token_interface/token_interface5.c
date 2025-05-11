/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:28:38 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/11 12:45:00 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Prepare token for processing with type determination
 * @param input: Input string
 * @param state: Parsing state
 * @param type: Pointer to token type variable
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

	// Extract the exact string from input
	token_value = extract_string(input, state->start, state->i);
	if (!token_value)
		return (NULL);

	// Preserve whitespace tokens as STR_LITERAL
	if (is_whitespace_token(token_value))
	{
		*type = STR_LITERAL;
		return (token_value);
	}

	// Handle quoted strings exactly as they appear
	if (token_value[0] == '\'' || token_value[0] == '"')
	{
		*type = STR_LITERAL;
		return (token_value);
	}

	// For other tokens, determine type and expand if needed
	token_type = decide_token_type(token_value, envp, state);
	*type = token_type;
	
	// Only expand environment variables when they're not part of quoted strings
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

	// Special handling for command tokens and filenames
	if (state->is_first_token && !is_whitespace_token(token_value) && 
		token_value[0] != '\'' && token_value[0] != '"' &&
		is_string_command(token_value, envp, &free_me))
	{
		token_type = CMD;
	}
	else if (state->expect_filename && token_type != ENV_VAR
		&& !is_redir_token_type(token_type) && !is_operator_token(token_type)
		&& !is_whitespace_token(token_value))
	{
		token_type = FILENAME;
		state->expect_filename = 0;
	}
	else if (state->expect_filename && !is_whitespace_token(token_value))
	{
		state->expect_filename = 0;
	}

	// Handle first token flag (only reset for non-whitespace)
	if (!is_whitespace_token(token_value))
		state->is_first_token = 0;

	free(free_me);
	add_token(state->tokens, token_value, token_type, state->filepath);
	free(state->filepath);
	state->filepath = NULL;
	state->in_word = 0;
}
