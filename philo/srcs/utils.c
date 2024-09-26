/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:49:10 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/25 13:35:51 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_isallnum(char *str)
{
	if (!(ft_atoi(str) >= 1))
		return (0);
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
	int	i;

	i = 0;
	while (av[++i])
	{
		if (!ft_isallnum(av[i]))
		{
			printf("Error\nARG %d (%s) is not an integer value,", i, av[i]);
			printf(" or is lower then 0\n");
			exit(1);
		}
	}
}

void	print_message(t_philo *philo, char *message, char *color)
{
	pthread_mutex_lock(philo->message);
	printf("%s%ldms philo %d %s\n", color,
		current_timestamp() - philo->main->time, philo->id, message);
	pthread_mutex_unlock(philo->message);
}

unsigned long	current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str <= 13)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}
