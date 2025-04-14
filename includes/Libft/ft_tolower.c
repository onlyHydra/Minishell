/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:05:46 by iatilla-          #+#    #+#             */
/*   Updated: 2024/11/16 14:05:04 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int ce)
{
	if (ce >= 'A' && ce <= 'Z')
		ce += 32;
	return (ce);
}
// #include <unistd.h>

// int	main(void)
// {
// 	int	i;

// 	i = ft_tolower(65);
// 	write(1, &i, 1);
// 	return (0);
// }
