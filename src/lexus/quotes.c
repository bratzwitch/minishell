#include "../../include/minishell.h"

t_token *handle_single_quotes_argument(char **input)
{
    char *current;
    char *start;
    char *token_value;

    current = *input;
    if (*current == '\'')
        current++;
    start = current;
    while (*current && *current != '\'')
        current++;
    if (*current != '\'')
    {
        printf("Unmatched quote detected.\n"); // i dont think well need this but just in case
        return (NULL);
    }
    token_value = strndup(start, current - start);
    if (!token_value)
    {
        printf("Memory allocation failed: %s\n", strerror(errno));
        return (NULL);
    }
    current++;
    *input = current;
    return (create_token(TOKEN_ARGUMENT, token_value));
}

char *handle_dollar_in_double_quotes(char **current)
{
    char *var_start = *current + 1;
    char *env_value;

    if (*var_start == '?')
    {
        *current = var_start + 1;
        printf("Encountered exit status.\n");
        // return (???);
    }
    while (ft_isalnum(*var_start) || *var_start == '_')
        var_start++;
    env_value = get_env_variable(&var_start, *current + 1);
    *current = var_start;
    return (env_value);
}

char *append_to_final_str(char *final_str, const char *start, size_t len)
{
    char *token_value;
    char *temp;

    token_value = strndup(start, len);
    temp = ft_strjoin(final_str, token_value);
    free(token_value);
    free(final_str);
    return (temp);
}

char *process_dollar(char **current, char *final_str, char **start)
{
    char *temp;
    char *env_value;

    temp = append_to_final_str(final_str, *start, *current - *start);
    env_value = handle_dollar_in_double_quotes(current);
    final_str = ft_strjoin(temp, env_value);
    free(temp);
    *start = *current;
    return (final_str);
}

t_token *handle_double_quotes_argument(char **input)
{
    char *current;
    char *start;
    char *final_str;

    current = *input + 1;
    start = current;
    final_str = ft_calloc(1, 1);
    if (!final_str)
        return (NULL);
    while (*current && *current != '\"')
    {
        if (*current == '$')
        {
            final_str = process_dollar(&current, final_str, &start);
            if (!final_str)
                return (NULL);
        }
        else
            current++;
    }
    if (*current != '\"')
    {
        printf("Unmatched double quote detected.\n");
        free(final_str);
        return (NULL);
    }
    final_str = append_to_final_str(final_str, start, current - start);
    *input = current + 1;
    return (create_token(TOKEN_ARGUMENT, final_str));
}
