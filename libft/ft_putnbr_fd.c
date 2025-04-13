/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:13:51 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:26:43 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			buf[12];
	int				i;
	unsigned int	num;

	i = 12;
	buf[--i] = '\0';
	if (n >= 0)
		num = n;
	else
		num = -n;
	while (1)
	{
		buf[--i] = num % 10 + '0';
		num /= 10;
		if (num == 0)
			break ;
	}
	if (n < 0)
		buf[--i] = '-';
	ft_putstr_fd(&buf[i], fd);
}

// int main()
// {
// 	ft_putnbr_fd(123, 1);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(-123, 1);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(0, 1);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(2147483647, 1);
// 	write(1, "\n", 1);
// 	ft_putnbr_fd(-2147483648, 1);
// 	write(1, "\n", 1);
// 	return (0);
// }