/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 11:12:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/17 11:14:49 by vvan-der      ########   odam.nl         */
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

# define ALIVE 0
# define DEATH 1

# define INFINITY 1

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	int			ph_num;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			num_eat;
	int			num;
	long		t_start;
	int			i;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*start;
	t_philo		**sjonnies;
};

struct s_philo
{
	int		num;
	int		num_eaten;
	int		max_eat;
	long	last_eaten;
	long	t_eat;
	long	t_sleep;
	long	t_die;
	long	t_start;
	bool	alive;
	bool	saturated;
	char	*sem_id;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*poke;
	t_data	*data;
};

/*	Initialization */

int		init_semaphores(t_data *data);
int		init_sjon(t_data *data, int num);
int		sjon_is_born(t_data *data, int num);

/*	Lock functions	*/

bool	poke_sjon(t_philo *sjon, sem_t *lock);

/*	Monitoring	*/

void	stalk_philos(t_data *d);

/*	Utility functions	*/

int		ft_philatoi(char *num);
char	*ft_philitoa(int n);
void	clean_up(t_data *data);
void	print_message(t_philo *sjon, char *msg);

/*	Time and sleep	*/

int		get_runtime(long t_start);
long	get_time(void);
void	ft_sleep(t_philo *sjon, long sleep_duration);

#endif
