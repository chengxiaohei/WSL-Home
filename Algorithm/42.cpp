#include <iostream>
#include <cstring>

void reverse(char *start, char *end){
    if(start == nullptr || end == nullptr)
        return;
    while(start < end){
        char temp = *start;
        *start = *end;
        *end = temp;
        start++; end--;
    }
}

char *reverseSentence(char *str, int length){
    if(str == nullptr || length < 1)
        return str;
    reverse(str, str + length - 2);
    char *p1 = str, *p2;
    for(int i=0; i<length-1; i++){
        if(str[i] == ' '){
            p2 = str + i - 1;
            reverse(p1, p2);
            p1 = p2 + 2;
        }
    }
    return str;
}

char *leftReverse(char *str, int length, int loc){
    if(str == nullptr || length < 2 || length < loc || loc < 1)
        return str;
    
    reverse(str, str + loc - 1);
    reverse(str + loc, str + length -2);
    reverse(str, str + length - 2);
    return str;
}

int main(int argc, char const *argv[]){
    char str[] = "I am a student.";
    int length = sizeof(str)/sizeof(char);

    // char *result = reverseSentence(str, length);
    // printf("%s\n", result);
    char *result = leftReverse(str, length, 4);
    printf("%s\n", result);
    return 0;
}