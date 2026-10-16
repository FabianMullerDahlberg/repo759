#!/usr/bin/env zsh
#SBATCH --partition=instruction 
#SBATCH --job-name=task6
#SBATCH --output=task6.out
#SBATCH --error=task6.err
#SBATCH --time=0-00:01:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1

# log in the submission directory
cd $SLURM_SUBMIT_DIR
cd repo759/HW01
g++ task6.cpp -Wall -O3 -std=c++17 -o task6
./task6 8
