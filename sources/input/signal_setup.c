/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:48:42 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/07 14:48:51 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/**
 * Set up signal handlers for interactive mode using signal() function
 * - SIGINT (Ctrl+C): handled by handle_signals_interactive
 * - SIGQUIT (Ctrl+\): ignored entirely
 */
void	setup_interactive_signals(void)
{
	signal(SIGINT, handle_signals_interactive);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * Set up signal handlers for execution mode
 * Used when commands are being executed
 */
void	setup_execution_signals(void)
{
	signal(SIGINT, handle_signals_child);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * Set up signal handler for the heredoc mode
 * Need to handle SIGINT differently during heredoc input
 */
void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_signals_child);
	signal(SIGQUIT, SIG_IGN);
}
