/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 17:02:24 by apavlov           #+#    #+#             */
/*   Updated: 2018/12/24 17:02:41 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(float *a, float *b)
{
	float c;

	c = *a;
	*a = *b;
	*b = c;
}
