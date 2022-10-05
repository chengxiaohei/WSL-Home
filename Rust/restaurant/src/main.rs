mod front_of_house;
use crate::front_of_house::hosting;

fn main(){
	println!("hello world");
	hosting::add_to_waitlist();
	hosting::a::a();
}
