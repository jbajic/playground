import argparse
import sys
from collections import defaultdict
from enum import Enum
from pathlib import Path
from typing import Optional

import matplotlib.pyplot as plt


class Keywords(Enum):
    CONTAINS = "contains"
    FIND = "find"
    INSERT = "insert"
    POP = "pop"
    PUSH = "push"
    RANDOM = "random"

    @classmethod
    def to_list(cls):
        return list(map(lambda c: c.value, cls))


class BenchmarkRow:
    def __init__(self, full_name: str, time: int, cpu: int, iterations: int):
        name = full_name.split("BM_Benchmark")
        assert len(name) == 2

        category_and_run_arg = name[1].split("/")
        self._name = category_and_run_arg[0]
        self._run_arg = None
        if len(category_and_run_arg) == 2:
            self._run_arg = category_and_run_arg[1]

        self._cpu = cpu
        self._time = time
        self._iterations = iterations

    @property
    def name(self):
        return self._name

    @property
    def run_arg(self):
        return self._run_arg

    @property
    def cpu(self):
        return self._cpu

    @property
    def time(self):
        return self._time

    @property
    def iterations(self):
        return self._iterations

    def __repr__(self) -> str:
        return f"BenchmarkRow(name={self._name}, run_arg={self._run_arg}, cpu={self._cpu}, time={self._time}, iterations={self._iterations})"


class GoogleBenchmarkResult:
    def __init__(self):
        self._categories = {k: [] for k in Keywords.to_list()}
        self._tests: dict[str, list[BenchmarkRow]] = defaultdict(list)

    def add_result(self, row: BenchmarkRow) -> None:
        if row._name not in self._tests:
            self._tests[row._name] = [row]
        else:
            self._tests[row._name].append(row)

    @property
    def tests(self):
        return self._tests

    @property
    def categories(self):
        return self._categories

    def __repr__(self) -> str:
        return f"{self._tests}"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Process benchmark results.")
    parser.add_argument("--log_file", type=str)
    return parser.parse_args()


def get_row_data(line: str) -> BenchmarkRow:
    splitted = line.split()
    assert len(splitted) == 6, f"Length is {len(splitted)}"
    assert splitted[2] == "ns"
    assert splitted[4] == "ns"
    return BenchmarkRow(splitted[0], int(splitted[1]), int(splitted[3]), int(splitted[5]))


def get_benchmark_res(args) -> Optional[GoogleBenchmarkResult]:
    file_path = Path(args.log_file)
    if not file_path.exists():
        print("Error file {file_path} not found!")
        return None
    with file_path.open("r") as file:
        res = GoogleBenchmarkResult()
        for line in file:
            if line.startswith("BM_Benchmark"):
                res.add_result(get_row_data(line))
        return res


def plot_res(results: GoogleBenchmarkResult) -> None:
    for name, rows in results.tests.items():
        if len(rows) > 1:
            # Print line chart
            x_axis = [elem.run_arg for elem in rows]
            y_time = [elem.time for elem in rows]
            y_cpu = [elem.cpu for elem in rows]
            y_iterations = [elem.iterations for elem in rows]
            plt.plot(x_axis, y_time, marker="", color="red", linewidth="2", label="time")
            plt.plot(x_axis, y_cpu, marker="", color="blue", linewidth="2", label="cpu")
            plt.title(f"Benchmark results {name}")
            plt.xlabel("Number of elements tested")
            plt.legend()
        else:
            print(f"Nothing to do for {name}...")
        plt.show()


def main():
    args = parse_args()
    res = get_benchmark_res(args)
    if res is None:
        print("Failed to get results from log file!")
        sys.exit(1)
    plot_res(res)


if __name__ == "__main__":
    main()
