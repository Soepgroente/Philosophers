/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/30 17:08:44 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	reconsider_life_choices(t_philo *henk)
{
	if (poke_henk(henk, &henk->lock, NONE) == false)
		return ;
	print_message(henk, &henk->data->print_lock, "is thinking\n");
	ft_sleep(henk, henk->t_think * 1000);
}

static void	after_dinner_dip(t_data *data, t_philo *henk)
{
	if (poke_henk(henk, &henk->lock, NONE) == true)
	{
		print_message(henk, &henk->data->print_lock, "is sleeping\n");
		ft_sleep(henk, data->t_sleep * 1000);
	}
}

static void	eat_foods(t_philo *henk)
{
	if (poke_henk(henk, &henk->lock, NONE) == false)
		return ;
	print_message(henk, &henk->data->print_lock, "is eating\n");
	pthread_mutex_lock(&henk->lock);
	henk->last_eaten = get_time();
	henk->num_eaten++;
	pthread_mutex_unlock(&henk->lock);
	ft_sleep(henk, henk->t_eat * 1000);
	return_forks(henk->fork1, henk->fork2);
}

static void	eat_sleep_repeat(t_data *data, t_philo *henk)
{
	while (INFINITY)
	{
		if (poke_henk(henk, &henk->lock, NONE) == false)
			return ;
		if (take_first_fork(henk, henk->fork1) == true && \
		take_second_fork(henk, henk->fork2) == true)
		{
			eat_foods(henk);
			after_dinner_dip(data, henk);
			reconsider_life_choices(henk);
		}
		else
			return ;
	}
}

void	*henk_is_born(void *input)
{
	t_philo	*henk;

	henk = (t_philo *) input;
	if (henk->num % 2 == 1)
	{
		print_message(henk, &henk->lock, "is thinking\n");
		usleep(1000);
	}
	eat_sleep_repeat(henk->data, henk);
	return (NULL);
}
