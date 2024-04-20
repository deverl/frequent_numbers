--[[
Problem Statement

Given an integer array 'nums' and integer 'k', return the k most frequent elements.
You may return the answer in any order.

Example 1
  nums: [1,1,1,2,2,3]
     k: 2
Output: [1,2]

Example 2
  nums: [1,4,2,5,7,4,4,5,5,5,2,7,2,5]
     k: 3
Output: [5,4,7]

Example 3
  nums: [9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1]
     k:  4
Output: [9, 1, 4, 3]

 --]]
 



-- Helper function to get the keys of a table, sorted largest to smallest
function getTableKeysSorted(t)
    local r = {}
    for k in pairs(t) do
        table.insert(r, k);
    end

     -- Sort the keys
    local function compare(a, b)
        return a > b
    end

    table.sort(r, compare)
    return r
end

-- Helper function to swap the positions of keys and values in a table
function transposeTable(t)
    local r = {}
    for k, v in pairs(t) do
        r[v] = k
    end
    return r
end

-- function printTable(title, t)
--     print("")
--     print(title)
--     for i, v in pairs(t) do
--         print(i, v)
--     end
-- end

function getMostFrequentNumbers(a, k)
    -- Build up a map where each key is a value from the input array
    -- and each value is the number of occurrences of the value in
    -- the input array.
    local m = {}
    for i, n in pairs(a) do
        if m[n] == nil then
            m[n] = 1
        else
            m[n] = m[n] + 1
        end
    end

    -- printTable("m:", m)

    local m2 = transposeTable(m)

    -- printTable("m2:", m2)

    -- Sort the table by value.
    -- We'll do this by getting the table keys, sorting them in the order we want
    -- and then getting the values by key.
    
    -- Get the keys, sorted largest to smallest
    local keys = getTableKeysSorted(m2)

    -- Build up an array of the most frequent k values
    local r = {}
    local i = 0;

    for key, val in pairs(keys) do
        table.insert(r, m2[val])
        i = i + 1
        if i == k then
            break
        end
    end

  return r
end


-- Helper to print the values of an array, with a prefix.
function printArrayValues(prefix, a)
    local s = prefix .. "[ "
    for k, v in ipairs(a) do
        s = s .. tostring(v) .. " "
    end
    s = s .. "]"
    print(s)
end


function runTest(nums, k)
    local r = getMostFrequentNumbers(nums, k)

    -- Print the results
    print("")
    printArrayValues("  nums: ", nums)
    print("     k: " ..tostring(k))
    printArrayValues("result: ", r)
end


-- Test data and test runs

nums = {1,1,1,2,2,3}
k = 2
runTest(nums, k)

nums = {1,2,5,7,4,4,5,5,2,2}
k = 3
runTest(nums, k)

nums = {9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1}
k = 4
runTest(nums, k)

print("")
