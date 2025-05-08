/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:48:42 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/07 19:30:02 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/**
 * Sets up signal handling for interactive shell mode
 * Uses sigaction for more reliable signal handling
 */
void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct termios		term;

	sa_int.sa_handler = handle_signals_interactive;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	
	// Fix terminal settings to handle ^M issue
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;  // Enable ECHOCTL for proper control char display
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
 * Sets up signal handling for command execution mode
 * Uses sigaction for more reliable signal handling
 */
void	setup_execution_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct termios		term;

	sa_int.sa_handler = handle_signals_child;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	
	// Fix terminal settings to prevent ^M in cat mode
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;  // Disable ECHOCTL during command execution
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
 * Sets up signal handling for heredoc input mode
 * Uses sigaction for more reliable signal handling
 */
void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_signals_heredoc;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * Reset signals to default behavior
 * Typically called before executing external commands
 */
void	reset_signals(void)
{
	struct sigaction	sa_default;
	struct termios		term;

	sa_default.sa_handler = SIG_DFL;
	sa_default.sa_flags = 0;
	sigemptyset(&sa_default.sa_mask);
	
	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
	
	// Reset terminal settings for child processes
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;  // Disable ECHOCTL for external commands
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	write(STDOUT_FILENO, "\n", 1);
}

