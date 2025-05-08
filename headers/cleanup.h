/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:15:33 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 00:18:13 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(CLEANUP_H)
# define CLEANUP_H

# include "minishell.h"

/**
 * @brief Frees all resources before exiting the shell
 *
 * This function performs a comprehensive cleanup of all allocated resources
 * to ensure there are no memory leaks when the shell exits.
 *
 * @param exit_code The exit code to return when exiting
 * @param user_input Current user input buffer, if any
 * @param tokens Current token structure, if any
 * @param ast Current AST structure, if any
 */
void	cleanup_shell(int exit_code, char *user_input, t_token *tokens,
			t_node *ast);
/**
 * @brief Handles EOF signal (Ctrl+D)
 *
 * This function is called when EOF is detected (Ctrl+D) in the main read loop.
 * It displays "exit" message and performs proper cleanup before exiting.
 *
 * @param user_input Current user input buffer, if any
 * @param tokens Current token structure, if any
 * @param ast Current AST structure, if any
 */
void	handle_eof(char *user_input, t_token *tokens, t_node *ast);
void	free_args(char **args);
/**
 * @brief Frees an AST node and all its children recursively.
 * @param node Pointer to the root node of the tree to free.
 */
void	free_ast(t_node **node);

#endif
