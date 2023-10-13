/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 12:57:10 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/13 15:50:06 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	return_forks(t_philo *henk)
{
	pthread_mutex_unlock(&henk->fork2->lock);
	pthread_mutex_unlock(&henk->fork1->lock);
}

static int	take_fork2(t_philo *henk)
{
	if (poke_henk(henk) == false)
		return (-1);
	if (henk->data->ph_num > 1)
	{
		pthread_mutex_lock(&henk->fork2->lock);
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
	pthread_mutex_lock(&henk->fork1->lock);
	print_message(henk, &henk->data->print_lock, "has taken a fork\n");
	if (take_fork2(henk) == -1)
	{
		pthread_mutex_unlock(&henk->fork1->lock);
		return (-1);
	}
	return (0);
}
