/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/17 11:58:00 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	reconsider_life_choices(t_philo *sjon)
{
	if (poke_sjon(sjon, sjon->poke) == false)
		return ;
	print_message(sjon, "is thinking\n");
}

static void	after_dinner_dip(t_data *data, t_philo *sjon)
{
	if (poke_sjon(sjon, sjon->poke) == true)
	{
		print_message(sjon, "is sleeping\n");
		ft_sleep(sjon, sjon->t_sleep);
	}
}

static void	eat_foods(t_philo *sjon)
{
	if (poke_sjon(sjon, sjon->poke) == false)
		return ;
	sem_wait(sjon->forks);
	if (poke_sjon(sjon, sjon->poke) == false)
	{
		sem_post(sjon->forks);
		return ;
	}
	print_message(sjon, "has taken a fork\n");
	sem_wait(sjon->forks);
	if (poke_sjon(sjon, sjon->poke) == false)
	{
		sem_post(sjon->forks);
		sem_post(sjon->forks);
		return ;
	}
	print_message(sjon, "has taken a fork\n");
	print_message(sjon, "is eating\n");
	sem_wait(sjon->poke);
	sjon->last_eaten = get_time();
	sjon->num_eaten++;
	sem_post(sjon->poke);
	ft_sleep(sjon, sjon->t_sleep);
	sem_post(sjon->forks);
	sem_post(sjon->forks);
}

static void	eat_sleep_repeat(t_data *data, t_philo *sjon)
{
	while (INFINITY)
	{
		if (poke_sjon(sjon, sjon->poke) == false)
			return ;
		eat_foods(sjon);
		after_dinner_dip(data, sjon);
		reconsider_life_choices(sjon);
	}
}

int	sjon_is_born(t_data *data, int num)
{
	t_philo	*sjon;

	sjon = init_sjon(data, num);
	if (sjon == NULL)
		return (-1);
	sem_wait(data->start);
	sem_post(data->start);
	print_message(sjon, "is thinking\n");
	eat_sleep_repeat(sjon->data, sjon);
	return (0);
}
