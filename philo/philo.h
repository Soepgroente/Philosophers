/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 13:49:52 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/15 19:57:32 by vincent       ########   odam.nl         */
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

# define ALIVE 0
# define DEATH 1

# define INFINITY 1

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	int				ph_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	int				num;
	long			t_start;
	pthread_mutex_t	start;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		*threads;
};

struct s_philo
{
	int				num;
	int				num_eaten;
	int				max_eat;
	long			last_eaten;
	int				t_eat;
	int				t_think;
	long			t_die;
	long			t_start;
	bool			alive;
	bool			saturated;
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	t_data			*data;
};

/*	Cleaning up	*/

void	clean_up(t_data *data);
void	destroy_forks(pthread_mutex_t *forks, int num);

/*	Initialization */

int		thread_carefully(t_data *data, t_philo *philos);
int		init_structs(t_data *data);
void	*henk_is_born(void *d);

/*	Lock functions	*/

bool	check_if_saturated(t_philo *henk, pthread_mutex_t *lock);
bool	poke_henk(t_philo *henk);
void	eat_foods(t_philo *henk);
int		take_forks(t_philo *henk);
void	return_forks(t_philo *henk);
void	kill_henk(t_philo *henk, pthread_mutex_t *life_lock);

/*	Monitoring	*/

void	stalk_philos(t_data *d);

/*	Utility functions	*/

int		ft_philatoi(char *num);
void	print_message(t_philo *henk, pthread_mutex_t *lock, char *msg);

/*	Time and sleep	*/

int		get_runtime(long t_start);
long	get_time(void);
void	power_naps(t_philo *henk, long sleep_duration);

#endif
