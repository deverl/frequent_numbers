use std::collections::HashMap;


fn main() {
    let args: Vec<String> = std::env::args().skip(1).collect();
    if args.len() == 3 {
        let num_points = sanitized_int_from_string(args[0].clone());
        let num_values = sanitized_int_from_string(args[1].clone());
        let num_freq_values = sanitized_int_from_string(args[2].clone());
        println!("     num_points : {}", num_points);
        println!("     num_values : {}", num_values);
        println!("num_freq_values : {}", num_freq_values);
    }
    else {
        run_all_tests();
    }
}



fn sanitized_int_from_string(str: impl Into<String>) -> u32 {
    let s = str.into();
    return s.parse::<u32>().unwrap();
}




fn get_most_frequent_numbers(nums: Vec<u32>, _k: u32) -> Vec<u32> {
    let mut cache = HashMap::<u32,u32>::new();
    for n in nums {
        if cache.contains_key(&n) {
            let count = cache.get(&n).unwrap();
            cache.insert(n, count + 1);
        }
        else {
            cache.insert(n, 1);
        }
    }
    let mut cv : Vec<(u32, u32)> = Vec::new();
    println!("Cache:");
    for (key, value) in cache {
        println!("{}: {}", key, value);
        cv.push((key, value))
    }

    println!("Cache Vec:");
    for t in cv {
        println!("{} : {}", t.0, t.1);
    }

    cv.sort_by(|a,b| a.1.cmp(&b.1));

    println!("Sorted cache Vec:");
    for t in cv {
        println!("{} : {}", t.0, t.1);
    }

    let ret = vec![1, 2, 3];

    return ret;
}



fn run_all_tests() {
    println!("Running all tests");
    let nums1 = vec![1, 1, 1, 2, 2, 3];
    let k1 = 2;

    run_test(nums1, k1);

    let nums2 = vec![1,4,2,5,7,5,4,4,5,5,5,2,7,2,5,4];
    let k2 = 3;

    run_test(nums2, k2);

    let nums3 = vec![9,3,9,3,9,3,7,9,7,2,9,4,4,9,4,4,4,9,9,8,8,6,6,1,1,1,1,1,1];
    let k3 = 4;

    run_test(nums3, k3);
}



fn run_test(nums: Vec<u32>, k: u32) {
    println!("Running 1 test");
    let result = get_most_frequent_numbers(nums, k);
    for n in result {
        print!("{} ", n);
    }
    println!("");
}


