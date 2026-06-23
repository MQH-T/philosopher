#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

// typedef enum e_way {
// 	LEFT,
// 	RIGHT
// } t_eway;


typedef struct s_philo	t_philo;

typedef struct s_simulation
{
	int					nb_philo;
	int					number_of_times_each_philosopher_must_eat;
	long				start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	int					flag_death;

	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
}						t_simulation;

typedef struct s_philo
{
	int					id;
	long				last_meal_time;
	int					eat_count;
	pthread_t			thread;
	pthread_mutex_t		personal_mutex;
	pthread_mutex_t *left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_simulation		*table;
}						t_philo;

int						ft_isdigit(int c);
int						ft_atoi(const char *str);
int						is_space(char c);
int						ft_isnbr(const char *str);
long					get_time_ms(void);

void					launch_philo(t_simulation *table);
void					end_philosophers(t_simulation *table);
void					*moves(void *arg);
void					print_status(t_simulation *table, t_philo *my_philo,
							char *msg);
void					monitor(t_simulation *table);
void					odd_philosophers(t_philo *philos);
void					my_usleep(long ms, t_philo *my_philo);

#endif