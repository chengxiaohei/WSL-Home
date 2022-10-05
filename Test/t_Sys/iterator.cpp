#include <iostream>
#include <vector>

using namespace std;

void vectorTest()
{
    vector<int> container;
    for (int i = 0; i < 10; i++)
    {
        container.push_back(i);
    }

    vector<int>::iterator iter;
     for (iter = container.begin(); iter != container.end(); iter++)
    {
            if (*iter > 3)
              container.erase(iter);
    }

     for (iter = container.begin(); iter != container.end(); iter++)
    {
            cout<<*iter<<endl;
    }
}

int main(){
	vector<int> data({1,2,3,4,5,6,7,8,9});
	vector<int>::iterator it = data.begin();
	for(auto it = data.begin(); it != data.end(); ++it){
		if(*it > 3){
			data.erase(it--);
		}
	}
	for(int &i : data){
		cout << i << " ";
	}cout << endl;
	return 0;
}
	//for(auto it = data.begin(); it != data.end(); ++it){	
