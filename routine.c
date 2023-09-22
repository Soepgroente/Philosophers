/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:18:22 by vvan-der          #+#    #+#             */
/*   Updated: 2023/09/22 17:13:09 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	reconsider_life_choices(t_philo *henk)
{
	int	time;

	if (check_if_alive(henk, &henk->lock, NONE) == false)
			return ;
	time = get_runtime(henk->start_time);
	printf("%d %d is thinking\n", time, henk->num);
	ft_sleep(henk, henk->t_think);
}

static void	after_dinner_dip(t_data *data, t_philo *henk)
{
	int	time;

	time = get_runtime(henk->start_time);
	if (check_if_alive(henk, &henk->lock, NONE) == true)
	{
		printf("%d %d is sleeping\n", time, henk->num);
		ft_sleep(henk, data->t_sleep * 1000);
	}
}

static void	eat_foods(t_philo *henk)
{
	int	time;

	if (check_if_alive(henk, &henk->lock, NONE) == false)
		return ;
	time = get_runtime(henk->start_time);
	printf("%d %d is eating\n", time, henk->num);
	pthread_mutex_lock(&henk->lock);
	henk->last_eaten = time;
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
		if (check_if_alive(henk, &henk->lock, NONE) == false)
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
		usleep(100);
	eat_sleep_repeat(henk->data, henk);
	return (NULL);
}
