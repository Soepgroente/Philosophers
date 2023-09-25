/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/25 10:55:18 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	reconsider_life_choices(t_philo *henk)
{
	if (poke_henk(henk, henk->lock, NONE) == false)
		return ;
	print_message(henk, "is thinking\n");
}

static void	after_dinner_dip(t_data *data, t_philo *henk)
{
	if (poke_henk(henk, henk->lock, NONE) == true)
	{
		print_message(henk, "is sleeping\n");
		ft_sleep(henk, data->t_sleep * 1000);
	}
}

static void	eat_foods(t_philo *henk)
{
	if (poke_henk(henk, henk->lock, NONE) == false)
		return ;
	sem_wait(henk->forks);
	sem_wait(henk->forks);
	print_message(henk, "has taken a fork\n");
	print_message(henk, "has taken a fork\n");
	check_last_eaten(henk, henk->eat, true);
	print_message(henk, "is eating\n");
	check_if_saturated(henk, henk->eat2, true);
	ft_sleep(henk, henk->data->t_sleep * 1000);
	sem_post(henk->forks);
	sem_post(henk->forks);
}

static void	eat_sleep_repeat(t_data *data, t_philo *henk)
{
	while (INFINITY)
	{
		if (poke_henk(henk, henk->lock, NONE) == false)
			return ;
		eat_foods(henk);
		after_dinner_dip(data, henk);
		reconsider_life_choices(henk);
	}
}

void	*start_routine(void *input)
{
	t_philo	*henk;

	henk = (t_philo *) input;
	if (henk->num % 2 == 1)
		usleep(1000);
	eat_sleep_repeat(henk->data, henk);
	return (NULL);
}
