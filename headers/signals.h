/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:18:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 13:52:45 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* Signal handlers */
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	setup_interactive_signals(void);
void	reset_signal_handlers(void);
int		get_received_signal(void);
void	sigquit_handler(int sig);
#endif