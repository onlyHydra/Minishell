/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:17 by schiper           #+#    #+#             */
/*   Updated: 2025/04/30 17:31:45 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// volatile sig_atomic_t	g_sigint_received = 0;

/**
 * Struct explanation:
 * struct sigaction - used to define signal handling behavior.
 *  - sa_handler: pointer to the function to handle the signal.
 *  - sa_flags: modifies behavior (e.g., SA_RESTART to auto-retry syscalls).
 *  - sa_mask: set of signals to block during handler execution.
 */

 
/**
 * Handle SIGINT (Ctrl+C)
 * In bash: Displays a new prompt on a new line
 * This function clears the current input line and refreshes the prompt
 * so the user can continue typing a new command cleanly.
 */
void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


/**
 * Set up signal handlers for interactive mode
 * - SIGINT (Ctrl+C): handled by sigint_handler to avoid program termination
 * - SIGQUIT (Ctrl+\): ignored entirely
 */
void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * Process tokens, generate AST and execute command
 * @param labels: Tokenized input
 */
void	process_tokens_and_execute(t_token *labels)
{
	t_parsed_data	*parsed_data;
	t_parsed_data 	*copy;
	t_node			*ast;
	t_node 	*copy_ast;

	parsed_data = tokens_to_parsed_data(labels);
	copy = parsed_data;
	if (parsed_data)
	{
		ast = parse_expression(&copy);
		copy_ast = ast;
		dfs_walk(copy_ast);
		free_ast(ast);
		free_parsed_data_on_error(parsed_data, 0, 0);
	}
}

/**
 * Process a command entered by the user
 * @param user_input: The input string
 * @param envp: Environment variables
 */
void	process_command(char *user_input, char **envp)
{
	t_token	*labels;

	labels = process_input(user_input, envp);
	if (labels)
	{
		process_tokens_and_execute(labels);
		display_tokens(labels);
		free_token_struct(labels);
	}
}


/**
 * Modified main input reading loop that properly handles cleanup
 * user_input == NULL Handles EOF (Ctrl+D)
 * @param envp: Environment variables
 * @return: 0 for success, 1 for error
 */
int	read_loop(char **envp)
{
	char	*user_input;

	user_input = NULL;
	if (envp == NULL)
		return (1);
	setup_interactive_signals();
	while (1)
	{
		user_input = readline("minishell> ");
		if (user_input == NULL)
			handle_eof(NULL, NULL, NULL);
		if (*user_input != '\0')
		{
			add_history(user_input);
			process_command(user_input, envp);
		}
		free(user_input);
	}
	return (0);
}
