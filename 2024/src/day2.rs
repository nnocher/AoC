use std::time::Instant;
use rayon::prelude::*;

use crate::helpers::read_file;

const SAFETY_FAIL: u8 = 0;
const SAFETY_OK: u8 = 1;
const SAFETY_FAIL_BEFORE_SKIP: u8 = 2;

const NO_SKIP: i32 = -1;

pub fn run(challenge: i32) {
    match challenge {
        0 => sample(),
        1 => challenge1(),
        2 => challenge2(),
        _ => println!("Challenge not found :("),
    }
}

fn sample() {
    let data = read_file("day2_sample.txt");
    let count = data.par_iter().filter(|line| check_safety_dampened(line) == SAFETY_OK).count();
    println!("{} reactors are safe.", count);
}


fn challenge1() {
    let count = read_file("day2_1.txt")
        .par_iter().filter(|line| check_safety(line, NO_SKIP) == SAFETY_OK).count();
    println!("{} reactors are safe.", count);
}

fn challenge2() {
    let data = read_file("day2_1.txt");

    let now = Instant::now();
    
    let count = data.par_iter().filter(|line| check_safety_dampened(line) == SAFETY_OK).count();
    
    let elapsed = now.elapsed();
    println!("{} reactors are safe.", count);
    println!("Elapsed: {:.2?}", elapsed);
}

fn check_safety(data: &String, skip: i32) -> u8 {
    let mut levels = data.split(" ").clone();
    let mut current_index = 0;
    let mut mode: i32 = 0;

    if skip == 0 {
        levels.next();
        current_index = 1;
    }

    let mut previous = levels.next().unwrap().trim().parse::<i32>().unwrap();

    for level in levels {
        current_index = current_index + 1;
        if current_index == skip as i32 {
            continue;
        }

        let current = level.trim().parse::<i32>().unwrap();
        let delta = current - previous;

        if mode == 0 {
            if delta < 0 {
                mode = -1;
            } else if delta > 0 {
                mode = 1;
            } else {
                if current_index < skip {
                    return SAFETY_FAIL_BEFORE_SKIP;
                }
                return SAFETY_FAIL;
            }
        }
        if delta * mode < 1 || delta * mode > 3 {
            if current_index < skip {
                return SAFETY_FAIL_BEFORE_SKIP;
            }
            return SAFETY_FAIL;
        }

        previous = current;
    }

    return SAFETY_OK;
}

fn check_safety_dampened(data: &String) -> u8 {
    let level_count = data.split(" ").count() as i32;

    for i in -1..level_count {
        let result = check_safety(&data, i);
        if result != SAFETY_FAIL {
            return result;
        }
    }

    return SAFETY_OK;
}
