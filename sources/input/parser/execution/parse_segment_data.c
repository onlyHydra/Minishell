/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:50 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 23:44:37 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "minishell.h"

/**
 * This function is the core of the parsing process,
	processing a segment of input
 * by examining each character and delegating to specialized handlers.
 * It continues until it reaches the end of the segment or encounters an error.
 * At the end, it processes any remaining text as a token if necessary.
 *
 * The function uses a priority-based approach to character handling:

 * Handles parentheses: Opening '(' and closing ')'
 * whitespace: Spaces, tabs that separate tokens and are skipped
 * quotes: Both single quotes (') and double quotes (") for literal strings
 * operators: Shell operators like |, <, >, >>, &&, ||, etc.
 * regular text: Normal characters that form command names and arguments
 *
 * If a character is handled by one handler,
	the loop continues to the next character
 *
 * @param params: Contains input string, segment boundaries,
	and environment variables
 * @param segment_state: Tracks current parsing state including position, flags,
	and errors
 */
void	parse_segment(t_parse_params *params, t_parse_state *segment_state)
{
	while (segment_state->i < params->segment_end && !segment_state->error)
	{
		if (handle_parenthesis_char(params->input, segment_state, params->envp))
			continue ;
		if (handle_whitespace(params->input, segment_state, params->envp))
			continue ;
		if (handle_quoted_text(params->input, segment_state))
			continue ;
		if (handle_parsing_ops(params->input, segment_state, params->envp))
		{
			if (handle_filename(params->input, segment_state))
				continue ;
			continue ;
		}
		if (handle_regular_text(params->input, segment_state, params->envp))
			continue ;
		segment_state->i++;
	}
	if (params->input[segment_state->i] != '\0' && segment_state->in_word
		&& segment_state->start < segment_state->i && !segment_state->error)
		process_token(params->input, segment_state, params->envp);
	params->filepath = segment_state->filepath;
}

// void	parse_segment(t_parse_params *params, t_parse_state *state)
// {
// 	t_token_type	*label;

// 	label = CMD;
// 	while (params->input && !state->error)
// 	{
// 		if (ft_is_whitespace(*params->input ))
// 			handle_whitespace(params, state);
// 		else if (ft_is_quote(*params->input ))
// 			handle_quoted_text(params, state);
// 		else if (ft_is_env_var(*params->input ))
// 			handle_env_var(params, state);
// 		else if (ft_is_operator(*params->input ))
// 			handle_parsing_ops(params, state);
// 		else if (ft_is_paren(*params->input ))
// 			handle_parenthesis_char(params, state);
// 		else
// 			handle_regular_text(params, state);
// 	}
// }
