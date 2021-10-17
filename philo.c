/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:22 by adeburea          #+#    #+#             */
/*   Updated: 2021/10/14 17:16:15 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*parse(int ac, char **av, t_board *board)
{
	if (ac != 5 && ac != 6)
		return ("must have 4 or 5 arguments");
	board->number = ft_atoi(*(av + 1));
	if (board->number < 1)
		return ("arg 1 must be 'number_of_boardsophers'");
	board->die = ft_atoi(*(av + 2));
	if (board->die < 1)
		return ("arg 2 must be 'time_to_die'");
	board->eat = ft_atoi(*(av + 3));
	if (board->eat < 1)
		return ("arg 3 must be 'time_to_eat'");
	board->sleep = ft_atoi(*(av + 4));
	if (board->sleep < 1)
		return ("arg 4 must be 'time_to_sleep'");
	board->times = -1;
	if (ac == 6)
		board->times = ft_atoi(*(av + 5));
	if (ac == 6 && board->times < 1)
		return ("arg 5 must be 'number_of_times_each_philosopher_must_eat'");
	return (NULL);
}

int	init(t_board *board, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < board->number)
	{
		philo[i].is_die = 0;
		philo[i].is_eat = 0;
		philo[i].is_sleep = 0;
		philo[i].l_fork = 0;
		philo[i].r_fork = 0;
	}
	if (pthread_mutex_init(&board->lock, NULL))
		return (printf("pthread_mutex_init: error\n"));
	board->philo = philo;
	return (0);
}

int	main(int ac, char **av)
{
	t_board	board;
	t_philo	*philo;

	if (parse(ac, av, &board))
		return (printf("%s: error: %s\n", av[0], parse(ac, av, &board)));
	philo = malloc(sizeof(t_philo) * board.number);
	if (!philo || init(&board, philo) || routines(&board, philo))
		return (1);
	return (0);
}
