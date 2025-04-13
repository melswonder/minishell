/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:09:52 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:12:57 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

// #include <stdio.h>
// int main()
// {
// 	printf("%d\n", ft_isalnum('a'));
// 	printf("%d\n", ft_isalnum('A'));
// 	printf("%d\n", ft_isalnum('0'));
// 	printf("%d\n", ft_isalnum(' '));
// 	printf("%d\n", ft_isalnum('['));
// 	return (0);
// }