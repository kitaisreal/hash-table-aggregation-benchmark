#!/usr/bin/env python3

import subprocess
import sys
import shutil
import argparse
import statistics
from prettytable import PrettyTable

BENCHMARK_EXECUTABLE = "hash_table_aggregation_benchmark"

MEASURE_RUNS = 3

FILES = [
    "data/WatchID.bin",
    "data/URLHash.bin",
    "data/UserID.bin",
    "data/RegionID.bin",
    "data/CounterID.bin",
    "data/TraficSourceID.bin",
    "data/AdvEngineID.bin",
]

HASH_FUNCTIONS = ["std_hash", "ch_hash", "absl_hash"]

HASH_TABLES = [
    "ch_hash_map",
    "absl_hash_map",
    "tsl_hopscotch_hash_map",
    "ankerl_unordered_dense_hash_map",
    "ska_flat_hash_map",
    "ska_bytell_hash_map",
    "std_hash_map",
]


def format_readable_size(bytes):
    unit_prefixes = ["", "Ki", "Mi", "Gi", "Ti", "Pi", "Ei", "Zi", "Yi"]
    suffix = "B"

    for unit_prefix in unit_prefixes[:-1]:
        if abs(bytes) < 1024.0:
            return f"{bytes:.2f} {unit_prefix}{suffix}"

        bytes /= 1024.0

    return f"{bytes:.2f} {unit_prefixes[len(unit_prefixes) - 1]}{suffix}"


def parse_argument(argument):
    return argument.replace(" ", "").split(",")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="HashTableAggregationBenchmark runner",
        description="Runs hash table aggregation benchmark",
    )
    parser.add_argument(
        "-hash-tables",
        "-ht",
        default=", ".join(HASH_TABLES),
        help="Hash tables to benchmark",
    )
    parser.add_argument(
        "-hash-functions",
        "-hf",
        default=", ".join(HASH_FUNCTIONS),
        help="Hash functions to benchmark",
    )
    parser.add_argument(
        "-files", "-f", default=", ".join(FILES), help="Files for benchmark"
    )
    parser.add_argument(
        "-runs", "-r", type=int, default=MEASURE_RUNS, help="Number of measure runs"
    )
    parser.add_argument(
        "-debug", action="store_true", help="Run benchmark in debug mode"
    )

    args = parser.parse_args()

    hash_tables = parse_argument(args.hash_tables)
    hash_functions = parse_argument(args.hash_functions)
    files = parse_argument(args.files)
    runs = args.runs
    debug = args.debug

    def print_debug(*args, **kwargs):
        if debug:
            print(*args, **kwargs)

    print_debug(
        f"Hash tables {hash_tables} hash functions {hash_functions} files {files} runs {runs} debug {debug}"
    )

    if not hash_tables:
        print("Invalid input empty hash tables", file=sys.stderr)
        exit(-1)

    if not hash_functions:
        print("Invalid input empty hash functions", file=sys.stderr)
        exit(-1)

    if not files:
        print("Invalid input empty files", file=sys.stderr)
        exit(-1)

    if runs <= 0:
        print("Invalid runs value, expected to be positive integer", file=sys.stderr)
        exit(-1)

    if shutil.which(BENCHMARK_EXECUTABLE) is None:
        print(f"{BENCHMARK_EXECUTABLE} was not found in PATH")

    for file in files:
        key_type_name = None
        keys_size = None
        hash_table_max_keys_size = None
        results = []

        for hash_table in hash_tables:
            for hash_function in hash_functions:
                hash_table_name = None
                hash_function_name = None
                elapsed_seconds_values = []
                memory_usage_in_bytes_values = []

                for _ in range(0, runs):
                    cmd = f"{BENCHMARK_EXECUTABLE} {hash_table} {hash_function} {file}"
                    output = subprocess.check_output(cmd, shell=True).decode()

                    print_debug(f"Output\n{output}")

                    lines = output.split("\n")

                    elapsed_seconds = None
                    memory_usage_in_bytes = None

                    for line in lines:
                        if not line:
                            continue

                        parts = line.split(": ")
                        key = parts[0]
                        value = parts[1]

                        if key == "Key type name":
                            key_type_name = value
                        elif key == "Keys size":
                            keys_size = int(value)
                        elif key == "Hash table":
                            hash_table_name = value
                        elif key == "Hash function":
                            hash_function_name = value
                        elif key == "Hash table size":
                            hash_table_size = int(value)

                            if hash_table_max_keys_size is None:
                                hash_table_max_keys_size = hash_table_size

                            if hash_table_size != hash_table_max_keys_size:
                                print(
                                    f"Invalid hash map size for hash table {hash_table} with hash {hash_function}",
                                    file=sys.stderr,
                                )

                            hash_table_max_keys_size = max(
                                hash_table_size, hash_table_max_keys_size
                            )
                        elif key == "Elapsed":
                            elapsed_seconds = float(value.split(" ")[0])
                        elif key == "Memory usage":
                            memory_usage_in_bytes = int(value)

                    elapsed_seconds_values.append(elapsed_seconds)
                    memory_usage_in_bytes_values.append(memory_usage_in_bytes)

                elapsed_seconds_median = statistics.median(elapsed_seconds_values)
                memory_usage_in_bytes_median = statistics.median(
                    memory_usage_in_bytes_values
                )
                results.append(
                    [
                        hash_table_name,
                        hash_function_name,
                        f"{elapsed_seconds_median:.2f}",
                        format_readable_size(memory_usage_in_bytes_median),
                    ]
                )

        print(
            f"File: {file}\nKey type: {key_type_name}\nKeys size: {keys_size}\nUnique keys size: {hash_table_max_keys_size}"
        )

        table = PrettyTable()
        table.field_names = [
            "Hash Table",
            "Hash Function",
            "Elapsed (sec)",
            "Memory Usage",
        ]
        table.align["Hash Table"] = "l"
        table.align["Hash Function"] = "l"
        table.align["Memory Usage"] = "r"
        table.add_rows(results)

        print(table)
