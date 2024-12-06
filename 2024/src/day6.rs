use rayon::iter::*;
use core::time;
use std::thread::sleep;

use crate::helpers::read_file;

#[derive(Clone, Copy, PartialEq)]
struct Position {
    x: usize,
    y: usize
}

#[derive(Clone, PartialEq)]
struct Tile {
    x: usize,
    y: usize,
    c: char,
    move_dir: u8
}

const DIR_UP: u8 = 1;
const DIR_RIGHT: u8 = 2;
const DIR_DOWN: u8 = 4;
const DIR_LEFT: u8 = 8;

pub fn run(challenge: i32) {
    match challenge {
        0 => sample(),
        1 => challenge1(),
        2 => challenge2(),
        _ => println!("Challenge not found :("),
    }
}

fn sample() {
    let lines = read_file("day6_sample.txt");

    println!("Parsing map and finding possible locations...");
    let (map, width, pos) = parse_map(&lines);
    let mut move_map = map.clone();
    let _ = run_map(&mut move_map, width, pos, true, false);

    let possible_positions: Vec<&Tile> = move_map.par_iter().filter(|m| m.c == 'X' || m.c == 'O').collect();
    println!("{} possible positions found!", possible_positions.len());
    
    let results: i32 = possible_positions.par_iter().map(|t| {
            let mut map_clone = map.clone();
            map_clone[t.y * width + t.x].c = '#';
            if run_map(&mut map_clone, width, pos, false, false) {1} else {0}
        }).sum();

    println!("{} possible positions.", results);
}

fn challenge1() {
    let lines = read_file("day6_1.txt");

    let (map, width, pos) = parse_map(&lines);
    let mut move_map = map.clone();
    let _ = run_map(&mut move_map, width, pos, true, false);

    let visited = move_map.par_iter().filter(|m| m.c == 'X' || m.c == 'O').count();
    println!("{} positions visited.", visited);
}

fn challenge2() {
    let lines = read_file("day6_1.txt");

    let now = std::time::Instant::now();

    println!("Parsing map and finding possible locations...");
    let (map, width, pos) = parse_map(&lines);
    let mut move_map = map.clone();
    let _ = run_map(&mut move_map, width, pos, true, false);

    let possible_positions: Vec<&Tile> = move_map.par_iter().filter(|m| m.c == 'X' || m.c == 'O').collect();
    println!("{} possible positions found!", possible_positions.len());
    
    let results: i32 = possible_positions.par_iter().map(|t| {
            let mut map_clone = map.clone();
            map_clone[t.y * width + t.x].c = '#';
            if run_map(&mut map_clone, width, pos, false, false) {1} else {0}
        }).sum();

    let elapsed = now.elapsed();
    println!("{} possible positions.", results);
    println!("Elapsed: {:.2?}", elapsed);
}

fn run_map(move_map: &mut Vec<Tile>, width: usize, start: Position, no_cycle: bool, print_mode: bool) -> bool {
    let height = move_map.len() / width;

    let mut at_exit = false;
    let mut current_pos = Position {
        x: start.x,
        y: start.y
    };
    let mut current_dir = DIR_UP;
    let mut is_cycle = false;

    let mut counter: usize = 0;
    while !at_exit {
        // move
        let (possible, tmp_pos) = move_pos(&current_pos, current_dir);
        if !possible {
            // at left or top!
            at_exit = true;
        }
        else {
            if tmp_pos.y >= height || tmp_pos.x >= width {
                // at right or bottom!
                at_exit = true;
            }
            else {
                // check if free Tile and move
                let index = tmp_pos.y * width + tmp_pos.x;
                let current_index = current_pos.y * width + current_pos.x;

                if move_map[index].c != '#' {
                    if !no_cycle && move_map[index].move_dir & current_dir > 0 {
                        // Detect cycle
                        is_cycle = true;
                        break;
                    }

                    if !no_cycle {
                        move_map[index].move_dir = move_map[index].move_dir | current_dir;
                    }
                    move_map[current_index].c = 'X';
                    move_map[index].c = 'O';
                    current_pos = tmp_pos;
                }
                else {
                    current_dir = turn_direction(current_dir);
                    move_map[current_index].move_dir = move_map[current_index].move_dir | current_dir;
                }
            }
        }

        if print_mode {
            if counter % 50 == 0 {
                println!("Step {}", counter);
                _print_map(&move_map, width);
                sleep(time::Duration::from_millis(500));
            }

            counter = counter + 1;
        }
    }

    return is_cycle;
}

fn move_pos(pos: &Position, dir: u8) -> (bool, Position) {
    let mut new_pos = pos.clone();
    
    match dir {
        DIR_UP => {
            if pos.y == 0 {
                return (false, new_pos);
            }
            new_pos.y = pos.y - 1;
        },
        DIR_RIGHT => new_pos.x = pos.x + 1,
        DIR_DOWN => new_pos.y = pos.y + 1,
        DIR_LEFT => {
            if pos.x == 0 {
                return (false, new_pos);
            }
            new_pos.x = pos.x - 1;
        },
        _ => return (false, new_pos)
    }

    return (true, new_pos);
}

fn turn_direction(dir: u8) -> u8 {
    if dir == DIR_LEFT {
        return DIR_UP;
    }

    return dir << 1;
}

fn _print_map(map: &Vec<Tile>, width: usize) {
    for y in 0..map.len() / width {
        for x in 0..width {
            print!("{}", map[y * width + x].c);
        }
        print!("\n");
    }
}

fn parse_map(lines: &Vec<String>) -> (Vec<Tile>, usize, Position) {
    let mut map = Vec::<Tile>::new();
    let mut pos: Position = Position {
        x: 0,
        y: 0
    };

    for y in 0..lines.len() {
        let chars = lines[y].chars();
        let mut x = 0;

        for c in chars {
            map.push(Tile { x, y, c, move_dir: 0});
            if c == '^' {
                pos.x = x;
                pos.y = y;
            }
            x = x + 1;
        }
    }

    return (map, lines[0].len(), pos);
}