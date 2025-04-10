/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:51:57 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/10 22:55:20 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	print_node(t_node *node)
// {
// 	int			i;
// 	t_redirect	*redirect;

// 	i = 0;
// 	printf("\n\n\n---DEBUG_START---\n");
// 	while (node)
// 	{
// 		printf("[%d] command: ", i);
// 		if (node->command)
// 		{
// 			for (int j = 0; node->command[j] != NULL; j++)
// 				printf("%s ", node->command[j]);
// 		}
// 		else
// 			printf("NULL");
// 		printf("\n");
// 		redirect = node->redirects;
// 		if (redirect)
// 		{
// 			while (redirect)
// 			{
// 				switch (redirect->kind)
// 				{
// 				case RD_INPUT:
// 					printf("[%d] redirect = INPUT\n", i);
// 					break ;
// 				case RD_OUTPUT:
// 					printf("[%d] redirect = OUTPUT\n", i);
// 					break ;
// 				case RD_APPEND:
// 					printf("[%d] redirect = APPEND\n", i);
// 					break ;
// 				case RD_HEREDOC:
// 					printf("[%d] redirect = HEREDOC\n", i);
// 					break ;
// 				default:
// 					printf("[%d] redirect = UNKNOWN\n", i);
// 				}
// 				printf("[%d] filename = %s\n", i, redirect->filename);
// 				redirect = redirect->next;
// 			}
// 		}
// 		else
// 			printf("[%d] redirect = NULL\n", i);
// 		node = node->next;
// 		i++;
// 	}
// 	printf("---DEBUG_END---\n\n\n");
// }

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