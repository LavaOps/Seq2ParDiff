from pathlib import Path

this_dir = Path(__file__).resolve().parent
# my_dirs = ["3", "18", "25", "62", "68", "73", "100", "101", "117", "118", 
        #    "160", "171", "187", "208", "209", "237", "242", "245", "277", "287"]
class DatasetConfig:
    def __init__(self, database_name: str):
        self.db_name = database_name
        self.project_dir = this_dir.parent
        self.dir = this_dir / database_name
        self.data_dir = this_dir / "data" / database_name
        self.data_dir.mkdir(parents=True, exist_ok=True)
        self.src_dirs = sorted(
            [d for d in self.dir.iterdir() if d.is_dir() and d.name.isdigit()],
            key=lambda d: int(d.name) if d.name.isdigit() else float("inf")
        )
        # self.src_dirs = [this_dir / database_name / d for d in my_dirs]
        self.src_file = "1.c"
        self.seq_out_file = "1-seq.out"
        self.par_out_file = "1-par.out"
        self.civl_log_file = "civl.log"
        self.N = 50

    def seq_log_file(self, prefix):
        return f"{prefix}-seq.log"

    def par_log_file(self, prefix):
        return f"{prefix}-par.log"
