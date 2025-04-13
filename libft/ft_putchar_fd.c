/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:13:42 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:25:11 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	int	size;

	size = write(fd, &c, 1);
	(void)size;
}

// int main()
// {
// 	ft_putchar_fd('a', 1);
// 	return (0);
// }