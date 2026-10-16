#!/bin/bash
#SBATCH --partition=instruction
#SBATCH --job-name=hw03_task3_p1
#SBATCH --output=hw03_task3_p1.out
#SBATCH --error=hw03_task3_p1.err
#SBATCH --time=00:3:00
#SBATCH --cpus-per-task=20

g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp
for exp in $(seq 1 10) do
    ts=$((2**exp))
    ./task3 $((10**6)) 8 "$ts" 
done