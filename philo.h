/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 13:49:52 by vincent       #+#    #+#                 */
/*   Updated: 2023/09/12 20:38:04 by vvan-der      ########   odam.nl         */
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

typedef struct s_philo
{
	int				num;
	int				num_eaten;
	bool			alive;
	bool			*left_fork;
	bool			*right_fork;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_data
{
	int				ph_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	int				x;
	int				num;
	bool			*forks;
}	t_data;

/*	Initialization */

int		create_threads(t_data *d);
int		init_philo(t_data *data, t_philo *philo, int x);
int		parse_input(t_data *data, int argc, char **argv);

/*	Utility functions*/

int		ft_philatoi(char *num);
int		start_routine(t_data *data);

#endif
