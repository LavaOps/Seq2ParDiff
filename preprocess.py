import json
import re
import shutil
import subprocess
import hashlib
from pathlib import Path
from collections import defaultdict

import pandas as pd
import progressbar

from config import DatasetConfig


def find_duplicate_files(config: DatasetConfig):
    """Find duplicate src files in dataset.
    Some dataset files contain the same code.
    Saves the result in duplicate_files.log.
    """
    print(f"[{config.db_name}] Finding duplicate {config.src_file} files ....")

    subprocess.run(["gcc", "--version"])
    bar = progressbar.ProgressBar(max_value=len(config.src_dirs),
                                  redirect_stdout=True).start()
    hash_map = defaultdict(list)

    for i, dir in enumerate(config.src_dirs):
        src_file = dir / config.src_file
        clean_file = dir / f"{src_file.stem}.clean"

        if not src_file.is_file():
            print(f"{dir.name}/{config.src_file} does not exists.")
            continue

        code = remove_comments_and_whitespace(src_file)
        code = preprocess_with_gcc(code, clean_file)

        if code:
            code_hash = hashlib.sha256(code.encode("utf-8")).hexdigest()
            hash_map[code_hash].append(dir.name)
        
        if clean_file.exists():
            clean_file.unlink()
        
        bar.update(i+1)
    bar.finish()

    output = []
    for dirs in hash_map.values():
        if len(dirs) > 1:
            dirs_str = ", ".join(dirs)
            output.append(dirs_str)

    output_file = config.data_dir / "duplicate_files.log"
    with open(output_file, "w") as f:
        f.write("\n".join(output))


def remove_comments_and_whitespace(file):
    with open(file, "r") as f:
        code = f.read()

    # Remove all // comments
    code = re.sub(r'//.*', '', code)

    # Remove all /* */ comments (multiline)
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)

    # Strip leading/trailing whitespace and collapse multiple spaces
    lines = [re.sub(r'\s+', ' ', line.strip())
             for line in code.splitlines() if line.strip()]
    
    return '\n'.join(lines)


def preprocess_with_gcc(code, clean_file) -> str:
    with open(clean_file, "w") as f:
        f.write(code)

    res = subprocess.run(
        ['gcc', '-E', '-P', '-x', 'c', clean_file],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        check=True
    )

    if res.returncode == 0:
        return res.stdout
    else:
        print(f"Error: {res.stderr}")
    return None
 

def remove_duplicates(config: DatasetConfig):
    """Delete the duplicates files from dataset
    according to duplicate_files.log.
    """
    print(f"[{config.db_name}] Deleteing duplicate files ...")

    filepath = config.data_dir / "duplicate_files.log"

    with open(filepath, "r") as f:
        lines = f.readlines()

    for line in lines:
        dirs = [
            item.strip()
            for item in line.strip().split(",")
            if item.strip()
        ]

        if len(dirs) < 2:
            continue

        to_delete = dirs[1:]

        for dir in to_delete:
            dir_path = config.dir / f"{dir}"
            if dir_path.is_dir():
                shutil.rmtree(dir_path)


def remove_files_with_empty_blocks(config: DatasetConfig):
    """Remove directories from dataset mentioned in file.
    Each line in file contians a filepath whose parent directory
    needs to be removed. i.e., autoparllm/211/1.c, here directory
    211 should be removed.
    """
    print(f"[{config.db_name}] Deleting files with empty parallel blocks ...")

    file = config.data_dir / "empty_parallel_blocks.log"
    with open(file, "r") as f:
        lines = f.readlines()
    
    lines = [line.strip() for line in lines if line.strip()]
    files = [config.dir.parent / x for x in lines]

    for file in files:
        if file.parent.is_dir():
            shutil.rmtree(file.parent)
        else:
            print(f"Not a directory: {file.parent}")


def rename_directories(config: DatasetConfig):
    """Rename dataset directories from 1 to dir_count.
    After deleting duplicates files (duplicate_files.log)
    and files with empty for loop blocks (empty_parallel_blocks.log),
    rename the remaining files as 1~dir_count.
    Save the renaming maps to rename_dir_map.log for future reference.
    """
    print(f"[{config.db_name}] Renaming directories ...")

    temp_map: dict[Path, Path] = {}
    for i, original in enumerate(config.src_dirs, start=1):
        temp_name = original.with_name(f"{original.name}->{i}")
        if original.is_dir():
            original.rename(temp_name)
            temp_map[temp_name] = original.with_name(str(i))

    dir_names = [x.name for x in list(temp_map.keys())]
    sorted_dir_names = sorted(
        dir_names, key=lambda x: int(str(x).split("->")[0]))

    output_file = config.data_dir / "rename_dir_map.log"
    with open(output_file, "w") as f:
        f.write("\n".join(sorted_dir_names))

    for temp, final in temp_map.items():
        if final.exists():
            print(f"Conflict: {final} already exists")
        else:
            temp.rename(final)


def find_empty_log_files(config: DatasetConfig):
    """Find which C programs have empty log files and
    save the result in empty_log_files.log.
    """
    print(f"[{config.db_name}] Looking for empty log files ...")

    res = []
    for dir in config.src_dirs:
        seq_log_file = dir / "log" / "seq_logs" / config.seq_log_file(1)
        if seq_log_file.exists():
            with open(seq_log_file, "r") as file:
                if file.read().strip() == "":
                    res.append(dir.name)

    output_file = config.data_dir / "empty_log_files.log"
    content = "\n".join(res)
    with open(output_file, "w") as f:
        f.write(content)
    
    project_path = str(config.project_dir.parent) + "/"
    print(f"[{config.db_name}] Result saved to "
              f"{str(output_file).replace(project_path, '')}")


