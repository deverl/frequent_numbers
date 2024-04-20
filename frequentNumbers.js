function getMostFrequentNumbers(nums, k) {
    let mp = new Map();

    // Put count of all the distinct elements in Map with element as the key & count as the value.
    for (let i = 0; i < nums.length; i++) {
        // Get the count for the element if already present in the Map or get the default value which is 0. 
        if (mp.has(nums[i])) {
            mp.set(nums[i], mp.get(nums[i]) + 1)
        } else {
            mp.set(nums[i], 1)
        }
    }

    // Create a list from elements of the map
    let list = [...mp];

    // Sort the list
    list.sort((o1, o2) => o2[1] - o1[1])

    let r = [];

    for (let i = 0; i < k; i++) {
        r.push(list[i][0])
    }

    return r;
}


function printArray(prefix, arr) {
    let s = prefix + " [ ";
    for (i = 0; i < arr.length; i++) {
        s += arr[i] + " ";
    }
    s += "]";
    console.log(s);
}


function runTest(nums, k) {
    let r = getMostFrequentNumbers(nums, k);
    console.log("")
    printArray("  nums:", nums);
    console.log("     k:", k);
    printArray("result:", r)
}



function runAllTests() {
    // Test data

    let nums = [1,1,1,2,2,3];
    let k = 2;
    runTest(nums, k);

    nums = [1,4,2,5,7,5,4,4,5,5,5,2,7,2,5,4];
    k = 3;
    runTest(nums, k);

    nums = [9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1];
    k = 4;
    runTest(nums, k);

    console.log("")
}


runAllTests();

