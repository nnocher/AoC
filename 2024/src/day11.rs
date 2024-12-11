
use std::collections::HashMap;

use crate::helpers::read_file;

pub fn run(challenge: i32) {
    match challenge {
        0 => sample(),
        1 => challenge1(),
        2 => challenge2(),
        _ => println!("Challenge not found :("),
    }
}

fn sample() {
    let lines = read_file("day11_1.txt");

    let steps = 25;
    let mut cache = HashMap::<(u64, u8), u64>::new();
    let stones: Vec<u64> = lines.join("").split(" ").map(|s| s.parse::<u64>().unwrap()).collect();
    let result: u64 = stones.iter().map(|s| process_blink_optimized(*s, &mut cache, 0, steps)).sum();
    println!("After blinking {} times you get {} stones.", steps, result);
}

fn challenge1() {
    let lines = read_file("day11_1.txt");

    let steps = 25;
    let stones: Vec<u64> = lines.join("").split(" ").map(|s| s.parse::<u64>().unwrap()).collect();
    let result = blink(&stones, steps);
    println!("After blinking {} times you get {} stones.", steps, result.len());
}

fn challenge2() {
    let lines = read_file("day11_1.txt");

    let now = std::time::Instant::now();

    let steps = 75;
    let mut cache = HashMap::<(u64, u8), u64>::new();
    let stones: Vec<u64> = lines.join("").split(" ").map(|s| s.parse::<u64>().unwrap()).collect();
    let result: u64 = stones.iter().map(|s| process_blink_optimized(*s, &mut cache, 0, steps)).sum();

    let elapsed = now.elapsed();
    println!("After blinking {} times you get {} stones.", steps, result);
    println!("Elapsed: {:.2?}", elapsed);
}

fn blink(stones: &Vec<u64>, steps: u8) -> Vec<u64> {
    let mut result = stones.clone();

    for _ in 0..steps {
        result = process_blink(&result);
    }

    return result;
}

fn process_blink_optimized(stone: u64, cache: &mut HashMap<(u64, u8), u64>, step: u8, num_steps: u8) -> u64 {
    if step == num_steps {
        return 1;
    }

    if cache.contains_key(&(stone, step)) {
        return *cache.get(&(stone, step)).unwrap();
    }

    let result;
    if stone == 0 {
        result = process_blink_optimized(1, cache, step + 1, num_steps);
        
    }
    else {
        let number_of_digits: u32;
        number_of_digits = (stone as f64).log10() as u32 + 1;
            
        if number_of_digits % 2 == 0 {
            let factor = (10 as u64).pow(number_of_digits / 2);
            result = process_blink_optimized(stone / factor, cache, step + 1, num_steps) + 
                process_blink_optimized(stone % factor, cache, step + 1, num_steps);
        }
        else {
            result = process_blink_optimized(stone * 2024, cache, step + 1, num_steps);
        }
    }

    cache.insert((stone, step), result);
    result
}

fn _process_blink_optimized_str(stone: u64, cache: &mut HashMap<(u64, u8), u64>, step: u8, num_steps: u8) -> u64 {
    if step == num_steps {
        return 1;
    }

    if cache.contains_key(&(stone, step)) {
        return *cache.get(&(stone, step)).unwrap();
    }

    let result;
    if stone == 0 {
        result = process_blink_optimized(1, cache, step + 1, num_steps);
        
    }
    else {
        let str_value = stone.to_string();
        let str_length = str_value.len();

        if str_length % 2 == 0 {
            let first = &str_value[..str_length / 2];
            let second = &str_value[str_length / 2..];
            result = process_blink_optimized(first.parse().unwrap(), cache, step + 1, num_steps) + 
                process_blink_optimized(second.parse().unwrap(), cache, step + 1, num_steps);
        }
        else {
            result = process_blink_optimized(stone * 2024, cache, step + 1, num_steps);
        }
    }

    cache.insert((stone, step), result);
    result
}

fn process_blink(stones: &Vec<u64>) -> Vec<u64> {
    let mut result = Vec::<u64>::new();

    for stone in stones {
        if *stone == 0 {
            result.push(1);
            continue;
        }

        let number_of_digits: u32;
        number_of_digits = (*stone as f64).log10() as u32 + 1;
        
        if number_of_digits % 2 == 0 {
            let factor = (10 as u64).pow(number_of_digits / 2);
            result.push(stone / factor);
            result.push(stone % factor);
        }
        else {
            result.push(stone * 2024);
        }
    }

    return result;
}