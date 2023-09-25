/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 11:12:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/25 11:14:37 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <ctype.h>
# include <pthread.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <semaphore.h>

# define AVAILABLE 0
# define TAKEN 1

# define NONE 0
# define KILL 1

# define INFINITY 1

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	int		ph_num;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		num_eat;
	int		num;
	long	t_start;
	int		i;
	sem_t	*forks;
	sem_t	*print;
	t_philo	*philos;
};

struct s_philo
{
	int		num;
	int		num_eaten;
	int		max_eat;
	int		last_eaten;
	int		t_eat;
	int		t_think;
	int		t_die;
	long	t_start;
	bool	alive;
	bool	saturated;
	sem_t	*eat;
	sem_t	*eat2;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*lock;
	t_data	*data;
};

/*	Initialization */

int		run_threads(t_data *data, t_philo *philos);
int		init_structs(t_data *data);
void	*start_routine(void *d);

/*	Lock functions	*/

bool	check_last_eaten(t_philo *henk, sem_t *lock, bool eaten);
bool	check_if_saturated(t_philo *henk, sem_t *lock, bool eaten);
bool	poke_henk(t_philo *henk, sem_t *lock, bool action);

/*	Monitoring	*/

void	stalk_philos(t_data *d);

/*	Utility functions	*/

int		ft_philatoi(char *num);
char	*ft_philitoa(int n);
void	clean_up(t_data *data);
void	print_message(t_philo *henk, char *msg);

/*	Time and sleep	*/

int		get_runtime(long t_start);
long	get_time(void);
void	ft_sleep(t_philo *henk, long sleep_duration);

#endif
