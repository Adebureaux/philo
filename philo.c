/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:22 by adeburea          #+#    #+#             */
/*   Updated: 2021/10/14 10:36:54 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*parse(int ac, char **av, t_game *game)
{
	if (ac != 5 && ac != 6)
		return ("must have 4 or 5 arguments");
	game->number = ft_atoi(*(av + 1));
	if (game->number < 1)
		return ("arg 1 must be 'number_of_gamesophers'");
	game->die = ft_atoi(*(av + 2));
	if (game->die < 1)
		return ("arg 2 must be 'time_to_die'");
	game->eat = ft_atoi(*(av + 3));
	if (game->eat < 1)
		return ("arg 3 must be 'time_to_eat'");
	game->sleep = ft_atoi(*(av + 4));
	if (game->sleep < 1)
		return ("arg 4 must be 'time_to_sleep'");
	game->times = -1;
	if (ac == 6)
		game->times = ft_atoi(*(av + 5));
	if (ac == 6 && game->times < 1)
		return ("arg 5 must be 'number_of_times_each_gamesopher_must_eat' > 0");
	return (NULL);
}

int	init(t_game *game, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < game->number)
	{
		philo[i].is_die = 0;
		philo[i].is_eat = 0;
		philo[i].is_sleep = 0;
		philo[i].l_fork = 0;
		philo[i].r_fork = 0;
	}
	if (pthread_mutex_init(&game->lock, NULL))
		return (printf("pthread_mutex_init: error\n"));
	game->philo = philo;
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_philo	*philo;

	if (parse(ac, av, &game))
		return (printf("%s: error: %s\n", av[0], parse(ac, av, &game)));
	philo = malloc(sizeof(t_philo) * game.number);
	if (!philo || init(&game, philo) || routines(&game, philo))
		return (1);
	return (0);
}
