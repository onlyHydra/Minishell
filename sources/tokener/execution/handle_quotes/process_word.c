/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:20:57 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/13 16:28:30 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Append quoted content to the existing word buffer
 */
int	append_to_word_buffer(char **word_buffer, char *quoted_content,
		t_parse_state *state)
{
	char	*new_buffer;

	if (*word_buffer)
	{
		new_buffer = ft_strjoin(*word_buffer, quoted_content);
		free(*word_buffer);
		free(quoted_content);
		if (!new_buffer)
		{
			state->error = 1;
			return (0);
		}
		*word_buffer = new_buffer;
	}
	else
		*word_buffer = quoted_content;
	return (1);
}

/**
 * Check if this is part of a continuous word (no whitespace before or after)
 */
int	is_part_of_word(char *input, int i)
{
	int	is_start;
	int	is_end;

	is_start = (i == 0 || ft_is_whitespace(input[i - 1]) || is_operator(input, i
				- 1));
	is_end = (!input[i + 1] || ft_is_whitespace(input[i + 1])
			|| is_operator(input, i + 1));
	return (!(is_start && is_end));
}

/**
 * Initialize word buffer with text before the quote if needed
 */
char	*init_word_buffer(char *input, t_parse_state *state)
{
	char	*word_buffer;

	word_buffer = NULL;
	if (state->in_word && state->start < state->i)
	{
		word_buffer = extract_string(input, state->start, state->i);
		if (!word_buffer)
			state->error = 1;
	}
	return (word_buffer);
}
