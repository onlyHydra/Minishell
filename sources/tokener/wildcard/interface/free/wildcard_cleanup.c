/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:59:03 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 14:54:07 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/wildcard.h"
#include <stdlib.h>

/**
 * Clean up resources and return NULL
 *
 * @param dir: Directory pointer
 * @param dir_path: Directory path
 * @param file_pattern: File pattern
 * @return: NULL
 */
char	**cleanup_and_return_null(DIR *dir, char *dir_path, char *file_pattern)
{
	closedir(dir);
	free(dir_path);
	free(file_pattern);
	return (NULL);
}
