#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _card
{
    uint8_t _suit; // 1 spade 2 heart 3 diamond 4 club
    uint8_t _number;
    const char *_name;
    const char *_skill;
} card;
int32_t tempt = 0;

int foo(card *c){
    c->_suit = tempt;
    tempt += 1;
    return 0;
}

int main(){
    // card a = {1, 3, "Wow", "Jennifer Lopez"};
    card *b = calloc(1,sizeof(card));
    printf("%d\n", b->_suit);
    foo(b);
    printf("%d\n", b->_suit);
    foo(b);
    printf("%d\n", b->_suit);
    foo(b);
    printf("%d\n", b->_suit);
    
}