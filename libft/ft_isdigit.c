/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:12:10 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:15:09 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// #include <stdio.h>
// int main()
// {
// 	printf("%d\n", ft_isdigit('a'));
// 	printf("%d\n", ft_isdigit('A'));
// 	printf("%d\n", ft_isdigit('0'));
// 	printf("%d\n", ft_isdigit(' '));
// 	printf("%d\n", ft_isdigit('['));
// 	return (0);
// }