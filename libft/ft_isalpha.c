/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:11:45 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:11:46 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// #include <stdio.h>
// int main()
// {
// 	int c = 'a';
// 	printf("%d\n", ft_isalpha(c));
// 	c = 'A';
// 	printf("%d\n", ft_isalpha(c));
// 	c = 'z';
// 	printf("%d\n", ft_isalpha(c));
// 	c = 'Z';
// 	printf("%d\n", ft_isalpha(c));
// 	c = '1';
// 	printf("%d\n", ft_isalpha(c));
// 	c = ' ';
// 	printf("%d\n", ft_isalpha(c));
// 	c = '!';
// 	printf("%d\n", ft_isalpha(c));
// 	return (0);
// }