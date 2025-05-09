/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_syntax_tree.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 06:48:35 by schiper           #+#    #+#             */
/*   Updated: 2025/05/04 19:05:54 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(ABSTRACT_SYNTAX_TREE_H)
# define ABSTRACT_SYNTAX_TREE_H

# include "graph_interface.h"
# include "tokener.h"

/*Main entry point*/

/**
 * @brief Parses an expression and builds the corresponding AST node.
 * This function serves as the main entry point
 * for the recursive descent parser.
 * It processes tokens and constructs an Abstract Syntax
 * Tree (AST) for the given
 * expression.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the root node of the constructed AST,
	or NULL on failure.
 */
t_node		*parse_expression(t_parsed_data **tokens);

t_node		*parser_or(t_parsed_data **tokens);
/**
 * @brief Parses an "AND" expression (&&) and builds the corresponding AST node.
 *
 * This function handles the parsing of logical "AND" operations and constructs
 * a binary AST node representing the operation.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the constructed AST node, or NULL on failure.
 */
t_node		*parser_and(t_parsed_data **tokens);

/**
 * @brief Parses a pipe expression (|) and builds the corresponding AST node.
 *
 * This function handles the parsing of pipe operations and constructs a binary
 * AST node representing the operation.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the constructed AST node, or NULL on failure.
 */
t_node		*parser_pipe(t_parsed_data **tokens);

/**
 * @brief Parses a command and builds the corresponding AST node.
 *
 * This function handles the parsing of individual commands and constructs a
 * command node for the AST.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the constructed command node, or NULL on failure.
 */
t_node		*parser_command(t_parsed_data **tokens);

t_node		*parser_subshell(t_parsed_data **tokens);

t_node		*parser_primary(t_parsed_data **tokens);
/*Node Creators*/

/**
 * @brief Creates a binary AST node.
 *
 * This function constructs a binary AST node with the specified type and
 * child nodes.
 *
 * @param type The type of the binary node (e.g., AND, OR, PIPE).
 * @param left A pointer to the left child node.
 * @param right A pointer to the right child node.
 * @return A pointer to the newly created binary node, or NULL on failure.
 * @warning The caller is responsible for freeing the allocated memory
 *          for the returned node to avoid memory leaks.
 */
t_node		*create_binary_node(t_node_type type, t_node *left, t_node *right);

/**
 * @brief Creates a command AST node.
 *
 * This function constructs a command node for the AST using the provided
 * command data.
 *
 * @param cmd A pointer to the command data.
 * @return A pointer to the newly created command node, or NULL on failure.
 * @warning The caller is responsible for freeing the allocated memory
 *          for the returned node to avoid memory leaks.
 */
t_node		*create_command_node(t_cmd *cmd);

/**
 * @brief Creates a subshell AST node.
 *
 * This function constructs a subshell node for the AST, representing a
 * subshell operation.
 *
 * @param child_ast A pointer to the child AST node for the subshell.
 * @return A pointer to the newly created subshell node, or NULL on failure.
 * @warning The caller is responsible for freeing the allocated memory
 *          for the returned node to avoid memory leaks.
 */
t_node		*create_subshell_node(t_node *child_ast);

/* CMD Builder*/

/**
 * @brief Builds a command from the given tokens.
 *
 * This function processes the tokens to construct a command structure,
 * which can then be used to create a command node in the AST.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the constructed command structure, or NULL on failure.
 * @warning The caller is responsible for freeing the allocated memory
 *          for the returned command structure to avoid memory leaks.
 */
t_cmd		*build_command(t_parsed_data **tokens);

void		add_argv(t_cmd **cmd, t_parsed_data **data);

void		add_redirection(t_cmd **cmd, t_parsed_data **tokens,
				t_token_type red_type);
/**
 * @brief Return NODE_TYPE that matches the TOKEN_TYPE given for node creations

 * This functions currently looks for types TOKEN_AND,TOKEN_OR,TOKEN_CMD,
 * TOKEN_PIPE, and returns NODE_COMMAND, NODE_AND, NODE_OR, NODE_PIPE,
	NODE_UNKNOWN
 * @param token_type : the token type, NON-NULL
 */
t_node_type	token_type_to_node_type(const t_token_type *token_type);

#endif // ABSTRACT_SYNTAX_TREE_H
