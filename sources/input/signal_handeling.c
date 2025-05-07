/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handeling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:17 by schiper           #+#    #+#             */
/*   Updated: 2025/05/07 14:48:41 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "execution.h"
#include "minishell.h"
#include <signal.h>
#include <stdio.h>

/**
 * Signal handler for child processes
 * Sets g_signal_received without affecting readline
 */
void	handle_signals_child(int signum)
{
	if (signum == SIGINT)
		g_signal_received = 1;
}

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
 * Reset signals to default behavior
 * Typically called before executing external commands
 */
void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

