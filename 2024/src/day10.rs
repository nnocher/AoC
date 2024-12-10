use rayon::iter::*;

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
    let lines = read_file("day10_sample.txt");

    let map_height = lines.len();
    let map_width = lines[0].len();
    let (map, start_points) = parse_map(&lines);

    let total_score: u32 = start_points.iter().map(|p| run_map(&map, &vec![*p], map_width, map_height, 0, false)).sum();
    println!("The total score is: {}", total_score);
}

fn challenge1() {
    let lines = read_file("day10_1.txt");

    let map_height = lines.len();
    let map_width = lines[0].len();
    let (map, start_points) = parse_map(&lines);

    let total_score: u32 = start_points.par_iter().map(|p| run_map(&map, &vec![*p], map_width, map_height, 0, true)).sum();
    println!("The total score is: {}", total_score);
}

fn challenge2() {
    let lines = read_file("day10_1.txt");

    let map_height = lines.len();
    let map_width = lines[0].len();
    let (map, start_points) = parse_map(&lines);

    let total_score: u32 = start_points.par_iter().map(|p| run_map(&map, &vec![*p], map_width, map_height, 0, false)).sum();
    println!("The total score is: {}", total_score);
}

fn parse_map(lines: &Vec<String>) -> (Vec<u8>, Vec<usize>) {
    let mut result = Vec::<u8>::new();
    let mut start_points = Vec::<usize>::new();

    for line in lines {
        for c in line.chars() {
            let d = c.to_digit(10).unwrap() as u8;
            result.push(d);
            if d == 0 {
                start_points.push(result.len() - 1);
            }
        }
    }

    return (result, start_points);
}

fn run_map(map: &Vec<u8>, start_points: &Vec<usize>, map_width: usize, map_height: usize, current_height: u8, tail_mode: bool) -> u32 {
    let mut next_points = Vec::<usize>::new();

    let next_value = current_height + 1;

    for p in start_points {
        let index = *p;
        let x = p % map_width;
        let y = p / map_width;

        if x + 1 < map_width && map[index + 1] == next_value {
            next_points.push(index + 1);
        }
        if x > 0 && map[index - 1] == next_value {
            next_points.push(index - 1);
        }
        if y + 1 < map_height && map[index + map_width] == next_value {
            next_points.push(index + map_width);
        }
        if y > 0 && map[index - map_width] == next_value {
            next_points.push(index - map_width);
        }
    }

    if next_value < 9 {
        run_map(map, &next_points, map_width, map_height, next_value, tail_mode)
    }
    else {
        if tail_mode {
            // count results
            let mut tmp_distinct = Vec::<usize>::new();
            next_points.iter().for_each(|p|  {
                if !tmp_distinct.contains(p) {
                    tmp_distinct.push(*p);
                }
            });
            tmp_distinct.len() as u32
        }
        else {
            next_points.len() as u32
        }
    }
}