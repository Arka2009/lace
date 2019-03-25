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

#define BENCH_LACE_DFS     
#define BENCH_LACE_CILKSORT
#define BENCH_LACE_FIB     
#define BENCH_LACE_PI      
#define BENCH_LACE_QUEENS  

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
    cpu_topology_t cpu_topology2;
    __eco_init(&cpu_topology2);

#ifdef BENCH_LACE_DFS
    sprintf(command,"binaries/x86/lacedfs.out -w %d 4 4 1 1",w);
    __eco_roi_begin(&cpu_topology2);
    if (system(command) != 0) {
        PRINTERROR("Execution Failed");
    }
    __eco_roi_end(&cpu_topology2);
#endif

#ifdef BENCH_LACE_CILKSORT
    sprintf(command,"binaries/x86/lacecilksort.out -w %d 10000",w); // Cannot change the input
    __eco_roi_begin(&cpu_topology2);
    if (system(command) != 0) {
        PRINTERROR("Execution Failed");
    }
    __eco_roi_end(&cpu_topology2);
#endif

#ifdef BENCH_LACE_FIB
    sprintf(command,"binaries/x86/lacefib.out -w %d 16",w);
     __eco_roi_begin(&cpu_topology2);
    if (system(command) != 0) {
        PRINTERROR("Execution Failed");
    }
    __eco_roi_end(&cpu_topology2);
#endif

#ifdef BENCH_LACE_PI
    sprintf(command,"binaries/x86/lacepi.out -w %d 1000",w);
     __eco_roi_begin(&cpu_topology2);
    if (system(command) != 0) {
        PRINTERROR("Execution Failed");
    }
    __eco_roi_end(&cpu_topology2);
#endif

#ifdef BENCH_LACE_QUEENS
    sprintf(command,"binaries/x86/lacequeens.out -w %d 6",w);
    __eco_roi_begin(&cpu_topology2);
    if (system(command) != 0) {
        PRINTERROR("Execution Failed");
    }
    __eco_roi_end(&cpu_topology2);
#endif
    // __eco_deinit(&cpu_topology2);
    return 0;
}
