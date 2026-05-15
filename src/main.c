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

// ach fork would have a corresponding mutex that ensures only one philosopher can pick up the fork at a time(initialize two mutexes, mutex_fork1 for F1 and mutex_fork2 for F2) 
// // by using pthread_mutex_init for F1 and pthread_mutex_init for F2
// — DRD: Run with valgrind --tool=drd to check for data races.

// — Helgrind: Run with valgrind --tool=helgrind to find lock issues and potential deadlocks.

// — FSanitise: Compile with -fsanitize=thread to detect threading problems while running.

#include "philo.h"

void* philosopher(void* arg) 
{
    int id;

    id = *(int *)arg;
    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); // Thinking

        printf("Philosopher %d is eating.\n", id);
        sleep(1); // Eating

        printf("Philosopher %d is sleeping.\n", id);
        sleep(1); // Sleeping
        printf("FINISHED :%d \n", id);
    }
}

void launch_philo(char **argv)
{
    t_philo philo;
    long    seconds;
    long    microseconds;
    long    milliseconds;
    struct timeval tv;
    pthread_t  thread1;
    pthread_t  thread2;
    int ids[2] = {1,2};

    (void)argv;

    gettimeofday(&tv, NULL);
    seconds = tv.tv_sec;
    microseconds = tv.tv_usec;
    memset(&philo, 0, sizeof(philo));
    printf("id %d last meal %ld eat count %d\n", philo.id,
    philo.last_meal_time,
    philo.eat_count);
    milliseconds = (seconds * 1000) + (microseconds / 1000);
    usleep(TIME_TO_EAT * 1000);
    printf("milliseconds %li\n", milliseconds);
    printf("gettimeofday :%i \n",
    gettimeofday(&tv, NULL));

    pthread_create(&thread1, NULL, philosopher, &ids[0]); 
    pthread_create(&thread2, NULL, philosopher, &ids[1]);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    printf("fini\n");
}


// It’s important to remember that the number of philosophers must be one or more, the eating time must be greater than zero, and the inputs must be numerical values, not characters.

int main(int argc, char **argv)
{
    int i;

    // i = 1;
    // while(i < argc)
    // {
    //     if (ft_isdigit() != 1)
    //     {
                
    //          printf("Wrong args please provide 4 unsigned integer!\n");
    //          return (-1);
    //     }
    //     i++;
    // }
    i = 0;
    
    ft_atoi(argv[i]);
    if(argc == 5)
        launch_philo(argv);
 return 0;
}
