#![allow(dead_code)]

#[derive(Debug)]
enum Gender {
    Female,
    Male,
}

#[derive(Debug)]
struct Person {
    name: String,
    age: u8,
    gender: Gender,
}

fn main() {
    let tom = Person {
        name: String::from("Tom"),
        age: 18,
        gender: Gender::Male,
    };
    print!("{:#?}\n", tom);
    print!("{:?}\n", tom.name);
}
