/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 13:49:52 by vincent           #+#    #+#             */
/*   Updated: 2023/09/17 14:52:25 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <ctype.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>

#define AVAILABLE 0
#define TAKEN 1

#define LEFT 0
#define RIGHT 1

#define INFINITY 1

typedef struct s_philo
{
	int				num;
	int				num_eaten;
	int				last_eaten;
	bool			alive;
	bool			*left_fork;
	bool			*right_fork;
	bool			lf;
	bool			rf;
	bool			saturated;
	pthread_mutex_t	lock;
}	t_philo;

typedef struct s_data
{
	int		ph_num;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		num_eat;
	int		x;
	int		num;
	long	start_time;
	bool	*forks;
	bool	ready;
	int		time;
	t_philo	*philos;
}	t_data;

typedef struct s_args
{
	t_data	*data_struct;
	int		num;
}	t_args;

/*	Initialization */

int		create_threads(t_data *d);
void	init_philo(t_data *data, t_philo *philo, int x);
int		parse_input(t_data *data, int argc, char **argv);
void	*start_routine(void *d);

/*	Monitoring	*/

void	stalk_philos(t_data *data);

/*	Utility functions	*/

int		ft_philatoi(char *num);
void	print_forks(t_data *data, bool *forks);

/*	Eat and think	*/

void	eat_foods(t_data *data, t_philo *henk);
void	get_forked(t_data *data, t_philo *henk);
void	take_left_fork(t_data *data, t_philo *henk);
void	take_right_fork(t_data *data, t_philo *henk);

/*	Time and sleep	*/

long	get_time(void);
void	ft_sleep(long sleep_duration);
void	after_dinner_dip(t_data *data, t_philo *henk);

#endif
