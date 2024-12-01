use std::{
    fs::File,
    io::{prelude::*, BufReader}
};


pub fn read_file(file_path: &str) -> Vec<String> {
    let mut full_file: String = "files/".to_owned();
    full_file.push_str(file_path);

    let file = File::open(full_file).expect("no such file");
    let buf = BufReader::new(file);
    buf.lines()
        .map(|l| l.expect("Could not parse line"))
        .collect()
}