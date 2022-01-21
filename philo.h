/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:20:23 by adeburea          #+#    #+#             */
/*   Updated: 2022/01/21 04:30:31 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define PURPLE	"\033[1;35m"
# define CYAN	"\033[1;36m"
# define DEF	"\033[1m"
# define DELAY	500

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print;
	size_t			start_eating;
	int				count_meal;
	char			color[7];
}				t_philo;

typedef struct s_board
{
	t_philo			*philo;
	pthread_mutex_t	*lock;
	size_t			start_time;
	char			color[7][10];
	int				rip;
	int				stop;
	int				id;
	int				full_number;
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				limit;
}			t_board;

size_t	get_time(void);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	ft_putstr(char *s);
void	ft_putnbr(size_t n);
char	*ft_strcpy(char *dst, char *src);
int		init_philo(t_board *board, t_philo *philo);
int		start_philo(t_board *board, t_philo *philo);
int		philo_live(t_board *board, t_philo *philo, int id);
void	philo_speak(t_board *board, t_philo *philo, char *str, int id);
void	*routine(void *arg);
void	free_philo(t_board *board, t_philo *philo);

#endif
