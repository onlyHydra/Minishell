/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:34:12 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 18:28:11 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard Libraries */
# define _POSIX_C_SOURCE 200809L
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* Project-specific Libraries */
# include "get_next_line.h"
# include "libft.h"

/* Model Structures - Important: order matters for dependencies */
# include "models/graph_struct.h"
# include "models/input_data_struct.h"
# include "models/token_struct.h"

/* Forward declaration for t_env_var */
typedef struct s_env_var	t_env_var;

/* Interfaces - Important: order matters for dependencies */
# include "graph_interface.h"
# include "input_data_interface.h"
# include "token_interface.h"

/* Core Components */
# include "abstract_syntax_tree.h"
# include "cleanup.h"
# include "envir.h"
# include "input.h"
# include "tokener.h"

/* Signal handlers */
void						sigint_handler(int sig);
void						setup_interactive_signals(void);

#endif