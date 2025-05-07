/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ctx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:11:04 by schiper           #+#    #+#             */
/*   Updated: 2025/05/06 22:41:27 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(EXEC_CTX_H)
# define EXEC_CTX_H

# include "models/envir_struct.h"
# include "models/graph_struct.h"
# include "models/input_data_struct.h"

typedef struct s_exec_ctx
{
	t_node			*ast_root;
	t_parsed_data	*parsed_data;
	t_env_var		*envp;
}					t_exec_ctx;

#endif // EXEC_STRUCT_H
