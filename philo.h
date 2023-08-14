/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 13:49:52 by vincent           #+#    #+#             */
/*   Updated: 2023/08/13 18:28:11 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <ctype.h>
# include <pthread.h>

typedef struct s_philo
{
	int		num;
	
}	t_philo;

typedef struct s_data
{
	t_philo	*philo;
	int		philos;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		num_eat;
}	t_data;

int		ft_philatoi(char *num);

#endif