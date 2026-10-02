#!/bin/bash
#SBATCH --partition=instruction
#SBATCH --job-name=hw02_task3
#SBATCH --output=hw02_task3.out
#SBATCH --error=hw02_task3.err
#SBATCH --time=00:1:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1

./task3