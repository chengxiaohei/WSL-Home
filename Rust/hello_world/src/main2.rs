#[derive(Debug)]
enum Cell{
    Int(i32),
    Float(f64),
    Text(String),
}

fn main(){
    let mut line: Vec<Cell> = vec![
        Cell::Int(12138),
        Cell::Float(3.1415926),
        Cell::Text(String::from("default")),
    ];
    line.push(Cell::Int(3));
    line.push(Cell::Float(3.6265));
    line.push(Cell::Text(String::from("hello")));

    for i in &line{
        println!("{i:?}");
    }

    for i in &line {
        // match i {
        //     Cell::Int(..) => println!("Integer"),
        //     Cell::Float(..) => println!("Float"),
        //     Cell::Text(..) => println!("Text"),
        //     // _ => (),
        // };
        if let Cell::Int(s) = i{
            println!("Integer:{s}");
        }
    }

}