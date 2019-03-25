#!/bin/bash

#gcc -O3 -pg -gdwarf-3 dfs-lace.c -o dfs-lace -llace -llace14 -lpthread -lm -lecotools -lgsl -lgslcblas
gcc dfs-lace.c -o lacedfs.out -llace -llace14 -lpthread -lm -lecotools 
#gcc ../ptss-wrapper.c -o ../ptss-wrapper -lecotools -lgsl -lgslcblas
