/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:16:26 by schiper           #+#    #+#             */
/*   Updated: 2025/05/02 15:56:26 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(ERROR_MESSAGE_H)
# define ERROR_MESSAGE_H

# include "libft.h"
# include <unistd.h>

void	print_execve_error(const char *cmd, int error_code);

#endif // ERROR_MESSAGE_H
