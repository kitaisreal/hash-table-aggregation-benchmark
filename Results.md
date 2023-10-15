# Results

Results for different platforms.

## X86-64 results on c6a.4xlarge:

File: data/WatchID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 99997493
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      6.39     |     4.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      7.49     |     4.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      6.79     |     4.00 GiB |
| absl::flat_hash_map          | std::hash       |     10.16     |     2.13 GiB |
| absl::flat_hash_map          | ClickHouse hash |     10.45     |     2.13 GiB |
| absl::flat_hash_map          | absl::Hash      |     10.24     |     2.13 GiB |
| tsl::hopscotch_map           | std::hash       |     14.82     |     3.00 GiB |
| tsl::hopscotch_map           | ClickHouse hash |     16.61     |     3.00 GiB |
| tsl::hopscotch_map           | absl::Hash      |     16.21     |     3.00 GiB |
| ankerl::unordered_dense::map | std::hash       |     12.86     |     2.49 GiB |
| ankerl::unordered_dense::map | ClickHouse hash |     13.97     |     2.49 GiB |
| ankerl::unordered_dense::map | absl::Hash      |     13.35     |     2.49 GiB |
| ska::flat_hash_map           | std::hash       |     10.88     |     6.00 GiB |
| ska::flat_hash_map           | ClickHouse hash |     12.08     |     6.00 GiB |
| ska::flat_hash_map           | absl::Hash      |     11.12     |     6.00 GiB |
| ska::bytell_hash_map         | std::hash       |     15.35     |     2.13 GiB |
| ska::bytell_hash_map         | ClickHouse hash |     15.80     |     2.13 GiB |
| ska::bytell_hash_map         | absl::Hash      |     15.11     |     2.13 GiB |
| std::unordered_map           | std::hash       |     57.47     |     3.74 GiB |
| std::unordered_map           | ClickHouse hash |     60.81     |     5.23 GiB |
| std::unordered_map           | absl::Hash      |     60.68     |     5.23 GiB |
+------------------------------+-----------------+---------------+--------------+

File: data/URLHash.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 20714865
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      2.33     |     1.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      2.85     |     1.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      2.52     |     1.00 GiB |
| absl::flat_hash_map          | std::hash       |      3.17     |   547.79 MiB |
| absl::flat_hash_map          | ClickHouse hash |      3.50     |   547.79 MiB |
| absl::flat_hash_map          | absl::Hash      |      3.34     |   547.75 MiB |
| tsl::hopscotch_map           | std::hash       |      4.01     |   771.76 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      4.82     |   771.74 MiB |
| tsl::hopscotch_map           | absl::Hash      |      4.59     |   771.83 MiB |
| ankerl::unordered_dense::map | std::hash       |      4.04     |   575.87 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      4.52     |   575.81 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      4.20     |   575.80 MiB |
| ska::flat_hash_map           | std::hash       |      2.94     |     1.50 GiB |
| ska::flat_hash_map           | ClickHouse hash |      3.42     |     1.50 GiB |
| ska::flat_hash_map           | absl::Hash      |      3.13     |     1.50 GiB |
| ska::bytell_hash_map         | std::hash       |      3.82     |   547.75 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      4.36     |   547.76 MiB |
| ska::bytell_hash_map         | absl::Hash      |      4.07     |   547.76 MiB |
| std::unordered_map           | std::hash       |      9.77     |   823.35 MiB |
| std::unordered_map           | ClickHouse hash |     11.22     |     1.11 GiB |
| std::unordered_map           | absl::Hash      |     11.14     |     1.11 GiB |
+------------------------------+-----------------+---------------+--------------+

