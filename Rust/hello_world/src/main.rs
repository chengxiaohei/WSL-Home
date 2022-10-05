fn main() {
    let mut s1 = String::from("Hello, ");
    let s2 = String::from("world!");
    s1 = s1 + &s2; // 注意 s1 被移动了，不能继续使用
    println!("s1:{s1}");
    println!("s2:{s2}");
    // println!("s3:{s3}");
    s1 = format!("{s1}-{s1}-{s2}");
    println!("s1:{s1}");
    println!("s2:{s2}");

}
