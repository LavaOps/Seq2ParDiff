#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename
# job standard output will go to the file slurm-%j.out (where %j is the job ID)

#SBATCH --time=47:59:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=4   # number of nodes
#SBATCH --ntasks-per-node=36   # 36 processor core(s) per node 
#SBATCH --mem=128G   # maximum memory per node
#SBATCH --job-name="CIVL"
#SBATCH --mail-user=youremail@anon.com   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL
#SBATCH --no-requeue
#SBATCH --output="slurm-civl-%j.out" # job standard output file (%j replaced by job id)

# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE


dataset_dir="<your-path-to-workspace>/Seq2ParDiff/autoparllm"
# count=0

for dir in $(ls -d "$dataset_dir"/*/ | sort -V); do
    if [[ -d "$dir" ]]; then
        cd "$dir" || continue

        file="1.c"
        log_file="log/civl.log"

        if [[ -f "$file" ]]; then
            echo "Verifying: $dir$file"
            civl verify -input_omp_thread_max=128 -maxdepth=200 -min -errorBound=100 -timeout=120 "$file" &> "$log_file"

            # ((count++))
            # if [[ $count -ge 2 ]]; then
            #     exit 0
            # fi
        else
            echo "Skipping $dir ($file not found)"
        fi

        cd - > /dev/null # Return to the original directory
    fi
done
