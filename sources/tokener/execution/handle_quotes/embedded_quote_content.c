/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   embedded_quote_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:14:43 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/21 21:28:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Extract quoted content for embedded quotes
 */
static char	*get_embedded_quoted_content(char *input, t_parse_state *state)
{
	int		end;
	char	*quoted_content;
	char	quote_char;

	quote_char = state->quote_char;
	end = find_closing_quote(input, state->i + 1, quote_char);
	if (end == -1)
	{
		state->error = 1;
		return (NULL);
	}
	quoted_content = extract_quoted_content(input, state->i + 1, end, state);
	if (!quoted_content)
		state->error = 1;
	return (quoted_content);
}

/**
 * Handle embedded quoted text within a word and append to the word buffer
 */
int	handle_embedded_quote(char *input, t_parse_state *state, char **word_buffer)
{
	int		end;
	char	*quoted_content;
	char	quote_char;

	quote_char = state->quote_char;
	quoted_content = get_embedded_quoted_content(input, state);
	if (!quoted_content)
		return (-1);
	if (!append_to_word_buffer(word_buffer, quoted_content, state))
		return (-1);
	end = find_closing_quote(input, state->i + 1, quote_char);
	return (end + 1);
}
