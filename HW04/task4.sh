#!/bin/bash
#SBATCH --partition=instruction
#SBATCH --job-name=nbody-task4
#SBATCH --output=task4_%j.out
#SBATCH --error=task4_%j.err
#SBATCH --cpus-per-task=8
#SBATCH --time=00:03:00

g++ task3.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp
printf 'schedule,threads,time_ms\n' > task4.csv

for policy in static dynamic guided; do
    export OMP_SCHEDULE="$policy"
    for threads in {1..8}; do
        output=$(./task3 100 100 "$threads")
        ms=$(printf '%s\n' "$output" | awk '/^time:/ {gsub(/ms/,"",$2); print $2}')
        printf '%s,%s,%s\n' "$policy" "$threads" "$ms" | tee -a task4.csv
    done
done
