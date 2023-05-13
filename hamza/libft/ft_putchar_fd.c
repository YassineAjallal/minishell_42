/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:26:33 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/18 21:51:15 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

//#include<stdio.h>
//int main(int argc, char const *argv[])
//{
//	int fd = open ("42.txt", O_CREAT| O_RDWR);
//	ft_putchar_fd('c',fd);
//	printf("%d",fd);
//	return 0;
//}
