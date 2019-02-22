/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 19:02:37 by ccommiss          #+#    #+#             */
/*   Updated: 2019/02/22 19:28:54 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_countchr(const char *s, int c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	printf ("COUCOU ICI %s ---\n", s);
	while (s[i])
	{
		if (s[i] == c && ft_isdigit(s[i - 1]))
		{
			count++;
		}
		i++;
	}
	return (count);
}
