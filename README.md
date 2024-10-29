# afsampling
This repository implements FracMinHash sketching and Affirmative Sampling. See `basicTest.cpp` for use case.

After making, the following programs are generated.

## basicTest
Purpose: basic testing of implementation

## sketchSizeTest
This program will do the following:
1. Generate a random set A with x elements
1. Generate the sketch of A using FMH and AS
1. Record the sketch sizes
1. Vary x from 1K to 10M

Results:

```
10000,10.2,2.6,573,8.82043
100000,96.5,7.32462,790.3,31.8624
1000000,1004.2,26.5548,1021,30.4335
10000000,9968.3,73.369,1247,42.1829
100000000,97035.5,302.213,1486.3,24.0626
```