X86-64 results:

+--------------------------------+-------------------------+---------------+----------------------+-----------------------+
|           Hash Table           |           File          | Elapsed (sec) | Memory Usage (bytes) | Memory Usage Readable |
+--------------------------------+-------------------------+---------------+----------------------+-----------------------+
|     ch_hash_map_absl_hash      |     data/WatchID.bin    |    6.85918    |      5098328064      |        4.75GiB        |
|     ch_hash_map_absl_hash      |     data/URLHash.bin    |     2.3244    |      1877024768      |        1.75GiB        |
|     ch_hash_map_absl_hash      |     data/UserID.bin     |     2.0195    |      1877045248      |        1.75GiB        |
|     ch_hash_map_absl_hash      |    data/RegionID.bin    |    0.15954    |      404283392       |       385.55MiB       |
|     ch_hash_map_absl_hash      |    data/CounterID.bin   |    0.175465   |      403558400       |       384.86MiB       |
|     ch_hash_map_absl_hash      | data/TraficSourceID.bin |    0.219176   |      202936320       |       193.54MiB       |
|     ch_hash_map_absl_hash      |   data/AdvEngineID.bin  |    0.164413   |      202805248       |       193.41MiB       |
| abseil_flat_hash_map_absl_hash |     data/WatchID.bin    |    9.38394    |      3085074432      |        2.87GiB        |
| abseil_flat_hash_map_absl_hash |     data/URLHash.bin    |    3.02736    |      1373937664      |        1.28GiB        |
| abseil_flat_hash_map_absl_hash |     data/UserID.bin     |    2.62513    |      1373900800      |        1.28GiB        |
| abseil_flat_hash_map_absl_hash |    data/RegionID.bin    |    0.250962   |      403767296       |       385.06MiB       |
| abseil_flat_hash_map_absl_hash |    data/CounterID.bin   |    0.260435   |      403689472       |       384.99MiB       |
| abseil_flat_hash_map_absl_hash | data/TraficSourceID.bin |    0.235962   |      202911744       |       193.51MiB       |
| abseil_flat_hash_map_absl_hash |   data/AdvEngineID.bin  |    0.243843   |      202911744       |       193.51MiB       |
|  hopscotch_hash_map_absl_hash  |     data/WatchID.bin    |     16.124    |      4024713216      |        3.75GiB        |
|  hopscotch_hash_map_absl_hash  |     data/URLHash.bin    |    4.18615    |      1608765440      |        1.50GiB        |
|  hopscotch_hash_map_absl_hash  |     data/UserID.bin     |    3.22029    |      1608740864      |        1.50GiB        |
|  hopscotch_hash_map_absl_hash  |    data/RegionID.bin    |    0.33298    |      403927040       |       385.21MiB       |
|  hopscotch_hash_map_absl_hash  |    data/CounterID.bin   |    0.412946   |      403628032       |       384.93MiB       |
|  hopscotch_hash_map_absl_hash  | data/TraficSourceID.bin |    0.234562   |      202899456       |       193.50MiB       |
|  hopscotch_hash_map_absl_hash  |   data/AdvEngineID.bin  |    0.251974   |      202858496       |       193.46MiB       |
|         llvm_dence_map         |     data/WatchID.bin    |    12.5978    |      2950959104      |        2.75GiB        |
|         llvm_dence_map         |     data/URLHash.bin    |    3.27139    |      1340289024      |        1.25GiB        |
|         llvm_dence_map         |     data/UserID.bin     |    2.18837    |      1340342272      |        1.25GiB        |
|         llvm_dence_map         |    data/RegionID.bin    |    0.14619    |      403755008       |       385.05MiB       |
|         llvm_dence_map         |    data/CounterID.bin   |    0.266909   |      403718144       |       385.02MiB       |
|         llvm_dence_map         | data/TraficSourceID.bin |    0.135488   |      202911744       |       193.51MiB       |
|         llvm_dence_map         |   data/AdvEngineID.bin  |    0.168302   |      202850304       |       193.45MiB       |
|     std_hash_map_absl_hash     |     data/WatchID.bin    |     56.188    |      6445981696      |        6.00GiB        |
|     std_hash_map_absl_hash     |     data/URLHash.bin    |    10.6603    |      2008367104      |        1.87GiB        |
|     std_hash_map_absl_hash     |     data/UserID.bin     |    8.70052    |      1860243456      |        1.73GiB        |
|     std_hash_map_absl_hash     |    data/RegionID.bin    |    0.448471   |      403779584       |       385.07MiB       |
|     std_hash_map_absl_hash     |    data/CounterID.bin   |    0.445925   |      403886080       |       385.18MiB       |
|     std_hash_map_absl_hash     | data/TraficSourceID.bin |    0.800458   |      202809344       |       193.41MiB       |
|     std_hash_map_absl_hash     |   data/AdvEngineID.bin  |    0.312831   |      202809344       |       193.41MiB       |
+--------------------------------+-------------------------+---------------+----------------------+-----------------------+

