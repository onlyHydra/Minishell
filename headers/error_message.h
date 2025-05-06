/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 00:16:26 by schiper           #+#    #+#             */
/*   Updated: 2025/05/06 00:13:05 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(ERROR_MESSAGE_H)
# define ERROR_MESSAGE_H

# include "libft.h"
# include <unistd.h>

void	print_execve_error(const char *cmd, int error_code);
int			print_export_error(char *arg);
int			print_unset_error(char *arg);

#endif // ERROR_MESSAGE_H
