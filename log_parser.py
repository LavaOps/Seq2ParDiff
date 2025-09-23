from pathlib import Path

import pandas as pd
import progressbar

from config import DatasetConfig


def parse_logs(config: DatasetConfig, n=10, log_type="without_env"):
    """Parse sequential and parallel execution
    output log files and compare the content. 
    Save the comparison result in diff_test_*.csv.

    Parameters:
    -----------
    n: number of log files to parse for each source file (1~n.log).
    with_env: denotes whether parallel executions of source files were with 
        setting environment variables or without of them. It tells where
        to look for the log files.
    """
    print(f"[{config.db_name}] Parsing log files for {log_type} ...")

    log_dir = "without_env"
    filename = "diff_test_without_env.csv"

    if log_type == "with_env":
        log_dir = "with_env"
        filename = "diff_test_with_env.csv"
    elif log_type == "seq":
        log_dir = "seq_logs"
        filename = "diff_test_seq.csv"

    data = {"file": [], "iteration": [], "status": []}
    bar = progressbar.ProgressBar(max_value=len(config.src_dirs),
                                  redirect_stdout=True).start()
    for i, dir in enumerate(config.src_dirs):
        src_log_file = dir / "log" / "seq_logs" / config.seq_log_file(1)
        # src_log_file = dir / "log" / "with_env" / config.par_log_file("1-1")

        if log_type == "with_env":
            env_file = config.data_dir / "env.csv"
            df = pd.read_csv(env_file)

            for j, _ in df.iterrows():
                for k in range(n):
                    data["file"].append(f"{dir.name}/{config.src_file}")
                    trg_log_file = dir / "log" / log_dir / config.par_log_file(f"{j+1}-{k+1}")

                    if trg_log_file.exists():
                        data["iteration"].append(f"{j+1}-{k+1}")
                        is_equal = compare_files(src_log_file, trg_log_file)
                        if is_equal:
                            data["status"].append("pass")
                        else:
                            data["status"].append("fail")
                    else:
                        data["iteration"].append("")
                        data["status"].append("")
        else:
            for j in range(n):
                data["file"].append(f"{dir.name}/{config.src_file}")
                trg_log_file = dir / "log" / log_dir / config.par_log_file(j+1)
                if log_type == "seq":
                    trg_log_file = dir / "log" / log_dir / config.seq_log_file(j+1)

                if trg_log_file.exists():
                    data["iteration"].append(f"{j+1}")
                    is_equal = compare_files(src_log_file, trg_log_file)
                    if is_equal:
                        data["status"].append("pass")
                    else:
                        data["status"].append("fail")
                else:
                    data["iteration"].append("")
                    data["status"].append("")
        
        bar.update(i+1)
    bar.finish()

    df = pd.DataFrame(data)
    output_file = config.data_dir / filename
    df.to_csv(output_file, header=True, index=False)

    project_path = str(config.project_dir.parent) + "/"
    print(f"[{config.db_name}] Result saved to "
              f"{str(output_file).replace(project_path, '')}")


def compare_files(file1, file2):
    """Compare files line by line without loading them
    fully into memory."""
    with open(file1, 'rb') as f1, open(file2, 'rb') as f2:
        for line1, line2 in zip(f1, f2):
            if line1 != line2:
                return False
    return True
            

def diff_test_fails(config: DatasetConfig, log_type="without_env"):
    """Read diff_test_*.csv, find fail cases and 
    save the result in diff_test_*_fails.log.
    """
    print(f"[{config.db_name}] Filtering fail cases for {log_type} ...")

    filename = "diff_test_without_env.csv"
    if log_type == "with_env":
        filename = "diff_test_with_env.csv"
    elif log_type == "seq":
        filename = "diff_test_seq.csv"

    csv_file = config.data_dir / filename
    df = pd.read_csv(csv_file, dtype=str)
    df = df[df["status"] == "fail"]

    files = df["file"].tolist()
    files = list(set(files))

    # Remove the nondet ones from the results.
    if log_type in ["without_env", "with_env"]:
        seq_fail_log = config.data_dir / "diff_test_seq_fails.log"
        with open(seq_fail_log, "r") as f:
            seq_fails = f.read()
        seq_fails = seq_fails.strip().split("\n")
        files = [item for item in files if item not in seq_fails]

    files = sorted(
        files,
        key=lambda x: int(str(Path(x).parent))
        if str(Path(x).parent).isdigit()
        else float("inf")
    )
    content = "\n".join(files)

    fail_filepath = config.data_dir / f"{csv_file.stem}_fails.log"
    with open(fail_filepath, "w") as f:
        f.write(content)


def parse_sanitizer_logs(config: DatasetConfig, tool_name):
    """Parse archer generated logs and create archer.csv.
    Read archer.log files and seach for 'ThreadSanitizer:' text.
    If found, that is a potential file with bug detection.
    """
    print(f"[{config.db_name}] Parsing {tool_name} log files ...")

    data = {"file": [], "status": []}
    bar = progressbar.ProgressBar(max_value=len(config.src_dirs),
                                  redirect_stdout=True).start()
    for i, dir in enumerate(config.src_dirs):
        data["file"].append(f"{dir.name}/{config.src_file}")
        log_file = dir / "log" / f"{tool_name}.log"

        if log_file.exists():
            if search_for_text(log_file, "ThreadSanitizer: data race"):
                data["status"].append("data race")
            elif search_for_text(log_file, "ThreadSanitizer:"):
                data["status"].append("error")
            else:
                data["status"].append("pass")
        else:
            data["status"].append("")
        
        bar.update(i+1)
    bar.finish()

    df = pd.DataFrame(data)
    output_file = config.data_dir / f"{tool_name}.csv"
    df.to_csv(output_file, header=True, index=False)

    project_path = str(config.project_dir.parent) + "/"
    print(f"[{config.db_name}] Result saved to "
              f"{str(output_file).replace(project_path, '')}")


def search_for_text(file, text):
    "Reads a large file line-by-line and prints lines containing text."
    try:
        with open(file, 'r', encoding='utf-8', errors='ignore') as f:
            for line in f:
                if text in line:
                    return True
    except FileNotFoundError:
        print(f"File not found: {file}")
    except Exception as e:
        print(f"Error reading file: {e}")
    return False


if __name__ == "__main__":
    # 
    # Dataset I: AutoParLLM
    #
    config = DatasetConfig("autoparllm")
    parse_logs(config, config.N, "seq")
    diff_test_fails(config, "seq")
    parse_logs(config, config.N, "without_env")
    diff_test_fails(config, "without_env")
    parse_logs(config, config.N, "with_env")
    diff_test_fails(config, "with_env")
    parse_sanitizer_logs(config, "archer")

    # 
    # Dataset II: DataRaceBench
    #
    config = DatasetConfig("dataracebench")
    parse_logs(config, config.N, "seq")
    diff_test_fails(config, "seq")
    parse_logs(config, config.N, "without_env")
    diff_test_fails(config, "without_env")
    parse_logs(config, config.N, "with_env")
    diff_test_fails(config, "with_env")
    parse_sanitizer_logs(config, "archer")

    pass