+-------------------+-------------------------+---------------+---------------+----------------------+-----------------------+
|     Hash Table    |           File          | Elapsed (sec) | Hash Map Size | Memory Usage (bytes) | Memory Usage Readable |
+-------------------+-------------------------+---------------+---------------+----------------------+-----------------------+
| ska_flat_hash_map |     data/WatchID.bin    |    11.7231    |    99997493   |      6445893176      |        6.00GiB        |
| ska_flat_hash_map |     data/URLHash.bin    |    3.14107    |    20714865   |      1614157368      |        1.50GiB        |
| ska_flat_hash_map |     data/UserID.bin     |    2.68465    |    17630976   |      1614186040      |        1.50GiB        |
| ska_flat_hash_map |    data/RegionID.bin    |    0.164607   |      9040     |       4236060        |        4.04MiB        |
| ska_flat_hash_map |    data/CounterID.bin   |    0.170541   |      6506     |       3896092        |        3.72MiB        |
| ska_flat_hash_map | data/TraficSourceID.bin |    0.146594   |       10      |       2974094        |        2.84MiB        |
| ska_flat_hash_map |   data/AdvEngineID.bin  |    0.170457   |       19      |       2957710        |        2.82MiB        |
+-------------------+-------------------------+---------------+---------------+----------------------+-----------------------+

+---------------------+-------------------------+---------------+---------------+----------------------+-----------------------+
|      Hash Table     |           File          | Elapsed (sec) | Hash Map Size | Memory Usage (bytes) | Memory Usage Readable |
+---------------------+-------------------------+---------------+---------------+----------------------+-----------------------+
| ska_bytell_hash_map |     data/WatchID.bin    |    15.0979    |    99997493   |      2285192760      |        2.13GiB        |
| ska_bytell_hash_map |     data/URLHash.bin    |    3.64635    |    20714865   |      573900344       |       547.31MiB       |
| ska_bytell_hash_map |     data/UserID.bin     |    2.83999    |    17630976   |      573830712       |       547.25MiB       |
| ska_bytell_hash_map |    data/RegionID.bin    |    0.209816   |      9040     |       3908380        |        3.73MiB        |
| ska_bytell_hash_map |    data/CounterID.bin   |    0.272808   |      6506     |       3703580        |        3.53MiB        |
| ska_bytell_hash_map | data/TraficSourceID.bin |    0.19356    |       10      |       2965902        |        2.83MiB        |
| ska_bytell_hash_map |   data/AdvEngineID.bin  |    0.22682    |       19      |       2830734        |        2.70MiB        |
+---------------------+-------------------------+---------------+---------------+----------------------+-----------------------+

+-----------------------+-------------------------+---------------+---------------+----------------------+-----------------------+
|       Hash Table      |           File          | Elapsed (sec) | Hash Map Size | Memory Usage (bytes) | Memory Usage Readable |
+-----------------------+-------------------------+---------------+---------------+----------------------+-----------------------+
| ch_hash_map_absl_hash |     data/WatchID.bin    |    6.76691    |    99997493   |      4298360376      |        4.00GiB        |
|     group_hash_map    |     data/WatchID.bin    |    7.12181    |    99997493   |      2285176376      |        2.13GiB        |
| ch_hash_map_absl_hash |     data/URLHash.bin    |    2.38387    |    20714865   |      1077089848      |        1.00GiB        |
|     group_hash_map    |     data/URLHash.bin    |    2.65418    |    20714865   |      573896248       |       547.31MiB       |
| ch_hash_map_absl_hash |     data/UserID.bin     |    2.02103    |    17630976   |      1077204536      |        1.00GiB        |
|     group_hash_map    |     data/UserID.bin     |    2.26909    |    17630976   |      573822520       |       547.24MiB       |
| ch_hash_map_absl_hash |    data/RegionID.bin    |    0.166162   |      9040     |       4277020        |        4.08MiB        |
|     group_hash_map    |    data/RegionID.bin    |    0.322864   |      9040     |       3625756        |        3.46MiB        |
| ch_hash_map_absl_hash |    data/CounterID.bin   |    0.18919    |      6506     |       3576604        |        3.41MiB        |
|     group_hash_map    |    data/CounterID.bin   |    0.318728   |      6506     |       3679004        |        3.51MiB        |
| ch_hash_map_absl_hash | data/TraficSourceID.bin |    0.219966   |       10      |       2920846        |        2.79MiB        |
|     group_hash_map    | data/TraficSourceID.bin |    0.373261   |       10      |       2818446        |        2.69MiB        |
| ch_hash_map_absl_hash |   data/AdvEngineID.bin  |    0.166544   |       19      |       2900366        |        2.77MiB        |
|     group_hash_map    |   data/AdvEngineID.bin  |    0.165472   |       19      |       2920846        |        2.79MiB        |
+-----------------------+-------------------------+---------------+---------------+----------------------+-----------------------+
