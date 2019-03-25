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


/* Size in bytes */
#define KB              1024L
#define MB              1024L*KB
#define GB              1024L*MB
#define ARRAYSIZE       128L*MB

static int w, n;


/* Compute a power series of */
static double node_computation_function(int N) {
    int i;
    double x, sum = 0.0;
    for (i = 0; i < N; i++) {
        x = (10 + rand()%100)/220.0;
        sum += pow(x,i);
    }
    // printf("Random Loop Bound = %d\n",N);
    return sum;
}

int __attribute__((noinline)) loop(int n2)
{
    int i, s=0;

    static unsigned int inv = 0;
    // printf("Entered Node function-%d\n",inv++);
    for( i=0; i<n; i++ ) {
        s += i;
        s *= i;
        s ^= i;
        s *= i;
        s += i;
    }
    // s = node_computation_function_llist(N,&dlist);
    // s = node_computation_function(n2);

    return s;
}

TASK_1(int, tree, int, d)
{
    // printf("Tree = %d, d = %d\n",tree,d);
    int n2 = 4;
    int b = 0;
    if( d>0 ) {
        int i;
        for (i=0;i<w;i++) SPAWN(tree, d-1);
        for (i=0;i<w;i++) SYNC(tree);
        return 0;
    } else {
        return loop(n2);    /* Found : Leaf Node is assumed to be found */
    }
}

void usage(char *s)
{
    fprintf(stderr, "%s -w <workers> [-q dqsize] <depth> <width> <grain> <reps>\n", s);
}


int main(int argc, char **argv) {
    //double t1 = wctime();
    int workers = 1, i = 0;
    int dqsize = 100000;
#ifdef ECOAFFINE
    affinity_set_cpu2(0);
#endif

    char c;
    while ((c=getopt(argc, argv, "w:q:h")) != -1) {
        switch (c) {
            case 'w':
                workers = atoi(optarg);
                break;
            case 'q':
                dqsize = atoi(optarg);
                break;
            case 'h':
                usage(argv[0]);
                break;
            default:
                abort();
        }
    }

    if (optind + 3 >= argc) {
        usage(argv[0]);
        exit(1);
    }

    int d, m;
    lace_init(workers, dqsize);
    lace_startup(0, 0, 0);

    LACE_ME;

    d = atoi(argv[optind]);
    w = atoi(argv[optind+1]);
    n = atoi(argv[optind+2]);
    m = atoi(argv[optind+3]);

#ifdef ECOPROFILE
	__eco_roi_start_timer();
    // PRINTTOPO("Eco Profiler enabled for DFS");
#endif
    for(i=0; i<m; i++) CALL(tree, d);
#ifdef ECOPROFILE
	__eco_roi_stop_timer();
#endif

    lace_exit();
    return 0;
}
