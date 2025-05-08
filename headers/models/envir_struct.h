/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:37:19 by schiper           #+#    #+#             */
/*   Updated: 2025/05/07 20:16:04 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(ENVIR_STRUCT_H)
# define ENVIR_STRUCT_H

typedef struct s_env_var
{
	char				*name;
	char				*value;
	int					exit_code;
	int					exported;
	struct s_env_var	*next;
}						t_env_var;

#endif // ENVIR_STRUCT_H
