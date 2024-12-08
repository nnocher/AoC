use std::ops;
use std::collections::HashMap;
use rayon::iter::*;

use crate::helpers::read_file;

#[derive(Clone, Copy, PartialEq, Eq)]
struct Coord {
    x: i32,
    y: i32
}

impl ops::Sub<Coord> for Coord {
    type Output = Coord;

    fn sub(self, _rhs: Coord) -> Coord {
        Coord {x: self.x - _rhs.x, y: self.y - _rhs.y}
    }
}

impl ops::Add<Coord> for Coord {
    type Output = Coord;

    fn add(self, _rhs: Coord) -> Coord {
        Coord {x: self.x + _rhs.x, y: self.y + _rhs.y}
    }
}

impl ops::Mul<i32> for Coord {
    type Output = Coord;

    fn mul(self, _rhs: i32) -> Coord {
        Coord {x: self.x * _rhs, y: self.y * _rhs}
    }
}

pub fn run(challenge: i32) {
    match challenge {
        0 => sample(),
        1 => challenge1(),
        2 => challenge2(),
        _ => println!("Challenge not found :(")
    }
}

fn sample() {
    let lines = read_file("day8_sample.txt");

    let map_width = lines.get(0).unwrap().len() as i32;
    let map_height = lines.len() as i32;
    let nodes = collect_nodes(&lines);
    let antinodes = collect_antinodes(&nodes, map_width, map_height, true);
    let count = distinct_nodes(&antinodes).len();

    println!("{} antinodes found.", count);
}

fn challenge1() {
    let lines = read_file("day8_1.txt");

    let map_width = lines.get(0).unwrap().len() as i32;
    let map_height = lines.len() as i32;
    let nodes = collect_nodes(&lines);
    let antinodes = collect_antinodes(&nodes, map_width, map_height, false);
    let count = distinct_nodes(&antinodes).len();

    println!("{} antinodes found.", count);
}

fn challenge2() {
    let lines = read_file("day8_1.txt");

    let map_width = lines.get(0).unwrap().len() as i32;
    let map_height = lines.len() as i32;
    let nodes = collect_nodes(&lines);
    let antinodes = collect_antinodes(&nodes, map_width, map_height, true);
    let count = distinct_nodes(&antinodes).len();

    println!("{} antinodes found.", count);
}

fn collect_nodes(lines: &Vec<String>) -> HashMap<char, Vec<Coord>> {
    let mut result = HashMap::<char, Vec<Coord>>::new();
    let mut y = 0;

    for line in lines {
        let mut x = 0;
        for c in line.chars() {
            if c != '.' {
                result.entry(c).or_insert(Vec::<Coord>::new()).push(Coord {x, y});
            }

            x = x + 1;
        }
        y = y + 1;
    }

    return result;
}

fn collect_antinodes(nodes: &HashMap<char, Vec<Coord>>, map_width: i32, map_height: i32, extended: bool) -> Vec<(char, Vec<Coord>)> {
    return nodes.par_iter().map(|v| {
        let mut antinodes = Vec::<Coord>::new();
        for i in 0..v.1.len() {
            let current = v.1.get(i).unwrap();
            v.1.iter().skip(i + 1).for_each(|c| {
                get_antinodes(*current, *c, map_width, map_height, extended).iter()
                    .for_each(|n| antinodes.push(*n));
            });
        }
        (*v.0, antinodes)
    }).collect();
}

fn get_antinodes(c0: Coord, c1: Coord, map_width: i32, map_height: i32, extended: bool) -> Vec<Coord> {
    let delta = c1 - c0;
    let mut result = Vec::<Coord>::new();

    if extended {
        // add self
        result.push(c0);
        result.push(c1);

        let mut run_up = true;
        let mut run_down = true;
        let mut i = 1;
        while run_up || run_down {
            let run_delta = delta * i;
            if run_up {
                let antinode_up = c0 - run_delta;
                if validate_node(&antinode_up, map_width, map_height) {
                    result.push(antinode_up);
                }
                else {
                    run_up = false;
                }
            }
            if run_down {
                let antinode_down = c1 + run_delta;
                if validate_node(&antinode_down, map_width, map_height) {
                    result.push(antinode_down);
                }
                else {
                    run_down = false;
                }
            }

            i = i + 1;
        }
    }
    else  {
        let antinode0 = c0 - delta;
        let antinode1 = c1 + delta;
        if validate_node(&antinode0, map_width, map_height) { result.push(antinode0) }
        if validate_node(&antinode1, map_width, map_height) { result.push(antinode1) }
    }

    return result;
}

fn validate_node(coord: &Coord, map_width: i32, map_height: i32) -> bool {
    !(coord.x < 0 || coord.y < 0 || coord.x >= map_width || coord.y >= map_height)
}

fn distinct_nodes(coords: &Vec<(char, Vec<Coord>)>) -> Vec<Coord> {
    let mut result = Vec::<Coord>::new();
    coords.iter().for_each(|p| {
        p.1.iter().for_each(|c| {
            if !result.contains(c) {
                result.push(*c);
            }
        });
    });

    return result;
}
