/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:24:09 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 19:21:01 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/wildcard.h"
#include "interfaces/wildcard_interface.h"
#include "libft.h"

/**
 * Allocates and initializes the resolved components array
 * @param components: Original path components
 * @return: Allocated resolved components array or NULL on failure
 */
static char	**init_resolved_components(char **components)
{
	char	**resolved_components;
	int		i;

	i = 0;
	while (components[i])
		i++;
	resolved_components = (char **)malloc(sizeof(char *) * (i + 1));
	return (resolved_components);
}

/**
 * Processes path components to handle "." and ".." navigation
 * @param components: Original path components
 * @param resolved_components: Array to store processed components
 * @return: Number of resolved components or -1 on failure
 */
static int	process_components(char **components, char **resolved_components)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (components[i])
	{
		if (ft_strcmp(components[i], ".") == 0)
			continue ;
		else if (ft_strcmp(components[i], "..") == 0)
		{
			if (j > 0)
				j--;
		}
		else if (components[i][0] != '\0')
			resolved_components[j++] = ft_strdup(components[i]);
		i++;
	}
	resolved_components[j] = NULL;
	return (j);
}

/**
 * Rebuilds the final path string from resolved components
 * @param resolved_components: Processed path components
 * @param count: Number of resolved components
 * @param is_absolute: Whether the original path was absolute
 * @return: Rebuilt path string or NULL on failure
 */
static char	*rebuild_path(char **resolved_components, int count,
		int is_absolute)
{
	char	*result;
	char	*old_result;
	int		i;

	if (is_absolute)
		result = ft_strdup("/");
	else
		result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		old_result = result;
		if (i == 0 && !is_absolute)
			result = ft_strdup(resolved_components[i]);
		else
			result = join_path(old_result, resolved_components[i]);
		free(old_result);
		i++;
	}
	return (result);
}

/**
 * Resolves a path string that might contain ".." or "."
 * @param path: Path to resolve
 * @return: Resolved path or NULL on failure
 */
char	*resolve_path(char *path)
{
	char	**components;
	char	**resolved_components;
	int		component_count;
	char	*result;
	int		is_absolute;

	if (!path)
		return (NULL);
	is_absolute = (path[0] == '/');
	components = ft_split(path, '/');
	if (!components)
		return (NULL);
	resolved_components = init_resolved_components(components);
	if (!resolved_components)
	{
		free_array(components);
		return (NULL);
	}
	component_count = process_components(components, resolved_components);
	result = rebuild_path(resolved_components, component_count, is_absolute);
	free_array(components);
	free_array(resolved_components);
	return (result);
}
