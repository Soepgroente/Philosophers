/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/04 19:13:00 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	reconsider_life_choices(t_philo *sjon)
{
	if (poke_sjon(sjon) == false)
		return ;
	print_message(sjon, "is thinking\n");
}

static void	after_dinner_dip(t_philo *sjon)
{
	if (poke_sjon(sjon) == false)
		return ;
	print_message(sjon, "is sleeping\n");
	power_naps(sjon, sjon->t_sleep);
}

static void	eat_foods(t_philo *sjon)
{
	if (poke_sjon(sjon) == false)
		return ;
	print_message(sjon, "is eating\n");
	sjon->last_eaten = get_time();
	sjon->num_eaten++;
	if (sjon->num_eaten == sjon->max_eat)
		sem_post(sjon->saturated);
	power_naps(sjon, sjon->t_eat);
}

static void	eat_sleep_repeat(t_philo *sjon)
{
	while (INFINITY)
	{
		if (poke_sjon(sjon) == false)
			return ;
		if (sjon->num_eaten != 0)
			special_naps(sjon);
		sem_wait(sjon->forks);
		sem_wait(sjon->forks);
		print_message(sjon, "has taken a fork\n");
		print_message(sjon, "has taken a fork\n");
		eat_foods(sjon);
		sem_post(sjon->forks);
		sem_post(sjon->forks);
		after_dinner_dip(sjon);
		reconsider_life_choices(sjon);
	}
}

void	sjon_is_born(t_philo *sjon)
{
	sem_wait(sjon->start);
	sem_post(sjon->start);
	sjon->last_eaten = get_time();
	print_message(sjon, "is thinking\n");
	if (sjon->num % 2 == 1)
		power_naps(sjon, sjon->t_die / 10);
	eat_sleep_repeat(sjon);
	free(sjon);
	exit(EXIT_SUCCESS);
}
