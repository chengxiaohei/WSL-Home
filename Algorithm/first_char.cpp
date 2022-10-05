#include <iostream>

char firstSingleChar(char *str, size_t length){
    int table[26] = {0};
    for(int i=0; i<length; i++){
        table[str[i]-'a']++;
    }
    for(int i=0; i<length; i++){
        if(table[i]==1) return 'a'+i;
    }
    return '0';
}

int main(int argc, char const * argv[]){
    char str[] = "hlloojdaghd";
    for(int i=0; i<sizeof(str)/sizeof(char)-1; i++){
        printf("%c,", str[i]);
    }
    
    char result = firstSingleChar(str, sizeof(str)/sizeof(char)-1);
    std::cout << result << std::endl;
    return 0;
}
