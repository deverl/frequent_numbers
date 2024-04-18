#!/usr/bin/env python3

import heapq
import random

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
    
# Some test data

nums = [9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1]
k = 4

print()

ret = getMostFrequentNumbers(nums, k)
print(" input = ", nums)
print("     k = ", k)
print("result = ", ret)
print()

#nums = [1,2,5,7,4,4,5,5,2,2]
#k = 3
#
#ret = getMostFrequentNumbers(nums, k)
#print(" input = ", nums)
#print("     k = ", k)
#print("result = ", ret)
#print()
#
#nums = getTestIntList(10, 40)
#k = 5
#
#ret = getMostFrequentNumbers(nums, k)
#print(" input = ", nums)
#print("     k = ", k)
#print("result = ", ret)
#print()


#nums = getTestIntList(100, 5000)
#k = 20
#
#ret = getMostFrequentNumbers(nums, k)
#print(" input = ", nums)
#print("     k = ", k)
#print("result = ", ret)
#print()

