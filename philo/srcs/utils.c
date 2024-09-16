/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:49:10 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/16 09:11:09 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_isallnum(char *str)
{
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
			return (0);
		str++;
	}
	return (1);
}

void	check_args(char **av)
{
	int i;

	i = 0;
	while (av[++i])
	{
		if (!ft_isallnum(av[i]))
		{
			printf("Error\nARG %d %s is not an integer value\n", i, av[i]);
			exit(1);
		}
	}
}

#include <ctype.h>

int ft_atoi(char *str)
{
    int res = 0;
    int sign = 1;

    // Ignorar espaços em branco e caracteres de controle
    while (isspace(*str))
        str++;

    // Verificar o sinal
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    // Converter números
    while (isdigit(*str))
    {
        res = res * 10 + (*str - '0');
        str++;
    }

    return res * sign;
}
