/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:03 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/21 17:00:07 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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
	philo[id].start_eating = get_time();
	while (42)
	{
		if (philo_live(board, philo, id))
			break ;
	}
	return (NULL);
}