File: data/UserID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 17630976
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      1.94     |     1.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      2.32     |     1.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      2.08     |     1.00 GiB |
| absl::flat_hash_map          | std::hash       |      2.63     |   547.82 MiB |
| absl::flat_hash_map          | ClickHouse hash |      2.89     |   547.78 MiB |
| absl::flat_hash_map          | absl::Hash      |      2.74     |   547.76 MiB |
| tsl::hopscotch_map           | std::hash       |      3.14     |   771.74 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      3.71     |   771.77 MiB |
| tsl::hopscotch_map           | absl::Hash      |      3.58     |   771.81 MiB |
| ankerl::unordered_dense::map | std::hash       |      3.15     |   528.63 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      3.56     |   528.64 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      3.29     |   528.65 MiB |
| ska::flat_hash_map           | std::hash       |      2.53     |     1.50 GiB |
| ska::flat_hash_map           | ClickHouse hash |      2.89     |     1.50 GiB |
| ska::flat_hash_map           | absl::Hash      |      2.67     |     1.50 GiB |
| ska::bytell_hash_map         | std::hash       |      3.13     |   547.76 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      3.44     |   547.76 MiB |
| ska::bytell_hash_map         | absl::Hash      |      3.29     |   547.76 MiB |
| std::unordered_map           | std::hash       |      8.28     |   729.24 MiB |
| std::unordered_map           | ClickHouse hash |      9.32     |   998.20 MiB |
| std::unordered_map           | absl::Hash      |      9.29     |   998.19 MiB |
+------------------------------+-----------------+---------------+--------------+

File: data/RegionID.bin
Key type: Int32
Keys size: 99997497
Unique keys size: 9040
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.14     |     4.50 MiB |
| ClickHouse HashMap           | ClickHouse hash |      0.20     |     4.49 MiB |
| ClickHouse HashMap           | absl::Hash      |      0.17     |     4.50 MiB |
| absl::flat_hash_map          | std::hash       |      3.19     |     3.97 MiB |
| absl::flat_hash_map          | ClickHouse hash |      0.36     |     4.08 MiB |
| absl::flat_hash_map          | absl::Hash      |      0.32     |     4.06 MiB |
| tsl::hopscotch_map           | std::hash       |      0.96     |     4.13 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.34     |     4.12 MiB |
| tsl::hopscotch_map           | absl::Hash      |      0.31     |     4.18 MiB |
| ankerl::unordered_dense::map | std::hash       |      0.46     |     3.87 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.56     |     3.90 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.54     |     3.87 MiB |
| ska::flat_hash_map           | std::hash       |      0.16     |     4.51 MiB |
| ska::flat_hash_map           | ClickHouse hash |      0.26     |     4.51 MiB |
| ska::flat_hash_map           | absl::Hash      |      0.21     |     4.51 MiB |
| ska::bytell_hash_map         | std::hash       |      0.23     |     4.01 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.32     |     4.03 MiB |
| ska::bytell_hash_map         | absl::Hash      |      0.29     |     4.02 MiB |
| std::unordered_map           | std::hash       |      0.46     |     3.83 MiB |
| std::unordered_map           | ClickHouse hash |      0.65     |     4.09 MiB |
| std::unordered_map           | absl::Hash      |      0.64     |     4.07 MiB |
+------------------------------+-----------------+---------------+--------------+

File: data/CounterID.bin
Key type: Int32
Keys size: 99997497
Unique keys size: 6506
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.11     |     3.80 MiB |
| ClickHouse HashMap           | ClickHouse hash |      0.18     |     3.78 MiB |
| ClickHouse HashMap           | absl::Hash      |      0.15     |     3.84 MiB |
| absl::flat_hash_map          | std::hash       |      1.38     |     3.88 MiB |
| absl::flat_hash_map          | ClickHouse hash |      0.35     |     3.93 MiB |
| absl::flat_hash_map          | absl::Hash      |      0.32     |     3.89 MiB |
| tsl::hopscotch_map           | std::hash       |      0.22     |     3.93 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.42     |     3.95 MiB |
| tsl::hopscotch_map           | absl::Hash      |      0.42     |     4.01 MiB |
| ankerl::unordered_dense::map | std::hash       |      0.34     |     3.87 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.40     |     3.81 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.37     |     3.81 MiB |
| ska::flat_hash_map           | std::hash       |      0.11     |     4.13 MiB |
| ska::flat_hash_map           | ClickHouse hash |      0.17     |     4.13 MiB |
| ska::flat_hash_map           | absl::Hash      |      0.16     |     4.18 MiB |
| ska::bytell_hash_map         | std::hash       |      0.28     |     3.88 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.41     |     3.90 MiB |
| ska::bytell_hash_map         | absl::Hash      |      0.35     |     3.90 MiB |
| std::unordered_map           | std::hash       |      0.20     |     3.84 MiB |
| std::unordered_map           | ClickHouse hash |      0.38     |     3.86 MiB |
| std::unordered_map           | absl::Hash      |      0.37     |     3.81 MiB |
+------------------------------+-----------------+---------------+--------------+

