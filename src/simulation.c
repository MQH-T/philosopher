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
		// my_usleep(100,table->philos);
		if (table->philos->id % 2 == 0)
		{
			table->philos->first_fork = table->philos->left_fork;
			table->philos->first_fork = table->philos->right_fork;
		}
		else
		{
			table->philos->first_fork = table->philos->right_fork;
			table->philos->first_fork = table->philos->left_fork;
		}	
	}
	monitor(table);
	i = 0;
	while (i < table->nb_philo)
		pthread_join(table->philos[i++].thread, NULL);
	end_philosophers(table);
}
void odd_philosophers(t_philo	*philos)
{
	(void) philos;
	return;
}


void	*moves(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (philos->table->flag_death == 1)
			break;
		print_status(philos->table, philos, "is thinking");
		my_usleep(1,philos);

		//prendre les fourchettes
		pthread_mutex_lock(philos->first_fork);
		print_status(philos->table, philos, "has taken a fork");
		pthread_mutex_lock(philos->second_fork);
		print_status(philos->table, philos, "has taken a fork");
		
		print_status(philos->table, philos, "is eating");
		pthread_mutex_lock(&philos->personal_mutex);
		philos->last_meal_time = get_time_ms();
		my_usleep(philos->table->time_to_eat,philos);
		pthread_mutex_unlock(&philos->personal_mutex);
		philos->eat_count++;
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		
		print_status(philos->table, philos, "is sleeping");
		my_usleep(philos->table->time_to_sleep,philos);
	}
	return NULL;
}

void	monitor(t_simulation *table)
{
	int i;

	i = 0;
	if (table->nb_philo == 1)
	{
		print_status(table, table->philos, "died");
		pthread_mutex_unlock(&table->print_mutex);
		return;
	}
	while (table->flag_death != 1)
	{
		while (i < table->nb_philo)
		{
			if (table->time_to_die < get_time_ms() - table->philos[i].last_meal_time)
			{
				pthread_mutex_lock(&table->death_mutex);
				table->flag_death = 1;
				pthread_mutex_unlock(&table->death_mutex);
				print_status(table, table->philos, "died");
				return;
			}
			i++;
		}
		my_usleep(100,table->philos);
	}
}

		// if (table->philos->id % 2 == 0)
		// {
  		// 	my_usleep(150,table->philos);
		// 	odd_philosophers(table->philos);
		// }