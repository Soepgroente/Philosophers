/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 13:49:52 by vincent       #+#    #+#                 */
/*   Updated: 2023/10/06 19:02:16 by vvan-der      ########   odam.nl         */
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

# define AVAILABLE 0
# define TAKEN 1

# define NONE 0
# define KILL 1

# define ALIVE 0
# define DEATH 1

# define INFINITY 1

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;
typedef struct s_fork	t_fork;

struct s_fork
{
	pthread_mutex_t	lock;
	bool			fork;
};

struct s_data
{
	int				ph_num;
	long			t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	int				num;
	long			t_start;
	pthread_mutex_t	lock;
	pthread_mutex_t	print_lock;
	t_fork			*forks;
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
	pthread_mutex_t	life_lock;
	pthread_mutex_t	food_lock;
	t_fork			*fork1;
	t_fork			*fork2;
	t_data			*data;
};

/*	Initialization */

int		run_threads(t_data *data, t_philo *philos);
int		init_structs(t_data *data);
void	*henk_is_born(void *d);

/*	Lock functions	*/

bool	check_if_saturated(t_philo *henk, pthread_mutex_t *lock);
bool	poke_henk(t_philo *henk, pthread_mutex_t *lock, bool action);
void	eat_foods(t_philo *henk);
void	take_forks(t_philo *henk);

/*	Monitoring	*/

void	stalk_philos(t_data *d);

/*	Utility functions	*/

int		ft_philatoi(char *num);
void	clean_up(t_data *data);
void	print_message(t_philo *henk, pthread_mutex_t *lock, char *msg);

/*	Time and sleep	*/

int		get_runtime(long t_start);
long	get_time(void);
void	ft_sleep(t_philo *henk, long sleep_duration);

#endif
