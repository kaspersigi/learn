fn main() {
    let a = 1995;
    let b = 11.22;
    let c = 'c';
    let d = "kaspersigi";
    let e = true;
    let f = [0, 1, 2, 3, 4, 5];
    let g = (a, b, c, d, e, f);
    print!("{:?}, {:?}, {:?}, {:?}, {:?}, {:?}\n", a, b, c, d, e, f);
    print!("{:?}\n", g);
    print!("{:#?}\n", g);
}
