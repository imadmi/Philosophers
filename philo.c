#include "philosophers.h"


void	print_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex);
	printf("%lu %d %s\n", get_time() - philo->data->currnt_time, philo->philo_nbr, str);
	pthread_mutex_unlock(&philo->data->mutex);
}

void	ft_usleep(int time)
{
	usleep(time * 990);
	// usleep(time * 1000);
	// size_t	start = get_time();
	// while(get_time() < (time + start))
	// 	usleep(1000);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int		ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = sign * -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (num * sign);
}

void	ft_sleep(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	ft_thinking(t_philo *philo)
{
	print_state(philo, "is thinking");
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->philo_nbr - 1]);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->philo_nbr % philo->data->nbr_of_philo]);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->change);
	philo->data->last_time_eating[philo->philo_nbr - 1] = get_time();
	pthread_mutex_unlock(&philo->data->change);
	pthread_mutex_unlock(&philo->data->forks[philo->philo_nbr % philo->data->nbr_of_philo]);
	pthread_mutex_unlock(&philo->data->forks[philo->philo_nbr - 1]);
}

void	*thread_executer(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->philo_nbr % 2))
		usleep(1000);
	while (1)
	{
		ft_eat(philo);
		pthread_mutex_lock(&philo->data->change);
		// pthread_mutex_lock(&philo->data->mutex);
		philo->is_eat++;
		if (philo->data->number_of_times_each_philosopher_must_eat != -1)
		{
			if (philo->is_eat > philo->data->number_of_times_each_philosopher_must_eat)
			{
				philo->data->die = ALIVE;
				pthread_mutex_unlock(&philo->data->change);
				// pthread_mutex_unlock(&philo->data->mutex);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&philo->data->change);
		// pthread_mutex_unlock(&philo->data->mutex);
		ft_sleep(philo);
		ft_thinking(philo);
		usleep(100);
	}
	return (NULL);
}

void	*check_death(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->change);
		if (get_time() - philo->data->last_time_eating[philo->philo_nbr - 1] \
		> (size_t)philo->data->time_to_die)
		{
			if (philo->data->die == 0)
			{
				pthread_mutex_lock(&philo->data->mutex);
				printf("%lu %d %s\n", get_time() - philo->data->currnt_time, philo->philo_nbr, "died");
				return (NULL);
			}
			pthread_mutex_unlock(&philo->data->change);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->change);
		usleep(1000);
	}
	return (NULL);
}

void	*ft_init_philo(t_data *data)
{
	int	i;
	i = 0;

	while (i < data->nbr_of_philo)
	{
		data->last_time_eating[data->philos->philo_nbr - 1] = get_time();
		pthread_create(&data->philos[i].thread_id, NULL, &thread_executer, &data->philos[i]);
		i++;
	}
	check_death(data->philos);
	i = 0;
	while (i < data->nbr_of_philo && data->die != 0)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	return (NULL);
}

int	print_error(char *str)
{
	printf("\033[0;31m%s\n",str);
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (4 < ac && ac < 7)
		while (av[++i])
		{
			if (ft_atoi(av[i]) < 0 && !ft_is_digit(ft_atoi(av[i])))
				return (printf("\033[0;31mInput error\n"));
		}
	else
		return (printf(ERR_USAGE));
	return (0);
}

void	get_args(int ac, char **av, t_data *data)
{
	data->nbr_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	return ;
}

void	init_mutex(t_data *data)
{
	int i = 0;
	
	data->die = DEAD;
	while (i < data->nbr_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			print_error("mutex error");
		data->philos[i].data = data;
		// data->philos[i].is_die = 0;//
		data->philos[i].is_eat = 1;
		data->philos[i].philo_nbr = i + 1;
		i++;
	}
	data->currnt_time = get_time();
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->change, NULL);
}

int	init_data(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
	if (!data->forks)
		return print_error("malloc error");
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!data->philos)
		return print_error("malloc error");
	data->last_time_eating = malloc (sizeof(size_t) * data->nbr_of_philo);
	if (!data->last_time_eating)
		return print_error("malloc error");
	return 0;
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex);
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
	free(data->last_time_eating);
	free(data);
}


int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data*)malloc(sizeof(t_data));
	if (data == NULL)
		return (0);

	check_args(ac, av);
	get_args(ac, av, data);
	if (data->number_of_times_each_philosopher_must_eat == 0)
		return 0;
	init_data(data);
	init_mutex(data);
	ft_init_philo(data);
	ft_free(data);
	return (0);
}
// int	main(int ac, char **av)
// {
// 	t_data	data;

// 	check_args(ac, av);
// 	get_args(ac, av, &data);
// 	init_data(&data);
// 	init_mutex(&data);
// 	ft_init_philo(&data);
// 	check_death(data.philos);
// 	ft_free(&data);
// }