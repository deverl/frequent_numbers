
fun getMostFrequentNumbers(numbers: List<Int>, k: Int) : List<Int> {
    var ret = arrayListOf<Int>()
    val cache = HashMap<Int, Int>()
    for (n in numbers) {
        var count = cache.getOrDefault(n, 0)
        cache[n] = count + 1
    }
    val l = cache.entries.toList().sortedByDescending { it.value }
    var i = 0
    while ( i < k && i < l.size) {
        ret.add(l[i].key)
        i++
    }
    return ret
}



fun runTest(numbers: List<Int>, k: Int) {
    val numInputs = numbers.size
    val freq = getMostFrequentNumbers(numbers, k)

    println()
    println("    n: $numInputs")
    if (numbers.size > 20) {
        val nums = numbers.slice(0..20)
        println(" nums: $nums (truncated)")
    } else {
        println(" nums: $numbers")
    }

    println("    k: $k")
    println("result: $freq")
}


fun runAllTests() {
    val numbers1 = listOf(1, 1, 1, 2, 2, 3)
    val k1 = 2
    runTest(numbers1, k1)

    val numbers2 = listOf(1,4,2,5,7,5,4,4,5,5,5,2,7,2,5,4)
    val k2 = 3
    runTest(numbers2, k2)

    val numbers3 = listOf(9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1)
    val k3 = 4
    runTest(numbers3, k3)

    println()
}

fun generateRandomList(numCount: Int, numValues: Int) : List<Int> {
    var l = arrayListOf<Int>()
    for (i in 1..numCount) {
        l.add(java.util.Random().nextInt(numValues))
    }
    return l
}

fun sanitizedIntFromString(s: String): Int {
    return s.replace("_", "").replace(",", "").toInt()
}


fun runRandomTest(args: Array<String>) {
    if (args.size > 2) { // Probably don't need to check here.
        val numCount = sanitizedIntFromString(args[0])
        val numValues = sanitizedIntFromString(args[1])
        val numMostFrequent = sanitizedIntFromString(args[2])
        val numbers = generateRandomList(numCount, numValues)
        runTest(numbers, numMostFrequent)
        println()
    }
}


fun main(args: Array<String>) {
    if (args.size > 2) {
        runRandomTest(args)
   } else {
        runAllTests()
    }
}