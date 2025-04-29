
#include "token_struct.h"
#include <stdlib.h>

/**
 * Free parsed data entries up to a specific index
 * @param parsed_data: The parsed data array to clean
 * @param up_to_index: Index up to which to free (inclusive)
 */
void	free_parsed_data_up_to(t_parsed_data *parsed_data, int up_to_index)
{
	int	i;

	if (!parsed_data)
		return ;
	i = 0;
	while (i <= up_to_index)
	{
		if (parsed_data[i].token)
			free(parsed_data[i].token);
		if (parsed_data[i].data)
			free(parsed_data[i].data);
		i++;
	}
}

/**
 * Free parsed data allocation and clean up in error cases
 * @param parsed_data: The parsed data array to free
 * @param index: Current index where allocation failed
 * @param free_token: Whether to free token at the current index
 */
void	free_parsed_data_on_error(t_parsed_data *parsed_data, int index,
		int free_token)
{
	if (free_token && parsed_data[index].token)
		free(parsed_data[index].token);
	if (index > 0)
		free_parsed_data_up_to(parsed_data, index - 1);
	free(parsed_data);
}

/**
 * Frees the parsed data structure
 * @param parsed_data Pointer to the parsed data structure
 */
void	free_parsed_data(t_parsed_data *parsed_data)
{
	if (!parsed_data)
		return ;
	if (parsed_data->data)
		free(parsed_data->data);
	free(parsed_data);
}
