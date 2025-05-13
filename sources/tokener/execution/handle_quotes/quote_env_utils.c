/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:24:59 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/13 16:28:36 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Expand environment variables in double-quoted content if needed
 */
static char	*expand_env_vars(char *content, char **envp, t_token_type *type)
{
	char	*expanded;

	if (is_environment_variable(content))
	{
		expanded = extract_env_value(content, envp);
		free(content);
		if (!expanded)
			return (NULL);
		*type = ENV_VAR;
		return (expanded);
	}
	return (content);
}

/**
 * Handle filename expectations and set the appropriate token type
 */
static char	*handle_token_type(char *content, t_parse_state *state,
		t_token_type *type)
{
	if (state->expect_filename && *type != ENV_VAR)
	{
		*type = FILENAME;
		state->expect_filename = 0;
	}
	else if (state->expect_filename)
		state->expect_filename = 0;
	return (content);
}

/**
 * Extract the content from a quoted string, handling environment variables
 * if needed (for double quotes)
 */
char	*extract_quoted_content(char *input, int start, int end,
		char quote_char, t_parse_state *state, t_token_type *type)
{
	char	*content;

	*type = STR_LITERAL;
	content = extract_string(input, start, end);
	if (!content)
		return (NULL);
	if (quote_char == '"')
		content = expand_env_vars(content, state->envp, type);
	return (handle_token_type(content, state, type));
}
