/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:29:31 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 21:45:54 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/error_message.h"
#include "models/graph_struct.h"
#include "models/input_data_struct.h"

void	syntax_check(t_parsed_data *data, t_node *node, int *exit_code)
{
	if (data == NULL && node == NULL)
	{
		syntax_error_msg("", exit_code);
		return ;
	}
	if (data->data != NULL)
	{
		syntax_error_msg(data->data, exit_code);
		return ;
	}
	if (node == NULL)
	{
		syntax_error_msg("", exit_code);
		return ;
	}
	*exit_code = 0;
}
