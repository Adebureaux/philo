/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:22 by adeburea          #+#    #+#             */
/*   Updated: 2021/10/11 11:33:17 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*parse_game(int ac, char **av, t_game *game)
{
	if (ac != 5 && ac != 6)
		return ("must have 4 or 5 arguments");
	game->number = ft_atoi(*(av + 1));
	if (game->number < 0)
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
		return ("arg 5 must be 'number_of_times_each_gamesopher_must_eat'");
	return (NULL);
}

void *myThreadFun(void *vargp)
{
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

void init_game(t_game *game)
{
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
}

int	main(int ac, char **av)
{
	t_game	game;

	if (parse_game(ac, av, &game))
		return (printf("%s: error: %s\n", av[0], parse_game(ac, av, &game)));
	init_game(&game);
	return (0);
}
