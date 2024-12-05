use rayon::iter::*;
use std::collections::{HashMap, VecDeque};

use crate::helpers::read_file;

pub fn run(challenge: i32) {
    match challenge {
        0 => sample(),
        1 => challenge1(),
        2 => challenge2(),
        _ => println!("Challenge not found :("),
    };
}

fn sample() {
    let lines = read_file("day5_sample.txt");

    let (rules, updates) = split_lines(lines);
    let sum = updates
        .iter()
        .filter(|u| !check_valid(u, &rules))
        .map(|u| get_middle(&validate(u, &rules)))
        .sum::<i32>();

    println!("Page sum is {}", sum);
}

fn challenge1() {
    let lines = read_file("day5_1.txt");

    let (rules, updates) = split_lines(lines);
    let sum = updates
        .par_iter()
        .filter(|u| check_valid(u, &rules))
        .map(|u| get_middle(u))
        .sum::<i32>();

    println!("Page sum is {}", sum);
}

fn challenge2() {
    let lines = read_file("day5_1.txt");

    let (rules, updates) = split_lines(lines);
    let sum = updates
        .par_iter()
        .filter(|u| !check_valid(u, &rules))
        .map(|u| get_middle(&validate(u, &rules)))
        .sum::<i32>();

    println!("Page sum is {}", sum);
}

fn split_lines(lines: Vec<String>) -> (HashMap<i32, Vec<i32>>, Vec<Vec<i32>>) {
    let mut rule_hash = HashMap::<i32, Vec<i32>>::new();
    let mut updates = Vec::<Vec<i32>>::new();

    let mut read_rules = true;
    for line in lines {
        if line.trim().is_empty() {
            read_rules = false;
        } else if read_rules {
            let rule = line
                .split("|")
                .map(|r| r.trim().parse::<i32>().unwrap())
                .collect::<Vec<i32>>();
            if !rule_hash.contains_key(&rule[0]) {
                rule_hash.insert(rule[0], Vec::<i32>::new());
            }

            rule_hash.entry(rule[0]).or_insert(Vec::new()).push(rule[1]);
        } else {
            updates.push(
                line.split(",")
                    .map(|p| p.trim().parse::<i32>().unwrap())
                    .collect::<Vec<i32>>(),
            );
        }
    }

    return (rule_hash, updates);
}

fn check_valid(updates: &Vec<i32>, rules: &HashMap<i32, Vec<i32>>) -> bool {
    let update_count = updates.len() - 1;
    for i in 0..update_count {
        let current_index = update_count - i;
        let current_page = updates[current_index];

        // Validate rules
        if rules.contains_key(&current_page) {
            let current_rules = rules.get(&current_page).unwrap();
            if updates
                .iter()
                .take(current_index)
                .any(|u| current_rules.contains(u))
            {
                return false;
            }
        }
    }

    return true;
}

fn validate(updates: &Vec<i32>, rules: &HashMap<i32, Vec<i32>>) -> Vec<i32> {
    let update_count = updates.len();
    let mut valid = updates.clone();

    let mut invalid_queue: VecDeque<i32> = VecDeque::from(updates.clone());

    while invalid_queue.len() > 0 {
        let current_page = invalid_queue.pop_front().unwrap();

        if rules.contains_key(&current_page) {
            let item_index = valid.iter().position(|p| *p == current_page).unwrap();

            for rule in rules.get(&current_page).unwrap() {
                for j in item_index + 1..update_count {
                    if valid[j] == *rule {
                        if !invalid_queue.contains(&valid[j]) {
                            invalid_queue.push_back(valid[j]);
                        }

                        valid.insert(item_index, valid[j]);
                        valid.remove(j + 1);
                        break;
                    }
                }
            }
        }
    }

    valid.reverse(); // Sortiert es falschherum aber funktionert.
    return valid;
}

fn get_middle(updates: &Vec<i32>) -> i32 {
    let middle_index = updates.len() / 2;
    return updates[middle_index];
}
