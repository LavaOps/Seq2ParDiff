import pandas as pd

from config import DatasetConfig


def create_civl_report(config: DatasetConfig):
    """Create civl.csv with execution status for each dataset file.
    Both stdout and stderr are saved to config.civl_log_file for 
    each file execution. When CIVL runs and detects any bug, it creates 
    trace and log files in CIVLREP, otherwise this directory is either
    empty, not created or has files other than trace and log files.
    """
    print(f"[{config.db_name}] Creating CIVL report ...")
    data = []
    for dir in config.src_dirs:
        civlrep_dir = dir / "CIVLREP"
        status = "crash"
        if civlrep_dir.exists() and civlrep_dir.is_dir():
            if not any(civlrep_dir.iterdir()):
                status = "pass"
            elif any(civlrep_dir.glob("*.trace")):
                status = "bug"
            else:
                status = "crash"
        data.append([f"{dir.name}/{config.src_file}", status])
    
    df = pd.DataFrame(data, columns=["file", "stataus"])
    csv_file = config.data_dir / "civl.csv"
    df.to_csv(csv_file, index=False)
    print(f"[{config.db_name}] Report saved to {csv_file}")


if __name__ == "__main__":
    # 
    # Dataset I: AutoParLLM
    #
    config = DatasetConfig("autoparllm")
    create_civl_report(config)

    # 
    # Dataset II: DataRaceBench
    #
    config = DatasetConfig("dataracebench")
    create_civl_report(config)
    
    pass