File: data/TraficSourceID.bin
Key type: Int16
Keys size: 99997497
Unique keys size: 10
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.22     |     3.28 MiB |
| ClickHouse HashMap           | ClickHouse hash |      0.27     |     3.29 MiB |
| ClickHouse HashMap           | absl::Hash      |      0.23     |     3.27 MiB |
| absl::flat_hash_map          | std::hash       |      0.27     |     3.27 MiB |
| absl::flat_hash_map          | ClickHouse hash |      0.35     |     3.30 MiB |
| absl::flat_hash_map          | absl::Hash      |      0.30     |     3.30 MiB |
| tsl::hopscotch_map           | std::hash       |      0.14     |     3.28 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.48     |     3.29 MiB |
| tsl::hopscotch_map           | absl::Hash      |      0.29     |     3.27 MiB |
| ankerl::unordered_dense::map | std::hash       |      0.31     |     3.30 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.59     |     3.27 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.56     |     3.27 MiB |
| ska::flat_hash_map           | std::hash       |      0.13     |     3.27 MiB |
| ska::flat_hash_map           | ClickHouse hash |      0.18     |     3.27 MiB |
| ska::flat_hash_map           | absl::Hash      |      0.34     |     3.28 MiB |
| ska::bytell_hash_map         | std::hash       |      0.21     |     3.30 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.32     |     3.29 MiB |
| ska::bytell_hash_map         | absl::Hash      |      0.47     |     3.30 MiB |
| std::unordered_map           | std::hash       |      0.42     |     3.27 MiB |
| std::unordered_map           | ClickHouse hash |      0.77     |     3.29 MiB |
| std::unordered_map           | absl::Hash      |      0.78     |     3.27 MiB |
+------------------------------+-----------------+---------------+--------------+

File: data/AdvEngineID.bin
Key type: Int16
Keys size: 99997497
Unique keys size: 19
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.09     |     3.27 MiB |
| ClickHouse HashMap           | ClickHouse hash |      0.07     |     3.29 MiB |
| ClickHouse HashMap           | absl::Hash      |      0.09     |     3.29 MiB |
| absl::flat_hash_map          | std::hash       |      0.26     |     3.30 MiB |
| absl::flat_hash_map          | ClickHouse hash |      0.35     |     3.27 MiB |
| absl::flat_hash_map          | absl::Hash      |      0.31     |     3.30 MiB |
| tsl::hopscotch_map           | std::hash       |      0.14     |     3.27 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.31     |     3.30 MiB |
| tsl::hopscotch_map           | absl::Hash      |      0.30     |     3.29 MiB |
| ankerl::unordered_dense::map | std::hash       |      0.32     |     3.27 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.41     |     3.27 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.34     |     3.29 MiB |
| ska::flat_hash_map           | std::hash       |      0.11     |     3.28 MiB |
| ska::flat_hash_map           | ClickHouse hash |      0.16     |     3.27 MiB |
| ska::flat_hash_map           | absl::Hash      |      0.14     |     3.28 MiB |
| ska::bytell_hash_map         | std::hash       |      0.20     |     3.27 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.29     |     3.27 MiB |
| ska::bytell_hash_map         | absl::Hash      |      0.26     |     3.30 MiB |
| std::unordered_map           | std::hash       |      0.28     |     3.27 MiB |
| std::unordered_map           | ClickHouse hash |      0.58     |     3.27 MiB |
| std::unordered_map           | absl::Hash      |      0.34     |     3.27 MiB |
+------------------------------+-----------------+---------------+--------------+

