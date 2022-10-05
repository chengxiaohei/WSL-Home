#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;

void fillVector(string Line, vector<int> &V){

}

void getRet(vector<int> &V){

}

int main(){
	ifstream infile;
	infile.open("text.txt");
	if(!infile.is_open())
		cout << "open file failure" << endl;
	string Line;
	vector<int> Y(210, 0);
	vector<int> Z(210, 0);
	vector<int> ret(210, 0);
	while(getline(infile, Line)){
		if(Line.size() == 0) continue;
		Line.erase(remove(Line.begin(), Line.end(), ' '), Line.end());
		cout << Line << endl;
		if(Line[0] == 'y'){
			fillVector(Line.substr(1), Y);
		}else if(Line[0] == 'z'){
			fillVector(Line, Z);
			getRet(ret);
			cout << "ret" << endl;
		}

	}
	return 0;
}

