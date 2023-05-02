#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
int main()
{
    printf("asd");
    char code[8] = { 0x08 ,  0x1b , 0x5b ,0x4b , 0x08 ,  0x1b , 0x5b ,0x4b } ; 
    int i = 1 ; 
    while (i)
    {   
        //putc(code[i], stdout);
		std::cout << "\nasdhjkg";
		_sleep(1000);
		//printf("\n");
        i++;
    }   

    printf("\n");
    return 0;
}