

#include "token_struct.h"
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
