import subprocess
import shutil

import progressbar

from config import DatasetConfig


def compile(config: DatasetConfig):
    """Compile dataset src_file programs as sequential and
    save any failures in seq_compile_fails.log.
    The compiled filename is config.seq_out_file.
    """
    print(f"[{config.db_name}] Compiling dataset sequentially ...")

    subprocess.run(["gcc", "--version"])
    bar = progressbar.ProgressBar(max_value=len(config.src_dirs),
                                  redirect_stdout=True).start()
    fails = []
    project_path = str(config.project_dir.parent) + "/"
    for i, dir in enumerate(config.src_dirs):
        log_dir = dir / "log"
        log_dir.mkdir(parents=True, exist_ok=True)

        src_filepath = dir / config.src_file
        exe_filepath = log_dir / config.seq_out_file

        cmd = ["gcc", src_filepath, "-o", exe_filepath]
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
        output_file = config.data_dir / "seq_compile_fails.log"
        with open(output_file, "w") as f:
            f.write("\n".join(fails))
        print(f"[{config.db_name}] Compilation failures saved to "
              f"{str(output_file).replace(project_path, '')}")


def execute(config: DatasetConfig, n=10):
    """Execute dataset files and
    save any failures in seq_compile_fails.log.
    Save the result in config.seq_log_file.
    """
    print(f"[{config.db_name}] Executing dataset sequentially ...")

    bar = progressbar.ProgressBar(max_value=len(config.src_dirs),
                                  redirect_stdout=True).start()
    for i, dir in enumerate(config.src_dirs):
        log_dir = dir / "log"
        seq_log_dir = log_dir / "seq_logs"

        if seq_log_dir.exists():
            shutil.rmtree(seq_log_dir)

        seq_log_dir.mkdir(parents=True, exist_ok=True)

        exe_filepath = log_dir / config.seq_out_file

        if not exe_filepath.exists():
            continue

        for iter in range(n):
            log_filepath = seq_log_dir / config.seq_log_file(iter + 1)
            with open(log_filepath, "w") as f:
                subprocess.run(exe_filepath, stdout=f, stderr=f, text=True)
    
        bar.update(i+1)
    bar.finish()


if __name__ == "__main__":
    # 
    # Dataset I: AutoParLLM
    #
    config = DatasetConfig("autoparllm")
    compile(config)
    execute(config, config.N)

    # 
    # Dataset II: DataRaceBench
    #
    config = DatasetConfig("dataracebench")
    compile(config)
    execute(config, config.N)

    pass