/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:15:14 by amashhad          #+#    #+#             */
/*   Updated: 2025/07/05 21:40:05 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	nill_case(char **argv)
{
	long	start_time;

	start_time = 0;
	if (safe_atoi(argv[1]) == 1)
	{
		start_time = time_ms();
		printf("%lldms Philosopher: %d has taken the left fork\n",
			time_ms() - time_ms(), 1);
		printf("%lldms Philosopher: %d is sleeping\n",
			time_ms() - start_time, 1);
		usleep(safe_atoi(argv[2]) * 1000);
		printf("%lldms Philosoper: %d has died\n",
			time_ms() - start_time, 1);
		return (1);
	}
	return (0);
}

static	int	check(t_data *data, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
	{
		fputendl(2, "Incorrect format\n""Required format: ./philo "
			" {(int)no.philos} {(int)time to die.ms}"
			" {(int)time to eat} {(int)time to sleep}"
			" {(int)time to sleep*} (*) is optional");
		return (1);
	}
	if (chk_val(argv))
		return (1);
	if (nill_case(argv))
		return (1);
	data->init_chk = full_initalization(data, argc, argv);
	if (data->init_chk != 0)
		return (1);
	return (0);
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	memset(&data, 0, sizeof(t_data));
	if (check(&data, argv, argc))
		return (1);
	while (i < data.num_philos)
	{
		if (pthread_create(&data.philos[i].thread, NULL,
				philo_routine, &data.philos[i]) != 0)
		{
			fputendl(2, "Error creating philosopher thread");
			free_all(&data);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, &data) != 0)
		return (free_all(&data));
	join_threads(&data);
	pthread_join(monitor_thread, NULL);
	free_all(&data);
	return (0);
}
