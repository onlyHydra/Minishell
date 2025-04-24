/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 06:48:35 by schiper           #+#    #+#             */
/*   Updated: 2025/04/24 18:03:10 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(GRAPH_FUNCTIONS_H)
# define GRAPH_FUNCTIONS_H

# include "graph.h"
# include "tokener.h"

/*Main entry point*/

/**
 * @brief Parses an expression and builds the corresponding AST node.
 *

	* This function serves as the main entry point
 *   for the recursive descent parser.

*	* It processes tokens and constructs an Abstract Syntax
	Tree (AST) for the given
 * expression.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the root node of the constructed AST,
	or NULL on failure.
 */
t_node			*parse_expression(t_parsed_data **tokens);

/* Parsing by Precedence and hierarchy */

/**
 * @brief Parses an "OR" expression (||) and builds the corresponding AST node.
 *
 * This function handles the parsing of logical "OR" operations and constructs
 * a binary AST node representing the operation.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the constructed AST node, or NULL on failure.
 */
t_node			*parser_or(t_parsed_data **tokens);

/**
 * @brief Parses an "AND" expression (&&) and builds the corresponding AST node.
 *
 * This function handles the parsing of logical "AND" operations and constructs
 * a binary AST node representing the operation.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the constructed AST node, or NULL on failure.
 */
t_node			*parser_and(t_parsed_data **tokens);

/**
 * @brief Parses a pipe expression (|) and builds the corresponding AST node.
 *
 * This function handles the parsing of pipe operations and constructs a binary
 * AST node representing the operation.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the constructed AST node, or NULL on failure.
 */
t_node			*parser_pipe(t_parsed_data **tokens);

/**
 * @brief Parses a command and builds the corresponding AST node.
 *
 * This function handles the parsing of individual commands and constructs a
 * command node for the AST.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the constructed command node, or NULL on failure.
 */
t_node			*parser_command(t_parsed_data **tokens);


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
t_node			*create_binary_node(t_node_type type, t_node *left,
					t_node *right);

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
t_node			*create_command_node(t_cmd *cmd);

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
t_node			*create_subshell_node(t_node *child_ast);

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
t_cmd			*build_command(t_parsed_data **tokens);

#endif // GRAPH_FUNCTIONS_H
