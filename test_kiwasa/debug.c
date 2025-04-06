#include "minishell.h"

void	print_node(t_node *node)
{
	int	i;
	int	in_redirect;

	i = 0;
	in_redirect = 0;
	printf("\n\n\n---DEBUG_START---");
	while (node->next != NULL)
	{
		printf("[%d]command%s\n", i, node->command);
		if (node->redirects != NULL)
		{
			if (in_redirect == 1)
				node->redirects = node->redirects->next;
			in_redirect = 1;
			switch (node->redirects != NULL)
			{
			case RD_INPUT:
				printf("[%d]redirect = %s\n", i, "INPUT");
			case RD_OUTPUT:
				printf("[%d]redirect = %s\n", i, "OUTPUT");
			case RD_APPEND:
				printf("[%d]redirect = %s\n", i, "APPEND");
			case RD_HEREDOC:
				printf("[%d]redirect = %s\n", i, "HEREDOC");
			}
		}
		else
			printf("[%d]redirect = %s\n", i, "NULL");
		printf("[%d]filname = %s\n", node->redirects->filename);
		node = node->next;
		i++;
	}
}

void print_tokenize(t_token *token)
{
    int i;
    
    if (!token)
        return;
        
    i = 0;
    printf("\n---TOKENS_DEBUG_START---\n");
    while (token)
    {
        printf("[%d] kind: ", i);
        if (token->kind == TK_WORD)
            printf("WORD");
        else if (token->kind == TK_RESERVED)
            printf("RESERVED");
        else if (token->kind == TK_EOF)
            printf("EOF");
        else
            printf("UNKNOWN");
            
        printf(", word: \"%s\"\n", token->word);
        
        token = token->next;
        i++;
    }
    printf("---TOKENS_DEBUG_END---\n\n");
}

char	**ft_join(char **env)
{
	int		i;
	int		len;
	char	**my_env;

	len = 0;
	while (env[len] != NULL)
		len++;
	my_env = (char **)malloc(sizeof(char *) * len + 1);
	my_env[len] = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		my_env[i] = strdup(env[i]);
		i++;
	}
	return (my_env);
}