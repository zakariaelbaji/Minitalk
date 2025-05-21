/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-baji <zel-baji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 03:08:42 by zel-baji          #+#    #+#             */
/*   Updated: 2025/03/12 03:18:20 by zel-baji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int g_received_ack;

void acknowledgment_handler(int signum)
{
    (void)signum;
    g_received_ack = 1;
}

void send_char(unsigned char c, int pid)
{
    int bit = 7;
    while (bit >= 0)
    {
        g_received_ack = 0;
        if ((c >> bit) & 1)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        while (!g_received_ack)
            usleep(100);
        usleep(500);
        bit--;
    }
}

void send_msg(char *msg, int pid)
{
    int i = 0;
    while (msg[i])
    {
        send_char(msg[i], pid);
        i++;
    }

    send_char('\0', pid);
}

void sigint_handler(int signum)
{
    (void)signum;
    write(1, "\nClient terminated.\n", 20);
    exit(0);
}

int main(int ac, char **av)
{
    if (ac != 3) {
        write(1, "Usage: ./client <server_pid> <message>\n", 39);
        exit(1);
    }
    
    signal(SIGINT, sigint_handler);
    signal(SIGUSR1, acknowledgment_handler);
    
    int pid = atoi(av[1]);
    send_msg(av[2], pid);
    
    return 0;
}
