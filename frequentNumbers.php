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
    
    
    
$nums = [9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1];
$k = 4;

$l = getFrequentNumbers($nums, $k);

print_r($l);