## ARM results on c6a.4xlarge:

File: data/WatchID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 99997493
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      6.48     |     4.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      6.99     |     4.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      6.89     |     4.00 GiB |
| absl::flat_hash_map          | std::hash       |      9.45     |     2.13 GiB |
| absl::flat_hash_map          | ClickHouse hash |      9.85     |     2.13 GiB |
| absl::flat_hash_map          | absl::Hash      |      9.84     |     2.13 GiB |
| tsl::hopscotch_map           | std::hash       |     16.39     |     3.00 GiB |
| tsl::hopscotch_map           | ClickHouse hash |     17.29     |     3.00 GiB |
| tsl::hopscotch_map           | absl::Hash      |     17.12     |     3.00 GiB |
| ankerl::unordered_dense::map | std::hash       |     15.42     |     2.49 GiB |
| ankerl::unordered_dense::map | ClickHouse hash |     17.43     |     2.49 GiB |
| ankerl::unordered_dense::map | absl::Hash      |     17.16     |     2.49 GiB |
| ska::flat_hash_map           | std::hash       |     10.61     |     6.00 GiB |
| ska::flat_hash_map           | ClickHouse hash |     11.08     |     6.00 GiB |
| ska::flat_hash_map           | absl::Hash      |     10.94     |     6.00 GiB |
| ska::bytell_hash_map         | std::hash       |     15.03     |     2.13 GiB |
| ska::bytell_hash_map         | ClickHouse hash |     15.65     |     2.13 GiB |
| ska::bytell_hash_map         | absl::Hash      |     14.56     |     2.13 GiB |
| std::unordered_map           | std::hash       |     63.79     |     3.74 GiB |
| std::unordered_map           | ClickHouse hash |     66.81     |     5.23 GiB |
| std::unordered_map           | absl::Hash      |     66.25     |     5.23 GiB |
+------------------------------+-----------------+---------------+--------------+

File: data/URLHash.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 20714865
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      2.33     |     1.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      2.67     |     1.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      2.58     |     1.00 GiB |
| absl::flat_hash_map          | std::hash       |      2.88     |   547.19 MiB |
| absl::flat_hash_map          | ClickHouse hash |      3.17     |   547.17 MiB |
| absl::flat_hash_map          | absl::Hash      |      3.12     |   547.18 MiB |
| tsl::hopscotch_map           | std::hash       |      4.25     |   771.19 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      5.21     |   771.19 MiB |
| tsl::hopscotch_map           | absl::Hash      |      5.07     |   771.19 MiB |
| ankerl::unordered_dense::map | std::hash       |      4.71     |   575.26 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      5.17     |   575.26 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      5.17     |   575.19 MiB |
| ska::flat_hash_map           | std::hash       |      3.25     |     1.50 GiB |
| ska::flat_hash_map           | ClickHouse hash |      3.52     |     1.50 GiB |
| ska::flat_hash_map           | absl::Hash      |      3.49     |     1.50 GiB |
| ska::bytell_hash_map         | std::hash       |      3.65     |   547.19 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      4.73     |   547.19 MiB |
| ska::bytell_hash_map         | absl::Hash      |      3.97     |   547.12 MiB |
| std::unordered_map           | std::hash       |     11.30     |   822.79 MiB |
| std::unordered_map           | ClickHouse hash |     13.13     |     1.11 GiB |
| std::unordered_map           | absl::Hash      |     13.10     |     1.11 GiB |
+------------------------------+-----------------+---------------+--------------+

