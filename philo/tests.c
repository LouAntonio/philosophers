
#include "includes/philosophers.h"

int main(void)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1) {
        perror("gettimeofday");
        return 1;
    }
    
    // Imprime o tempo atual em segundos e microssegundos
    printf("Tempo atual: %lds e %ldmcs \n", (long)tv.tv_sec, (long)tv.tv_usec);
    
    return 0;
}