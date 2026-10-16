#!/bin/bash
#SBATCH --partition=instruction
#SBATCH --job-name=hw03_task3_p2
#SBATCH --output=hw03_task3_p2.out
#SBATCH --error=hw03_task3_p2.err
#SBATCH --time=00:3:00
#SBATCH --cpus-per-task=20

g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp
for t in {1..20}
do
    ./task3 $((10**6)) $t 
done

