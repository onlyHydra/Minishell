/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:18:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 14:57:19 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>

/* Signal handlers */
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	setup_interactive_signals(void);
void	reset_signal_handlers(void);
int		get_received_signal(void);

#endif