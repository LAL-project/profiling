#!/bin/bash

gprof build-profile/profiling $1 > $2.txt
python3 gprof2dot.py $2.txt | dot -Tdot -o $2.dot

