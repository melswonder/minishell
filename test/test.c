/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:44:40 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/04 15:56:52 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// int main(void)
// {
//     char *input = readline("Enter your name: ");
//     if (input)
//     {
//         printf("Hello, %s!\n", input);
//         free(input);
//     }
//     return (0);
// 	rl_replace_line();
// }

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	if (access("infile", F_OK) == -1)
	{
		printf("infile not found\n");
		return(1);
	}
	else if(access("infile", R_OK) == -1) //読み込みはできるか？
	{
		printf("infile: Permission denied\n");
		return(1);
	}
	return(0);
}