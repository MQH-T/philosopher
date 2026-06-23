// Any state change of a philosopher must be formatted as follows:
// ◦ timestamp_in_ms X has taken a fork
// // ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died
// Replace timestamp_in_ms with the current timestamp in milliseconds
// and X with the philosopher number
// ICI SI JE COMPREND BIEN CHQAUE THREAD PEUT FAIRE UNE TACHE DIFFERENTE C CELA QU IL FAUT RETENIR TOUT COMME A UNE TABLE CHAQUE INVITE FAIT QUELQUE CHOSE DE DIFFERENT
// Example with Mutex

//     Philosopher 1 wants to eat:
//     Locks Fork 1 (left).
//     Locks Fork 2 (right).
//     Eats.
//     Unlocks Fork 1.
//     Unlocks Fork 2.
//     Philosopher 2 can only attempt to lock their forks after Philosopher 1 has unlocked them

// Example without Mutex

//
//     Philosopher 1 and Philosopher 2 both try to grab their forks at the same time.
//
//     Both may see the forks as available and attempt to pick them up simultaneously,
// 	leading to potential conflicts and race conditions.

//
// OKAY SI JE RESUME JE DOIS UTILISER MUTEX POUR LOCKER LES FORKS CAD LES FOURCHETTES POUR EVITER UNE COURSE ENTRE LEES DEUX THREAD
//
// MAIS CA N EMPECHE PAS LES DEADLOCKS QUI ARRIVENT LORSQUE UN PHILO ARRIVE PAS A CHOPER LA DEUXIEME FOURCHETTE

// // Fork Acquisition Order:

// //     Even-ID Philosophers (P0, P2): Pick up the left fork first,
// 	then the right fork.
// //     Odd-ID Philosophers (P1, P3): Pick up the right fork first,
// 	then the left fork.

// ATTENTION CELA NE SUFFIT PAS IL FAUT AUSSI METTRE UNE TIME LIMIT POUR EVITER DE MONOPOLISER
// AVEC CES STRATEGIES ON EVITE LES DEADLOCKS

// STRATEGIES ENCORE PLUS SAFE METTRE UN SERVEUR QUI DONNE LES AUTORISATIONS
// timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died
// Replace timestamp_in_ms with the current timestamp in milliseconds
// and X with the philosopher number

//
// ach fork would have a corresponding mutex that ensures only one philosopher can pick up the fork at a time(initialize two mutexes,
// 	mutex_fork1 for F1 and mutex_fork2 for F2)
// // // by using pthread_mutex_init for F1 and pthread_mutex_init for F2
// // — DRD: Run with valgrind --tool=drd to check for data races.

//
// — Helgrind: Run with valgrind --tool=helgrind to find lock issues and potential deadlocks.

// // — FSanitise: Compile with
// 	-fsanitize=thread to detect threading problems while running.

#include "philo.h"

void	init_table(t_simulation *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	table->flag_death = 0;
	pthread_mutex_init(&table->print_mutex, NULL); 
	pthread_mutex_init(&table->death_mutex, NULL);
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL); //pthread_mutex_init sur chaque fourchette (tableau de N mutexes), plus le mutex print, plus le mutex d'état.
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{ 
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];//les philos partagent les fourchettes
		table->philos[i].table = table;
		i++;
	}
}

void end_philosophers(t_simulation *table)
{
	int i;
	(void) table;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
}

int	main(int argc, char **argv)
{
	int i;
	t_simulation table;

	i = 1;

	if (argc == 5  || argc == 6)
	{
		
		while (i < argc)
		{
			if ((ft_isnbr(argv[argc])) != 1)
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
		if(argv[5])
			table.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		init_table(&table);
		launch_philo(&table); //il faut que my philo pointe sur table?
		
	}
	
	return (0);
}