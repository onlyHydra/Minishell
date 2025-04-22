
#include "header.h"

/**
 * Processes an operator and adds it to the token list using the params struct
 * @param params: Struct containing input, tokens list, and envp
 * @param i: Current index in the input string
 * @return new index after processing the operator (i + 1 or i + 2)
 */
static int	process_operator(t_parse_params *params, int i)
{
	char			*operator;
	t_token_type	op_type;

	if ((params->input[i] == '&' && params->input[i + 1] == '&')
		|| (params->input[i] == '|' && params->input[i + 1] == '|'))
	{
		operator= extract_token(params->input, i, i + 2);
		op_type = decide_token_type(operator, params->envp);
		add_token(params->tokens, operator, op_type);
		return (i + 2);
	}
	else
	{
		operator= extract_token(params->input, i, i + 1);
		op_type = decide_token_type(operator, params->envp);
		add_token(params->tokens, operator, op_type);
		return (i + 1);
	}
}

/**
 * Handles an operator segment by processing preceding segment and operator
 * @param params: Struct containing input, tokens list, and envp
 * @param i: Current index in the input string
 * @return new index after processing the operator
 */
int	handle_operator_segment(t_parse_params *params, int i)
{
	int	new_pos;

	handle_segment(params, i);
	new_pos = process_operator(params, i);
	params->segment_start = new_pos;
	params->is_first_segment = 0;
	return (new_pos);
}

/**
 * Handles calling process_segment for the input before an operator
 * @param params: Struct containing input, tokens list, and envp
 * @param i: Index where operator starts
 */
void	handle_segment(t_parse_params *params, int i)
{
	t_parse_params	segment_params;

	if (params->segment_start < i)
	{
		segment_params = *params;
		segment_params.segment_end = i;
		process_segment(&segment_params);
	}
}

/**
 * Handles parsing logic for a text segment
 * @param params: Struct containing input, tokens list, and envp
 * @param segment_state: Current parsing state
 */
void handle_segment_parsing(t_parse_params *params, t_parse_state *segment_state)
{
    while (segment_state->i < params->segment_end && !segment_state->error)
    {
        if (handle_whitespace(params->input, segment_state, params->envp))
            continue;
        if (handle_backslash(params->input, segment_state))
            continue;
        if (handle_quotes(params->input, segment_state, params->envp))
            continue;
        if (handle_operators(params->input, segment_state))
            continue;
        if (!segment_state->in_word)
        {
            segment_state->in_word = 1;
            segment_state->start = segment_state->i;
        }
        segment_state->i++;
    }
    if (segment_state->in_word && segment_state->start < segment_state->i
        && !segment_state->error)
        process_token(params->input, segment_state, segment_state->i,
            params->envp);
}

/**
 * Processes a text segment between operators or input boundaries
 * @param params: Struct containing input, tokens list, and envp
 */
void process_segment(t_parse_params *params)
{
    t_parse_state segment_state;
    
    init_parse_state(&segment_state, params->tokens);
    segment_state.i = params->segment_start;
    segment_state.start = params->segment_start;
    segment_state.is_first_token = params->is_first_segment;
    
    handle_segment_parsing(params, &segment_state);
}
