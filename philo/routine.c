/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 20:55:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/13 15:54:11 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	reconsider_life_choices(t_philo *henk)
{
	if (poke_henk(henk) == false)
		return ;
	print_message(henk, &henk->data->print_lock, "is thinking\n");
	// usleep(henk->t_die / 1000);
}

static void	after_dinner_dip(t_data *data, t_philo *henk)
{
	if (poke_henk(henk) == true)
	{
		print_message(henk, &henk->data->print_lock, "is sleeping\n");
		power_naps(henk, data->t_sleep * 1000);
	}
}

static void	eat_sleep_repeat(t_data *data, t_philo *henk)
{
	while (INFINITY)
	{
		if (poke_henk(henk) == false)
			return ;
		if (take_forks(henk) == -1)
			return ;
		eat_foods(henk);
		return_forks(henk);
		after_dinner_dip(data, henk);
		reconsider_life_choices(henk);
	}
}

void	*henk_is_born(void *input)
{
	t_philo	*henk;

	henk = (t_philo *) input;
	pthread_mutex_lock(&henk->data->start);
	pthread_mutex_unlock(&henk->data->start);
	henk->t_start = henk->data->t_start;
	print_message(henk, &henk->data->print_lock, "is thinking\n");
	if (henk->num % 2 == 1)
		usleep(2000);
	eat_sleep_repeat(henk->data, henk);
	return (NULL);
}
