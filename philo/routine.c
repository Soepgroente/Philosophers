/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/25 11:14:37 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	reconsider_life_choices(t_philo *henk)
{
	if (poke_henk(henk, &henk->lock, NONE) == false)
		return ;
	print_message(henk, &henk->data->print_lock, "is thinking\n");
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
	henk->last_eaten = get_runtime(henk->t_start);
	henk->num_eaten++;
	if (henk->num_eaten >= henk->max_eat)
		henk->saturated = true;
	pthread_mutex_unlock(&henk->lock);
	ft_sleep(henk, henk->t_eat * 1000);
	return_forks(henk, henk->fork1, henk->fork2);
}

static void	eat_sleep_repeat(t_data *data, t_philo *henk)
{
	while (INFINITY)
	{
		if (poke_henk(henk, &henk->lock, NONE) == false)
			return ;
		take_first_fork(henk, henk->fork1);
		take_second_fork(henk, henk->fork2);
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
