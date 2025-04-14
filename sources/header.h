/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:27:58 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/10 14:32:14 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

/* Standard Libraries */
# include <stdio.h>          
# include <stdlib.h>         
# include <unistd.h>         
# include <fcntl.h>          
# include <sys/types.h>      
# include <sys/stat.h>       
# include <sys/wait.h>       
# include <signal.h>         
# include <dirent.h>         
# include <string.h>         
# include <sys/ioctl.h>      
# include <termios.h>        
# include <termcap.h>        

/* Readline */
# include <readline/readline.h>   
# include <readline/history.h>    

/* Project-specific Includes */
# include "../includes/Libft/get_next_line/get_next_line.h"
# include "../includes/Libft/libft.h"

#endif 
