// ft_usleep

// get_current_time

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			seconds;
	long			microseconds;
	long			milliseconds;

	gettimeofday(&tv, NULL);
	seconds = tv.tv_sec;
	microseconds = tv.tv_usec;
	milliseconds = (seconds * 1000) + (microseconds / 1000);
	gettimeofday(&tv, NULL);
	return (milliseconds);
}

void print_status(t_simulation *table, t_philo *my_philo, char *msg)
{
	long start;

	start = get_time_ms();
    pthread_mutex_lock(&table->print_mutex);
    printf("%ld %d %s\n",start - table->start_time , my_philo->id, msg);
    pthread_mutex_unlock(&table->print_mutex);
}

void my_usleep(long ms)
{
    long start;

    start = get_time_ms();
    while (get_time_ms() - start < ms)
    {
        usleep(50);
    }
}