/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:23 by adeburea          #+#    #+#             */
/*   Updated: 2021/10/11 11:32:47 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_game
{
	int	number;
	int	die;
	int	eat;
	int	sleep;
	int	times;
}			t_game;

typedef struct s_philo
{
	int	is_die;
	int	is_eat;
	int	is_sleep;
	int	l_fork;
	int	r_fork;
}			t_philo;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
#endif
