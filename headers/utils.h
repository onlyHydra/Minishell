/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:26:21 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 14:38:45 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* String utilities */
char	*extract_string(char *input, int start, int end);
int		is_valid_var_char(char c);
int		is_valid_var_name(const char *name);
int		is_valid_numeric_argument(char *str);
int		is_dash_n_flag(const char *arg);

/* Input processing utilities */
int		update_quote_state(char *input, int i, int *in_quote, char *quote_char);
int		is_quote(char c, char *quote_char);

/* Command utilities */
int		is_builtin(const char *cmd);

#endif
