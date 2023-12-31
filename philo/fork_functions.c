/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 12:57:10 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/02 14:58:24 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sqrt(long num)
{
	long	i;

	i = 0;
	while (i * i < num)
		i++;
	return ((int) i);
}

void	return_forks(t_philo *henk)
{
	pthread_mutex_unlock(henk->fork2);
	pthread_mutex_unlock(henk->fork1);
}

static int	take_fork2(t_philo *henk)
{
	if (poke_henk(henk) == false)
		return (-1);
	if (henk->data->ph_num > 1)
	{
		if (henk->num_eaten != 0)
		{
			if (henk->t_die - (get_time() - henk->last_eaten) > henk->t_eat)
				special_naps(henk);
		}
		pthread_mutex_lock(henk->fork2);
		print_message(henk, &henk->data->print_lock, "has taken a fork\n");
	}
	else
	{
		power_naps(henk, henk->t_die * 10);
		return (-1);
	}
	return (0);
}

int	take_forks(t_philo *henk)
{
	if (poke_henk(henk) == false)
		return (-1);
	if (henk->num_eaten != 0)
	{
		if (henk->t_die - (get_time() - henk->last_eaten) > henk->t_eat)
			special_naps(henk);
	}
	pthread_mutex_lock(henk->fork1);
	print_message(henk, &henk->data->print_lock, "has taken a fork\n");
	if (take_fork2(henk) == -1)
	{
		pthread_mutex_unlock(henk->fork1);
		return (-1);
	}
	return (0);
}
