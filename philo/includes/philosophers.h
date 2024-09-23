/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:06:57 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/23 13:11:48 by lantonio         ###   ########.fr       */
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
	pthread_mutex_t	*message;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_main			*main;
}					t_philo;

// UTILS
int		ft_atoi(char *str);
void	check_args(char **av);
unsigned long	current_timestamp(void);
void	print_message(t_philo *philo, char *message, char *color);

// INITIALIZATION
void	init_main(int ac, char **av, t_main *main_program);
void	init_threads(t_main *main_program, t_philo *philo, pthread_t *thread);
void	init_mutexes(t_main *main_program, pthread_mutex_t *fork, pthread_mutex_t print_locker);
void	init_philo(t_philo *philo, t_main *main_program, pthread_mutex_t *fork, pthread_mutex_t *print_locker);

void	check_death(t_main *main_program, t_philo *philo);

// GETTERS
void	error_on_alocate(void);
void	*philo_routine(void	*arg);
int		get_is_dead(t_main main_program);

#endif