/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran <mtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 17:09:43 by mtran             #+#    #+#             */
/*   Updated: 2026/06/23 18:25:38 by mtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_philo(t_simulation *table)
{
	int	i;

	i = 0;
	table->start_time = get_time_ms();
	while (i < table->nb_philo)
	{
		table->philos[i].last_meal_time = table->start_time;
		pthread_create(&table->philos[i].thread, NULL, moves,
			&table->philos[i]);
		i++;
	}
	monitor(table);
	i = 0;
	while (i < table->nb_philo)
		pthread_join(table->philos[i++].thread, NULL);
	end_philosophers(table);
}

void	only_one_philo(t_philo *philos)
{
	print_status(philos->table, philos, "is thinking");
	my_usleep(1, philos);
	pthread_mutex_lock(philos->first_fork);
	print_status(philos->table, philos, "has taken a fork");
	pthread_mutex_unlock(philos->first_fork);
	return ;
}

void	lock_moves(t_philo *philos)
{
	print_status(philos->table, philos, "is thinking");
	if (philos->table->nb_philo % 2 != 0)
		my_usleep(2, philos);
	pthread_mutex_lock(philos->first_fork);
	print_status(philos->table, philos, "has taken a fork");
	pthread_mutex_lock(philos->second_fork);
	print_status(philos->table, philos, "has taken a fork");
	print_status(philos->table, philos, "is eating");
	pthread_mutex_lock(&philos->personal_mutex);
	philos->last_meal_time = get_time_ms();
	philos->eat_count++;
	pthread_mutex_unlock(&philos->personal_mutex);
	my_usleep(philos->table->time_to_eat, philos);
	pthread_mutex_unlock(philos->first_fork);
	pthread_mutex_unlock(philos->second_fork);
	print_status(philos->table, philos, "is sleeping");
	my_usleep(philos->table->time_to_sleep, philos);
}

void	*moves(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->table->nb_philo == 1)
	{
		only_one_philo(philos);
		return (NULL);
	}
	if (philos->id % 2 == 0)
		my_usleep(philos->table->time_to_eat / 10, philos);
	while (1)
	{
		if (death_copy(philos->table) == 1)
			break ;
		lock_moves(philos);
	}
	return (NULL);
}

int	death_copy(t_simulation *table)
{
	int	flag_copy;

	pthread_mutex_lock(&table->death_mutex);
	flag_copy = table->flag_death;
	pthread_mutex_unlock(&table->death_mutex);
	return (flag_copy);
}
