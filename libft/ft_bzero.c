/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:08:37 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:08:40 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset (s, 0, n);
}

// #include <stdio.h>
// int main()
// {
// 	char s[] = "Hello, World!";
// 	ft_bzero(s, 5);
// 	printf("%s\n", s);
// 	return (0);
// }