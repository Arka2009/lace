#!/bin/bash

#if [${EUID} -ne 0]; then
#	echo "Run as root, exiting"
#	exit 1
#fi

# Build All the benchmarks
LACEROOT=${PWD}
bash ${LACEROOT}/compile.sh
dir2="ptss-lace-$(date -I)"


# Build the wrapper
bench="FIB"
dir3="${dir2}/${bench}"
mkdir -p ${dir3}
gcc -DBENCH_LACE_${bench} ptss-wrapper.c -o x86lace.out -llace -llace14 -lpthread -lm -lecotools -lgsl -lgslcblas


# Collect Execution Time Statistics
for nth1 in $(seq 1 32); do
	exe1="${LACEROOT}/x86lace.out ${nth1}"
	fname="${dir2}/dataset_${bench}_${nth1}.csv"
	echo "ITEM,TIME">>${fname}
	for iter in $(seq 1 5000); do
		${exe1} | grep "ROI-STATS" >> ${fname}
		echo "Finished Iteration-${iter}"
	done
	echo "Finished Statistics Collection for alloc-${nth1}"
done
chown -R amaity:amaity ${LACEROOT}
