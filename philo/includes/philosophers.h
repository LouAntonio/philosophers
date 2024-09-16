/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:06:57 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/16 09:13:10 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// MAIN STRUCTURE
typedef struct s_main
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_meals;
	int				is_dead;
	int				all_eaten;
	unsigned long	time;
	pthread_mutex_t	main_mutex;
}					t_main;

// PHILOSOPHER STRUCTURE
typedef struct s_philo
{
	int				id;
	unsigned long	last_meal;
	int				eaten;
	int				no_eat;
	pthread_mutex_t	*messager;
	pthread_mutex_t	*fork;
	t_main			*main;
}					t_philo;

// UTILS
void	check_args(char **av);
int	ft_atoi(char *str);

#endif