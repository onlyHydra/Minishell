/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:34:12 by schiper           #+#    #+#             */
/*   Updated: 2025/04/29 23:56:50 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard Libraries */
# define _POSIX_C_SOURCE 200809L
# include <dirent.h>
# include <fcntl.h>
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
# include <readline/history.h>
# include <readline/readline.h>

/* Project-specific Libraries */
# include "get_next_line.h"
# include "libft.h"

/* Model Structures - Important: order matters for dependencies */
# include "models/graph_struct.h"
# include "models/token_struct.h"
# include "models/input_data_struct.h"

/* Interfaces - Important: order matters for dependencies */
# include "graph_interface.h"
# include "input_data_interface.h"
# include "token_interface.h"

/* Core Components */
# include "abstract_syntax_tree.h"
# include "tokener.h"
# include "input.h"

/* ============================= */
/*          ADDITIONAL          */
/*    PROJECT-WIDE FUNCTIONS    */
/* ============================= */

/* Add any additional project-wide functions, macros or definitions here */

#endif /* MINISHELL_H */