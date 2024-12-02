use std::io;

mod day1;
mod day2;

mod helpers;

fn main() {
    println!("Advent of Code 2024!");
    println!("Select day: ");

    // --- Day prompt
    // // Get day
    // let mut input = String::new();
    // io::stdin()
    //     .read_line(&mut input)
    //     .expect("Failed to read line");
    // let day = input.trim().parse::<i32>().unwrap();
    
    // // Get challenge
    // println!("Select challenge [1/2]: ");
    // input = String::new();
    // io::stdin()
    //     .read_line(&mut input)
    //     .expect("Failed to read line");
    // let challenge = input.trim().parse::<i32>().unwrap();
    // ---
    let day = 2;
    let challenge = 2;

    println!("------------------------------");
    println!("Selected: Day {} Challenge {}", day, challenge);
    println!("------------------------------");
    run_day(day, challenge);
    
}

fn run_day(day: i32, challenge: i32) {
    match day {
        1=> day1::run(challenge),
        2=> day2::run(challenge),
        _=> println!("Day not found :(")
    }
}
