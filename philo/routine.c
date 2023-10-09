/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/09 10:58:45 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	reconsider_life_choices(t_philo *henk)
{
	if (poke_henk(henk, &henk->life_lock, NONE) == false)
		return ;
	print_message(henk, &henk->data->print_lock, "is thinking\n");
}

static void	after_dinner_dip(t_data *data, t_philo *henk)
{
	if (poke_henk(henk, &henk->life_lock, NONE) == true)
	{
		print_message(henk, &henk->data->print_lock, "is sleeping\n");
		ft_sleep(henk, data->t_sleep * 1000);
	}
}

static void	eat_sleep_repeat(t_data *data, t_philo *henk)
{
	while (INFINITY)
	{
		if (poke_henk(henk, &henk->life_lock, NONE) == false)
			return ;
		take_forks(henk);
		after_dinner_dip(data, henk);
		reconsider_life_choices(henk);
	}
}

void	*henk_is_born(void *input)
{
	t_philo	*henk;

	henk = (t_philo *) input;
	print_message(henk, &henk->data->print_lock, "is thinking\n");
	if (henk->num % 2 == 1)
		usleep(2000);
	eat_sleep_repeat(henk->data, henk);
	return (NULL);
}
