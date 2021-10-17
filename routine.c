/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:03 by adeburea          #+#    #+#             */
/*   Updated: 2021/10/15 03:34:52 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat(void *arg)
{
	t_board	*board;
	t_philo	*philo;

	board = arg;
	philo = board->philo;
	if (pthread_mutex_lock(&board->lock))
	{
		printf("ERROR\n");
		return (NULL);
	}
	board->timer++;
	usleep(board->eat * 1000 + 100);
	if (pthread_mutex_unlock(&board->lock))
	{
		printf("ERROR\n");
		return (NULL);
	}
	printf("%d ms -> philo %d is eating\n", board->timer);
	return NULL;
}

int	routines(t_board *board, t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	while (board->times == -1 || (i < board->times && board->times != -1))
	{
		j = 0;
		while (j < board->number)
		{
			gettimeofday(&board->tp[0], NULL);
			if (pthread_create(&(philo[j].philo), NULL, &eat, board))
				return (printf("pthread_create: error: can't create thread\n"));
			gettimeofday(&board->tp[1], NULL);
			board->time = (board->tp[1].tv_usec - board->tp[0].tv_usec) / 1000;
			if (board->time < 0)
				board->time = 1000 - board->time * -1;
			printf("%d ms\n", board->time);
			j++;
		}
		i++;
	}
	pthread_mutex_destroy(&board->lock);
	return (0);
}
