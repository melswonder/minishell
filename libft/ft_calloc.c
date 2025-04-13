/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:08:45 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/27 15:47:20 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	if (num == 0 || size == 0)
	{
		ptr = malloc(0);
		return ((void *)ptr);
	}
	if (num != 0 && (((num * size) / num) != size))
		return (NULL);
	ptr = malloc(num * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, num * size);
	return (ptr);
}

// #include <stdio.h>
// int main()
// {
// 	char *s = (char *)ft_calloc(10, sizeof(char));
// 	if (s == NULL)
// 	{
// 		printf("Failed to allocate memory\n");
// 		return 1;
// 	}
// 	printf("%s\n", s);
// 	free(s);
// 	return 0;
// }