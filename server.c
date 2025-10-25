/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbauer <mbauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:58:49 by mbauer            #+#    #+#             */
/*   Updated: 2025/10/25 17:57:05 by mbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

typedef struct s_data {
    unsigned char current_char;
    int           bit_count;
} t_data;

t_data g_data = {0, 0};

void	ft_putchar(char m)
{
	write(1, &m, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void ft_putnbr(int n)
{
    if (n == -2147483648)
    {
        write(1, "-2147483648", 11);
        return;
    }
    if (n < 0)
    {
        ft_putchar('-');
        n = -n;
    }
    if (n >= 10)
    {
        ft_putnbr(n / 10);
    }
    ft_putchar(n % 10 + '0');
}

void handler(int sig)
{
    if (sig == SIGUSR2)
        g_data.current_char |= (1 << g_data.bit_count);
    g_data.bit_count++;
    if (g_data.bit_count == 8)
    {
        write(1, &g_data.current_char, 1);
        g_data.current_char = 0;
        g_data.bit_count = 0;
    }
}

int main(void)
{
    int pid;

    pid = getpid();
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    ft_putstr("Server PID: ");
    ft_putnbr(pid);
    ft_putstr("\n");
    while (1)
        pause();
    
    return 0;
}
