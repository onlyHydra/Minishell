/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handeling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:17 by schiper           #+#    #+#             */
/*   Updated: 2025/05/07 19:27:38 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"


/**
 * Signal handler for interactive mode (main shell)
 * Handles SIGINT (Ctrl+C) by creating a new prompt line
 */
void	handle_signals_interactive(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * Signal handler for child processes and execution mode
 * Sets g_signal_received and prints newline
 */
void	handle_signals_child(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = 1;
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * Signal handler for heredoc input
 * Sets g_signal_received and exits the heredoc input loop
 */
void	handle_signals_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = 1;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}
