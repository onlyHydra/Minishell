/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:27:58 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/29 13:39:00 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENER_H
# define TOKENER_H

/* Standard Libraries */
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
/* Project-specific Includes */
# include "../includes/Libft/get_next_line/get_next_line.h"
# include "../includes/Libft/libft.h"
# include "token_struct.h"
# include "token_interface.h"

/* ============================= */
/*         DECLARATIONS         */
/* ============================= */

/* --- Main Functions --- */
t_parsed_data	*tokenize_input(char **argv, char **envp);

/* --- Utility Functions --- */
int				ft_is_whitespace(char c);

#endif
