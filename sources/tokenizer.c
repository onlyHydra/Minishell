/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/15 19:06:27 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_tokens(t_token *tokens)
{
}

/*
*this function will tokeneze a whole array of string 
*@params: argv input
*@return: 
*/
t_token	*tokenize(char **input)
{
	t_token	tokener;

	tokener.split_values = ft_split(input, ' ');
	if (!tokener.split_values)
		return (1);
	
}
