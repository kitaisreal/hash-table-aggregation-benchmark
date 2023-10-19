# Results

Results for different platforms.

## X86-64 results on c6a.4xlarge:

```
File: data/WatchID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 99997493
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      6.23     |     4.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      7.36     |     4.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      6.70     |     4.00 GiB |
| absl::flat_hash_map          | std::hash       |      9.92     |     2.13 GiB |
| absl::flat_hash_map          | ClickHouse hash |     10.26     |     2.13 GiB |
| absl::flat_hash_map          | absl::Hash      |     10.01     |     2.13 GiB |
| google::dense_hash_map       | std::hash       |      9.80     |     4.00 GiB |
| google::dense_hash_map       | ClickHouse hash |     10.18     |     4.00 GiB |
| google::dense_hash_map       | absl::Hash      |      9.88     |     4.00 GiB |
| tsl::hopscotch_map           | std::hash       |     14.76     |     3.00 GiB |
| tsl::hopscotch_map           | ClickHouse hash |     16.31     |     3.00 GiB |
| tsl::hopscotch_map           | absl::Hash      |     16.02     |     3.00 GiB |
| ankerl::unordered_dense::map | std::hash       |     12.43     |     2.49 GiB |
| ankerl::unordered_dense::map | ClickHouse hash |     13.63     |     2.49 GiB |
| ankerl::unordered_dense::map | absl::Hash      |     12.93     |     2.49 GiB |
| ska::flat_hash_map           | std::hash       |     10.74     |     6.00 GiB |
| ska::flat_hash_map           | ClickHouse hash |     11.95     |     6.00 GiB |
| ska::flat_hash_map           | absl::Hash      |     10.95     |     6.00 GiB |
| ska::bytell_hash_map         | std::hash       |     15.12     |     2.13 GiB |
| ska::bytell_hash_map         | ClickHouse hash |     15.55     |     2.13 GiB |
| ska::bytell_hash_map         | absl::Hash      |     15.04     |     2.13 GiB |
| std::unordered_map           | std::hash       |     55.17     |     3.74 GiB |
| std::unordered_map           | ClickHouse hash |     58.37     |     5.23 GiB |
| std::unordered_map           | absl::Hash      |     58.03     |     5.23 GiB |
+------------------------------+-----------------+---------------+--------------+

File: data/URLHash.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 20714865
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      2.25     |     1.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      2.79     |     1.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      2.48     |     1.00 GiB |
| absl::flat_hash_map          | std::hash       |      3.09     |   544.62 MiB |
| absl::flat_hash_map          | ClickHouse hash |      3.43     |   544.58 MiB |
| absl::flat_hash_map          | absl::Hash      |      3.26     |   544.55 MiB |
| google::dense_hash_map       | std::hash       |      3.12     |     1.00 GiB |
| google::dense_hash_map       | ClickHouse hash |      3.48     |     1.00 GiB |
| google::dense_hash_map       | absl::Hash      |      3.32     |     1.00 GiB |
| tsl::hopscotch_map           | std::hash       |      3.95     |   768.57 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      4.76     |   768.64 MiB |
| tsl::hopscotch_map           | absl::Hash      |      4.50     |   768.61 MiB |
| ankerl::unordered_dense::map | std::hash       |      3.92     |   572.65 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      4.39     |   572.65 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      4.13     |   572.62 MiB |
| ska::flat_hash_map           | std::hash       |      2.89     |     1.50 GiB |
| ska::flat_hash_map           | ClickHouse hash |      3.38     |     1.50 GiB |
| ska::flat_hash_map           | absl::Hash      |      3.09     |     1.50 GiB |
| ska::bytell_hash_map         | std::hash       |      3.73     |   544.57 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      4.24     |   544.57 MiB |
| ska::bytell_hash_map         | absl::Hash      |      4.02     |   544.57 MiB |
| std::unordered_map           | std::hash       |      9.34     |   820.18 MiB |
| std::unordered_map           | ClickHouse hash |     10.77     |     1.11 GiB |
| std::unordered_map           | absl::Hash      |     10.80     |     1.11 GiB |
+------------------------------+-----------------+---------------+--------------+

File: data/UserID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 17630976
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      1.87     |     1.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      2.27     |     1.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      2.03     |     1.00 GiB |
| absl::flat_hash_map          | std::hash       |      2.55     |   544.60 MiB |
| absl::flat_hash_map          | ClickHouse hash |      2.82     |   544.61 MiB |
| absl::flat_hash_map          | absl::Hash      |      2.65     |   544.60 MiB |
| google::dense_hash_map       | std::hash       |      2.59     |     1.00 GiB |
| google::dense_hash_map       | ClickHouse hash |      2.86     |     1.00 GiB |
| google::dense_hash_map       | absl::Hash      |      2.70     |     1.00 GiB |
| tsl::hopscotch_map           | std::hash       |      3.10     |   768.57 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      3.65     |   768.64 MiB |
| tsl::hopscotch_map           | absl::Hash      |      3.59     |   768.64 MiB |
| ankerl::unordered_dense::map | std::hash       |      3.04     |   525.47 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      3.45     |   525.47 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      3.17     |   525.43 MiB |
| ska::flat_hash_map           | std::hash       |      2.48     |     1.50 GiB |
| ska::flat_hash_map           | ClickHouse hash |      2.87     |     1.50 GiB |
| ska::flat_hash_map           | absl::Hash      |      2.64     |     1.50 GiB |
| ska::bytell_hash_map         | std::hash       |      3.07     |   544.57 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      3.33     |   544.57 MiB |
| ska::bytell_hash_map         | absl::Hash      |      3.24     |   544.55 MiB |
| std::unordered_map           | std::hash       |      7.84     |   726.08 MiB |
| std::unordered_map           | ClickHouse hash |      8.91     |   995.03 MiB |
| std::unordered_map           | absl::Hash      |      8.81     |   995.00 MiB |
+------------------------------+-----------------+---------------+--------------+

File: data/RegionID.bin
Key type: Int32
Keys size: 99997497
Unique keys size: 9040
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.14     |     1.16 MiB |
| ClickHouse HashMap           | ClickHouse hash |      0.21     |     1.18 MiB |
| ClickHouse HashMap           | absl::Hash      |      0.17     |     1.15 MiB |
| absl::flat_hash_map          | std::hash       |      2.98     |   604.00 KiB |
| absl::flat_hash_map          | ClickHouse hash |      0.36     |   728.00 KiB |
| absl::flat_hash_map          | absl::Hash      |      0.32     |   720.00 KiB |
| google::dense_hash_map       | std::hash       |      0.34     |   936.00 KiB |
| google::dense_hash_map       | ClickHouse hash |      0.38     |   936.00 KiB |
| google::dense_hash_map       | absl::Hash      |      0.32     |   936.00 KiB |
| tsl::hopscotch_map           | std::hash       |      0.97     |   812.00 KiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.32     |   812.00 KiB |
| tsl::hopscotch_map           | absl::Hash      |      0.34     |   876.00 KiB |
| ankerl::unordered_dense::map | std::hash       |      0.46     |   560.00 KiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.55     |   624.00 KiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.52     |   560.00 KiB |
| ska::flat_hash_map           | std::hash       |      0.16     |     1.17 MiB |
| ska::flat_hash_map           | ClickHouse hash |      0.26     |     1.17 MiB |
| ska::flat_hash_map           | absl::Hash      |      0.23     |     1.17 MiB |
| ska::bytell_hash_map         | std::hash       |      0.23     |   700.00 KiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.32     |   700.00 KiB |
| ska::bytell_hash_map         | absl::Hash      |      0.28     |   700.00 KiB |
| std::unordered_map           | std::hash       |      0.46     |   500.00 KiB |
| std::unordered_map           | ClickHouse hash |      0.65     |   764.00 KiB |
| std::unordered_map           | absl::Hash      |      0.64     |   764.00 KiB |
+------------------------------+-----------------+---------------+--------------+

File: data/CounterID.bin
Key type: Int32
Keys size: 99997497
Unique keys size: 6506
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.11     |   440.00 KiB |
| ClickHouse HashMap           | ClickHouse hash |      0.19     |   476.00 KiB |
| ClickHouse HashMap           | absl::Hash      |      0.14     |   496.00 KiB |
| absl::flat_hash_map          | std::hash       |      1.28     |   528.00 KiB |
| absl::flat_hash_map          | ClickHouse hash |      0.35     |   572.00 KiB |
| absl::flat_hash_map          | absl::Hash      |      0.32     |   604.00 KiB |
| google::dense_hash_map       | std::hash       |      0.35     |   656.00 KiB |
| google::dense_hash_map       | ClickHouse hash |      0.38     |   680.00 KiB |
| google::dense_hash_map       | absl::Hash      |      0.32     |   680.00 KiB |
| tsl::hopscotch_map           | std::hash       |      0.23     |   620.00 KiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.43     |   684.00 KiB |
| tsl::hopscotch_map           | absl::Hash      |      0.49     |   684.00 KiB |
| ankerl::unordered_dense::map | std::hash       |      0.34     |   500.00 KiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.40     |   500.00 KiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.37     |   500.00 KiB |
| ska::flat_hash_map           | std::hash       |      0.12     |   812.00 KiB |
| ska::flat_hash_map           | ClickHouse hash |      0.17     |   812.00 KiB |
| ska::flat_hash_map           | absl::Hash      |      0.16     |   812.00 KiB |
| ska::bytell_hash_map         | std::hash       |      0.28     |   564.00 KiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.40     |   564.00 KiB |
| ska::bytell_hash_map         | absl::Hash      |      0.37     |   564.00 KiB |
| std::unordered_map           | std::hash       |      0.20     |   500.00 KiB |
| std::unordered_map           | ClickHouse hash |      0.38     |   500.00 KiB |
| std::unordered_map           | absl::Hash      |      0.37     |   500.00 KiB |
+------------------------------+-----------------+---------------+--------------+

File: data/TraficSourceID.bin
Key type: Int16
Keys size: 99997497
Unique keys size: 10
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.21     |     4.00 KiB |
| ClickHouse HashMap           | ClickHouse hash |      0.27     |     4.00 KiB |
| ClickHouse HashMap           | absl::Hash      |      0.23     |     4.00 KiB |
| absl::flat_hash_map          | std::hash       |      0.27     |     4.00 KiB |
| absl::flat_hash_map          | ClickHouse hash |      0.35     |     4.00 KiB |
| absl::flat_hash_map          | absl::Hash      |      0.30     |     4.00 KiB |
| google::dense_hash_map       | std::hash       |      0.34     |     4.00 KiB |
| google::dense_hash_map       | ClickHouse hash |      0.50     |     4.00 KiB |
| google::dense_hash_map       | absl::Hash      |      0.31     |     4.00 KiB |
| tsl::hopscotch_map           | std::hash       |      0.14     |     4.00 KiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.51     |     4.00 KiB |
| tsl::hopscotch_map           | absl::Hash      |      0.28     |     4.00 KiB |
| ankerl::unordered_dense::map | std::hash       |      0.31     |     4.00 KiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.59     |     4.00 KiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.65     |     4.00 KiB |
| ska::flat_hash_map           | std::hash       |      0.13     |     4.00 KiB |
| ska::flat_hash_map           | ClickHouse hash |      0.18     |     4.00 KiB |
| ska::flat_hash_map           | absl::Hash      |      0.26     |     4.00 KiB |
| ska::bytell_hash_map         | std::hash       |      0.20     |     4.00 KiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.32     |     4.00 KiB |
| ska::bytell_hash_map         | absl::Hash      |      0.37     |     4.00 KiB |
| std::unordered_map           | std::hash       |      0.41     |     4.00 KiB |
| std::unordered_map           | ClickHouse hash |      0.77     |     4.00 KiB |
| std::unordered_map           | absl::Hash      |      0.66     |     4.00 KiB |
+------------------------------+-----------------+---------------+--------------+

File: data/AdvEngineID.bin
Key type: Int16
Keys size: 99997497
Unique keys size: 19
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.06     |     4.00 KiB |
| ClickHouse HashMap           | ClickHouse hash |      0.09     |     4.00 KiB |
| ClickHouse HashMap           | absl::Hash      |      0.09     |     4.00 KiB |
| absl::flat_hash_map          | std::hash       |      0.26     |     4.00 KiB |
| absl::flat_hash_map          | ClickHouse hash |      0.35     |     4.00 KiB |
| absl::flat_hash_map          | absl::Hash      |      0.31     |     4.00 KiB |
| google::dense_hash_map       | std::hash       |      0.34     |     4.00 KiB |
| google::dense_hash_map       | ClickHouse hash |      0.31     |     4.00 KiB |
| google::dense_hash_map       | absl::Hash      |      0.31     |     4.00 KiB |
| tsl::hopscotch_map           | std::hash       |      0.14     |     4.00 KiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.33     |     4.00 KiB |
| tsl::hopscotch_map           | absl::Hash      |      0.31     |     4.00 KiB |
| ankerl::unordered_dense::map | std::hash       |      0.32     |     4.00 KiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.41     |     4.00 KiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.32     |     4.00 KiB |
| ska::flat_hash_map           | std::hash       |      0.11     |     4.00 KiB |
| ska::flat_hash_map           | ClickHouse hash |      0.16     |     4.00 KiB |
| ska::flat_hash_map           | absl::Hash      |      0.16     |     4.00 KiB |
| ska::bytell_hash_map         | std::hash       |      0.20     |     4.00 KiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.29     |     4.00 KiB |
| ska::bytell_hash_map         | absl::Hash      |      0.26     |     4.00 KiB |
| std::unordered_map           | std::hash       |      0.27     |     4.00 KiB |
| std::unordered_map           | ClickHouse hash |      0.58     |     4.00 KiB |
| std::unordered_map           | absl::Hash      |      0.78     |     4.00 KiB |
+------------------------------+-----------------+---------------+--------------+
```

