#include <stdio.h>
#include "foo.h"
#include "bar.h"

int main(int argc, char const *argv[]){
    int f = foo(1,2);
    int b = bar(1,2);
    printf("f = %d, b = %d\n", f, b);
    return 0;
}
