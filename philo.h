/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:23 by adeburea          #+#    #+#             */
/*   Updated: 2021/10/14 11:28:09 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	philo;
	int			is_die;
	int			is_eat;
	int			is_sleep;
	int			l_fork;
	int			r_fork;
}			t_philo;

typedef struct s_game
{
	pthread_mutex_t	lock;
	struct timeval	tp[2];
	void			*philo;
	int				timer;
	int				count;
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				times;
}			t_game;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		routines(t_game *game, t_philo *philo);
#endif
