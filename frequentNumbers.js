function printMostFrequentNumbers(nums, k) {
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

    let s = `The ${k} numbers with the highest frequency are:`;

    for (let i = 0; i < k; i++) {
        if (i > 0) {
            s += ",";
        }
        s += " " + list[i][0];;
    }

    console.log(s);
    document.write(s);
}

// Test data
let nums = [9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1];
let k = 4;

printMostFrequentNumbers(nums, k);

