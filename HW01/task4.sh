#!/usr/bin/env bash
#SBATCH --partition=instruction
#SBATCH --job-name=FirstSlurm
#SBATCH --output=FirstSlurm.out
#SBATCH --error=FirstSlurm.err
#SBATCH --time=0-00:01:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=2

cd $SLURM_SUBMIT_DIR
hostname