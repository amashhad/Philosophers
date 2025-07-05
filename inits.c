/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 05:15:39 by amashhad          #+#    #+#             */
/*   Updated: 2025/07/05 21:38:07 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fruther_init_mutexes(t_data *data, int i)
{
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
	{
		reverse_destroy(data, i);
		free(data->forks);
		free(data->forks_init);
		fputendl(2, "Error: print lock mutex init failure");
		return (1);
	}
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_lock);
		reverse_destroy(data, i);
		free(data->forks);
		free(data->forks_init);
		fputendl(2, "Error: death lock mutex init failure");
		return (1);
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		free(data->forks_init);
		fputendl(2, "Error: malloc failed at data->forks");
		return (1);
	}
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			fputendl(2, "Error: forks mutex init failure");
			reverse_destroy(data, i);
			free(data->forks);
			free(data->forks_init);
			return (1);
		}
		i++;
	}
	return (fruther_init_mutexes(data, i));
}

int	init_philos(t_data *data)
{
	data->philos = my_calloc(data->num_philos, sizeof(t_philo));
	if (!data->philos)
	{
		pthread_mutex_destroy(&data->death_lock);
		pthread_mutex_destroy(&data->print_lock);
		reverse_destroy(data, data->num_philos - 1);
		free(data->forks);
		free(data->forks_init);
		fputendl(2, "Error: calloc failed at data->philos");
		return (1);
	}
	if (meals_n_forks(data))
	{
		pthread_mutex_destroy(&data->death_lock);
		pthread_mutex_destroy(&data->print_lock);
		reverse_destroy(data, data->num_philos - 1);
		free(data->forks);
		free(data->forks_init);
		free(data->philos);
		return (1);
	}
	return (0);
}

int	full_initalization(t_data *data, int argc, char **argv)
{
	data->num_philos = safe_atoi(argv[1]);
	data->time_to_die = safe_atoi(argv[2]);
	data->time_to_eat = safe_atoi(argv[3]);
	data->time_to_sleep = safe_atoi(argv[4]);
	if (argc == 6)
		data->meal_cnt = safe_atoi(argv[5]);
	else
		data->meal_cnt = -1;
	data->death_flag = 0;
	data->start_time = time_ms();
	data->forks_init = my_calloc(data->num_philos, sizeof(int));
	if (!data->forks_init)
	{
		fputendl(2, "Error: calloc failed at fork_init");
		return (1);
	}
	data->init_chk = init_mutexes(data);
	if (data->init_chk != 0)
		return (1);
	data->init_chk = init_philos(data);
	if (data->init_chk != 0)
		return (1);
	return (0);
}
