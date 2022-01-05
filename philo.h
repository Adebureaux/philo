/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:23 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/05 15:10:38 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define PURPLE	"\033[1;35m"
# define CYAN	"\033[1;36m"
# define DEF	"\033[1m"

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print;
	int				last_meal;
	int				count_meal;
	char			color[7];
}				t_philo;

typedef struct s_board
{
	t_philo			*philo;
	size_t			start_time;
	char			color[7][10];
	int				id;
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				limit;
	int				stop;
}			t_board;

size_t	get_time(void);
void	usleep_custom(size_t time);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	ft_putstr(char *s);
void	ft_putnbr(size_t n);
char	*ft_strcpy(char *dst, char *src);
int		init_philo(t_board *board, t_philo *philo);
int		start_philo(t_board *board, t_philo *philo);
void	*routine(void *arg);
#endif
