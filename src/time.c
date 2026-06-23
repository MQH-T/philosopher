/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran <mtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 17:05:55 by mtran             #+#    #+#             */
/*   Updated: 2026/06/23 18:20:56 by mtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			seconds;
	long			microseconds;
	long			milliseconds;

	gettimeofday(&tv, NULL);
	seconds = tv.tv_sec;
	microseconds = tv.tv_usec;
	milliseconds = (seconds * 1000) + (microseconds / 1000);
	gettimeofday(&tv, NULL);
	return (milliseconds);
}

void	my_usleep(long ms, t_philo *philos)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
	{
		if (death_copy(philos->table) == 1)
			break ;
		if (ms - (get_time_ms() - start) >= 1)
			usleep(500);
	}
}

void	flag_meals(t_simulation *table)
{
	pthread_mutex_lock(&table->death_mutex);
	table->flag_death = 1;
	pthread_mutex_unlock(&table->death_mutex);
}

void	monitor(t_simulation *table)
{
	int		i;
	long	last_time_cpy;

	while (death_copy(table) != 1)
	{
		i = 0;
		if (monitor_meals(table) == 1)
			flag_meals(table);
		while (i < table->nb_philo)
		{
			pthread_mutex_lock(&table->philos[i].personal_mutex);
			last_time_cpy = table->philos[i].last_meal_time;
			pthread_mutex_unlock(&table->philos[i].personal_mutex);
			if (table->time_to_die <= get_time_ms() - last_time_cpy)
			{
				pthread_mutex_lock(&table->death_mutex);
				table->flag_death = 1;
				pthread_mutex_unlock(&table->death_mutex);
				print_status(table, &table->philos[i], "died");
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}

int	monitor_meals(t_simulation *table)
{
	int	i;
	int	stock;

	stock = table->number_of_times_each_philosopher_must_eat;
	i = 0;
	if (stock != -1)
	{
		while (i < table->nb_philo)
		{
			pthread_mutex_lock(&table->philos[i].personal_mutex);
			if (table->philos[i].eat_count < stock)
			{
				pthread_mutex_unlock(&table->philos[i].personal_mutex);
				return (0);
			}
			pthread_mutex_unlock(&table->philos[i].personal_mutex);
			i++;
		}
	}
	else if (stock == -1)
		return (0);
	return (1);
}
