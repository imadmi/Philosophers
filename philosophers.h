#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>


# define ERR_USAGE "\033[0;31mUsage: ./philo <nbr of philosophers> <time to die> <time to eat>\
 <time to sleep> [times each philosopher must eat]\n"

# define DEAD 0
# define ALIVE 1

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"

typedef struct s_info
{
	struct s_data		*data;
	pthread_t 			check_death_thread;
	pthread_t			thread_id;
	int					ate;
	int					philo_nbr;
}	t_info;

typedef struct s_data
{
	pthread_mutex_t		print;
	pthread_mutex_t		change;
	pthread_mutex_t		*forks;
	size_t				currnt_time;
	size_t				*last_time_eating;
	int					nbr_of_philo;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					die;
	int					number_of_times_each_philosopher_must_eat;
	t_info				*philos;
}	t_data;

size_t		get_time(void);

#endif