/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_interface.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:29:22 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/21 18:31:05 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_INTERFACE_H
# define WILDCARD_INTERFACE_H

char	*resolve_path(char *path);
char	*join_path(char *base, char *component);
char	*resolve_relative_path(char *path, char **envp);
char	*get_current_directory(char **envp);
char	*ft_strjoin3(char *s1, char *s2, char *s3);

#endif