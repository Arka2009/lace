#include "lace-1.h"
#include <stdio.h> // for printf, fprintf
#include <stdlib.h> // for exit, atoi
#include <sys/time.h>
#include <getopt.h>

double wctime() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec + 1E-6 * tv.tv_usec);
}

TASK_1(int, pfib, int, n)
{
    if( n < 2 ) {
        return n;
    } else {
        int m,k;
        SPAWN( pfib, n-1 );
        k = CALL( pfib, n-2 );
        m = SYNC( pfib );
        return m+k;
    }
}

int n;

void f(void)
{
    double t1 = wctime();
    int m = CALL(pfib, n);
    double t2 = wctime();

    printf("fib(%d) = %d\n", n, m);
    printf("Time: %f\n", t2-t1);
}

void usage(char *s)
{
    fprintf(stderr, "%s -w <workers> [-q dqsize] <n>\n", s);
}

int main(int argc, char **argv)
{
    int workers = 1;
    int dqsize = 100000;

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

    if (optind == argc) {
        usage(argv[0]);
        exit(1);
    }

    n = atoi(argv[optind]);

    lace_boot(workers, dqsize, 0, f);
    return 0;
}