def create_drb_info(config: DatasetConfig):
    """Read DRB-metainfo.json and create DRB-metainfo.csv."""

    print(f"[{config.db_name}] Creating DRB-metainfo.csv ...")

    metainfo_json = config.data_dir / "DRB-metainfo.json"

    with open(metainfo_json, "r") as f:
        data = json.load(f)

    rows = []
    for key, value in data.items():
        if key.endswith(".c") or key.endswith(".cpp"):
            row = {
                "id": value["basicInfo"].get("id", 0),
                "file": key,
                "plabel": ",".join(value["basicInfo"].get("Plabel", [])),
                "language": value["basicInfo"].get("language", ""),
                "ompversion": value["OMPProperty"].get("version", ""),
                "hw": value["OMPProperty"].get("HW", ""),
                "pattern": ",".join(value["codeProeprty"].get("pattern", [])),
            }
            rows.append(row)
    
    csv_file = config.data_dir / "DRB-metainfo.csv"
    df = pd.DataFrame(rows)
    df.to_csv(csv_file, index=False)


def create_db_structure(config: DatasetConfig):
    """Rename DRB files to 1.c and keep them in directories 1, 2, 3, ...
    Directory names are based on id from DRB-metainfo.json.
    """
    print(f"[{config.db_name}] Creating directory structure ...")

    csv_file = config.data_dir / "DRB-metainfo.csv"
    df = pd.read_csv(csv_file)

    for _, row in df.iterrows():
        dir_name = row["id"]
        dir = config.dir / f"{dir_name}"
        src_file = config.dir / row["file"]
        dst_file = dir / "1.c"
        try:
            dir.mkdir(parents=True, exist_ok=True)
            if src_file.exists():
                src_file.rename(dst_file)
                # shutil.copy2(src_file, dst_file)
        except Exception as e:
            print(f"Exception: {e}")


def move_files_to_skipped(config: DatasetConfig):
    # 1. Skip cpp files: 4 (86, 87, 100, 101)
    # 2. Skip files to skipped based on seq_compile_fails.log: 34
    # 3. Skip files for empty_log_files: 59
    # 4. Skip files only targeting parallel: 2 (76, 108)
    # 5. Skip infinity loop files: 4 (190, 191, 198, 199)
    # Total: 103
    # Remaining files: 201 - 103 = 98

    skipped_dir = config.project_dir / "differential-testing" / "dataracebench-skipped"
    skipped_dir.mkdir(parents=True, exist_ok=True)

    cpp_files = ["86", "87", "100", "101"]
    move_dirs(config.dir, skipped_dir, cpp_files)

    file_comp_fails = config.data_dir / "seq_compile_fails.log"
    with open(file_comp_fails, "r") as f:
        lines = f.readlines()
    pattern = re.compile(r"^(\d+)/1\.c:")
    comp_fails = []
    for line in lines:
        match = pattern.match(line)
        if match:
            comp_fails.append(match.group(1))
    move_dirs(config.dir, skipped_dir, comp_fails)

    file_empty_logs = config.data_dir / "empty_log_files.log"
    with open(file_empty_logs, "r") as f:
        lines = f.readlines()
    empty_logs = [line.strip() for line in lines]
    move_dirs(config.dir, skipped_dir, empty_logs)

    only_parallel_files = ["76", "108"]
    move_dirs(config.dir, skipped_dir, only_parallel_files)

    infinity_loop_files = ["190", "191", "198", "199"]
    move_dirs(config.dir, skipped_dir, infinity_loop_files)


def move_dirs(src_root, dst_root, dirs):
    for dir in dirs:
        src = src_root / dir
        dst = dst_root / dir
        if src.exists() and src.is_dir():
            print(f"Moving {src} -> {dst}")
            shutil.move(src, dst)
        else:
            print(f"{src} not found")


def files_after_preprocess(config: DatasetConfig):
    metainfo_file = config.data_dir / "DRB-metainfo.csv"
    df = pd.read_csv(metainfo_file)
    all_dirs = df["id"].astype(str).tolist()

    empty_dirs = []
    emtpy_log_file = config.data_dir / "empty_log_files.log"
    with open(emtpy_log_file, "r") as f:
        empty_dirs = f.read().strip().splitlines()

    skipped_dir = config.project_dir / "differential-testing" / "dataracebench-skipped"
    skipped_dirs = [d.name for d in skipped_dir.iterdir() if d.is_dir() and d.name.isdigit()]

    excluded = set(empty_dirs) | set(skipped_dirs)
    remaining_dirs = [item for item in all_dirs if item not in excluded]
    remaining_dirs = sorted(remaining_dirs)
    
    filtered_df = df[df["id"].astype(str).isin(remaining_dirs)]
    filtered_df = filtered_df[["id", "file", "plabel"]]
    res_file = config.data_dir / "files_after_preprocessing.csv"
    filtered_df.to_csv(res_file, index=False)


def preprocess_dataracebench(config: DatasetConfig):
    create_drb_info(config)
    create_db_structure(config)
    find_empty_log_files(config)
    move_files_to_skipped(config)
    files_after_preprocess(config)


if __name__ == "__main__":
    # 
    # Dataset I: AutoParLLM
    # 
    config = DatasetConfig("autoparllm")
    # find_duplicate_files(config)
    # remove_duplicates(config)
    # remove_files_with_empty_blocks(config)
    # rename_directories(config)
    # find_empty_log_files(config)

    # 
    # Dataset II: DataRaceBench
    # 
    config = DatasetConfig("dataracebench")
    # preprocess_dataracebench(config)
    
    pass
    