#ifndef PHILO_H
# define PHILO_H


#include <time.h>

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>


typedef struct s_philo t_philo;

typedef struct s_simulation
{
  int nb_philo;
  int number_of_times_each_philosopher_must_eat;
  long  start_time;

  t_philo         *philos;       // tableau de N philos (malloc)
  pthread_mutex_t *forks;        // tableau de N mutexes (malloc)
  int             flag_death;

  pthread_mutex_t print_mutex;
  pthread_mutex_t death_mutex;
 
} t_simulation;


typedef struct s_philo{
    int id;
    long last_meal_time;
    int eat_count;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    pthread_t       thread;
    pthread_mutex_t mutex;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_simulation         *table;   
} t_philo;



int	ft_isdigit(int c);
int	ft_atoi(const char *str);
int	is_space(char c);

#endif