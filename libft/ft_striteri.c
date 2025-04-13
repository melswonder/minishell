/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:14:17 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:28:18 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// void ft_striteri_test(unsigned int i, char *c)
// {
// 	if (i % 2 == 0)
// 		*c = *c - 32;
// }

// int main()
// {
// 	char s[] = "hello world";
// 	ft_striteri(s, &ft_striteri_test);
// 	printf("%s\n", s);
// 	return (0);
// }