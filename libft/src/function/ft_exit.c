/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:24:05 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/23 16:37:07 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_exit(int i, char *error_msg)
{
	if (i == 1)
	{
		ft_putendl_fd(error_msg, 2);
		exit(1);
	}
	exit (0);
}
