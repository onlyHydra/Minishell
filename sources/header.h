/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:27:58 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/16 15:37:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

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

/* Enums and Structures */
typedef enum e_token_type
{
	CMD,
	PIPE = '|',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	REDIRECT_APPEND,
	HEREDOC,
	ENV_VAR,
	EXIT_STATUS,
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"'
}					t_token_type;

typedef struct s_parsed_data
{
	t_token_type	*token;
	char			*data;
}					t_parsed_data;

typedef struct s_token
{
	char			*value;
	char			**split_values;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

t_parsed_data		*tokenize_data(char **data);

#endif
