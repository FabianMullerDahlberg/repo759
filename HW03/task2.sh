#!/bin/bash
#SBATCH --partition=instruction
#SBATCH --job-name=hw03_task2
#SBATCH --output=hw03_task2.out
#SBATCH --error=hw03_task2.err
#SBATCH --time=00:3:00
#SBATCH --cpus-per-task=20

g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp
for t in {1..20}
do
    ./task2 1024 $t
done