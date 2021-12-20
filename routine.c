/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:03 by adeburea          #+#    #+#             */
/*   Updated: 2021/12/20 17:24:02 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int		i;
	t_board	*board;
	t_philo	*philo;

	i = 0;
	board = arg;
	philo = board->philo;
	printf("board time = %d\n", board->limit);
	while (board->limit == -1 || (i < board->limit && board->limit != -1))
	{
		gettimeofday(&board->tp[0], NULL);
		usleep(5000);
		gettimeofday(&board->tp[1], NULL);
		board->time = (board->tp[1].tv_usec - board->tp[0].tv_usec) / 1000;
		if (board->time < 0)
			board->time = 1000 - board->time * -1;
		printf("time = %d\n", board->time);
		i++;
	}
	return ((void*)philo);
}
