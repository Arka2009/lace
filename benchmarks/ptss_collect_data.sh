#!/bin/bash

# Collect Execution Time Statistics for PTSS scheduler model
lace_root="/home/amaity/Desktop/lace/benchmarks"

# App1
nth1="8"
exe1="${lace_root}/dfs/dfs-lace -w ${nth1} 11 5 10 1"

# App2
nth2="16"
exe2="${lace_root}/queens/queens-lace -w ${nth2} 10"

# App3
nth3="32"
exe3="${lace_root}/fib/fib-lace -w ${nth3} 32"

rm -rf synth_sp_lace
mkdir -p synth_sp_lace
echo "phase,time">>synth_sp_lace/dataset_ph1.csv
echo "phase,time">>synth_sp_lace/dataset_ph2.csv
echo "phase,time">>synth_sp_lace/dataset_ph3.csv
echo "total,time">>synth_sp_lace/dataset_sf1.csv
echo "total,time">>synth_sp_lace/dataset_sf2.csv
for iter in $(seq 1 2000); do
	#start1=$(date +%s.%N)
	${exe1} | grep "Time" >> synth_sp_lace/dataset_ph1.csv
	#dur1=$(echo "$(date +%s.%N) - $start1" | bc)
    #echo "iter-${iter},${dur1}">>synth_sp_lace/dataset_ph1.csv

	#start2=$(date +%s.%N)
	#${exe2} > /dev/null
	#dur2=$(echo "$(date +%s.%N) - $start2" | bc)
    #echo "iter-${iter},${dur2}">>synth_sp_lace/dataset_ph2.csv

	#start3=$(date +%s.%N)
	#${exe3} > /dev/null
	#dur3=$(echo "$(date +%s.%N) - $start3" | bc)
    #echo "iter-${iter},${dur3}">>synth_sp_lace/dataset_ph3.csv
	##echo "iter-${iter},${durb}">>synth_sp_lace/dataset_sf1.csv

	#starta=$(date +%s.%N)
	#${exe1} > /dev/null
	#${exe2} > /dev/null
	#${exe3} > /dev/null
	#dura=$(echo "$(date +%s.%N) - $starta" | bc)
	#echo "iter-${iter},${dura}">>synth_sp_lace/dataset_sf2.csv
	echo "Finished Iteration-${iter}"
done
