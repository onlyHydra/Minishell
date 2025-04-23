
#include "header.h"

/**
 * Check if character is valid for an environment variable name
 * @param c: Character to check
 * @return 1 if valid, 0 otherwise
 */
static int is_valid_env_var_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

/**
 * Get length of environment variable name
 * @param str: String starting after $ character
 * @return Length of the variable name
 */
static int get_env_var_name_length(const char *str)
{
    int i;

    i = 0;
    // Handle special case for $?
    if (str[0] == '?')
        return 1;
    
    // Handle ${VAR} syntax if supported
    if (str[0] == '{')
    {
        i = 1;
        while (str[i] && str[i] != '}')
            i++;
        if (str[i] == '}')
            return i + 1; // Include the closing brace
        return 0; // Incomplete ${VAR} syntax
    }
    
    // Regular $VAR_NAME syntax
    while (str[i] && is_valid_env_var_char(str[i]))
        i++;
    
    return i;
}

/**
 * Extract environment variable name from string
 * @param str: String starting after $ character
 * @return Newly allocated string containing the variable name
 */
static char *extract_env_var_name(const char *str)
{
    int var_len;
    char *var_name;
    
    var_len = get_env_var_name_length(str);
    if (var_len == 0)
        return NULL;
    
    // Handle special case for $?
    if (str[0] == '?')
        return ft_strdup("?");
    
    // Handle ${VAR} syntax
    if (str[0] == '{')
    {
        var_name = ft_substr(str, 1, var_len - 2); // Exclude braces
        return var_name;
    }
    
    // Regular variable name
    var_name = ft_substr(str, 0, var_len);
    return var_name;
}

/**
 * Get value of environment variable
 * @param var_name: Name of the variable
 * @param envp: Environment variables array
 * @param exit_status: Last command exit status (for $?)
 * @return Value of the variable or empty string if not found
 */
static char *get_env_var_value(char *var_name, char **envp, int exit_status)
{
    int i;
    int var_len;
    
    // Handle special case for $?
    if (ft_strcmp(var_name, "?") == 0)
        return ft_itoa(exit_status);
    
    var_len = ft_strlen(var_name);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], var_name, var_len) == 0 && envp[i][var_len] == '=')
            return ft_strdup(envp[i] + var_len + 1);
        i++;
    }
    
    // Variable not found, return empty string
    return ft_strdup("");
}

/**
 * Expand environment variables in a string
 * @param str: Input string that may contain environment variables
 * @param envp: Environment variables array
 * @param exit_status: Last command exit status
 * @return New string with variables expanded
 */
char *expand_env_variables(char *str, char **envp, int exit_status)
{
    int i;
    int in_single_quote;
    int in_double_quote;
    char *result;
    char *var_name;
    char *var_value;
    char *temp;
    
    i = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    result = ft_strdup("");
    
    while (str[i])
    {
        // Track quote state
        if (str[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        else if (str[i] == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        
        // Expand variables outside single quotes
        if (str[i] == '$' && !in_single_quote && (is_valid_env_var_char(str[i + 1]) || 
                                                 str[i + 1] == '?' || 
                                                 str[i + 1] == '{'))
        {
            i++; // Move past $
            var_name = extract_env_var_name(str + i);
            if (var_name)
            {
                var_value = get_env_var_value(var_name, envp, exit_status);
                
                // Append variable value to result
                temp = result;
                result = ft_strjoin(result, var_value);
                free(temp);
                free(var_value);
                
                // Move past the variable name
                if (str[i] == '{')
                    i += ft_strlen(var_name) + 2; // +2 for the braces
                else
                    i += ft_strlen(var_name);
                
                free(var_name);
                continue;
            }
        }
        
        // Append current character to result
        temp = result;
        result = ft_strjoin_char(result, str[i]);
        free(temp);
        i++;
    }
    
    return result;
}

/**
 * Handle environment variable expansion during token processing
 * @param token: Input token that may contain environment variables
 * @param envp: Environment variables array
 * @param exit_status: Last command exit status
 * @return New token with variables expanded
 */
char *handle_env_variables(char *token, char **envp, int exit_status)
{
    char *expanded;
    
    expanded = expand_env_variables(token, envp, exit_status);
    free(token);
    return expanded;
}

/**
 * Helper function to concatenate a character to a string
 * @param str: Original string
 * @param c: Character to append
 * @return New string with character appended
 */
static char *ft_strjoin_char(char *str, char c)
{
    char *result;
    int len;
    
    len = ft_strlen(str);
    result = (char *)malloc(sizeof(char) * (len + 2));
    if (!result)
        return NULL;
    
    ft_strcpy(result, str);
    result[len] = c;
    result[len + 1] = '\0';
    
    return result;
}
