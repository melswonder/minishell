/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:13:48 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:25:40 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd (s, fd);
	ft_putchar_fd ('\n', fd);
}

// int main()
// {
// 	ft_putendl_fd("hello world", 1);
// 	return (0);
// }