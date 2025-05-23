/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:58:08 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 23:40:57 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(GRAPH_INTERFACE_H)
# define GRAPH_INTERFACE_H

# include "models/graph_struct.h"

/**
 * @brief Allocates and initializes a new command structure.
 * @return Pointer to a newly allocated t_cmd. NULL if allocation fails.
 */
t_cmd		*allocate_cmd(void);

/**
 * @brief Frees the memory used by a t_cmd structure, including argv and redirs.
 * @param cmd Pointer to the t_cmd to free.
 */
void		free_cmd(t_cmd **cmd);

/**
 * @brief Allocates a new redirection structure.
 * @param type Type of redirection (<, >, >>, <<)
 * @param filename File target of redirection
 * @return Pointer to the new t_redir or NULL on failure.
 */
t_redir		*allocate_redir(int type, const char *filename);

/**
 * @brief Frees a linked list of t_redir structures.
 * @param redir Pointer to the head of redirection list.
 */
void		free_redir_list(t_redir *redir);

/**
 * @brief Allocates a new subshell node, wrapping a subtree.
 * @param child The child AST root inside the subshell.
 * @return Pointer to t_subshell. NULL if allocation fails.
 */
t_subshell	*allocate_subshell(t_node *child);

/**
 * @brief Frees a t_subshell and its child node.
 * @param sub Pointer to the t_subshell to free.
 */
void		free_subshell(t_subshell *sub);

/**
 * @brief Allocates a new AST node of the given type.
 * @param type The type of the node (COMMAND, PIPE, AND, etc).
 * @return Pointer to the newly created node or NULL if fails.
 */
t_node		*allocate_node(t_node_type type);

#endif // GRAPH_INTERFACE_H
