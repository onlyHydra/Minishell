/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ctx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:11:04 by schiper           #+#    #+#             */
/*   Updated: 2025/05/04 18:37:16 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(EXEC_CTX_H)
# define EXEC_CTX_H

# include "models/graph_struct.h"

typedef struct s_exec_ctx
{
	t_node	*ast_root;
	char	**envp;
}			t_exec_ctx;

#endif // EXEC_STRUCT_H
