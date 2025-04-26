

#include "token_struct.h"
#include <stdlib.h>

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
//
