/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   embedded_quote_content.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:14:43 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/13 16:42:59 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Extract quoted content for embedded quotes
 */
static char	*get_embedded_quoted_content(char *input, t_parse_state *state,
		char quote_char, t_token_type *token_type)
{
	int		end;
	char	*quoted_content;

	end = find_closing_quote(input, state->i + 1, quote_char);
	if (end == -1)
	{
		state->error = 1;
		return (NULL);
	}
	quoted_content = extract_quoted_content(input, state->i + 1, end,
			quote_char, state, token_type);
	if (!quoted_content)
		state->error = 1;
	return (quoted_content);
}

/**
 * Handle embedded quoted text within a word and append to the word buffer
 */
int	handle_embedded_quote(char *input, t_parse_state *state, char quote_char,
		char **word_buffer)
{
	int				end;
	char			*quoted_content;
	t_token_type	token_type;

	quoted_content = get_embedded_quoted_content(input, state, quote_char,
			&token_type);
	if (!quoted_content)
		return (-1);
	if (!append_to_word_buffer(word_buffer, quoted_content, state))
		return (-1);
	end = find_closing_quote(input, state->i + 1, quote_char);
	return (end + 1);
}
