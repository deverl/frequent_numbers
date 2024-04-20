<?php

function getFrequentNumbers(array $nums, int $k) : array {
    // Create a map where the keys are the unique values in the input array $nums
    // and the values are the number of times it appears in the input array.
    $m = [];
    for ($i = 0; $i < count($nums); $i++) {
        $key = $nums[$i];
        if (isset($m[$key])) {
            $m[$key] += 1;
        } else {
            $m[$key] = 1;
        }
    }
    // Sort the map by value (number of occurrences)
    uasort($m, function(int $a, int $b): int {
        return $b - $a;
    });
    // Get the keys (the most frequent values in the input array)
    // Take the first k keys from the list.
    return array_slice(array_keys($m), 0, $k);
}


function printArray(string $prefix, array $a) {
    echo "$prefix [ ";
    foreach ($a as $n) {
        echo "$n ";
    }
    echo "]" . PHP_EOL;
}
    

function runTest(array $nums, int $k) {
    $l = getFrequentNumbers($nums, $k);

    echo PHP_EOL;
    printArray("  nums:", $nums);
    echo "     k: $k" . PHP_EOL;
    printArray("result:", $l);
}

function runAllTests() {
    $nums1 = [1,1,1,2,2,3];
    $k1 = 2;

    runTest($nums1, $k1);

    $nums2 = [1,4,2,5,7,5,4,4,5,5,5,2,7,2,5,4];
    $k2 = 3;

    runTest($nums2, $k2);

    $nums3 = [9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1];
    $k3 = 4;

    runTest($nums3, $k3);

    echo PHP_EOL;
}
    

runAllTests();
