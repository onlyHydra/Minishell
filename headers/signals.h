/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:42:47 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/07 19:28:04 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

extern volatile sig_atomic_t	g_signal_received;

/**
 * Signal handler for child processes
 * Sets g_signal_received without affecting readline
 */
void	handle_signals_child(int signum);

/**
 * Signal handler for interactive mode (main shell)
 * Handles SIGINT (Ctrl+C) by creating a new prompt line
 */
void	handle_signals_interactive(int signum);

/**
 * Signal handler for heredoc input
 * Sets g_signal_received and exits the heredoc input loop
 */
void	handle_signals_heredoc(int signum);

/**
 * Sets up signal handling for interactive shell mode
 * Uses sigaction for more reliable signal handling
 */
void	setup_interactive_signals(void);

/**
 * Sets up signal handling for command execution mode
 * Uses sigaction for more reliable signal handling
 */
void	setup_execution_signals(void);

/**
 * Sets up signal handling for heredoc input mode
 * Uses sigaction for more reliable signal handling
 */
void	setup_heredoc_signals(void);

/**
 * Reset signals to default behavior
 * Typically called before executing external commands
 */
void	reset_signals(void);

#endif
