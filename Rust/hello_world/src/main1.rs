#[derive(Debug)]
struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}

struct Tup(i32, i32, i32);

struct AlwaysEqual;

#[derive(Debug)]
enum Message {
    Quit,
    Move (User),
    Write (String),
    ChangeColor(i32, i32, i32),
}
impl Message {
	fn call(&self) {
		// 在这里定义方法体
		println!("{self:?}");
	}
}

fn main() {
    let user1 = User {
        email: String::from("someone@example.com"),
        username: String::from("someusername123"),
        active: true,
        sign_in_count: 1,
    };
	let user1 = User {
		email: String::from("fuck.com"),
		..user1
	};
	println!("{user1:?}");

	let tuple = Tup(1,2,3);

	let sub = AlwaysEqual;

	let m1 = Message::Quit;
	let m2 = Message::Move(user1);
	let m2 = Message::Move(User {active:true, email:String::from("hello"), username:String::from("changjie"), sign_in_count:32u64});
	let m2 = Message::Quit;
	let m3 = Message::Write(String::from("hello"));
	let m4 = Message::ChangeColor(1, 2, 3);

	// let a = match m2 {
	// 	Message::Quit => 0,
	// 	Message::Move(_) => 1,
	// 	Message::Write(_) => 2,
	// 	Message::ChangeColor(_, _, _) => 4,
	// 	// _ => 5,
	// 	other => 5,
	// };

	if let Message::Write(arg) = m3{
		println!("write {arg}");
	};
	// m1.call();
	// m2.call();
	// m3.call();
	// m4.call();

}

// fn main() {

// 	let str = String::from("what the fuck ?");
// 	let s = &str[..];
// 	let fuck = "fuck";
// 	for (i, c) in s.as_bytes().iter().enumerate(){
// 		println!("index:{i}==>char:{c:?}");
// 	}
// 	for c in s.chars(){
// 		print!("{c} ");
// 	}
// 	println!("s: {s}");
// }


fn find_max_value(data: &[i32]) -> i32{
	let mut max_value = data[0];
	for d in data.iter(){
		if *d > max_value {
			max_value = *d;
		}
	}
	max_value
}
