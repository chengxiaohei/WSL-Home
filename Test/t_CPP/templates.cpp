#include <iostream>
#include <vector>
#include <string>
#include <tuple>
using namespace std;

// template<typename... Args>
// ostream &operator << (ostream &os, const tuple<Args&...> t){
// 	os << '(';
// 	PRINT_TUPLE<0, sizeof...(Args), Args>::print(os, t);
// 	return os << ')';
// }

// template<int MAX, typename... Args>
// struct PRINT_TUPLE<MAX, MAX, Args...> {
// 	static void print(ostream &os, const tuple<Args&...> &t){ }
// };

// template<int IDX, int MAX, typename... Args>
// struct PRINT_TUPLE {
// 	static void print(ostream &os, const tuple<Args&...> t){
// 		os << get<IDX>(t) << (IDX+1==MAX ? "" : ",");
// 		PRINT_TUPLE<IDX+1, MAX, Args...>::print(os, t);
// 	}
// };

template <typename... Types>
void printEveryThing(const Types&... args){
	// if constexpr(sizeof...(args) == 0){
	// 	cout << arg1 << endl;
	// }else{
	// 	cout << arg1 << endl;
	// 	printEveryThing(args...);
	// }
	((cout << args << ","), ...) << endl;
}

template <typename... Types>
double Sum(Types... args){
	return (args + ...);
	// return (... + args);
}

template<auto... values>
double Sum(){
	return (values + ...);
}

int main(){
	// vector<int> A{1,2,3,4};
	string B("hello");
	int num = 11;
	float a = 1.536342;
	auto t = make_tuple("1", 2, 3.13, "heloo", 'a');
	printEveryThing(B, num, a);
	cout << Sum(1,3,56,1,2.25) << endl;
	cout << Sum<1,2,3,4>() << endl;
	int *p = new int(1);
	p = nullptr;
	delete p;
	return 0;
}
