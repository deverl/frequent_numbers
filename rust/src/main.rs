use std::collections::HashMap;
use std::env;
use std::time::{SystemTime, UNIX_EPOCH};

/// Gets an environment variable as an integer, or returns a default value
fn get_env_var_as_int(name: &str, default_value: i32) -> i32 {
    env::var(name)
        .ok()
        .and_then(|s| s.parse().ok())
        .unwrap_or(default_value)
}

/// Returns the k most frequent elements from the input vector
fn get_most_frequent_numbers(nums: &[i32], k: usize) -> Vec<i32> {
    // Build up a HashMap where keys are unique values from nums
    // and values are the count of occurrences
    let mut frequency_map: HashMap<i32, usize> = HashMap::new();
    for &num in nums {
        *frequency_map.entry(num).or_insert(0) += 1;
    }
    
    // Convert the HashMap to a vector of (number, frequency) pairs
    let mut frequency_vec: Vec<(i32, usize)> = frequency_map.into_iter().collect();
    
    // Sort by frequency in descending order
    frequency_vec.sort_by(|a, b| b.1.cmp(&a.1));
    
    // Extract the top k elements
    frequency_vec.iter()
        .take(k)
        .map(|(num, _)| *num)
        .collect()
}

/// Prints a vector with optional truncation
fn print_vec(label: &str, v: &[i32]) {
    let no_truncate = get_env_var_as_int("NO_TRUNCATE_ARRAYS", 0) != 0;
    print!("{}[ ", label);
    
    for (i, &val) in v.iter().enumerate() {
        if i > 0 {
            print!(", ");
        }
        if !no_truncate && i >= 30 {
            print!("... ");
            break;
        }
        print!("{}", val);
    }
    println!(" ]");
}

/// Runs a test with the given input
fn run_test(nums: &[i32], k: usize) {
    let result = get_most_frequent_numbers(nums, k);
    
    println!();
    println!("     n: {}", nums.len());
    print_vec("  nums: ", nums);
    println!("     k: {}", k);
    print_vec("result: ", &result);
}

/// Runs a test with random inputs
fn run_random_inputs_test(num_data_points: usize, max_value: i32, num_most_frequent: usize) {
    let mut nums = Vec::new();
    
    // Seed with current time
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_secs();
    
    // Simple pseudo-random number generator (LCG)
    let mut rng_state = seed;
    for _ in 0..num_data_points {
        rng_state = rng_state.wrapping_mul(1103515245).wrapping_add(12345);
        let n = ((rng_state / 65536) % (max_value as u64)) as i32;
        nums.push(n);
    }
    
    run_test(&nums, num_most_frequent);
}

/// Extracts digits from a string and converts to integer
fn int_from_string(s: &str) -> i32 {
    let digits: String = s.chars().filter(|c| c.is_ascii_digit()).collect();
    digits.parse().unwrap_or(0)
}

fn main() {
    let args: Vec<String> = env::args().collect();
    
    if args.len() > 3 {
        // Run with user-supplied inputs
        let num_data_points = int_from_string(&args[1]);
        let max_value = int_from_string(&args[2]);
        let num_most_frequent = int_from_string(&args[3]);
        
        run_random_inputs_test(
            num_data_points as usize,
            max_value,
            num_most_frequent as usize
        );
    } else {
        // Run with canned test data
        let nums1 = vec![1, 1, 1, 2, 2, 3];
        let k1 = 2;
        run_test(&nums1, k1);
        
        let nums2 = vec![1, 4, 2, 5, 7, 5, 4, 4, 5, 5, 5, 2, 7, 2, 5, 4];
        let k2 = 3;
        run_test(&nums2, k2);
        
        let nums3 = vec![9, 3, 9, 3, 9, 3, 7, 9, 7, 2, 9, 4, 4, 9, 4, 4, 4, 9, 9, 8, 8, 6, 6, 1, 1, 1, 1, 1, 1];
        let k3 = 4;
        run_test(&nums3, k3);
    }
    
    println!();
}

