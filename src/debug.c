#include "../inc/minishell.h"

void	print_node(t_node *node)
{
	int			i;
	t_redirect	*redirect;

	i = 0;
	printf("\n\n\n---DEBUG_START---\n");
	while (node) // 全てのノードを出力する
	{
		// コマンド配列の出力
		printf("[%d] command: ", i);
		if (node->command)
		{
			for (int j = 0; node->command[j] != NULL; j++)
				printf("%s ", node->command[j]);
		}
		else
			printf("NULL");
		printf("\n");
		// リダイレクトの出力
		redirect = node->redirects;
		if (redirect)
		{
			while (redirect)
			{
				switch (redirect->kind) // リダイレクトの種類を比較
				{
				case RD_INPUT:
					printf("[%d] redirect = INPUT\n", i);
					break ;
				case RD_OUTPUT:
					printf("[%d] redirect = OUTPUT\n", i);
					break ;
				case RD_APPEND:
					printf("[%d] redirect = APPEND\n", i);
					break ;
				case RD_HEREDOC:
					printf("[%d] redirect = HEREDOC\n", i);
					break ;
				default:
					printf("[%d] redirect = UNKNOWN\n", i);
				}
				printf("[%d] filename = %s\n", i, redirect->filename);
				redirect = redirect->next;
			}
		}
		else
			printf("[%d] redirect = NULL\n", i);
		node = node->next;
		i++;
	}
	printf("---DEBUG_END---\n\n\n");
}

// void print_tokenize(t_token *token)
// {
//     int i;

//     if (!token)
//         return ;

//     i = 0;
//     printf("\n---TOKENS_DEBUG_START---\n");
//     while (token)
//     {
//         printf("[%d] kind: ", i);
//         if (token->kind == TK_WORD)
//             printf("WORD");
//         else if (token->kind == TK_RESERVED)
//             printf("RESERVED");
//         else if (token->kind == TK_EOF)
//             printf("EOF");
//         else
//             printf("UNKNOWN");

//         printf(", word: \"%s\"\n", token->word);

//         token = token->next;
//         i++;
//     }
//     printf("---TOKENS_DEBUG_END---\n\n");
// }

// char	**ft_join(char **env)
// {
// 	int		i;
// 	int		len;
// 	char	**my_env;

// 	len = 0;
// 	while (env[len] != NULL)
// 		len++;
// 	my_env = (char **)malloc(sizeof(char *) * len + 1);
// 	my_env[len] = NULL;
// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		my_env[i] = strdup(env[i]);
// 		i++;
// 	}
// 	return (my_env);
// }