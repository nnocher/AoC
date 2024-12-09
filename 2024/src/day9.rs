use rayon::iter::*;

use crate::helpers::read_file;

#[derive(Clone, Copy)]
struct DataFragment {
    start: usize,
    end: usize,
    len: usize,
    data: u32,
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
    let lines = read_file("day9_sample.txt");

    let expanded = expand_data(&lines);

    let fragments = collect_fragments(&expanded);
    let defragmented = defragment(&fragments);
    let checksum = calc_fragment_checksum(&defragmented);
    println!("The checksum is {}", checksum);
}

fn challenge1() {
    let lines = read_file("day9_1.txt");

    let expanded = expand_data(&lines);
    println!("Data size: {}", expanded.len());
    let compressed = compress(&expanded);
    let checksum = calc_checksum(&compressed);
    println!("The checksum is {}", checksum);
}

fn challenge2() {
    let lines = read_file("day9_1.txt");

    let expanded = expand_data(&lines);

    let fragments = collect_fragments(&expanded);
    let defragmented = defragment(&fragments);
    let checksum = calc_fragment_checksum(&defragmented);
    println!("The checksum is {}", checksum);
}

fn expand_data(str_data: &Vec<String>) -> Vec<u32> {
    let data: Vec<u8> = str_data
        .join("")
        .bytes()
        .map(|b| (b as char).to_digit(10).unwrap() as u8)
        .collect();

    let mut result = Vec::<u32>::new();
    let mut current_index: u32 = 0;
    let mut mode = false;
    for d in data {
        let push_value = if mode {
            0
        } else {
            current_index = current_index + 1;
            current_index
        };
        for _ in 0..d {
            result.push(push_value);
        }
        mode = !mode;
    }

    return result;
}

fn compress(data: &Vec<u32>) -> Vec<u32> {
    let mut result = data.clone();
    let mut back_index = data.len() - 1;

    for i in 0..result.len() {
        if result[i] != 0 {
            continue;
        }

        result[i] = result[back_index];
        result[back_index] = 0;
        back_index = back_index - 1;
        while result[back_index] == 0 && back_index > i {
            back_index = back_index - 1;
        }

        if back_index <= i + 1 {
            break;
        }
    }

    return result;
}

fn collect_fragments(data: &Vec<u32>) -> Vec<DataFragment> {
    let mut result = Vec::<DataFragment>::new();

    let mut current_data = data[0];
    let mut start_index = 0;

    for i in 1..data.len() {
        if data[i] != current_data {
            result.push(DataFragment {
                start: start_index,
                end: i,
                len: i - start_index,
                data: current_data,
            });

            current_data = data[i];
            start_index = i;
        }
    }

    result.push(DataFragment {
        start: start_index,
        end: data.len(),
        len: data.len() - start_index,
        data: current_data,
    });

    return result;
}

fn defragment(data: &Vec<DataFragment>) -> Vec<DataFragment> {
    let mut result: Vec<DataFragment> = data.clone();
    let data_size = data.len();

    for i in 1..data_size - 1 {
        let fragment_index = data_size - i;
        // get fragment from original data
        let fragment = data[fragment_index];
        if fragment.data == 0 {
            continue;
        }

        // try to find open slot
        for j in 0..fragment_index {
            if result[j].data == 0 && result[j].len >= fragment.len {
                result[fragment_index].start = result[j].start;
                result[fragment_index].end = result[j].start + fragment.len;

                result[j].start = result[j].start + fragment.len;
                result[j].len = result[j].len - fragment.len;
                break;
            }
        }
    }

    return result.iter().filter(|d| d.data != 0).map(|d| *d).collect();
}

fn calc_fragment_checksum(data: &Vec<DataFragment>) -> u64 {
    return data.par_iter().map(|d| {
        let mut sum: u64 = 0;
        for i in d.start..d.end {
            sum = sum + i as u64 * (d.data - 1) as u64;
        }
        sum
    }).sum();
}

fn calc_checksum(data: &Vec<u32>) -> u64 {
    let mut checksum = 0;
    for i in 0..data.len() {
        if data[i] == 0 {
            break;
        }

        checksum = checksum + i as u64 * (data[i] - 1) as u64;
    }

    return checksum;
}
