#include <iostream>
#include <regex>

int main(){
	std::string data1 = "{\"code\":200,\"msg\":\"\",\"count\":0,\"data\":40}\r\n\0\r\n\r\n}";
	std::regex line_re("[\n\r]");
	std::vector<std::string> v1(std::sregex_token_iterator(data1.begin(), data1.end(), line_re, -1), std::sregex_token_iterator());
	printf("%s\n", v1[0].c_str());	
	
	std::string data2 = "{\"code\":200,\"msg\":\"\",\"count\"d0,\"data\":40}\r\n";
	line_re="[\n\r]";
	std::vector<std::string> v2(std::sregex_token_iterator(data2.begin(), data2.end(), line_re, -1), std::sregex_token_iterator());
	printf("%s\n", v2[0].c_str());	
	return 0;
}
