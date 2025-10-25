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
    unsigned char current_char;  // Das Zeichen das wir bauen
    int           bit_count;     // Wie viele Bits haben wir schon?
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
    // Wenn SIGUSR2, ist das Bit eine 1
    if (sig == SIGUSR2)
        g_data.current_char |= (1 << g_data.bit_count);
    
    // Wenn SIGUSR1, ist das Bit eine 0
    // → Nichts tun, Bit bleibt 0
    
    g_data.bit_count++;
    
    // Haben wir 8 Bits = 1 komplettes Zeichen?
    if (g_data.bit_count == 8)
    {
        write(1, &g_data.current_char, 1);  // ← AUSGABE!
        
        // Reset für nächstes Zeichen
        g_data.current_char = 0;
        g_data.bit_count = 0;
    }
}

int main(void)
{
    int pid;

    pid = getpid();
    signal(SIGUSR1, handler); // Bit 0
    signal(SIGUSR2, handler); // Bit 1
    ft_putstr("Server PID: ");
    ft_putnbr(pid);
    ft_putstr("\n");
    while (1)
        pause(); // Warten auf Signale
    
    return 0;
}
