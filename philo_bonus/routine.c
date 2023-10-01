/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/30 18:15:21 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	reconsider_life_choices(t_philo *sjon)
{
	if (poke_sjon(sjon, sjon->lock, NONE) == false)
		return ;
	print_message(sjon, "is thinking\n");
	ft_sleep(sjon, sjon->t_think * 1000);
}

static void	after_dinner_dip(t_data *data, t_philo *sjon)
{
	if (poke_sjon(sjon, sjon->lock, NONE) == true)
	{
		print_message(sjon, "is sleeping\n");
		ft_sleep(sjon, data->t_sleep * 1000);
	}
}

static void	eat_foods(t_philo *sjon)
{
	if (poke_sjon(sjon, sjon->lock, NONE) == false)
		return ;
	sem_wait(sjon->forks);
	sem_wait(sjon->forks);
	if (check_last_eaten(sjon, sjon->eat, true) == false)
	{
		sem_post(sjon->forks);
		sem_post(sjon->forks);
		return ;
	}
	print_message(sjon, "has taken a fork\n");
	print_message(sjon, "has taken a fork\n");
	// if (check_last_eaten(sjon, sjon->eat, true) == false)
	// 	poke_sjon(sjon, sjon->lock, KILL);
	// else
	print_message(sjon, "is eating\n");
	// check_if_saturated(sjon, sjon->eat2);
	ft_sleep(sjon, sjon->data->t_sleep * 1000);
	sem_post(sjon->forks);
	sem_post(sjon->forks);
}

static void	eat_sleep_repeat(t_data *data, t_philo *sjon)
{
	while (INFINITY)
	{
		if (poke_sjon(sjon, sjon->lock, NONE) == false)
			return ;
		eat_foods(sjon);
		after_dinner_dip(data, sjon);
		reconsider_life_choices(sjon);
	}
}

void	*sjon_is_born(void *input)
{
	t_philo	*sjon;

	sjon = (t_philo *) input;
	if (sjon->num % 2 == 1)
	{
		print_message(sjon, "is thinking\n");
		usleep(1000);
	}
	eat_sleep_repeat(sjon->data, sjon);
	return (NULL);
}
