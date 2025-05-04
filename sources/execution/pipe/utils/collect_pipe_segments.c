/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_pipe_segments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:21:21 by schiper           #+#    #+#             */
/*   Updated: 2025/05/04 23:18:27 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models/graph_struct.h"

t_node	*flatten_pipe(t_node *root, int max)
{
	while (root && root->type == NODE_PIPE && max > 0)
		root = root->left;
	return (root);
}

int	collect_pipe_segments(t_node *root, t_node **segm, int max)
{
	int	num;

	num = 0;
	while (root && root->type == NODE_PIPE && num + 1 < max)
	{
		segm[num++] = root->left;
		root = root->right;
	}
	if (root && num < max)
		segm[num++] = root;
	return (num);
}
