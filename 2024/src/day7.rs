use rayon::iter::*;

use crate::helpers::read_file;

static INVALID_INDEX_MASKS: &'static [u32] = &[
    0b00000000000000000000000000000011,
    0b00000000000000000000000000001100,
    0b00000000000000000000000000110000,
    0b00000000000000000000000011000000,
    0b00000000000000000000001100000000,
    0b00000000000000000000110000000000,
    0b00000000000000000011000000000000,
    0b00000000000000001100000000000000,
    0b00000000000000110000000000000000,
    0b00000000000011000000000000000000,
    0b00000000001100000000000000000000,
    0b00000000110000000000000000000000,
    0b00000011000000000000000000000000,
    0b00001100000000000000000000000000,
    0b00110000000000000000000000000000,
    0b11000000000000000000000000000000,
];

pub fn run(challenge: i32) {
    match challenge {
        0 => sample(),
        1 => challenge1(),
        2 => challenge2(),
        _ => println!("Challenge not found :("),
    }
}

fn sample() {
    let lines = read_file("day7_sample.txt");
    let sum: u64 = lines.par_iter().map(|l| check_operation(l)).sum();
    println!("The sum is {}", sum);
}

fn challenge1() {
    let lines = read_file("day7_1.txt");
    let sum: u64 = lines.par_iter().map(|l| check_operation(l)).sum();
    println!("The sum is {}", sum);
}

fn challenge2() {
    let lines = read_file("day7_1.txt");
    let now = std::time::Instant::now();

    let sum: u64 = lines.par_iter().map(|l| check_operation2(l)).sum();
    
    let elapsed = now.elapsed();
    println!("The sum is {}", sum);
    println!("Elapsed: {:.2?}", elapsed);
}

fn check_operation(op: &String) -> u64 {
    let (result, values) = read_operation(op);
    let check_count = (1 << values.len()) - 1;

    for i in 0..check_count {
        let run_result = values.iter().fold((0, 0), |(r, j), v| {
            // Operation flag consists of 2 bit.
            // 0 -> +
            // 1 -> *
            // 10 -> ||
            let operation = if j == 0 {0} else {i >> ((j - 1)) & 1};
            match operation {
                0 => (r + *v as u64, j + 1),
                1 => (r * *v as u64, j + 1),
                _ => (r, j + 1) // ??
            }
        }).0;

        if run_result == result {
            return result;
        }
    }

    return 0;
}

fn check_operation2(op: &String) -> u64 {
    let (result, values) = read_operation(op);
    let check_count = (1 << (values.len() * 2)) - 1;

    for i in (0..check_count).filter(|i| validate_index(*i)) {
        let run_result = values.iter().fold((0, 0), |(r, j), v| {
            // Operation flag consists of 2 bit.
            // 00 -> +
            // 01 -> *
            // 10 -> ||
            let operation = if j == 0 {0} else {i >> ((j - 1) * 2) & 3};
            match operation {
                0 => (r + *v as u64, j + 1),
                1 => (r * *v as u64, j + 1),
                2 => {
                    let mut new_value = r.to_string();
                    new_value.push_str(&v.to_string());
                    let new = new_value.parse::<u64>().unwrap();
                    (new, j + 1)
                }
                _ => (r, j + 1) // ??
            }
        }).0;

        if run_result == result {
            return result;
        }
    }

    return 0;
}

fn validate_index(i: u32) -> bool {
    for m in INVALID_INDEX_MASKS {
        if *m > i {
            return true;
        }
        if i & m == *m {
            return false;
        }
    }
    
    return true;
}

fn read_operation(op: &String) -> (u64, Vec<u16>) {
    let mut op_split = op.split(":");
    let result = op_split.next().unwrap_or("0").trim().parse::<u64>().unwrap_or(0);
    let values: Vec<u16> = op_split.next().unwrap_or("").trim()
        .split(" ").map(|s| s.trim().parse::<u16>().unwrap_or(0)).collect();

    return (result, values);
}