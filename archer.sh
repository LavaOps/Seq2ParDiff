#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename
# job standard output will go to the file slurm-%j.out (where %j is the job ID)

#SBATCH --time=47:59:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=4   # number of nodes
#SBATCH --ntasks-per-node=36   # 36 processor core(s) per node 
#SBATCH --mem=128G   # maximum memory per node
#SBATCH --job-name="archer"
#SBATCH --mail-user=youremail@anon.com   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL
#SBATCH --no-requeue
#SBATCH --output="slurm-archer-%j.out" # job standard output file (%j replaced by job id)

# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE

LIB_PATH="<your-path-to-workspace>/.lib"
export PATH="$PATH:$LIB_PATH/clang+llvm-18.1.8-x86_64-linux-gnu-ubuntu-18.04/bin"
export LD_LIBRARY_PATH="$LIB_PATH/libtinfo5_6.3-2/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="$LIB_PATH/clang+llvm-18.1.8-x86_64-linux-gnu-ubuntu-18.04/lib:$LD_LIBRARY_PATH"

export OMP_TOOL_LIBRARIES="$LIB_PATH/clang+llvm-18.1.8-x86_64-linux-gnu-ubuntu-18.04/lib/libarcher.so"
export TSAN_OPTIONS="ignore_noninstrumented_modules=1"
export ARCHER_OPTIONS=verbose=1

dataset_dir="<your-path-to-workspace>/Seq2ParDiff/autoparllm"

CFLAGS="-fopenmp -fsanitize=thread -g -fno-omit-frame-pointer"

# count=0
for dir in $(ls -d "$dataset_dir"/*/ | sort -V); do
    if [[ -d "$dir" ]]; then
        cd "$dir" || continue
        src="1.c"
        exe="log/archer.out"
        log="log/archer.log"

        if [[ -f "$src" ]]; then
            echo "Processing $dir$src"
            clang $CFLAGS -o "$exe" "$src" 2>"$log"
            "$exe" >>"$log" 2>&1

            # ((count++))
            # if [[ $count -ge 26 ]]; then
            #     exit 0
            # fi
        else
            echo "Warning: $src not found, skipping."
        fi
        cd - > /dev/null # Return to the original directory
    fi
done
