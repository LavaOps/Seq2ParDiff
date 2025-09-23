The experiments can be conducted on a Linux machine.

## Get Artifact
- Create a directory named `workspace` and open a terminal there
- Clone the project repository: `git clone git@github.com:LavaOps/Seq2ParDiff.git`

## Install Libraries and Tools

- `mkdir .lib && cd .lib`

- CVC4
    - `wget https://github.com/CVC4/CVC4-archived/releases/download/1.8/cvc4-1.8-x86_64-linux-opt`
    - `mv cvc4-1.8-x86_64-linux-opt cvc4`
    - `chmod +x cvc4`
- Z3
    - `wget https://github.com/Z3Prover/z3/releases/download/z3-4.13.0/z3-4.13.0-x64-glibc-2.31.zip`
    - `unzip z3-4.13.0-x64-glibc-2.31.zip`
    - `mv z3-4.13.0-x64-glibc-2.31 z3`
    - Check binary works: `./z3/bin/z3 --version`
- JDK 17
    - `wget https://builds.openlogic.com/downloadJDK/openlogic-openjdk/17.0.13+11/openlogic-openjdk-17.0.13+11-linux-x64.tar.gz`
    - `tar -xvf openlogic-openjdk-17.0.13+11-linux-x64.tar.gz`
- CIVL
    - `wget https://vsl.cis.udel.edu/lib/sw/civl/1.22/r5854/release/CIVL-1.22_5854.tgz`
    - `tar -xzvf CIVL-1.22_5854.tgz`
    - Open file .lib/CIVL-1.22_5854/bin/civl
    - Replace `/opt/CIVL-1.22_5854/lib/civl-1.22_5854.jar` by `<your-path-to-workspace>/.lib/CIVL-1.22_5854/lib/civl-1.22_5854.jar`
- Clang
    - `wget https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.8/clang+llvm-18.1.8-x86_64-linux-gnu-ubuntu-18.04.tar.xz`
    - `tar -xvf clang+llvm-18.1.8-x86_64-linux-gnu-ubuntu-18.04.tar.xz`
- libtinfo5_6.3-2
    - `wget http://security.ubuntu.com/ubuntu/pool/universe/n/ncurses/libtinfo5_6.3-2ubuntu0.1_amd64.deb`
    - `dpkg-deb -x libtinfo5_6.3-2ubuntu0.1_amd64.deb libtinfo5_6.3-2`
- Update PATH variable
    - Open file Seq2ParDiff/paths.sh and update the `LIB_PATH` at line 3 
    - `cd Seq2ParDiff`
    - `source paths.sh`
    - `java -version`
    - `civl config`
- Install other dependencies
    - `sudo apt install python3-venv gcc cloc` (For latest version of gcc, you need to build it from source (optional).)
    - `python3 -m venv .venv`
    - `source .venv/bin/activate`
    - `pip install pandas progressbar2`


## Dataset Preprocessing
If you want to start from the scratch, delete the two dataset directories: autoparllm and dataracebench, from the project directory.
Then, follow the below steps for preprocessing.

### AutoParLLM

#### Get Dataset
- Download the AutoParLLM dataset from `https://github.com/quazirafi/AutoParLLM/blob/main/datasets/full-dataset.zip`
- Unzip and rename `full-dataset` to `autoparllm` and keep it under Seq2ParDiff

#### Format Dataset (optional)
- From Seq2ParDiff directory: `find autoparllm -name "1.c" | xargs clang-format -i --style="{IndentWidth: 4}"`

#### Remove Duplicate Files
- Find duplicate files and save the result in `duplicate_files.log`
    - Use function: preprocess.py::find_duplicate_files()
- Remove the duplicates: preprocess.py::remove_duplicates()

#### Remove Files with Empty Parallel Blocks
- Find files with empty parallel block
    - From Seq2ParDiff directory: `./empty_parallel_blocks.sh <dataset> <filename> > data/<dataset>/empty_parallel_blocks.log`
        - Replace \<dataset\> by dataset name, i.e., autoparllm
        - Replace \<filename\> by filename where we want to look for empty parallel block, i.e., 1.c
- Delete the files and directories: preprocess.py::remove_files_with_empty_blocks()

#### Rename Directories
After removing duplicate files and files with empty parallel block, rename
file directories from 1 to number of files. Also, save the renaming maps,
the old and new directory names, to `rename_dir_map.log` for future reference.
- Use function: preprocess.py::rename_directories()

#### Fix Compilation Errors
Compile dataset files and check if there is any compilation error.
Fix the compilation errors, if any, in the source code files.
- Sequential
    - Compile dataset: sequential.py::compile()
    - Fix compile errors if any, according to `seq_compile_fails.log`
- Parallel
    - Compile dataset: parallel.py::compile()
    - Fix compile errors if any, according to `par_compile_fails.log`

#### Add printfs to Files without Output
We need program output for differential testing. Therefore, the programs 
should print the results that they calculate and store in different 
variables. Some C programs do not output anything and we cannot 
compare the results between the sequential and parallel executions 
without any output.
- Execute programs as sequential: sequential.py::execute()
    - The output is saved to config.seq_log_file for each program
- Find the programs, if any, that do not print output: preprocess.py::find_empty_log_files()
    - It saves the result in `empty_log_files.log`
- Add print statements to the files according to `empty_log_files.log` 


### DataRaceBench
- Get the DataRaceBench dataset from `https://github.com/LLNL/dataracebench/tree/v1.4.1/micro-benchmarks`
- Keep the micro-benchmarks directory under Seq2ParDiff and rename it to dataracebench
- Delete direcotories: polybench, utilities and benchmarkList.md file from dataracebench

#### Preprocess Dataset
- Use function: preprocess.py::preprocess_dataracebench()

## Differential Testing
- Sequential execution: `python3 sequential.py`
- Parallel execution: `python3 parallel.py`

## Execute CIVL for datasets
- Open file civl.sh and update line 22 with correct path (first part) and dataset name (last part with autoparllm or dataracebench)
- `chmod +x civl.sh`
- For each dataset, execute `./civl.sh`

## Execute ARCHER for datasets
- Open file archer.sh
- Update lines 21 with correct path
- Update line 30 with correct path (first part) and dataset name (last part with autoparllm or dataracebench)
- `chmod +x archer.sh`
- For each dataset, execute `./archer.sh`

## Generate Reports
- Generate execution results of Seq2ParDiff, CIVL and ARCHER
    - `python3 log_parser.py`
    - `python3 civl.py`
- Result files are located under data/<datasetname> directory (i.e., data/autoparllm).
    - Sequential execution (non-determinism): diff_test_seq.csv, diff_test_seq_fails.log
    - Parallel default threads: diff_test_without_env.csv, diff_test_without_env_fails.log
    - Parallel fixed threads: diff_test_with_env.csv, diff_test_with_env_fails.log
    - ARCHER result: archer.csv
    - CIVL result: civl.csv 


