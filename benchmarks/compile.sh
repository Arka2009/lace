#!/bin/bash

#gcc -O3 -pg -gdwarf-3 dfs-lace.c -o dfs-lace -llace -llace14 -lpthread -lm -lecotools -lgsl -lgslcblas
gcc dfs/dfs-lace.c -o dfs/dfs-lace -llace -llace14 -lpthread -lm -lecotools -lgsl -lgslcblas
gcc ptss-wrapper.c -o ptss-wrapper -llace -llace14 -lpthread -lm -lecotools -lgsl -lgslcblas
