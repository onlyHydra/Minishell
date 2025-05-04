/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:08:00 by schiper           #+#    #+#             */
/*   Updated: 2025/05/03 04:42:29 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns a string for further token proccesing
 * @param input: The input string
 * @param start: Start index
 * @param end: End index
 * @return: The extracted token as a string
 */
char	*extract_string(char *input, int start, int end)
{
	int		len;
	char	*token;

	if (!input || start < 0 || end < start)
		return (NULL);
	len = end - start;
	token = (char *)malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	ft_memcpy(token, input + start, len);
	token[len] = '\0';
	return (token);
}
