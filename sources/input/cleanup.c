/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:52:33 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 00:29:50 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "models/token_struct.h"
#include "models/graph_struct.h"
#include "cleanup.h"

/**
 * @brief Frees all resources before exiting the shell
 *
 * This function performs a comprehensive cleanup of all allocated resources
 * to ensure there are no memory leaks when the shell exits. It handles:
 * 1. Command history cleanup
 * 2. Any active AST nodes
 * 3. Token structures
 * 4. Any other allocated resources
 *
 * @param exit_code The exit code to return when exiting
 * @param user_input Current user input buffer, if any
 * @param tokens Current token structure, if any
 * @param ast Current AST structure, if any
 */
void	cleanup_shell(int exit_code, char *user_input, t_token *tokens,
		t_node *ast)
{
	rl_clear_history();
	if (user_input)
		free(user_input);
	if (tokens)
		free_token_struct(&tokens);
	if (ast)
		free_ast(&ast);
	exit(exit_code);
}

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
void	handle_eof(char *user_input, t_token *tokens, t_node *ast)
{
	write(STDOUT_FILENO, "exit\n", 5);
	cleanup_shell(0, user_input, tokens, ast);
}
