/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:33:26 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/27 15:55:30 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_is_dead(t_main main_program)
{
	int	value;

	pthread_mutex_lock(&main_program.main_mutex);
	value = main_program.is_dead;
	pthread_mutex_unlock(&main_program.main_mutex);
	return (value);
}

int	get_eaten_enouth(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->main->main_mutex);
	value = philo->eaten_enouth;
	pthread_mutex_unlock(&philo->main->main_mutex);
	return (value);
}

int	get_t_meals(t_main main_program)
{
	int	value;

	pthread_mutex_lock(&main_program.main_mutex);
	value = main_program.t_meals;
	pthread_mutex_unlock(&main_program.main_mutex);
	return (value);
}

void	set_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->main_mutex);
	philo->meals += 1;
	if (philo->meals == philo->main->t_meals)
		philo->eaten_enouth = 1;
	pthread_mutex_unlock(&philo->main->main_mutex);
}

// FROM UTILS
void	print_death(t_philo *philo, char *message, char *color)
{
	pthread_mutex_lock(philo->message);
	if (philo->main->is_dead == 1)
	{
		printf("%s%ldms %d %s\n", color,
			current_timestamp() - philo->main->time, philo->id, message);
	}
	pthread_mutex_unlock(philo->message);
}