## ARM results on m7g.4xlarge:

```
File: data/WatchID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 99997493
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      6.50     |     4.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      6.88     |     4.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      6.87     |     4.00 GiB |
| absl::flat_hash_map          | std::hash       |      9.21     |     2.13 GiB |
| absl::flat_hash_map          | ClickHouse hash |      9.73     |     2.13 GiB |
| absl::flat_hash_map          | absl::Hash      |      9.49     |     2.13 GiB |
| google::dense_hash_map       | std::hash       |      8.86     |     4.00 GiB |
| google::dense_hash_map       | ClickHouse hash |     10.32     |     4.00 GiB |
| google::dense_hash_map       | absl::Hash      |     10.26     |     4.00 GiB |
| tsl::hopscotch_map           | std::hash       |     16.00     |     3.00 GiB |
| tsl::hopscotch_map           | ClickHouse hash |     16.99     |     3.00 GiB |
| tsl::hopscotch_map           | absl::Hash      |     16.60     |     3.00 GiB |
| ankerl::unordered_dense::map | std::hash       |     14.83     |     2.49 GiB |
| ankerl::unordered_dense::map | ClickHouse hash |     16.72     |     2.49 GiB |
| ankerl::unordered_dense::map | absl::Hash      |     16.88     |     2.49 GiB |
| ska::flat_hash_map           | std::hash       |     10.56     |     6.00 GiB |
| ska::flat_hash_map           | ClickHouse hash |     10.93     |     6.00 GiB |
| ska::flat_hash_map           | absl::Hash      |     10.81     |     6.00 GiB |
| ska::bytell_hash_map         | std::hash       |     14.73     |     2.13 GiB |
| ska::bytell_hash_map         | ClickHouse hash |     15.29     |     2.13 GiB |
| ska::bytell_hash_map         | absl::Hash      |     14.37     |     2.13 GiB |
| std::unordered_map           | std::hash       |     61.47     |     3.74 GiB |
| std::unordered_map           | ClickHouse hash |     65.53     |     5.23 GiB |
| std::unordered_map           | absl::Hash      |     64.34     |     5.23 GiB |
+------------------------------+-----------------+---------------+--------------+

File: data/URLHash.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 20714865
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      2.32     |     1.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      2.67     |     1.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      2.56     |     1.00 GiB |
| absl::flat_hash_map          | std::hash       |      3.58     |   544.73 MiB |
| absl::flat_hash_map          | ClickHouse hash |      3.08     |   544.67 MiB |
| absl::flat_hash_map          | absl::Hash      |      3.07     |   544.67 MiB |
| google::dense_hash_map       | std::hash       |      3.08     |     1.00 GiB |
| google::dense_hash_map       | ClickHouse hash |      3.65     |     1.00 GiB |
| google::dense_hash_map       | absl::Hash      |      3.62     |     1.00 GiB |
| tsl::hopscotch_map           | std::hash       |      4.23     |   768.67 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      5.07     |   768.67 MiB |
| tsl::hopscotch_map           | absl::Hash      |      4.84     |   768.67 MiB |
| ankerl::unordered_dense::map | std::hash       |      4.58     |   572.75 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      5.08     |   572.68 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      4.99     |   572.68 MiB |
| ska::flat_hash_map           | std::hash       |      3.18     |     1.50 GiB |
| ska::flat_hash_map           | ClickHouse hash |      3.48     |     1.50 GiB |
| ska::flat_hash_map           | absl::Hash      |      3.38     |     1.50 GiB |
| ska::bytell_hash_map         | std::hash       |      3.55     |   544.67 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      4.69     |   544.61 MiB |
| ska::bytell_hash_map         | absl::Hash      |      3.92     |   544.61 MiB |
| std::unordered_map           | std::hash       |     11.12     |   820.28 MiB |
| std::unordered_map           | ClickHouse hash |     12.56     |     1.11 GiB |
| std::unordered_map           | absl::Hash      |     13.18     |     1.11 GiB |
+------------------------------+-----------------+---------------+--------------+

File: data/UserID.bin
Key type: Int64
Keys size: 99997497
Unique keys size: 17630976
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      2.08     |     1.00 GiB |
| ClickHouse HashMap           | ClickHouse hash |      2.26     |     1.00 GiB |
| ClickHouse HashMap           | absl::Hash      |      2.25     |     1.00 GiB |
| absl::flat_hash_map          | std::hash       |      2.50     |   544.73 MiB |
| absl::flat_hash_map          | ClickHouse hash |      2.62     |   544.67 MiB |
| absl::flat_hash_map          | absl::Hash      |      2.58     |   544.67 MiB |
| google::dense_hash_map       | std::hash       |      2.56     |     1.00 GiB |
| google::dense_hash_map       | ClickHouse hash |      2.92     |     1.00 GiB |
| google::dense_hash_map       | absl::Hash      |      2.92     |     1.00 GiB |
| tsl::hopscotch_map           | std::hash       |      3.24     |   768.67 MiB |
| tsl::hopscotch_map           | ClickHouse hash |      3.88     |   768.67 MiB |
| tsl::hopscotch_map           | absl::Hash      |      3.80     |   768.67 MiB |
| ankerl::unordered_dense::map | std::hash       |      3.49     |   525.57 MiB |
| ankerl::unordered_dense::map | ClickHouse hash |      3.87     |   525.50 MiB |
| ankerl::unordered_dense::map | absl::Hash      |      3.86     |   525.50 MiB |
| ska::flat_hash_map           | std::hash       |      2.75     |     1.50 GiB |
| ska::flat_hash_map           | ClickHouse hash |      3.02     |     1.50 GiB |
| ska::flat_hash_map           | absl::Hash      |      2.98     |     1.50 GiB |
| ska::bytell_hash_map         | std::hash       |      2.90     |   544.67 MiB |
| ska::bytell_hash_map         | ClickHouse hash |      3.58     |   544.61 MiB |
| ska::bytell_hash_map         | absl::Hash      |      3.12     |   544.61 MiB |
| std::unordered_map           | std::hash       |      9.18     |   726.18 MiB |
| std::unordered_map           | ClickHouse hash |     10.56     |   995.06 MiB |
| std::unordered_map           | absl::Hash      |     10.35     |   995.06 MiB |
+------------------------------+-----------------+---------------+--------------+

File: data/RegionID.bin
Key type: Int32
Keys size: 99997497
Unique keys size: 9040
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.17     |     1.22 MiB |
| ClickHouse HashMap           | ClickHouse hash |      0.20     |     1.22 MiB |
| ClickHouse HashMap           | absl::Hash      |      0.21     |     1.22 MiB |
| absl::flat_hash_map          | std::hash       |      5.27     |   764.00 KiB |
| absl::flat_hash_map          | ClickHouse hash |      0.31     |   860.00 KiB |
| absl::flat_hash_map          | absl::Hash      |      0.32     |   864.00 KiB |
| google::dense_hash_map       | std::hash       |      0.27     |     1.01 MiB |
| google::dense_hash_map       | ClickHouse hash |      0.33     |     1.01 MiB |
| google::dense_hash_map       | absl::Hash      |      0.33     |     1.01 MiB |
| tsl::hopscotch_map           | std::hash       |      1.34     |   912.00 KiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.34     |   912.00 KiB |
| tsl::hopscotch_map           | absl::Hash      |      0.34     |   976.00 KiB |
| ankerl::unordered_dense::map | std::hash       |      0.55     |   660.00 KiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.70     |   660.00 KiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.73     |   660.00 KiB |
| ska::flat_hash_map           | std::hash       |      0.19     |     1.27 MiB |
| ska::flat_hash_map           | ClickHouse hash |      0.26     |     1.33 MiB |
| ska::flat_hash_map           | absl::Hash      |      0.27     |     1.27 MiB |
| ska::bytell_hash_map         | std::hash       |      0.23     |   800.00 KiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.27     |   800.00 KiB |
| ska::bytell_hash_map         | absl::Hash      |      0.30     |   800.00 KiB |
| std::unordered_map           | std::hash       |      0.56     |   620.00 KiB |
| std::unordered_map           | ClickHouse hash |      1.24     |   884.00 KiB |
| std::unordered_map           | absl::Hash      |      1.17     |   884.00 KiB |
+------------------------------+-----------------+---------------+--------------+

File: data/CounterID.bin
Key type: Int32
Keys size: 99997497
Unique keys size: 6506
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.20     |   532.00 KiB |
| ClickHouse HashMap           | ClickHouse hash |      0.21     |   532.00 KiB |
| ClickHouse HashMap           | absl::Hash      |      0.22     |   532.00 KiB |
| absl::flat_hash_map          | std::hash       |      1.60     |   664.00 KiB |
| absl::flat_hash_map          | ClickHouse hash |      0.33     |   724.00 KiB |
| absl::flat_hash_map          | absl::Hash      |      0.33     |   728.00 KiB |
| google::dense_hash_map       | std::hash       |      0.28     |   780.00 KiB |
| google::dense_hash_map       | ClickHouse hash |      0.35     |   780.00 KiB |
| google::dense_hash_map       | absl::Hash      |      0.34     |   780.00 KiB |
| tsl::hopscotch_map           | std::hash       |      0.31     |   720.00 KiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.49     |   720.00 KiB |
| tsl::hopscotch_map           | absl::Hash      |      0.51     |   784.00 KiB |
| ankerl::unordered_dense::map | std::hash       |      0.44     |   620.00 KiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.55     |   620.00 KiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.55     |   620.00 KiB |
| ska::flat_hash_map           | std::hash       |      0.20     |   912.00 KiB |
| ska::flat_hash_map           | ClickHouse hash |      0.21     |   976.00 KiB |
| ska::flat_hash_map           | absl::Hash      |      0.22     |   912.00 KiB |
| ska::bytell_hash_map         | std::hash       |      0.28     |   664.00 KiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.34     |   664.00 KiB |
| ska::bytell_hash_map         | absl::Hash      |      0.39     |   664.00 KiB |
| std::unordered_map           | std::hash       |      0.30     |   620.00 KiB |
| std::unordered_map           | ClickHouse hash |      0.88     |   620.00 KiB |
| std::unordered_map           | absl::Hash      |      0.78     |   620.00 KiB |
+------------------------------+-----------------+---------------+--------------+

File: data/TraficSourceID.bin
Key type: Int16
Keys size: 99997497
Unique keys size: 10
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.24     |     4.00 KiB |
| ClickHouse HashMap           | ClickHouse hash |      0.27     |     4.00 KiB |
| ClickHouse HashMap           | absl::Hash      |      0.27     |     4.00 KiB |
| absl::flat_hash_map          | std::hash       |      0.26     |     4.00 KiB |
| absl::flat_hash_map          | ClickHouse hash |      0.31     |     4.00 KiB |
| absl::flat_hash_map          | absl::Hash      |      0.33     |     4.00 KiB |
| google::dense_hash_map       | std::hash       |      0.24     |     4.00 KiB |
| google::dense_hash_map       | ClickHouse hash |      0.51     |     4.00 KiB |
| google::dense_hash_map       | absl::Hash      |      0.32     |     4.00 KiB |
| tsl::hopscotch_map           | std::hash       |      0.16     |     4.00 KiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.49     |     4.00 KiB |
| tsl::hopscotch_map           | absl::Hash      |      0.58     |     4.00 KiB |
| ankerl::unordered_dense::map | std::hash       |      0.38     |     4.00 KiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.71     |     4.00 KiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.90     |     4.00 KiB |
| ska::flat_hash_map           | std::hash       |      0.15     |     4.00 KiB |
| ska::flat_hash_map           | ClickHouse hash |      0.17     |     4.00 KiB |
| ska::flat_hash_map           | absl::Hash      |      0.19     |     4.00 KiB |
| ska::bytell_hash_map         | std::hash       |      0.21     |     4.00 KiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.28     |     4.00 KiB |
| ska::bytell_hash_map         | absl::Hash      |      0.41     |     4.00 KiB |
| std::unordered_map           | std::hash       |      1.23     |     4.00 KiB |
| std::unordered_map           | ClickHouse hash |      1.55     |     4.00 KiB |
| std::unordered_map           | absl::Hash      |      1.23     |     4.00 KiB |
+------------------------------+-----------------+---------------+--------------+

File: data/AdvEngineID.bin
Key type: Int16
Keys size: 99997497
Unique keys size: 19
+------------------------------+-----------------+---------------+--------------+
| Hash Table                   | Hash Function   | Elapsed (sec) | Memory Usage |
+------------------------------+-----------------+---------------+--------------+
| ClickHouse HashMap           | std::hash       |      0.19     |     4.00 KiB |
| ClickHouse HashMap           | ClickHouse hash |      0.19     |     4.00 KiB |
| ClickHouse HashMap           | absl::Hash      |      0.19     |     4.00 KiB |
| absl::flat_hash_map          | std::hash       |      0.24     |     4.00 KiB |
| absl::flat_hash_map          | ClickHouse hash |      0.31     |     4.00 KiB |
| absl::flat_hash_map          | absl::Hash      |      0.31     |     4.00 KiB |
| google::dense_hash_map       | std::hash       |      0.24     |     4.00 KiB |
| google::dense_hash_map       | ClickHouse hash |      0.32     |     4.00 KiB |
| google::dense_hash_map       | absl::Hash      |      0.32     |     4.00 KiB |
| tsl::hopscotch_map           | std::hash       |      0.19     |     4.00 KiB |
| tsl::hopscotch_map           | ClickHouse hash |      0.31     |     4.00 KiB |
| tsl::hopscotch_map           | absl::Hash      |      0.31     |     4.00 KiB |
| ankerl::unordered_dense::map | std::hash       |      0.40     |     4.00 KiB |
| ankerl::unordered_dense::map | ClickHouse hash |      0.58     |     4.00 KiB |
| ankerl::unordered_dense::map | absl::Hash      |      0.54     |     4.00 KiB |
| ska::flat_hash_map           | std::hash       |      0.19     |     4.00 KiB |
| ska::flat_hash_map           | ClickHouse hash |      0.19     |     4.00 KiB |
| ska::flat_hash_map           | absl::Hash      |      0.21     |     4.00 KiB |
| ska::bytell_hash_map         | std::hash       |      0.21     |     4.00 KiB |
| ska::bytell_hash_map         | ClickHouse hash |      0.26     |     4.00 KiB |
| ska::bytell_hash_map         | absl::Hash      |      0.28     |     4.00 KiB |
| std::unordered_map           | std::hash       |      0.36     |     4.00 KiB |
| std::unordered_map           | ClickHouse hash |      0.97     |     4.00 KiB |
| std::unordered_map           | absl::Hash      |      0.87     |     4.00 KiB |
+------------------------------+-----------------+---------------+--------------+
```
