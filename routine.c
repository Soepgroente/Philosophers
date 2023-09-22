/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:18:22 by vvan-der          #+#    #+#             */
/*   Updated: 2023/09/22 13:24:26 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	reconsider_life_choices(t_data *data, t_philo *henk)
{
	if (check_if_alive(henk, &henk->lock) == true)
		printf("%d %d is thinking\n", data->time, henk->num);
}

static void	after_dinner_dip(t_data *data, t_philo *henk)
{
	if (check_if_alive(henk, &henk->lock) == true)
	{
		printf("%d %d is sleeping\n", data->time, henk->num);
		ft_sleep(henk, data->t_sleep * 1000);
	}
}

static void	eat_foods(t_data *data, t_philo *henk)
{
	int	time;

	time = get_runtime(data->start_time, &data->lock);
	printf("%d %d is eating\n", time, henk->num);
	henk->last_eaten = time;
}

static void	eat_sleep_repeat(t_data *data, t_philo *henk)
{
	while (INFINITY)
	{
		if (check_if_alive(henk, &henk->lock) == false)
			return ;
		take_first_fork(data, henk, henk->fork1);
		take_second_fork(data, henk, henk->fork2);
		eat_foods(data, henk);
		after_dinner_dip(data, henk);
		reconsider_life_choices(data, henk);
	}
}

void	*start_routine(void *input)
{
	t_philo	*henk;

	henk = (t_philo *) input;
	usleep(100);
	printf("Philosopher %d reporting!\n", henk->num);
	eat_sleep_repeat(henk->data, henk);
	return (NULL);
}
