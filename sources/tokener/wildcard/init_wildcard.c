/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:46:22 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/02 15:46:41 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/**
 * Initialize wildcard matches array
 *
 * @param pattern: The wildcard pattern to match against
 * @return: Directory pointer and initialized matches array in a struct
 */
t_expand_context	*init_wildcard_expand(const char *pattern)
{
	t_expand_context	*context;

	context = malloc(sizeof(t_expand_context));
	if (!context)
		return (NULL);
	context->matches = NULL;
	context->match_count = 0;
	context->dir = opendir(".");
	if (!context->dir)
	{
		free(context);
		return (NULL);
	}
	context->pattern = pattern;
	return (context);
}
