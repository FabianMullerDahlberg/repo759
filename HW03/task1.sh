#!/bin/bash
#SBATCH --partition=instruction
#SBATCH --job-name=hw03_task1
#SBATCH --output=hw03_task1.out
#SBATCH --error=hw03_task1.err
#SBATCH --time=00:3:00
#SBATCH --cpus-per-task=20

g++ task1.cpp matmul.cpp -Wall -O3 -std=c++17 -o task1 -fopenmp
for t in {1..20}
do
    ./task1 1024 $t
done