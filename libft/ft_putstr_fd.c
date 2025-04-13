/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:13:56 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:27:01 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	size;

	if (s == NULL)
		return ;
	size = write(fd, s, ft_strlen(s));
	(void)size;
}

// int main()
// {
// 	ft_putstr_fd("hello world", 1);
// 	return (0);
// }