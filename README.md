# Hash tables aggregation benchmark

## Motivation

This benchmark is created to compare the performance of different hash tables with different hash functions in in-memory aggregation scenario.

Benchmark is based on real anonymized web analytics data from [Yandex.Metrica dataset](https://clickhouse.com/docs/en/getting-started/example-datasets/metrica).

Benchmark computes mapping for each unique key to count for columns from the dataset, similar to such SQL query `SELECT column, count(column) FROM hits GROUP BY column`.

Because each column in the benchmark has different cardinality and distribution, it is possible to check how different hash tables work for in-memory aggregation on real-world data.

There are two different scenarios:

1. When hash table fits in CPU caches. Performance of hash table operations depends on arithmetic operations like hash function calculation, computing slot location, elements comparisons, and other operations that are required for specific hash table memory layout.
2. When hash table does not fit in CPU caches. For such a scenario, number of random memory accesses per operation is the most important factor for hash table performance.

Here are some general recommendations that can be applied to all hash table implementations:

1. You should avoid complex logic on a hot path of your hash table operations. If there are a lot of instructions on the hot path, hash table will work slow when all data fits in CPU caches.
2. You should not store a lot of additional metadata in your hash table because your hash table will stop fitting into CPU caches quickly.
3. You should decrease the number of random memory accesses in your hash table operations because otherwise, it will significantly slow down your hash table implementation after hash table does not fit in CPU caches. Ideally, you should have one memory access for each operation. This also implies that you cannot make complex layouts (2 hash tables, keys and values separation, complex metadata) because usually, this will require additional memory accesses during operations.

Additionally, for the aggregation scenario, you need to consider not only lookup/insert latency but also the memory size of hash table. If during aggregation hash table does not fit in RAM memory, the aggregation algorithm should switch implementation from in-memory aggregation to external memory aggregation, but this will work significantly slower.

For more information, take a look at my blog post about [hash tables](https://maksimkita.com/blog/hash_tables.html).

## Examples

Benchmark itself is a `hash_table_aggregation_benchmark` binary that takes `hash_table`, `hash_function`, and `file` in ClickHouse
[RowBinaryWithNamesAndTypes](https://clickhouse.com/docs/en/interfaces/formats#rowbinarywithnamesandtypes) format and runs in-memory aggregation.

```
hash_table_aggregation_benchmark absl_hash_map absl_hash data/WatchID.bin

Hash table type: absl_hash_map
Hash function type: absl_hash
Key type name: Int64
File name: data/WatchID.bin
Keys size: 99997497
Hash table: absl::flat_hash_map
Hash function: absl::Hash
Hash table size: 99997493
Elapsed: 10.7699 (9284909 elem/sec.)
Memory usage: 2285594168
```

`benchmark.py` is just a wrapper around `hash_table_aggregation_benchmark` that provides the ability to specify multiple hash tables, hash functions, and files
and run `hash_table_aggregation_benchmark` for each combination.

Run benchmark to test Abseil Hash Map using Abseil hash function for `WatchID` column:

```
./benchmark.py --hash-tables="absl_hash_map" --hash-functions="absl_hash" --files="data/WatchID.bin"

File: data/WatchID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 99997493
+---------------------+---------------+---------------+--------------+
| Hash Table          | Hash Function | Elapsed (sec) | Memory Usage |
+---------------------+---------------+---------------+--------------+
| absl::flat_hash_map | absl::Hash    |     10.77     |     2.13 GiB |
+---------------------+---------------+---------------+--------------+
```

Run benchmark to test ClickHouse Hash Map using all available hash functions for `WatchID` column:

```
./benchmark.py --hash-tables="ch_hash_map" --files="data/WatchID.bin"

File: data/WatchID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 99997493
+--------------------+-----------------+---------------+--------------+
| Hash Table         | Hash Function   | Elapsed (sec) | Memory Usage |
+--------------------+-----------------+---------------+--------------+
| ClickHouse HashMap | std::hash       |      6.14     |     4.00 GiB |
| ClickHouse HashMap | ClickHouse hash |      6.98     |     4.00 GiB |
| ClickHouse HashMap | absl::Hash      |      6.55     |     4.00 GiB |
+--------------------+-----------------+---------------+--------------+
```

Run benchmark to test ClickHouse Hash Map and Abseil Hash Map using Abseil hash function and standard hash function for `WatchID` and `UserID` columns:

```
./benchmark.py --hash-tables="ch_hash_map, absl_hash_map" --hash-functions="absl_hash, std_hash" --files="data/WatchID.bin, data/UserID.bin"

File: data/WatchID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 99997493
+---------------------+---------------+---------------+--------------+
| Hash Table          | Hash Function | Elapsed (sec) | Memory Usage |
+---------------------+---------------+---------------+--------------+
| ClickHouse HashMap  | absl::Hash    |      6.56     |     4.00 GiB |
| ClickHouse HashMap  | std::hash     |      6.19     |     4.00 GiB |
| absl::flat_hash_map | absl::Hash    |     10.53     |     2.13 GiB |
| absl::flat_hash_map | std::hash     |      9.31     |     2.13 GiB |
+---------------------+---------------+---------------+--------------+

File: data/UserID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 17630976
+---------------------+---------------+---------------+--------------+
| Hash Table          | Hash Function | Elapsed (sec) | Memory Usage |
+---------------------+---------------+---------------+--------------+
| ClickHouse HashMap  | absl::Hash    |      1.96     |     1.00 GiB |
| ClickHouse HashMap  | std::hash     |      1.86     |     1.00 GiB |
| absl::flat_hash_map | absl::Hash    |      2.82     |   547.74 MiB |
| absl::flat_hash_map | std::hash     |      2.71     |   547.62 MiB |
+---------------------+---------------+---------------+--------------+
```

You can extract columns from other datasets or generate columns using `clickhouse-local` (it is downloaded as part of the benchmark data load, or you can download it manually).
For example, you can generate a column with 150 million random numbers and run a benchmark to check ClickHouse Hash Map and Abseil Hash Map against this column:

```
./clickhouse local --multiquery "INSERT INTO TABLE FUNCTION file('RandomNumbers.bin', RowBinaryWithNamesAndTypes) SELECT rand64() FROM numbers_mt(150000000);"

File: RandomNumbers.bin
Key type: UInt64
Keys size: 150000000
Unique keys size: 150000000
+---------------------+-----------------+---------------+--------------+
| Hash Table          | Hash Function   | Elapsed (sec) | Memory Usage |
+---------------------+-----------------+---------------+--------------+
| ClickHouse HashMap  | std::hash       |     11.30     |     8.00 GiB |
| ClickHouse HashMap  | ClickHouse hash |     13.08     |     8.00 GiB |
| ClickHouse HashMap  | absl::Hash      |     12.01     |     8.00 GiB |
| absl::flat_hash_map | std::hash       |     15.72     |     4.25 GiB |
| absl::flat_hash_map | ClickHouse hash |     17.98     |     4.25 GiB |
| absl::flat_hash_map | absl::Hash      |     17.58     |     4.25 GiB |
+---------------------+-----------------+---------------+--------------+
```

## Prerequisites

1. git
2. python3 with pip installed
3. cmake with minimum version 3.20
4. clang-15 or higher
5. wget
6. curl

For Ubuntu Linux with 22.04 LTS these prerequisites can be downloaded using the following command:
```
sudo apt install git cmake clang-15 python3 python3-pip wget curl
```

## Build instructions

Clone repository with benchmark and checkout submodules

```
git clone git@github.com:kitaisreal/hash-table-aggregation-benchmark.git
cd hash-table-aggregation-benchmark
git submodule update --init --recursive
```

Download benchmark data (a new `data` folder will be created). All benchmark data takes around 20 GB.

```
./load_data.sh
```

Download python dependencies from `requirements.txt`:

```
python3 -m pip install -r requirements.txt
```

Build benchmark and add the folder with result binary to PATH:

```
cd build
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang++-15 -DCMAKE_C_COMPILER=/usr/bin/clang-15 -DCMAKE_BUILD_TYPE=RelWithDebInfo
make -j32
export PATH=`pwd`/src:$PATH
```

Run benchmark with different `--hash-tables`, `--hash-functions`, and `--files` options. By default, all hash tables, hash functions
and files from the benchmark are specified.

```
./benchmark.py
```

## Hash tables included

- [x] ClickHouse Hash Map (https://github.com/ClickHouse/ClickHouse)
- [x] Google Abseil Hash Map (https://github.com/abseil/abseil-cpp)
- [x] Google Dense Hash Map (https://github.com/sparsehash/sparsehash-c11)
- [x] Tsl Hopscotch Map (https://github.com/Tessil/hopscotch-map)
- [ ] Tsl Robin Hood Map (https://github.com/Tessil/robin-map)
- [x] Ankerl Unordered Dense Map (https://github.com/martinus/unordered_dense)
- [x] Ska Flat Hash Map (https://github.com/skarupke/flat_hash_map)
- [x] Ska Bytell Hash Map (https://github.com/skarupke/flat_hash_map)
- [x] Standard Unordered Map (depends on standard library implementation)

## Hash functions included

- [x] ClickHouse Hash (https://github.com/ClickHouse/ClickHouse)
- [x] Abseil Hash (https://github.com/abseil/abseil-cpp)
- [x] Standard Hash (depends on standard library implementation)

## Results

All tests were run on `c6a.4xlarge` VM in AWS for X86-64 platform and on `m7g.4xlarge` in AWS for ARM platform with 128 GB gp2.

Results for X86-64 on `c6a.4xlarge` instance for all hash tables with Abseil hash on `WatchID`, `UserID` and `RegionID` columns.
For full results, see [Results.md](Results.md).

WatchID file:

```
File: data/WatchID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 99997493
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | absl::Hash      |      6.70     |     4.00 GiB |
| absl::flat_hash_map          | absl::Hash      |     10.01     |     2.13 GiB |
| google::dense_hash_map       | absl::Hash      |      9.88     |     4.00 GiB |
| tsl::hopscotch_map           | absl::Hash      |     16.02     |     3.00 GiB |
| ankerl::unordered_dense::map | absl::Hash      |     12.93     |     2.49 GiB |
| ska::flat_hash_map           | absl::Hash      |     10.95     |     6.00 GiB |
| ska::bytell_hash_map         | absl::Hash      |     15.04     |     2.13 GiB |
| std::unordered_map           | absl::Hash      |     58.03     |     5.23 GiB |
+------------------------------+-----------------+---------------+--------------+
```

UserID file:

```
File: data/UserID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 17630976
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | absl::Hash      |      2.03     |     1.00 GiB |
| absl::flat_hash_map          | absl::Hash      |      2.65     |   544.60 MiB |
| google::dense_hash_map       | absl::Hash      |      2.70     |     1.00 GiB |
| tsl::hopscotch_map           | absl::Hash      |      3.59     |   768.64 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      3.17     |   525.43 MiB |
| ska::flat_hash_map           | absl::Hash      |      2.64     |     1.50 GiB |
| ska::bytell_hash_map         | absl::Hash      |      3.24     |   544.55 MiB |
| std::unordered_map           | absl::Hash      |      8.81     |   995.00 MiB |
+------------------------------+-----------------+---------------+--------------+
```

RegionID file:

```
File: data/RegionID.bin
Key type: Int32
Keys size: 99997497
Unique keys size: 9040
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | absl::Hash      |      0.17     |     1.15 MiB |
| absl::flat_hash_map          | absl::Hash      |      0.32     |   720.00 KiB |
| google::dense_hash_map       | absl::Hash      |      0.32     |   936.00 KiB |
| tsl::hopscotch_map           | absl::Hash      |      0.34     |   876.00 KiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.52     |   560.00 KiB |
| ska::flat_hash_map           | absl::Hash      |      0.23     |     1.17 MiB |
| ska::bytell_hash_map         | absl::Hash      |      0.28     |   700.00 KiB |
| std::unordered_map           | absl::Hash      |      0.64     |   764.00 KiB |
+------------------------------+-----------------+---------------+--------------+
```

# How to add a new hash table or hash function

Add a submodule with a hash table or hash function to the repository.

Add a new hash table in `src/HashTables.h` and update `benchmark.py`.

Add a new hash function in `src/HashFunctions.h` and update `benchmark.py`.

# Contacts

If you have any questions or suggestions, you can contact me at kitaetoya@gmail.com.
