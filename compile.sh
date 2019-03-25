#!/bin/bash

benchmarks="\
cilksort \
dfs \
fib \
knapsack \
matmul \
pi \
queens \
strassen \
"

laceroot=${PWD}
bin1="${laceroot}/binaries/x86"
bin2="${laceroot}/binaries/sniper"
lacebuid="${laceroot}/build"
rm -rf ${lacebuid}
mkdir -p ${bin1} ${bin2} ${lacebuid}

echo "Building for native execution"
rm -rf ${lacebuid} && mkdir -p ${lacebuid}
cd ${lacebuid} && cmake ${laceroot} -DECOPROFILE=ON -DECOAFFINE=ON && make install && cd ${laceroot}
for bench in ${benchmarks}; do
	echo "Building benchmark (x86) ${bench}"
	gcc -DECOAFFINE -DECOPROFILE benchmarks/${bench}/${bench}-lace.c -o ${bin1}/lace${bench}.out -llace -llace14 -lpthread -lm -lecotools -lgsl -lgslcblas
done

echo "Building for sniper execution"
rm -rf ${lacebuid} && mkdir -p ${lacebuid}
cd ${lacebuid} && cmake ${laceroot} -DECOPROFILE=OFF -DECOAFFINE=OFF && make install && cd ${laceroot}
for bench in ${benchmarks}; do
	echo "Building benchmark (sniper) ${bench}"
	gcc benchmarks/${bench}/${bench}-lace.c -o ${bin2}/lace${bench}.out -llace -llace14 -lpthread -lm -lecotools -lgsl -lgslcblas
done

chown -R amaity:amaity ${laceroot}
