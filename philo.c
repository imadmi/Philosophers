#include "philosophers.h"

int	ft_is_digit(int c)
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

int	print_error(char *str)
{
	printf("\033[1m\033[31m%s\n",str);
	return (1);
}

void	print_state(t_info *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lu\t%d %s\n", get_time() - philo->data->currnt_time,\
		philo->philo_nbr, str);
	pthread_mutex_unlock(&philo->data->print);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(t_info *philo)
{
	print_state(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 994);
}

void	ft_thinking(t_info *philo)
{
	print_state(philo, THINKING);
}

void	ft_eat(t_info *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->philo_nbr - 1]);
	pthread_mutex_lock(&philo->data->forks[philo->philo_nbr \
		% philo->data->nbr_of_philo]);
	print_state(philo, FORK);
	print_state(philo, FORK);
	print_state(philo, EATING);
	usleep(philo->data->time_to_eat * 994);
	pthread_mutex_lock(&philo->data->change);
	philo->data->last_time_eating[philo->philo_nbr - 1] = get_time();
	pthread_mutex_unlock(&philo->data->change);
	pthread_mutex_unlock(&philo->data->forks[philo->philo_nbr \
		% philo->data->nbr_of_philo]);
	pthread_mutex_unlock(&philo->data->forks[philo->philo_nbr - 1]);
}

void	*thread_executer(void *arg)
{
	t_info	*philo;

	philo = (t_info *)arg;
	if (!(philo->philo_nbr % 2 == 1))
		usleep(1000);
	while (1)
	{
		ft_eat(philo);
		pthread_mutex_lock(&philo->data->change);
		philo->ate++;
		if (philo->data->number_of_times_each_philosopher_must_eat != -1)
		{
			if (philo->ate > philo->data->number_of_times_each_philosopher_must_eat)
			{
				philo->data->die = ALIVE;
				pthread_mutex_unlock(&philo->data->change);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&philo->data->change);
		ft_sleep(philo);
		ft_thinking(philo);
		usleep(1000);
	}
	return (NULL);
}

void	check_death(t_info *philo)
{
	size_t  i;
	
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->change);
		if (get_time() - philo[i % philo->data->nbr_of_philo].data->last_time_eating[philo->philo_nbr - 1] \
			> (size_t)philo[i % philo->data->nbr_of_philo].data->time_to_die)
		{
			if (philo[i % philo->data->nbr_of_philo].data->die == DEAD)
			{
				pthread_mutex_lock(&philo[i % philo->data->nbr_of_philo].data->print);
				printf("%zu\t%d ", get_time() - philo[i % philo->data->nbr_of_philo].data->currnt_time, \
					philo[i % philo->data->nbr_of_philo].philo_nbr);
				print_error("died");
				return ;
			}
			pthread_mutex_unlock(&philo->data->change);
			return ;
		}
		i++;
		pthread_mutex_unlock(&philo->data->change);
		// usleep(1000);
	}
}

void	ft_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		data->last_time_eating[data->philos->philo_nbr - 1] = get_time();
		pthread_create(&data->philos[i].thread_id, NULL, &thread_executer, &data->philos[i]);
		i++;
	}

	return ;
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (4 < ac && ac < 7)
		while (av[++i])
		{
			if (ft_atoi(av[i]) < 0 && !ft_is_digit(ft_atoi(av[i])))
				return (print_error("Input error"));
		}
	else
		return (print_error(ERR_USAGE));
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
}

void	init_mutex(t_data *data)
{
	int	i;
	
	i = 0;
	data->die = DEAD;
	while (i < data->nbr_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			print_error("mutex error");
		data->philos[i].data = data;
		data->philos[i].ate = 1;
		data->philos[i].philo_nbr = i + 1;
		i++;
	}
	data->currnt_time = get_time();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->change, NULL);
}

int	init_data(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
	if (!data->forks)
		return print_error("malloc error");
	data->philos = malloc(sizeof(t_info) * data->nbr_of_philo);
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
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->change);
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

void	ft_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo && data->die != DEAD)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

int	main(int ac, char *av[])
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
	ft_thread(data);
	check_death(data->philos);
	ft_join(data);
	ft_free(data);
	return (0);
}
