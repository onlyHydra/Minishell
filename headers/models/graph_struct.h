/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 05:04:55 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 15:24:20 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(GRAPH_STRUCT_H)
# define GRAPH_STRUCT_H


# define ARG_SIZE 500
# define ARG_LIMIT 500
/*
 * Enum to Type node types
 * It defined NODE_COMMAND, NODE_PIPE ('|'), NODE_AND ('&&') , NODE_OR ('||') ,
	NODE_SUBSHELL ( commands grouped by parantheses )
 *
 */
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL,
    NODE_SUBSHELL_START,
    NODE_SUBSHELL_END,
	NODE_UNKNOWN
}						t_node_type;

/*
 *Struct to define the redirections <,>,<<,>>
 */
typedef struct s_redir
{
	int					type;
	char				*filename;
}						t_redir;

/*
 *Struct that defines commands as argv, redir_list and cmd_path for execve
 */
typedef struct s_cmd
{
	char				*cmd_path;
	char				**argv;
	t_redir				*redir_list;
}						t_cmd;

/*
 * Struct that defines subshell as a list of childs depending on the paranthesis
 */
typedef struct s_subshell
{
	struct s_node		*child;
}						t_subshell;

/*
 * Struct that defines 1 graph node
 *  type value			Valid union field					Meaning
 *NODE_COMMAND			node->cmd					Holds command,args,redirs
 *NODE_SUBSHELL			node->subshell				Holds a child AST for group
 *NODE_PIPE				none (use left/right)		No union data; just structure
 *NODE_AND				none (use left/right)		No union data; just structure
 *NODE_OR				none (use left/right)		No union data; just structur
 **/
typedef struct s_node	t_node;
typedef struct s_node
{
	t_node_type			type;
	t_node				*left;
	t_node				*right;
	union
	{
		t_cmd			*cmd;
		t_subshell		*sub;
	} u_data;
}						t_node;

#endif // GRAPH_STRUCT_H
