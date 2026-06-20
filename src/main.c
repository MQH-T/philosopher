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

//     Philosopher 1 and Philosopher 2 both try to grab their forks at the same time.
//     Both may see the forks as available and attempt to pick them up simultaneously, leading to potential conflicts and race conditions.

// OKAY SI JE RESUME JE DOIS UTILISER MUTEX POUR LOCKER LES FORKS CAD LES FOURCHETTES POUR EVITER UNE COURSE ENTRE LEES DEUX THREAD
// MAIS CA N EMPECHE PAS LES DEADLOCKS QUI ARRIVENT LORSQUE UN PHILO ARRIVE PAS A CHOPER LA DEUXIEME FOURCHETTE

// Fork Acquisition Order:
    
//     Even-ID Philosophers (P0, P2): Pick up the left fork first, then the right fork.
//     Odd-ID Philosophers (P1, P3): Pick up the right fork first, then the left fork.

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

// ach fork would have a corresponding mutex that ensures only one philosopher can pick up the fork at a time(initialize two mutexes, mutex_fork1 for F1 and mutex_fork2 for F2) 
// // by using pthread_mutex_init for F1 and pthread_mutex_init for F2
// — DRD: Run with valgrind --tool=drd to check for data races.

// — Helgrind: Run with valgrind --tool=helgrind to find lock issues and potential deadlocks.

// — FSanitise: Compile with -fsanitize=thread to detect threading problems while running.

#include "philo.h"

void* moves(void* arg) 
{
    t_philo *p;

    p = (t_philo *)arg;

    while (1) {
        printf("Philosopher %d is thinking.\n", p->id);
        sleep(1); // Thinking

        printf("Philosopher %d is eating.\n", p->id);
        sleep(1); // Eating

        printf("Philosopher %d is sleeping.\n", p->id);
        sleep(1); // Sleeping
        printf("FINISHED :%d \n", p->id);
    }
}

long get_time_ms(void)
{
    struct timeval tv;
    long    seconds;
    long    microseconds;
    long    milliseconds;

    gettimeofday(&tv, NULL);
    seconds = tv.tv_sec;
    microseconds = tv.tv_usec;
    milliseconds = (seconds * 1000) + (microseconds / 1000);
    gettimeofday(&tv, NULL);
    return (milliseconds);
}

void init_table(t_simulation *table)
{
    int i;
  
    i = 0;

    table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
    table->philos = malloc(sizeof(t_philo) * table->nb_philo);
    table->flag_death = 0;
    pthread_mutex_init(&table->print_mutex, NULL);
    pthread_mutex_init(&table->death_mutex, NULL);

    while (i < table->nb_philo)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < table->nb_philo)
    {
        table->philos[i].id = i + 1;
        table->philos[i].eat_count = 0;
        table->philos[i].left_fork = &table->forks[i];
        table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
        table->philos[i].table = table;
        i++;
    }

}

void launch_philo(t_simulation *table, t_philo *my_philosopher)
{
    int i;
    (void) my_philosopher;
    
    i = 0;
    table->start_time = get_time_ms();
        
    while(i < table->nb_philo)
    {
        table->philos[i].last_meal_time = table->start_time;
        pthread_create(&table->philos[i].thread, NULL, moves, &table->philos[i]); 
        i++;
    }
     while(i < table->nb_philo)
          pthread_join(table->philos[i++].thread,NULL);
  
}
    
    // It’s important to remember that the number of philosophers must be one or more, the eating time must be greater than zero, and the inputs must be numerical values, not characters.
    
int main(int argc, char **argv)
{
    int i;
    t_philo my_philosopher;
    t_simulation table;

    i = 1;
        while(i < argc)
        {
            if ((ft_atoi(argv[argc])) != 1 )
                 {
                    printf("Wrong args please provide 4 unsigned integer!\n");
                    return (-1);
                }
        i++;
        }
        if(argc == 5)
                {
                    table.nb_philo = ft_atoi(argv[1]);
                    my_philosopher.time_to_die = ft_atoi(argv[2]);
                    my_philosopher.time_to_eat = ft_atoi(argv[3]);
                    my_philosopher.time_to_sleep = ft_atoi(argv[4]);
                    init_table(&table);
                    launch_philo(&table, &my_philosopher);
                }
        // pthread_mutex_destroy(&my_philosopher.mutex);
        return 0;
}