/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbauer <mbauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:38:32 by mbauer            #+#    #+#             */
/*   Updated: 2025/10/26 16:04:04 by mbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

void	ft_send(int pit, char m)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (m & 1)
			kill(pit, SIGUSR2);
		else
			kill(pit, SIGUSR1);
		usleep(100);
		m = m >> 1;
		i++;
	}
}

void	ft_putchar(char m)
{
	write(1, &m, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_putchar('\n');
}

int	main(int argc, char **argv)
{
	int	pid;
	int	str_counter;

	str_counter = 0;
	if (argc != 3)
	{
		ft_putstr("invalid input!\n");
		return (0);
	}
	pid = ft_atoi(argv[1]);
	while (argv[2][str_counter])
	{
		ft_send(pid, argv[2][str_counter]);
		str_counter++;
	}
}
