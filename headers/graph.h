/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 05:04:55 by schiper           #+#    #+#             */
/*   Updated: 2025/04/21 15:06:39 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(GRAPH_H)
# define GRAPH_H

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
	NODE_SUBSHELL
}					t_node_type;

/*
 *Struct to define the redirections <,>,<<,>>
 */
typedef struct s_redir
{
	int				type;
	char			*filename;
}					t_redir;

/*
 *Struct that defines commands as argv, redir_list and cmd_path for execve
 */
typedef struct s_cmd
{
	char			*cmd_path;
	char			**argv;
	t_redir			*redir_list;
}					t_cmd;

/*
 * Struct that defines subshell as a list of childs depending on the paranthesis
 */
typedef struct s_subshell
{
	struct s_node	*child;
}					t_subshell;

/*
 * Struct that defines 1 graph node
 *  type value			Valid union field					Meaning
 *NODE_COMMAND			node->cmd					Holds command,args,redirs
 *NODE_SUBSHELL			node->subshell				Holds a child AST for group
 *NODE_PIPE				none (use left/right)		No union data; just structure
 *NODE_AND				none (use left/right)		No union data; just structure
 *NODE_OR				none (use left/right)		No union data; just structur
 **/
typedef struct s_node
{
	t_node_type		type;
	t_node			*left;
	t_node			*right;
	union
	{
		t_cmd		cmd;
		t_subshell	sub;
	} u_data;
}					t_node;


/**
 * @brief Allocates and initializes a new command structure.
 * @return Pointer to a newly allocated t_cmd. NULL if allocation fails.
 */
t_cmd *allocate_cmd(void);

/**
 * @brief Frees the memory used by a t_cmd structure, including argv and redirs.
 * @param cmd Pointer to the t_cmd to free.
 */
void free_cmd(t_cmd *cmd);


/**
 * @brief Allocates a new redirection structure.
 * @param type Type of redirection (<, >, >>, <<)
 * @param filename File target of redirection
 * @return Pointer to the new t_redir or NULL on failure.
 */
t_redir *allocate_redir(int type, const char *filename);

/**
 * @brief Frees a linked list of t_redir structures.
 * @param redir Pointer to the head of redirection list.
 */
void free_redir_list(t_redir *redir);


/**
 * @brief Allocates a new subshell node, wrapping a subtree.
 * @param child The child AST root inside the subshell.
 * @return Pointer to t_subshell. NULL if allocation fails.
 */
t_subshell *allocate_subshell(t_node *child);

/**
 * @brief Frees a t_subshell and its child node.
 * @param sub Pointer to the t_subshell to free.
 */
void free_subshell(t_subshell *sub);


/**
 * @brief Allocates a new AST node of the given type.
 * @param type The type of the node (COMMAND, PIPE, AND, etc).
 * @return Pointer to the newly created node or NULL if fails.
 */
t_node *allocate_node(t_node_type type);

/**
 * @brief Frees an AST node and all its children recursively.
 * @param node Pointer to the root node of the tree to free.
 */
void free_ast(t_node *node);

#endif // GRAPH_H
