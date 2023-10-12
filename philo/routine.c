/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 20:55:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/12 21:26:49 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	reconsider_life_choices(t_philo *henk)
{
	if (poke_henk(henk, &henk->life_lock) == false)
		return ;
	print_message(henk, &henk->data->print_lock, "is thinking\n");
	// usleep(henk->t_die / 100);
}

static void	after_dinner_dip(t_data *data, t_philo *henk)
{
	if (poke_henk(henk, &henk->life_lock) == true)
	{
		print_message(henk, &henk->data->print_lock, "is sleeping\n");
		power_naps(henk, data->t_sleep * 1000);
	}
}

static void	eat_sleep_repeat(t_data *data, t_philo *henk)
{
	if (data->ph_num > 1)
	{
		while (INFINITY)
		{
			if (poke_henk(henk, &henk->life_lock) == false)
				return ;
			take_forks(henk);
			after_dinner_dip(data, henk);
			reconsider_life_choices(henk);
		}
	}
	print_message(henk, &data->print_lock, "has taken a fork\n");
}

void	*henk_is_born(void *input)
{
	t_philo	*henk;

	henk = (t_philo *) input;
	pthread_mutex_lock(&henk->data->start);
	pthread_mutex_unlock(&henk->data->start);
	henk->t_start = henk->data->t_start;
	henk->last_eaten = get_time();
	print_message(henk, &henk->data->print_lock, "is thinking\n");
	if (henk->num % 2 == 1)
		usleep(2000);
	eat_sleep_repeat(henk->data, henk);
	return (NULL);
}
