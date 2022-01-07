/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:03 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/07 04:13:42 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_board	*board;
	t_philo	*philo;
	int		id;

	board = (t_board *)arg;
	id = board->id;
	philo = board->philo;
	philo[id].last_meal = get_time();
	while (42)
	{
		if (philo_live(board, philo, id))
			break ;
	}
	return (NULL);
}
