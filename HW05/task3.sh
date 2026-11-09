#!/bin/bash
#SBATCH --partition=instruction
#SBATCH --job-name=task3
#SBATCH --output=task3.out
#SBATCH --error=task3.err
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --gpus-per-task=1
#SBATCH --time=00:10:00

module load nvidia/cuda/13.0.0 
nvcc task3.cu vscale.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task3

echo "n,time_ms"

for p in {10..29}; do
    n=$((2**p))
    time_ms=$(./task3 "$n" | head -n 1)
    echo "$n,$time_ms"
done