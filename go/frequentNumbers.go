package main

import (
	"fmt"
	"math/rand"
	"os"
	"sort"
	"strconv"
)

type Tuple struct {
	k int // One value from the input array nums
	v int // The number of times this value appears in nums
}

// ByValue implements sort.Interface based on the v (or value) field.
type ByValue []Tuple

func (t ByValue) Len() int           { return len(t) }
func (t ByValue) Less(i, j int) bool { return t[i].v > t[j].v }
func (t ByValue) Swap(i, j int)      { t[i], t[j] = t[j], t[i] }

// // Helper to get the value of an environment variable as an integer.
// func getEnvVarAsInt(name string, default_value int) int {
// 	s := os.Getenv(name)
// 	if s != "" {
// 		ret, err := strconv.Atoi(s)
// 		if err != nil {
// 			fmt.Println("Couldn't convert environment variable", s, " to int. err =", err)
// 			return default_value
// 		}
// 		return ret
// 	}
// 	return default_value
// }

func minInt(a int, b int) int {
	if a < b {
		return a
	}
	return b
}

func printIntSlice(title string, arr []int) {
	fmt.Print(title)
	fmt.Print(" [ ")
	n := len(arr)
	var numInts int
	noTruncate := os.Getenv("NO_TRUNCATE_ARRAYS")
	if noTruncate == "" {
		numInts = minInt(n, 30)
	} else if noTruncate != "0" {
		numInts = n
	} else {
		numInts = minInt(n, 30)
	}
	for i := 0; i < numInts; i++ {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(arr[i])
	}
	if numInts < n {
		fmt.Print(", ...")
	}
	fmt.Println(" ]")
}

func runTest(nums []int, k int) {
	result := getMostFrequentNumbers(nums, k)
	fmt.Println("")
	fmt.Println("     n:", len(nums))
	// fmt.Println("  nums =", nums)
	printIntSlice("  nums:", nums)
	fmt.Println("     k:", k)
	// fmt.Println("result =", result)
	printIntSlice("result:", result)
}

func runRandomDataTest(numDataPoints int, maxValue int, numMostFrequent int) {
	nums := []int{}

	for i := 0; i < numDataPoints; i++ {
		rn := rand.Intn(maxValue)
		nums = append(nums, rn)
	}

	runTest(nums, numMostFrequent)
}

func main() {
	if len(os.Args) > 3 {
		// Run the program with user supplied inputs.
		numDataPoints, err := strconv.Atoi(os.Args[1])
		if err != nil {
			fmt.Println("Couldn't convert arg 1 to int. err =", err)
			os.Exit(1)
		}
		maxValue, err := strconv.Atoi(os.Args[2])
		if err != nil {
			fmt.Println("Couldn't convert arg 2 to int. err =", err)
			os.Exit(1)
		}
		numMostFrequent, err := strconv.Atoi(os.Args[3])
		if err != nil {
			fmt.Println("Couldn't convert arg 3 to int. err =", err)
			os.Exit(1)
		}

		runRandomDataTest(numDataPoints, maxValue, numMostFrequent)

	} else {
		// Run the program with some canned data.

		nums := []int{1, 1, 1, 2, 2, 3}
		k := 2

		runTest(nums, k)

		nums = []int{1, 4, 2, 5, 7, 5, 4, 4, 5, 5, 5, 2, 7, 2, 5, 4}
		k = 3

		runTest(nums, k)

		nums = []int{9, 3, 9, 3, 9, 3, 7, 9, 7, 2, 9, 4, 4, 9, 4, 4, 4, 9, 9, 8, 8, 6, 6, 1, 1, 1, 1, 1, 1}
		k = 4

		runTest(nums, k)
	}

	fmt.Println("")
}

func getMostFrequentNumbers(nums []int, k int) []int {
	// Create a map of the inputs where the key is the input number
	// and the value is the number of occurrences of it.
	m := make(map[int]int)
	for _, num := range nums {
		m[num]++
	}
	// Put the map contents into a slice.
	l := []Tuple{}
	for num, freq := range m {
		l = append(l, Tuple{num, freq})
	}
	// Sort the slice by value (frequency)
	sort.Sort(ByValue(l))
	// Put the top k input values into the result
	result := make([]int, k)
	for i := 0; i < k; i++ {
		result[i] = l[i].k
	}
	return result
}

// Helper to generate a slice of count ints from 0 to (max - 1)
func generateRandomInputValues(max int, count int) []int {
	r := make([]int, count)
	for i := 0; i < count; i++ {
		r[i] = rand.Intn(max)
	}
	return r
}
