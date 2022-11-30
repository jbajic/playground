import argparse
import sys
from dataclasses import dataclass
from enum import Enum
from pathlib import Path
from typing import Optional

import matplotlib.pyplot as plt


class Operation(Enum):
    CONTAINS = "contains"
    FIND = "find"
    INSERT = "insert"
    POP = "pop"
    PUSH = "push"
    RANDOM = "random"

    @classmethod
    def to_list(cls):
        return list(map(lambda c: c.value, cls))


@dataclass(frozen=True)
class DatastructureOperationRow:
    name: str
    category: Operation
    real_time: int
    cpu_time: int
    iterations: int
    datastructure: str
    run_arg: Optional[str]


class DatastructureResults:
    def __init__(self):
        self._results: list[DatastructureOperationRow] = []
        self._datastructure = None

    def add_datastructure_result(self, row: DatastructureOperationRow) -> None:
        if self._datastructure is None:
            self._datastructure = row.datastructure
        assert self._datastructure == row.datastructure
        self._results.append(row)

    @property
    def results(self) -> list[DatastructureOperationRow]:
        return self._results

    @property
    def datastructure(self) -> str:
        assert self._datastructure is not None
        return self._datastructure


class OperationResults:
    def __init__(self):
        self._results: dict[Operation, list[DatastructureResults]] = dict()
        self._category = None

    def results(self, category: Operation) -> list[DatastructureResults]:
        return self._results[category]

    @property
    def category(self) -> Operation:
        assert self._category is not None
        return self._category


def find_category(s: str) -> Operation:
    for category in Operation.to_list():
        if category in s.lower():
            return Operation[category.upper()]
    raise Exception(f"Category in {s} not found")


def get_row_data(line: str) -> DatastructureOperationRow:
    splitted = line.split()
    assert len(splitted) == 6, f"Length is {len(splitted)}"
    assert splitted[2] == "ns"
    assert splitted[4] == "ns"

    full_name = splitted[0].split("BM_Benchmark")
    assert len(full_name) == 2
    category_and_run_arg = full_name[1].split("/")
    name = category_and_run_arg[0]

    run_arg = None
    if len(category_and_run_arg) == 2:
        run_arg = category_and_run_arg[1]
    return DatastructureOperationRow(name, find_category(name), splitted[1], splitted[3], splitted[5], run_arg)


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


def plot_by_name(results: GoogleBenchmarkResult) -> None:
    for name, rows in results.tests.items():
        if len(rows) > 1:
            # Print line chart
            x_axis = [elem.run_arg for elem in rows]
            y_time = [elem.time for elem in rows]
            y_cpu = [elem.cpu for elem in rows]
            plt.plot(x_axis, y_time, marker="", color="red", linewidth="2", label="time")
            plt.plot(x_axis, y_cpu, marker="", color="blue", linewidth="2", label="cpu")
            plt.title(f"Benchmark results {name}")
            plt.xlabel("Number of elements tested")
            plt.legend()
        else:
            print(f"Nothing to do for {name}...")
        plt.show()


def plot_by_category(results: GoogleBenchmarkResult) -> None:
    for category, rows in results.categories.items():
        if len(rows) > 1:
            # Print line chart
            x_axis = [elem.run_arg for elem in rows]
            y_time = [elem.time for elem in rows]
            # y_cpu = [elem.cpu for elem in rows]
            plt.plot(x_axis, y_time, marker="", color="red", linewidth="2", label="time")
            # plt.plot(x_axis, y_cpu, marker="", color="blue", linewidth="2", label="cpu")
            plt.title(f"Benchmark results {category}")
            plt.xlabel("Number of elements tested")
            plt.legend()
        else:
            print(f"Nothing to do for {name}...")
        plt.show()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Process benchmark results.")
    parser.add_argument("--log_file", type=str)
    return parser.parse_args()


def main():
    args = parse_args()
    res = get_benchmark_res(args)
    if res is None:
        print("Failed to get results from log file!")
        sys.exit(1)
    plot_res(res)


if __name__ == "__main__":
    main()
