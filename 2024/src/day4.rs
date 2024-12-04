use rayon::prelude::*;

use crate::helpers::read_file;

bitflags::bitflags! {
    #[derive(Clone, Copy, PartialEq, Eq)]
    struct Directions: u8 {
        const NONE =        0b00000000;
        const UP =          0b00000001;
        const DOWN =        0b00000010;
        const LEFT =        0b00000100;
        const RIGHT =       0b00001000;
        const LEFTUP =      0b00010000;
        const LEFTDOWN =    0b00100000;
        const RIGHTUP =     0b01000000;
        const RIGHTDOWN =   0b10000000;
    }
}

pub fn run(challenge: i32) {
    match challenge {
        0 => sample(),
        1 => challenge1(),
        2 => challenge2(),
        _ => println!("Challenge not found :("),
    }
}

fn sample() {
    let data = read_file("day4_sample.txt");
    let count = xmas_cross_search(&data);
    println!("{} X-MAS found.", count);
}

fn challenge1() {
    let data = read_file("day4_1.txt");
    let count = xmas_search(&data);
    println!("{} XMAS found.", count);
}

fn challenge2() {
    let data = read_file("day4_1.txt");

    let now = std::time::Instant::now();
    let count = xmas_cross_search(&data);

    let elapsed = now.elapsed();
    println!("{} X-MAS found.", count);
    println!("Elapsed: {:.2?}", elapsed);
}

fn xmas_cross_search(map: &Vec<String>) -> usize {
    let width = map[0].len();

    let map_line = map.join("").char_indices().map(|c| (c.0, c.1)).collect::<Vec<(usize, char)>>();
    return map_line.par_iter()
        .filter(|c| c.1 == 'A' && check_xmas_cross(c.0, width, &map_line)).count()
}

fn check_xmas_cross(pos: usize, map_width: usize, map: &Vec<(usize, char)>) -> bool {
    let check_direction = 
        Directions::LEFTUP | Directions::RIGHTDOWN | Directions::RIGHTUP | Directions::LEFTDOWN;

    let m_direction = filter_valid_directions(pos, map_width, map, check_direction, 'M', 1);
    let s_direction = filter_valid_directions(pos, map_width, map, check_direction & !m_direction, 'S', 1);

    if (m_direction | s_direction).bits() == check_direction.bits() &&
        has_two_directions(m_direction) {
        // check if not diagonal
        if m_direction != (Directions::LEFTUP | Directions::RIGHTDOWN) &&
            m_direction != (Directions::RIGHTUP | Directions::LEFTDOWN) {
            return true;
        }
    }

    return false;
}

fn has_two_directions(direction: Directions) -> bool {
    return direction.iter().filter(|d| !d.is_empty()).count() == 2
}

fn xmas_search(map: &Vec<String>) -> usize {
    let width = map[0].len();

    let map_line = map.join("").char_indices().map(|c| (c.0, c.1)).collect::<Vec<(usize, char)>>();
    return map_line.iter()
        .filter(|c| c.1 == 'X').fold(0,|sum, c| {
            sum + check_xmas(c.0, width, &map_line)
        });
}

fn check_xmas(pos: usize, map_width: usize, map: &Vec<(usize, char)>) -> usize {
    let mut check_direction = Directions::all();

    check_direction = filter_valid_directions(pos, map_width, map, check_direction, 'M', 1);
    check_direction = filter_valid_directions(pos, map_width, map, check_direction, 'A', 2);
    check_direction = filter_valid_directions(pos, map_width, map, check_direction, 'S', 3);

    return check_direction.iter().filter(|d| !d.is_empty()).count();
}

fn filter_valid_directions(pos: usize, map_width: usize, map: &Vec<(usize, char)>, direction: Directions, target: char, distance: usize) -> Directions {
    if direction.is_empty() {
        return Directions::NONE; // Shortcut
    }

    return direction.iter().fold(Directions::empty(),| result, f | {
        if check_direction(pos, map_width, map, f, target, distance) {
            result | f
        }
        else {
            result
        }
    });
}

fn check_direction(pos: usize, map_width: usize, map: &Vec<(usize, char)>, direction: Directions, target: char, distance: usize) -> bool {
    let x = pos % map_width;
    let y = pos / map_width;
    let map_height = map.len() / map_width;

    match direction {
        Directions::UP => {
            if y < distance {
                return false;
            }
            else {
                return map[(y - distance) * map_width + x].1 == target;
            }
        },
        Directions::DOWN => {
            if y + distance >= map_height {
                return false;
            }
            else {
                return map[(y + distance) * map_width + x].1 == target;
            }
        },
        Directions::LEFT => {
            if x < distance {
                return false;
            }
            else {
                return map[y * map_width + (x - distance)].1 == target;
            }
        },
        Directions::RIGHT => {            
            if x + distance >= map_width {
                return false;
            }
            else {
                return map[y * map_width + (x + distance)].1 == target;
            }
        },
        Directions::LEFTUP => {
            if y < distance || x < distance {
                return false;
            }
            else {
                return map[(y - distance) * map_width + (x - distance)].1 == target;
            }
        },
        Directions::LEFTDOWN => {
            if y + distance >= map_height || x < distance {
                return false;
            }
            else {
                return map[(y + distance) * map_width + (x - distance)].1 == target;
            }
        },
        Directions::RIGHTUP => {
            if y < distance || x + distance >= map_width {
                return false;
            }
            else {
                return map[(y - distance) * map_width + (x + distance)].1 == target;
            }
        },
        Directions::RIGHTDOWN => {
            if y + distance >= map_height || x + distance >= map_width {
                return false;
            }
            else {
                return map[(y + distance) * map_width + (x + distance)].1 == target;
            }
        },
        _ => return false,
    }
}