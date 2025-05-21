/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-baji <zel-baji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 03:46:19 by zel-baji          #+#    #+#             */
/*   Updated: 2025/03/12 02:36:27 by zel-baji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

static t_data g_data;

void reset_state()
{
    g_data.bit_count = 0;
    g_data.character = 0;
}

void handler(int signal, siginfo_t *info, void *ucontext)
{
    pid_t client_pid = info->si_pid;
    
    if (client_pid != g_data.last_pid)
    {
        reset_state();
        g_data.last_pid = client_pid;
    }
    g_data.character = g_data.character << 1;
    if (signal == SIGUSR2)
        g_data.character |= 1;
    g_data.bit_count++;
    
    if (g_data.bit_count == 8)
    {
        write(1, &g_data.character, 1);
        
        if (g_data.character == '\0')
        {
            write(1, "\n", 1);
        }
        reset_state();
    }
}

int main()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    printf("server PID: %d\n", getpid());
    while (1)
    {
        pause();
    }
    return 0;
}
