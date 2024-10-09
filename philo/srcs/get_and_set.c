/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:33:26 by lantonio          #+#    #+#             */
/*   Updated: 2024/10/09 09:09:18 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_is_dead(t_main main)
{
	int	value;

	pthread_mutex_lock(&main.main_mutex);
	value = main.is_dead;
	pthread_mutex_unlock(&main.main_mutex);
	return (value);
}

int	get_t_meals(t_main main)
{
	int	value;

	pthread_mutex_lock(&main.main_mutex);
	value = main.t_meals;
	pthread_mutex_unlock(&main.main_mutex);
	return (value);
}

// FROM UTILS
void	print_death(t_philo *philo, char *message, char *color)
{
	pthread_mutex_lock(philo->message);
	if (get_is_dead(*philo->main))
	{
		printf("%s%ldms %d %s\n", color,
			current_timestamp() - philo->main->time, philo->id, message);
	}
	pthread_mutex_unlock(philo->message);
}
