use std::{vec, collections::HashMap};

use crate::helpers::read_file;

pub fn run(challenge: i32) {
    match challenge {
        0=> sample(),
        1=> challenge1(),
        2=> challenge2(),
        _=> println!("Challenge not found :("),
    }
}

fn sample() {
    let lines = read_file("day1_sample.txt");

    //let sum = count_distanes(lines);
    let sum = count_similarity(lines);
    println!("The sum of all distances is {}", sum);
}

fn challenge1() {
    let lines = read_file("day1_1.txt");
    
    let sum = count_distanes(lines);
    println!("The sum of all distances is {}", sum);
}

fn challenge2() {
    let lines = read_file("day1_1.txt");

    let sum = count_similarity(lines);
    println!("The sum of similarity is {}", sum);
}

fn count_distanes(lines: Vec<String>) -> i32 {
    let mut left: Vec<i32> = vec![];
    let mut right: Vec<i32> = vec![];
    parse_lines(lines, &mut left, &mut right);
    left.sort();
    right.sort();

    let mut sum = 0;

    for i in 0..left.len() {
        let delta = (left[i] - right[i]).abs();
        println!("{} -- {}|{} - {}", i, left[i], right[i], delta);

        sum = sum + delta;
    }
    return sum;
}

fn count_similarity(lines: Vec<String>) -> i32 {
    let mut left: Vec<i32> = vec![];
    let mut right: Vec<i32> = vec![];
    parse_lines(lines, &mut left, &mut right);

    let mut count_hash = HashMap::<i32, usize>::new();
    let mut sum: i32 = 0;
    for i in left {
        let count;
        if count_hash.contains_key(&i) {
            count = count_hash[&i];
        }
        else {
            count = right.iter().filter(|&n| *n == i).count();
            count_hash.insert(i, count);
        }

        println!("{} - {}", i, count);
        
        sum = sum + i * count as i32;
    }

    return sum;
}

fn parse_lines(lines: Vec<String>, left: &mut Vec<i32>, right: &mut Vec<i32>) {
    for line in lines {
        let mut content = line.split("   ");
        
        left.push(content.next().expect("Failed to read line").trim().parse::<i32>().unwrap());
        right.push(content.next().expect("Failed to read line").trim().parse::<i32>().unwrap());
    }
}