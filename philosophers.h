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

# define false 0
# define true 1

# define SUCCES 0
# define FAILURE 1

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"

typedef struct philo
{
	struct s_data	*data;
	int				is_eat;
	int				is_die;
	int				philo_nbr;
	pthread_t		thread_id;
	pthread_t 		check_death_thread;
}t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	mutex;
	pthread_mutex_t	change;
	pthread_mutex_t	*forks;
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	size_t		currnt_time;
	size_t		*last_time_eating;
	int				die;
}t_data;

size_t	get_time(void);
void		ft_usleep(int time);
int			ft_atoi(char *str);
int			check_args(int ac, char **av);
void		get_args(int ac, char **av, t_data *data);
int			init_data(t_data *data);
void		*ft_init_philo(t_data *data);
void		print_state(t_philo *philo, char *s);
void		*check_death(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_thinking(t_philo *philo);
void		ft_free(t_data *data);


#endif