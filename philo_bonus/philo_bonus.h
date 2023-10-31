/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/25 11:12:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/31 13:27:43 by vvan-der      ########   odam.nl         */
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
# include <string.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <semaphore.h>

# define ALIVE 0
# define DEATH 1

# define INFINITY 1

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	int		ph_num;
	int		num;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		num_eat;
	long	t_start;
	pid_t	*processes;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*start;
	sem_t	*death;
	sem_t	*saturated;
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
	sem_t	*forks;
	sem_t	*print;
	sem_t	*start;
	sem_t	*death;
	sem_t	*saturated;
};

/*	Cleanup	*/

/*	Initialization */

int		init_semaphores(t_data *data);
t_philo	*init_sjon(t_data *data);
int		fork_process(t_data *data);

/*	Lock functions	*/

/*	Routine	*/

int		sjon_is_born(t_philo *sjon);

/*	Monitoring	*/

bool	poke_sjon(t_philo *sjon);
void	kill_children(pid_t *pids, int amount);
int		wait_for_ending(t_data *d);
void	kill_sjon(t_philo *sjon);
void	simulation_end(t_data *data);

/*	Utility functions	*/

int		ft_philatoi(char *num);
char	*ft_philitoa(int n);
void	*ft_calloc(size_t size);
void	clean_up(t_data *data, t_philo *philo);
void	print_message(t_philo *sjon, char *msg);

/*	Time and sleep	*/

int		get_runtime(long t_start);
long	get_time(void);
void	ft_sleep(t_philo *sjon, long sleep_duration);

#endif
