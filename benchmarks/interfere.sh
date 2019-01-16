#!/bin/bash

# Collect Execution Time Statistics for PTSS scheduler model
lace_root="/home/amaity/Desktop/lace/benchmarks"

# App1
nth1="8"
arg="20 8 10 1"
exe2="${lace_root}/dfs/dfs-lace-aff9-16 -w ${nth1} ${arg}"
exe3="${lace_root}/dfs/dfs-lace-aff17-24 -w ${nth1} ${arg}"
exe4="${lace_root}/dfs/dfs-lace-aff25-32 -w ${nth1} ${arg}"
exe5="${lace_root}/dfs/dfs-lace-aff33-40 -w ${nth1} ${arg}"
exe6="${lace_root}/dfs/dfs-lace-aff41-48 -w ${nth1} ${arg}"
exe7="${lace_root}/dfs/dfs-lace-aff49-56 -w ${nth1} ${arg}"

# Just run to cause interference
for iter in $(seq 1 200000); do
	${exe2} > /dev/null &
	${exe3} > /dev/null &
	${exe4} > /dev/null &
	${exe5} > /dev/null &
	${exe6} > /dev/null &
	${exe7} > /dev/null &
	wait
	echo "Interfere Iteration-${iter}"
done
