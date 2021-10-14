/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:35:03 by adeburea          #+#    #+#             */
/*   Updated: 2021/10/14 12:04:25 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct timeval current_time;
struct timeval old_time;
int counter;

void* doSomeThing(void *arg)
{
	t_game	*game;
	t_philo	*philo;

	game = arg;
	philo = game->philo;
    if (pthread_mutex_lock(&game->lock))
	{
		printf("ERROR\n");
		return (NULL);
	}

    counter++;
	usleep(100);
    printf("Philo %d is eating\n", counter);
    if (pthread_mutex_unlock(&game->lock))
	{
		printf("ERROR\n");
		return (NULL);
	}
    return NULL;
}

int	routines(t_game *game, t_philo *philo)
{
	int	i;

	i = 0;
    while (game->times == -1 || (i < game->times && game->times != -1))
    {
		gettimeofday(&game->tp[0], NULL);
		usleep(200000);
		if (pthread_create(&(philo[i].philo), NULL, &doSomeThing, game))
			return (printf("pthread_create: error: can't create thread\n"));
		gettimeofday(&game->tp[1], NULL);
		int time = (game->tp[1].tv_usec) - (game->tp[0].tv_usec);
		if (time < 0)
		{
			time *= -1;
			time = 1000000 - time;
		}
		printf("Time spend = %d\n", time);
		i++;
    }

	i = 0;
	while (game->times == -1 || (i < game->times && game->times != -1))
		pthread_join((philo[i++].philo), NULL);
    pthread_mutex_destroy(&game->lock);

    return 0;
}
