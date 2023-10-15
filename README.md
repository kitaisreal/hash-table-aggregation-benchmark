# Hash tables aggregation benchmark

## Motivation

This benchmark is created to compare performance of different hash tables with different hash functions on in-memory aggregation scenario.

Benchmark is based on real anonimized web analytics data from [Yandex.Metrica dataset](https://clickhouse.com/docs/en/getting-started/example-datasets/metrica).

Benchmark tries to compute mapping for each unique key to count for columns from dataset, similar to such SQL query `SELECT column, count() FROM hits GROUP BY column`.

There are two different scenarios:

1. When hash table fits in CPU caches. Performance of hash table operations depends on arithmetic operations like hash function calculation, computing slot location, elements comparisons, and other operations that are required for specific hash table memory layout.

2. When hash table does not fit in CPU caches. For such a scenario, number of random memory accesses per operation is the most important factor for hash table performance.

Here are some general recommendations that can be applied to all hash table implementations:

1. You should avoid complex logic on hot path of your hash table operations. Because if there are a lot of instructions on hot path, hash table will work slow when all data fits in CPU caches.
2. You should not store a lot of additional metadata in your hash table, because, otherwise, your hash table will stop fitting into CPU caches quickly.
3. You should decrease the number of random memory accesses in your hash table operations because otherwise, it will significantly slow down your hash table implementation after hash table does not fit in CPU caches. Ideally, you should have one memory access for each operation. This also implies that you cannot make complex layouts (2 hash tables, keys and values separation, complex metadata) because usually, this will require additional memory accesses during operations.

Additionally, for the aggregation scenario, you need to consider not only lookup/insert latency but also memory size of hash table. If during aggregation hash table does not fit in RAM memory, the aggregation algorithm should switch implementation from in-memory aggregation to external memory aggregation, but this will work significantly slower.

Because each column in benchmark has different cardinality and distribution, it is possible to check how different hash tables with different hash functions work in read-world data.

## Examples

Run benchmark to test Abseil Hash Map using Abseil hash function for WatchID column:
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

Run benchmark to test ClickHouse Hash Map using all available hash function for WatchID column:

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

Run benchmark to test ClickHouse Hash Map and Abseil hash table using Abseil hash function and standard hash function
for WatchID and UserID columns.

```
./benchmark.py --hash-tables="ch_hash_map" --hash-functions="absl_hash, std_hash" --files="data/WatchID.bin, data/UserID.bin"

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

You can extract columns from other datasets or generate columns using `clickhouse-local` (it is downloaded as part of benchmark run or you can download it manually).
For example you can generate column with random 150 million random numbers and run benchmark to check ClickHouse HashMap and Abseil HashMap against this column.

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

For Ubuntu Linux with 22.04 LTS this prerequisites can be downloaded using following command:
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

Download benchmark data (new `data` folder will be created), all benchmark data takes around 20GB:

```
./load_data.sh
```

After that you can check data files:
```
ls data/

AdvEngineID.bin  clickhouse  CounterID.bin  hits.parquet  RegionID.bin  TraficSourceID.bin  URLHash.bin  UserID.bin  WatchID.bin
```

Download python dependencies from `requirements.txt`:

```
python3 -m pip install -r requirements.txt
```

Build benchmark and add result binary to PATH:

```
cd build
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang++-15 -DCMAKE_C_COMPILER=/usr/bin/clang-15 -DCMAKE_BUILD_TYPE=RelWithDebInfo
make -j32
```

Add benchmark binary to PATH assuming you are in `build` folder:
```
cd src
export PATH=`pwd`:$PATH
```

Run benchmark with different `--hash-tables`, `--hash-functions` and `--files` options. By default all hash tables, hash functions
and files from benchmark are specified.

```
./benchmark.py
```

## Hash tables included

- [x] ClickHouse Hash Map (https://github.com/abseil/abseil-cpp)
- [x] Google Abseil Hash Map (https://github.com/abseil/abseil-cpp)
- [ ] Google Dense Hash Map (https://github.com/sparsehash/sparsehash)
- [x] Tsl Hopscotch Map (https://github.com/Tessil/hopscotch-map)
- [x] Ankerl Unordered Dense Map (https://github.com/martinus/unordered_dense)
- [x] Ska Flat Hash Map (https://github.com/skarupke/flat_hash_map)
- [x] Ska Bytell Hash Map (https://github.com/skarupke/flat_hash_map)
- [x] Standard Unordered Map (depends on standard library implementation)

## Hash functions included

- [x] ClickHouse Hash (https://github.com/abseil/abseil-cpp)
- [x] Abseil Hash (https://github.com/abseil/abseil-cpp)
- [x] Standard Hash (depends on standard library implementation)

## Results

All tests are run on c6a.4xlarge VM in AWS for X86 platform and on m7g.4xlarge for ARM platform with 128 GB gp2.

Full results can be found here. TODO: Link to Results.md

# How to add new hash table or hash function

Add submodule with hash table or hash function to repository.
Add new hash table in `src/HashTables.h` and update `benchmark.py`.
Add new hash function in `src/HashFunctions.h` and update `benchmark.py`.

# Contacts

TODO:
For additional information
