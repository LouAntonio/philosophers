/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:01:05 by lantonio          #+#    #+#             */
/*   Updated: 2024/09/13 14:39:04 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	cur_time(void)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1) {
        perror("gettimeofday");
        return 1;
    }
    
    // Imprime o tempo atual em segundos e microssegundos
    printf("Tempo atual: %lds e %ldmcs \n", (long)tv.tv_sec, (long)tv.tv_usec);
}