#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <getopt.h>
#include <lace.h>
#include <math.h>
#include <stdint.h>
#include <unistd.h>
#include <ecotools/cpu_uarch.h>
#include <ecotools/roi_hooks.h>

void usage(char *s)
{
    char log[BUFSIZ];
    sprintf(log, "%s <workers>\n", s);
    PRINTERROR(log);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        usage(argv[0]);
    }
    int w = atoi(argv[1]);
    char command[BUFSIZ];
    sprintf(command,"dfs/dfs-lace -w %d 8 5 10 1",w);
	//PRINTTOPO(command);
	
	/* Put the other cores to sleep to lowest "energy state" */
	int w2;
	for (w2 = 0; w2 < 64; w2++) {
        if (w2 <= w)
            set_frequency(w2,1300000); /* Low Energy (KNL) */
        else
            set_frequency(w2,1000000); /* Low Energy (KNL) */
	}
    usleep(10000); /* Wait for stabilization */

    __eco_init();
    __eco_roi_begin();
    if (system(command) != 0) {
        PRINTERROR("dfs/dfs-lace execution Failed");
    }
	//usleep(21000);
    __eco_roi_end();

    return 0;
}
