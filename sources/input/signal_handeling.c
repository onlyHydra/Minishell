/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handeling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:17 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 16:54:25 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "execution.h"
#include "minishell.h"
#include <signal.h>
#include <stdio.h>

/**
 * Struct explanation:
 * struct sigaction - used to define signal handling behavior.
 * - sa_handler: pointer to the function to handle the signal.
 * - sa_flags: modifies behavior (e.g., SA_RESTART to auto-retry syscalls).
 * - sa_mask: set of signals to block during handler execution.
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
