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