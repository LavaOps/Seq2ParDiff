import re
import subprocess
import shutil

import progressbar
import pandas as pd

from config import DatasetConfig


def compile(config: DatasetConfig):
    """Compile dataset programs as parallel and
    save any failures in par_compile_fails.log.
    The compiled filename is config.par_out_file.
    """
    print(f"[{config.db_name}] Compiling dataset parallelly ...")

    subprocess.run(["gcc", "--version"])
    bar = progressbar.ProgressBar(max_value=len(config.src_dirs),
                                  redirect_stdout=True).start()
    fails = []
    project_path = str(config.project_dir.parent) + "/"
    for i, dir in enumerate(config.src_dirs):
        log_dir = dir / "log"
        log_dir.mkdir(parents=True, exist_ok=True)

        src_filepath = dir / config.src_file
        exe_filepath = log_dir / config.par_out_file
        
        if exe_filepath.exists():
            exe_filepath.unlink()

        cmd = ["gcc", "-fopenmp", src_filepath, "-o", exe_filepath]
        res = subprocess.run(cmd, stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE, text=True)
        
        if res.stderr.strip():
            msg = f"{dir.name}/{config.src_file}:\n{res.stderr}"
            msg = msg.replace(project_path, "")
            fails.append(msg)
        
        bar.update(i+1)
    bar.finish()

    print(f"[{config.db_name}] Compilation fails for {len(fails)} files")

    if len(fails) > 0:
        output_file = config.data_dir / "par_compile_fails.log"
        with open(output_file, "w") as f:
            f.write("\n".join(fails))
        print(f"[{config.db_name}] Compilation failures saved to "
              f"{str(output_file).replace(project_path, '')}")


def execute_without_env(config: DatasetConfig, n=10):
    """Execute parallel programs n times and
    save any failures in par_execution_fails.log.
    Save each result in config.par_log_file in log/without_env directory.
    """
    print(f"[{config.db_name}] Executing dataset parallelly ...")

    bar = progressbar.ProgressBar(max_value=len(config.src_dirs),
                                  redirect_stdout=True).start()
    for i, dir in enumerate(config.src_dirs):
        log_dir = dir / "log"
        without_env_log_dir = log_dir / "without_env"

        if without_env_log_dir.exists():
            shutil.rmtree(without_env_log_dir)

        without_env_log_dir.mkdir(parents=True, exist_ok=True)

        exe_file = log_dir / config.par_out_file
        
        if not exe_file.exists():
            continue

        for iter in range(n):
            log_file = without_env_log_dir / config.par_log_file(iter + 1)
            with open(log_file, "w") as f:
                subprocess.run(exe_file, stdout=f, stderr=f, text=True)
        bar.update(i+1)
    bar.finish()


def generate_env(config: DatasetConfig):
    """Read TSL test cases (env.tsl.tsl) and generate env.csv  
    containing commands with env variables to use in parallel executions.
    """
    print(f"[{config.db_name}] Generating env.csv ...")

    tsl_file = config.data_dir / "env.tsl.tsl"
    with open(tsl_file, "r") as f:
        tsl_lines = f.readlines()
    
    key1 = "OMP_NUM_THREADS"
    # key2 = "OMP_SCHEDULE-modifier"
    # key3 = "OMP_SCHEDULE-kind"
    # key4 = "OMP_SCHEDULE-chunk"

    key1_pattern = re.compile(fr"^\s+{key1}\s+:\s+(.*)$")
    # key2_pattern = re.compile(fr"^\s+{key2}\s+:\s+(.*)$")
    # key3_pattern = re.compile(fr"^\s+{key3}\s+:\s+(.*)$")
    # key4_pattern = re.compile(fr"^\s+{key4}\s+:\s+(.*)$")

    key1_values = [matched.group(1) for line in tsl_lines
                   if (matched := key1_pattern.search(line))]
    # key2_values = [matched.group(1) for line in tsl_lines
    #                if (matched := key2_pattern.search(line))]
    # key3_values = [matched.group(1) for line in tsl_lines
    #                if (matched := key3_pattern.search(line))]
    # key4_values = [matched.group(1) for line in tsl_lines
    #                if (matched := key4_pattern.search(line))]

    commands = []
    for i in range(len(key1_values)):
        # command = (f"OMP_NUM_THREADS=\"{key1_values[i]}\""
        #           f" OMP_SCHEDULE=\"{key2_values[i]}:{key3_values[i]},{key4_values[i]}\"")
        command = f"OMP_NUM_THREADS=\"{key1_values[i]}\""
        commands.append(command)
    
    data = {
        key1: key1_values,
        # key2: key2_values,
        # key3: key3_values,
        # key4: key4_values,
        "command": commands
    }

    df = pd.DataFrame(data)
    csv_file = config.data_dir / "env.csv"
    df.to_csv(csv_file, header=True, index=False)


def execute_with_env(config: DatasetConfig, n=10):
    """Execute parallel programs n times (n=number of rows in env.csv) and
    save any failures in par_execution_with_env_fails.log.
    Save each execution result in config.par_log_file in log/with_env directory.
    """
    print(f"[{config.db_name}] Executing parallel programs with env ...")

    env_file = config.data_dir / "env.csv"
    df = pd.read_csv(env_file)

    bar = progressbar.ProgressBar(max_value=len(config.src_dirs),
                                  redirect_stdout=True).start()
    for i, dir in enumerate(config.src_dirs):
        log_dir = dir / "log"
        with_env_log_dir = log_dir / "with_env"

        if with_env_log_dir.exists():
            shutil.rmtree(with_env_log_dir)

        with_env_log_dir.mkdir(parents=True, exist_ok=True)

        exe_filepath = log_dir / config.par_out_file

        if not exe_filepath.exists():
            continue

        for j, row in df.iterrows():
            for k in range(n):
                log_file = with_env_log_dir / config.par_log_file(f"{j+1}-{k+1}")
                with open(log_file, "w") as f_log:
                    subprocess.run(f'export {row["command"]} && {exe_filepath}',
                                stdout=f_log, stderr=f_log,
                                shell=True, text=True)
        
        bar.update(i+1)
    bar.finish()


if __name__ == "__main__":
    # 
    # Dataset I: AutoParLLM
    #
    config = DatasetConfig("autoparllm")
    compile(config)
    execute_without_env(config, config.N)
    generate_env(config)
    execute_with_env(config, config.N)

    # 
    # Dataset II: AutoParLLM
    #
    config = DatasetConfig("dataracebench")
    compile(config)
    execute_without_env(config, config.N)
    generate_env(config)
    execute_with_env(config, config.N)


    pass