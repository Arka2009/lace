#!/bin/bash

# Collect Execution Time Statistics for PTSS scheduler model
lace_root="/home/amaity/Desktop/lace/benchmarks"
bench="queens"
dir2="ptss-lace-${bench}_$(date -I)"
bash compile.sh

rm -rf ${dir2}
mkdir -p ${dir2}

for nth1 in $(seq 1 32); do
	# App1
	exe1="${lace_root}/ptss-wrapper ${bench} ${nth1}"
	fname="${dir2}/dataset_${bench}_${nth1}.csv"
	echo "ITEM,TIME">>${fname}
	for iter in $(seq 1 5000); do
		${exe1} | grep "ROI-STATS" >> ${fname}
		#echo "Finished Iteration-${iter}"
	done
	echo "Finished Statistics Collection for alloc-${nth1}"
done
chown -R amaity:amaity ${dir2}
