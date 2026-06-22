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
	i = 0;
	while (i < table->nb_philo)
		pthread_join(table->philos[i++].thread, NULL);
	// pthread_join tous les philos.
}

void	*moves(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (philos->table->flag_death == 1)
			return NULL;
		print_status(philos->table, philos, "is thinking");
		my_usleep(1);

		//prendre les fourchettes
		print_status(philos->table, philos, "is eating");
		philos->last_meal_time = get_time_ms();
		my_usleep(philos->table->time_to_eat);
		print_status(philos->table, philos, "is sleeping");
		my_usleep(philos->table->time_to_sleep);
	}
}

void	monitor(t_simulation *table)
{
	int i;

	i = 0;
	while (table->flag_death != 1)
	{
		while (i < table->nb_philo)
		{
			if (table->time_to_die < get_time_ms() - table->philos[i].last_meal_time)
			{
				table->flag_death = 1;
				print_status(table, table->philos, "died");
				end_philosophers(table);
				return;
			}
			i++;
		}
		usleep(100);
	}
}