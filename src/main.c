/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran <mtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 17:05:38 by mtran             #+#    #+#             */
/*   Updated: 2026/06/23 17:51:55 by mtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_simulation *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
		table->philos[i].table = table;
		pthread_mutex_init(&table->philos[i].personal_mutex, NULL);
		if (table->philos[i].id % 2 == 0)
		{
			table->philos[i].first_fork = table->philos[i].left_fork;
			table->philos[i].second_fork = table->philos[i].right_fork;
		}
		else
		{
			table->philos[i].first_fork = table->philos[i].right_fork;
			table->philos[i].second_fork = table->philos[i].left_fork;
		}
		i++;
	}
}

void	init_table(t_simulation *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	table->flag_death = 0;
	table->number_of_times_each_philosopher_must_eat = -1;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	init_forks(table);
}

void	end_philosophers(t_simulation *table)
{
	int	i;

	(void)table;
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philos);
}

void	print_status(t_simulation *table, t_philo *my_philo, char *msg)
{
	long	start;

	if (death_copy(table) == 1 && ft_strncmp(msg, "died", 4))
		return ;
	start = get_time_ms();
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %d %s\n", start - table->start_time, my_philo->id, msg);
	pthread_mutex_unlock(&table->print_mutex);
}

int	main(int argc, char **argv)
{
	t_simulation	table;
	int				i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (i < argc)
		{
			if ((ft_isnbr(argv[i])) != 1)
			{
				printf("Wrong args please provide 4 unsigned integer!\n");
				return (-1);
			}
			i++;
		}
		table.nb_philo = ft_atoi(argv[1]);
		table.time_to_die = ft_atoi(argv[2]);
		table.time_to_eat = ft_atoi(argv[3]);
		table.time_to_sleep = ft_atoi(argv[4]);
		init_table(&table);
		if (argv[5])
			table.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		launch_philo(&table);
	}
	return (0);
}
