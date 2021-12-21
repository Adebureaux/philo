/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:22 by adeburea          #+#    #+#             */
/*   Updated: 2021/12/21 13:08:20 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec) * 1000 + (tv.tv_usec / 1000)));
}

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
	board->limit = -1;
	if (ac == 6)
		board->limit = ft_atoi(*(av + 5));
	if (ac == 6 && board->limit < 1)
		return ("arg 5 must be 'number_of_times_each_philosopher_must_eat'");
	return (NULL);
}

int	start_philo(t_board *board, t_philo *philo)
{
	int	i;

	i = -1;
	board->philo = philo;
	printf("start_philo address: %p\n", board);
	while (++i < board->number)
	{
		philo[i].is_die = 0;
		philo[i].is_eat = 0;
		philo[i].is_sleep = 0;
		philo[i].eat_count = 0;
		if (pthread_create(&(philo[i].philo), NULL, &routine, board))
			return (printf("pthread_create: error: can't create thread\n"));
	}
	return (0);
}


int	main(int ac, char **av)
{
	t_board	board;
	t_philo	*philo;

	if (parse(ac, av, &board))
		return (printf("%s: error: %s\n", av[0], parse(ac, av, &board)));
	philo = malloc(sizeof(t_philo) * board.number);
	if (!philo)
		return (printf("malloc error\n"));
	start_philo(&board, philo);
	return (1);
}
