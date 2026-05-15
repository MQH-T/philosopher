#ifndef PHILO_H
# define PHILO_H



#define TIME_TO_EAT 2000



typedef struct s_philo{
    int id;
    long last_meal_time;
    int eat_count;
} t_philo;

// struct timeval
// {
//     time_t  tv_sec; // seconds 
//     suseconds_t tv_usec; //microseconds
// };


#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <stddef.h>

int	ft_isdigit(int c);
int	ft_atoi(const char *str);
int	is_space(char c);

#endif