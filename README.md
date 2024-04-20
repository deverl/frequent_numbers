# Most Frequent Numbers

## Overview

The programs in this project are possible solutions to a problem where you are given an integer array `nums` and integer `k` and you are to return the `k` most frequent elements from `nums`.

The results may be returned in any order.

See [problem.txt](https://github.com/deverl/frequent_numbers/blob/main/problem.txt) for some sample data and the expected results.

There are probably many ways this problem could be solved. These are just some examples.

## Running

There is a makefile that can run each of the programs, building executables if required (go, c, cpp, java).

You can run any of the programs with `make RUNTARGET` where `RUNTARGET` is one of:
- runc
- runcpp
- rungo
- runjava
- runlua
- runpython (or runpy)
- runjs
- runphp

## Cleanup

There is also a make target to clean up all of the executables and intermediaries. Use `make clean` to cleanup.

## Caveats

None of these solutions take special care to handle these situations:
- Where there are multiple input elements with the same frequency. There is no guarantee on the output in this case.
- Where there are fewer values in `nums` than requested by the value of `k`

