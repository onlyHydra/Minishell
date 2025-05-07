/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:42:47 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/07 14:44:16 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal_received;

/**
 * Signal handler for child processes
 * Sets g_signal_received without affecting readline
 */
void							handle_signals_child(int signum);

/**
 * Signal handler for interactive mode (main shell)
 * Handles SIGINT (Ctrl+C) by creating a new prompt line
 */
void							handle_signals_interactive(int signum);

/**
 * Set up signal handlers for interactive mode using signal() function
 * - SIGINT (Ctrl+C): handled by handle_signals_interactive
 * - SIGQUIT (Ctrl+\): ignored entirely
 */
void							setup_interactive_signals(void);

/**
 * Set up signal handlers for execution mode
 * Used when commands are being executed
 */
void							setup_execution_signals(void);

/**
 * Reset signals to default behavior
 * Typically called before executing external commands
 */
void							reset_signals(void);

/**
 * Set up signal handler for the heredoc mode
 * Need to handle SIGINT differently during heredoc input
 */
void							setup_heredoc_signals(void);

#endif
