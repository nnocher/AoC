use crate::helpers::read_file;

use regex::Regex;

pub fn run(challenge: i32) {
    match challenge {
        0 => sample(),
        1 => challenge1(),
        2 => challenge2(),
        _ => println!("Challenge not found :("),
    }
}

fn sample() {
    let data = read_file("day3_sample.txt");
    let data_str = data.join("");

    let reg = Regex::new(r"(mul\([0-9]+,[0-9]+\))|(don\'t\(\))|(do\(\))").unwrap();

    let mut enabled = true;
    let sum = reg.captures_iter(&data_str).map(|capture|
        process_mul(capture.get(0).unwrap().as_str(), &mut enabled)).sum::<i32>();
    println!("Sum: {}", sum);
}

fn challenge1() {
    let data = read_file("day3_1.txt");
    let data_str = data.join("");

    let reg = Regex::new(r"mul\([0-9]+,[0-9]+\)").unwrap();

    let mut enabled = true;
    let sum = reg.captures_iter(&data_str).map(|capture|
        process_mul(capture.get(0).unwrap().as_str(), &mut enabled)).sum::<i32>();
    println!("Sum: {}", sum);
}

fn challenge2() {
    let data = read_file("day3_1.txt");
    let data_str = data.join("");

    let reg = Regex::new(r"(mul\([0-9]+,[0-9]+\))|(don\'t\(\))|(do\(\))").unwrap();

    let mut enabled = true;
    let sum = reg.captures_iter(&data_str).map(|capture|
        process_mul(capture.get(0).unwrap().as_str(), &mut enabled)).sum::<i32>();
    println!("Sum: {}", sum);
}

fn process_mul(mul: &str, enabled: &mut bool) -> i32 {
    if mul.starts_with("don't") {
        *enabled = false;
    }
    else if mul.starts_with("do") {
        *enabled = true;
    }
    else if *enabled {
        let reg = Regex::new(r"([0-9]+)").unwrap();
        let captures = reg.captures_iter(mul)
            .map(|capture| capture.get(0).unwrap().as_str().parse().unwrap()).collect::<Vec<i32>>();

        return captures[0] * captures[1];
    }

    return 0
}