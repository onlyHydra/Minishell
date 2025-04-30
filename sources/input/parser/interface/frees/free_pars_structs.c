

#include "models/token_struct.h"
#include "input_data_interface.h"
#include <stdlib.h>

/**
 * Frees the parse parameters structure
 * @param params Pointer to the parameters structure
 */
void	free_params_struct(t_parse_params *params)
{
	if (!params)
		return ;
	if (params->input)
		free(params->input);
	free(params);
}

/**
 * Frees the parse state structure
 * @param state Pointer to the parse state structure
 */
void	free_state_struct(t_parse_state *state)
{
	if (!state)
		return ;
	free(state);
}