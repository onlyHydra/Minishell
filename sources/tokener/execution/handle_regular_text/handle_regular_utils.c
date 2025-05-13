/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_regular_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:02:52 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/13 16:10:19 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Check if a character might start a quoted section
 */
int	is_possible_quote(char *input, int i)
{
	return (input[i] == '\'' || input[i] == '"');
}

/**
 * Check if character is an operator
 */
int	is_operator(char *input, int i)
{
	if (!input || i >= (int)ft_strlen(input))
		return (0);
	if (i + 1 < (int)ft_strlen(input))
	{
		if (twochar_operator(input + i) == STR_LITERAL)
		{
			if (onechar_operator(input + i) == STR_LITERAL)
				return (0);
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}
