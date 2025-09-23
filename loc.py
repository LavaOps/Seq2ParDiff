# 
# Generate loc.csv:
#    find autoparllm/ -name "1.c" -print0 | xargs -0 cloc --by-file --csv --out=loc.csv
#    find dataracebench/ -name "1.c" -print0 | xargs -0 cloc --by-file --csv --out=loc.csv
# 

import pandas as pd

from config import DatasetConfig


def generate_stats(config: DatasetConfig):
    print(f"[{config.db_name}] LOC stats ...")

    loc_file = config.data_dir / "loc.csv"
    df = pd.read_csv(loc_file)
    df = df[(df["language"] == "C") & (df["filename"].str.endswith("1.c"))]

    loc_values = df["code"]

    stats = {
        "Files analyzed": len(loc_values),
        "Average LOC per file": loc_values.mean(),
        "Median LOC per file": loc_values.median(),
        "Min LOC": loc_values.min(),
        "Max LOC": loc_values.max(),
        "StdDev LOC": loc_values.std()
    }

    for k, v in stats.items():
        print(f"{k}: {v}")
        

if __name__ == "__main__":
    # 
    # Dataset I: AutoParLLM
    #
    config = DatasetConfig("autoparllm")
    generate_stats(config)

    # 
    # Dataset II: AutoParLLM
    #
    config = DatasetConfig("dataracebench")
    generate_stats(config)

    pass