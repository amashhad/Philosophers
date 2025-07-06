/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:31:57 by amashhad          #+#    #+#             */
/*   Updated: 2025/07/05 22:08:52 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;
typedef struct s_check	t_check;

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	meal_nb_lock;
	pthread_t		thread;
	int				id;
	long			last_meal;
	int				meals_eaten;
	t_data			*data;
}	t_philo;

struct	s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	long			start_time;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_cnt;
	int				death_flag;
	int				*forks_init;
	int				init_chk;
	t_philo			*philos;
};

long long	time_ms(void);
int			safe_atoi(char *str);
int			meals_n_forks(t_data *data);
int			chk_val(char **str);
int			is_digit(char	*str);
int			full_initalization(t_data *data, int argc, char **argv);
int			init_meals(t_data *data, int i);
int			init_mutexes(t_data *data);
int			death_flag(t_data *data);
int			free_all(t_data *data);
int			nill_case(t_philo *philo);

void		*my_calloc(size_t nmem, size_t size);
void		*philo_routine(void *arg);
void		*monitor(void *arg);
void		set_death_flag(t_data *data);
void		reverse_destroy(t_data *data, int limit);
void		destroy_meals(t_data *data, int limit);
void		safe_print(t_philo *philo, char *msg);
void		eat(t_philo *philo);
void		fputendl(int fd, char *str);
void		fputstr(int fd, char *str);
void		ft_usleep(long long time_in_ms, t_data *data);

#endif
