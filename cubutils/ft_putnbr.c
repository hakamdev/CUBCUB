/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:54:15 by ehakam            #+#    #+#             */
/*   Updated: 2020/10/19 20:04:06 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubengine.h"

void	ft_putnbr(int n)
{
	char	c;
	long	nn;

	nn = n;
	if (nn < 0)
	{
		nn = -nn;
		write(1, "-", 1);
	}
	if (nn >= 0 && nn <= 9)
	{
		c = nn + 48;
		write(1, &c, 1);
	}
	if (nn > 9)
	{
		ft_putnbr(nn / 10);
		ft_putnbr(nn % 10);
	}
}
