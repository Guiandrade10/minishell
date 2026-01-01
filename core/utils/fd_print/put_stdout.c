/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_stdout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:00:00 by biphuyal          #+#    #+#             */
/*   Updated: 2025/12/17 16:21:43 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putendl(char *s)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void	ft_putnbr(int n)
{
	char	digits;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	digits = '0' + (n % 10);
	write(1, &digits, 1);
}
