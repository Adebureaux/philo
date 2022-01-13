/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:03 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/13 11:20:40 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_board	*board;
	t_philo	*philo;
	int		id;

	board = (t_board *)arg;
	pthread_mutex_lock(board->lock);
	id = board->id;
	board->id++;
	pthread_mutex_unlock(board->lock);
	philo = board->philo;
	philo[id].last_meal = get_time();
	while (42)
	{
		if (philo_live(board, philo, id))
			break ;
	}
	return (NULL);
}
