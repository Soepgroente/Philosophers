/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 13:49:52 by vincent       #+#    #+#                 */
/*   Updated: 2023/09/12 12:47:21 by vvan-der      ########   odam.nl         */
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
	int		num;
	bool	alive;
	int		*left_fork;
	int		*right_fork;
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
	int				*forks;
	pthread_mutex_t	mutex;
}	t_data;

/*	Initialization */

int		create_threads(t_data *d);
int		init_philo(t_data *data, t_philo *philo, int x);
int		parse_input(t_data *data, int argc, char **argv);

/*	Utility functions*/

int		ft_philatoi(char *num);
void	*some_function(void *data);

#endif