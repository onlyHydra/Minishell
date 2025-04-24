/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_pointer_array.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:31 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/24 18:43:56 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Free the split array of strings
 * @param dirs: Array of strings to free
 */
void	free_array(char **dirs)
{
	int	i;

	i = 0;
	while (dirs[i])
	{
		free(dirs[i]);
		i++;
	}
	free(dirs);
}
