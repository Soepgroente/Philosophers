/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/09 17:36:33 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	reconsider_life_choices(t_philo *sjon)
{
	if (poke_sjon(sjon, sjon->poke, NONE) == false)
		return ;
	print_message(sjon, "is thinking\n");
	ft_sleep(sjon, sjon->t_die * 200);
}

static void	after_dinner_dip(t_data *data, t_philo *sjon)
{
	if (poke_sjon(sjon, sjon->poke, NONE) == true)
	{
		print_message(sjon, "is sleeping\n");
		ft_sleep(sjon, data->t_sleep * 1000);
	}
}

static void	eat_foods(t_philo *sjon)
{
	if (poke_sjon(sjon, sjon->poke, NONE) == false)
		return ;
	sem_wait(sjon->forks);
	sem_wait(sjon->forks);
	if (check_last_eaten(sjon, sjon->eat, true) == -1)
	{
		sem_post(sjon->forks);
		sem_post(sjon->forks);
		return ;
	}
	print_message(sjon, "has taken a fork\n");
	print_message(sjon, "has taken a fork\n");
	print_message(sjon, "is eating\n");
	ft_sleep(sjon, sjon->data->t_sleep * 1000);
	sem_post(sjon->forks);
	sem_post(sjon->forks);
}

static void	eat_sleep_repeat(t_data *data, t_philo *sjon)
{
	while (INFINITY)
	{
		if (poke_sjon(sjon, sjon->poke, NONE) == false)
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
	print_message(sjon, "is thinking\n");
	if (sjon->num % 2 == 1)
	eat_sleep_repeat(sjon->data, sjon);
	return (NULL);
}
