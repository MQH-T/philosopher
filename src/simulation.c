// Une boucle rapide (usleep(100) à usleep(1000)) qui passe sur chaque philo :

// lit last_meal_time sous mutex, calcule get_time_ms() - last_meal_time,
// 	et si c'est > time_to_die → print « died » + lève le flag someone_died
// 	+ on arrête.
//
// vérifie si tous ont atteint nb_meals → on arrête proprement (sans message de mort).
//
// Le print de mort ne passe pas par la même condition que les autres : même si le flag vient de monter,
// 	le « died » doit sortir.

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
	monitor_meals(table);
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

void	*moves(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->table->nb_philo == 1)
	{
		only_one_philo(philos);
		return (NULL);
	}
	while (1)
	{
		if (death_copy(philos->table) == 1)
			break ;
		if (monitor_meals(philos->table) == 1)
			break ;
		print_status(philos->table, philos, "is thinking");
		my_usleep(1, philos);
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
void	monitor(t_simulation *table)
{
	int		i;
	long	last_time_cpy;

	while (death_copy(table) != 1)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			pthread_mutex_lock(&table->philos[i].personal_mutex);
			last_time_cpy = table->philos[i].last_meal_time;
			pthread_mutex_unlock(&table->philos[i].personal_mutex);
			if (table->time_to_die < get_time_ms() - last_time_cpy)
			{
				pthread_mutex_lock(&table->death_mutex);
				table->flag_death = 1;
				pthread_mutex_unlock(&table->death_mutex);
				print_status(table, &table->philos[i], "died");
				return ;
			}
			i++;
		}
		usleep(100);
	}
}

int	monitor_meals(t_simulation *table)
{
	int i;
	i = 0;
	if (table->number_of_times_each_philosopher_must_eat != -1)
	{
		while (i < table->nb_philo)
		{
			pthread_mutex_lock(&table->philos[i].personal_mutex);

			if (table->philos[i].eat_count < table->number_of_times_each_philosopher_must_eat)
			{
				pthread_mutex_unlock(&table->philos[i].personal_mutex);
				return (0);
			}
			pthread_mutex_unlock(&table->philos[i].personal_mutex);
			i++;
		}
	}
	return (1);
}