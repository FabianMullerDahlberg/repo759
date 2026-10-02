#!/bin/bash
#SBATCH --partition=instruction
#SBATCH --job-name=hw02_task1
#SBATCH --output=hw02_task1.out
#SBATCH --error=hw02_task1.err
#SBATCH --time=00:1:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1

for exp in $(seq 10 30)
do
    n=$((2**exp))
    echo "$n"
    ./task1 "$n"
done