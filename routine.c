/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:03 by adeburea          #+#    #+#             */
/*   Updated: 2021/12/21 13:08:42 by adeburea         ###   ########.fr       */
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
	printf("routine address: %p\n", board);
	while (board->limit == -1)
	{
		printf("ICI %d\n", board->eat);
		philo->eat_count++;
	}
	return ((void*)philo);
}
