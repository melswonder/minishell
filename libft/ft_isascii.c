/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:12:03 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:12:04 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%d\n", ft_isascii('a'));
// 	printf("%d\n", ft_isascii('A'));
// 	printf("%d\n", ft_isascii('0'));
// 	printf("%d\n", ft_isascii(' '));
// 	printf("%d\n", ft_isascii('['));
// 	printf("%d\n", ft_isascii(128));
// 	return (0);
// }