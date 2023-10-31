/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 12:18:22 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/31 13:29:23 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static void	reconsider_life_choices(t_philo *sjon)
// {
// }

// static void	after_dinner_dip(t_data *data, t_philo *sjon)
// {
// }

// static void	eat_foods(t_philo *sjon)
// {
// }

// static void	eat_sleep_repeat(t_data *data, t_philo *sjon)
// {
// }

int	sjon_is_born(t_philo *sjon)
{
	sem_wait(sjon->start);
	printf("Hi from process %d\n", sjon->num);
	sem_post(sjon->start);
	sem_post(sjon->saturated);
	// free_everything(sjon);
	return (42);
}
