#!/usr/bin/env python3

import heapq
import os
import random
import sys

# Gets a list of the k most frequent values from nums
def getMostFrequentNumbers(nums, k):
    # Construct a map where the keys are the values from nums and and the values are the number of times it appears in nums.
    m = {}
    for v in nums:
        if v in m:
            m[v] += 1
        else:
            m[v] = 1
    # Construct a priority queue with each tuple from the map.
    h = []
    for key in m:
        v = m[key]
        heapq.heappush(h, (v,key))
    # Get the k most frequent values
    l = heapq.nlargest(k, h)
    # Create an array of the k most frequent values
    ret = []
    for t in l:
        # In each tuple (t), the frequency is at index zero and the value is at index one
        ret.append(t[1])
    return ret
    



# Helper to generate lists or random numbers.
def getTestIntList(maxValue, count):
    l = []
    random.seed()
    for i in range(count):
        l.append(random.randint(0, maxValue - 1))
    return l



def printArray(title, arr):
    numInts = 30
    noTruncate = os.environ.get('NO_TRUNCATE_ARRAYS', "NA")
    if noTruncate == "NA":
        numInts = min(len(arr), numInts)
    elif noTruncate == "1":
        numInts = len(arr)
    else:
        numInts = min(len(arr), numInts)

    print(title + "[ ", end="")
    for i in range(len(arr)):
        if (i > 0):
            print(", ", end="")
        print(arr[i], end="")
    print(" ]")


def runTest(nums, k):
    print()
    ret = getMostFrequentNumbers(nums, k)
    print("     n =", len(nums))
    printArray(" input = ", nums)
    print("     k =", k)
    printArray("result = ", ret)



if (len(sys.argv) > 3):
    # Run the program with user supplied inputs.
    numDataPoints = int(sys.argv[1])
    maxValue = int(sys.argv[2])
    numMostFrequent = int(sys.argv[3])
    nums = getTestIntList(maxValue, numDataPoints)
    runTest(nums, numMostFrequent)
else:
    # Run the program with some canned data

    nums = [1, 1, 1, 2, 2, 3]
    k = 2
    runTest(nums, k)

    nums = [1,4,2,5,7,5,4,4,5,5,5,2,7,2,5,4]
    k = 3
    runTest(nums, k)

    nums = [9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1]
    k = 4
    runTest(nums, k)

print("")