File: data/UserID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 17630976
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      2.09     |     1.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      2.29     |     1.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      2.25     |     1.00 GiB |
| absl::flat_hash_map          | std::hash       |      2.55     |   547.18 MiB |
| absl::flat_hash_map          | ClickHouse hash |      2.67     |   547.18 MiB |
| absl::flat_hash_map          | absl::Hash      |      2.66     |   547.18 MiB |
| tsl::hopscotch_map           | std::hash       |      3.27     |   771.19 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      3.94     |   771.19 MiB |
| tsl::hopscotch_map           | absl::Hash      |      3.88     |   771.19 MiB |
| ankerl::unordered_dense::map | std::hash       |      3.56     |   528.08 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      3.89     |   528.07 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      3.96     |   528.02 MiB |
| ska::flat_hash_map           | std::hash       |      2.78     |     1.50 GiB |
| ska::flat_hash_map           | ClickHouse hash |      3.05     |     1.50 GiB |
| ska::flat_hash_map           | absl::Hash      |      2.98     |     1.50 GiB |
| ska::bytell_hash_map         | std::hash       |      2.86     |   547.19 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      3.64     |   547.19 MiB |
| ska::bytell_hash_map         | absl::Hash      |      3.10     |   547.12 MiB |
| std::unordered_map           | std::hash       |      9.50     |   728.69 MiB |
| std::unordered_map           | ClickHouse hash |     10.46     |   997.64 MiB |
| std::unordered_map           | absl::Hash      |     10.38     |   997.58 MiB |
+------------------------------+-----------------+---------------+--------------+

File: data/RegionID.bin
Key type: Int32
Keys size: 99997497
Unique keys size: 9040
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.17     |     3.89 MiB |
| ClickHouse HashMap           | ClickHouse hash |      0.20     |     3.89 MiB |
| ClickHouse HashMap           | absl::Hash      |      0.22     |     3.89 MiB |
| absl::flat_hash_map          | std::hash       |      5.04     |     3.32 MiB |
| absl::flat_hash_map          | ClickHouse hash |      0.31     |     3.45 MiB |
| absl::flat_hash_map          | absl::Hash      |      0.32     |     3.45 MiB |
| tsl::hopscotch_map           | std::hash       |      1.34     |     3.55 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.34     |     3.56 MiB |
| tsl::hopscotch_map           | absl::Hash      |      0.34     |     3.54 MiB |
| ankerl::unordered_dense::map | std::hash       |      0.57     |     3.31 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.72     |     3.31 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.71     |     3.31 MiB |
| ska::flat_hash_map           | std::hash       |      0.18     |     3.93 MiB |
| ska::flat_hash_map           | ClickHouse hash |      0.27     |     3.93 MiB |
| ska::flat_hash_map           | absl::Hash      |      0.29     |     3.93 MiB |
| ska::bytell_hash_map         | std::hash       |      0.23     |     3.45 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.28     |     3.45 MiB |
| ska::bytell_hash_map         | absl::Hash      |      0.31     |     3.45 MiB |
| std::unordered_map           | std::hash       |      0.58     |     3.28 MiB |
| std::unordered_map           | ClickHouse hash |      1.24     |     3.54 MiB |
| std::unordered_map           | absl::Hash      |      1.15     |     3.54 MiB |
+------------------------------+-----------------+---------------+--------------+

File: data/CounterID.bin
Key type: Int32
Keys size: 99997497
Unique keys size: 6506
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.20     |     3.18 MiB |
| ClickHouse HashMap           | ClickHouse hash |      0.21     |     3.19 MiB |
| ClickHouse HashMap           | absl::Hash      |      0.22     |     3.19 MiB |
| absl::flat_hash_map          | std::hash       |      1.76     |     3.26 MiB |
| absl::flat_hash_map          | ClickHouse hash |      0.34     |     3.31 MiB |
| absl::flat_hash_map          | absl::Hash      |      0.34     |     3.32 MiB |
| tsl::hopscotch_map           | std::hash       |      0.31     |     3.37 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.49     |     3.37 MiB |
| tsl::hopscotch_map           | absl::Hash      |      0.51     |     3.37 MiB |
| ankerl::unordered_dense::map | std::hash       |      0.45     |     3.28 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.56     |     3.28 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.57     |     3.27 MiB |
| ska::flat_hash_map           | std::hash       |      0.20     |     3.54 MiB |
| ska::flat_hash_map           | ClickHouse hash |      0.21     |     3.56 MiB |
| ska::flat_hash_map           | absl::Hash      |      0.22     |     3.56 MiB |
| ska::bytell_hash_map         | std::hash       |      0.27     |     3.32 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.36     |     3.32 MiB |
| ska::bytell_hash_map         | absl::Hash      |      0.37     |     3.32 MiB |
| std::unordered_map           | std::hash       |      0.30     |     3.28 MiB |
| std::unordered_map           | ClickHouse hash |      0.87     |     3.28 MiB |
| std::unordered_map           | absl::Hash      |      0.82     |     3.28 MiB |
+------------------------------+-----------------+---------------+--------------+

File: data/TraficSourceID.bin
Key type: Int16
Keys size: 99997497
Unique keys size: 10
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.24     |     2.68 MiB |
| ClickHouse HashMap           | ClickHouse hash |      0.27     |     2.67 MiB |
| ClickHouse HashMap           | absl::Hash      |      0.28     |     2.68 MiB |
| absl::flat_hash_map          | std::hash       |      0.26     |     2.68 MiB |
| absl::flat_hash_map          | ClickHouse hash |      0.31     |     2.68 MiB |
| absl::flat_hash_map          | absl::Hash      |      0.33     |     2.68 MiB |
| tsl::hopscotch_map           | std::hash       |      0.16     |     2.68 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.50     |     2.68 MiB |
| tsl::hopscotch_map           | absl::Hash      |      0.39     |     2.66 MiB |
| ankerl::unordered_dense::map | std::hash       |      0.40     |     2.68 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.72     |     2.68 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.79     |     2.68 MiB |
| ska::flat_hash_map           | std::hash       |      0.15     |     2.68 MiB |
| ska::flat_hash_map           | ClickHouse hash |      0.17     |     2.68 MiB |
| ska::flat_hash_map           | absl::Hash      |      0.19     |     2.68 MiB |
| ska::bytell_hash_map         | std::hash       |      0.22     |     2.68 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.28     |     2.68 MiB |
| ska::bytell_hash_map         | absl::Hash      |      0.41     |     2.68 MiB |
| std::unordered_map           | std::hash       |      1.23     |     2.67 MiB |
| std::unordered_map           | ClickHouse hash |      1.56     |     2.68 MiB |
| std::unordered_map           | absl::Hash      |      1.17     |     2.68 MiB |
+------------------------------+-----------------+---------------+--------------+

File: data/AdvEngineID.bin
Key type: Int16
Keys size: 99997497
Unique keys size: 19
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.19     |     2.68 MiB |
| ClickHouse HashMap           | ClickHouse hash |      0.19     |     2.68 MiB |
| ClickHouse HashMap           | absl::Hash      |      0.19     |     2.68 MiB |
| absl::flat_hash_map          | std::hash       |      0.25     |     2.68 MiB |
| absl::flat_hash_map          | ClickHouse hash |      0.31     |     2.68 MiB |
| absl::flat_hash_map          | absl::Hash      |      0.32     |     2.68 MiB |
| tsl::hopscotch_map           | std::hash       |      0.19     |     2.68 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.31     |     2.68 MiB |
| tsl::hopscotch_map           | absl::Hash      |      0.31     |     2.68 MiB |
| ankerl::unordered_dense::map | std::hash       |      0.41     |     2.68 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.60     |     2.68 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.66     |     2.68 MiB |
| ska::flat_hash_map           | std::hash       |      0.19     |     2.68 MiB |
| ska::flat_hash_map           | ClickHouse hash |      0.19     |     2.68 MiB |
| ska::flat_hash_map           | absl::Hash      |      0.25     |     2.68 MiB |
| ska::bytell_hash_map         | std::hash       |      0.23     |     2.68 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.26     |     2.68 MiB |
| ska::bytell_hash_map         | absl::Hash      |      0.28     |     2.68 MiB |
| std::unordered_map           | std::hash       |      0.36     |     2.67 MiB |
| std::unordered_map           | ClickHouse hash |      0.99     |     2.68 MiB |
| std::unordered_map           | absl::Hash      |      0.79     |     2.68 MiB |
+------------------------------+-----------------+---------------+--------------+
