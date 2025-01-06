#include<stdio.h>

void displaymenu();
void horizontalline (int x);

int main()
{
	displaymenu();
	
	return 0;
}

void displaymenu()
{
	int i;
	
	char edge = '+';
	char vline = '|';
	
	printf("%c", edge);
	horizontalline(69); // Call to the function with 69 as the argument
	printf("%c\n", edge);
	
	printf("%c", vline);
	printf("%39s", "Mi Kolok Menu"); // 13 characters
	printf("%31c\n", vline);
	
	printf("%c", edge);
	horizontalline(22);
	printf("%c", edge);
    horizontalline(13);
    printf("%c", edge);
    horizontalline(13);
    printf("%c", edge);
    horizontalline(18);
    printf("%c", edge);
    
	printf("\n%c", vline);
	printf("%14s", "Package"); // 7 characters
	printf("%9c", vline);
	printf("%12s", "Regular (R)"); // 11 characters
	printf("%2c", vline);
	printf("%12s", "Special (S)"); // 11 characters
	printf("%2c", vline);
	printf("%14s", "Extra (RM)"); // 10 characters
	printf("%5c\n", vline);
	
	printf("%c", vline);
	printf("%23c", vline);
	printf("%9s", "(RM)"); // 4 characters
	printf("%5c", vline);
	printf("%9s", "(RM)"); // 4 characters
	printf("%5c", vline);
    printf("%19c\n", vline);

	
	printf("%c", vline);
	horizontalline(22);
	printf("%c", edge);
    horizontalline(13);
    printf("%c", edge);
    horizontalline(13);
    printf("%c", edge);
	horizontalline(18);
    printf("%c", edge);

    
	printf("\n%c", vline);
	printf("%20s", "a) Mi Kolok Kosong"); //18 words
	printf("%3c", vline);
	printf("%9s", "4.50"); // 4 characters
	printf("%5c", vline);
	printf("%9s", "-----"); // 5 characters
	printf("%5c", vline);
	printf("%13s", "Mee/1.50"); // 8 characters
	printf("%6c\n", vline);
	
	printf("%c", edge);
	horizontalline(22);
	printf("%c", edge);
    horizontalline(13);
    printf("%c", edge);
    horizontalline(13);
    printf("%c", vline);
    printf("%19c\n", vline);
	
	printf("%c", vline);
	printf("%18s", "b) Mi Kolok Ayam"); // 16 characters
	printf("%5c", vline);
	printf("%9s", "7.00"); // 4 characters
	printf("%5c", vline);
	printf("%9s", "9.00"); // 4 characters
	printf("%5c", vline);
	printf("%15s", "Chicken/1.50"); // 12 characters
	printf("%4c\n", vline);
	
	printf("%c", edge);
	horizontalline(22);
	printf("%c", edge);
    horizontalline(13);
    printf("%c", edge);
    horizontalline(13);
    printf("%c", vline);
    printf("%19c\n", vline);
	
	printf("%c", vline);
	printf("%20s", "c) Mi Kolok Daging"); // 18 characters
	printf("%3c", vline);
	printf("%9s", "8.00"); // 4 characters
	printf("%5c", vline);
	printf("%9s", "10.00"); // 5 characters
	printf("%5c", vline);
	printf("%14s", "Meat/1.50"); // 9 characters
	printf("%5c\n", vline);
	
	printf("%c", edge);
	horizontalline(22);
	printf("%c", edge);
    horizontalline(13);
    printf("%c", edge);
    horizontalline(13);
    printf("%c", vline);
    printf("%19c\n", vline);
	
	printf("%c", vline);
	printf("%20s", "d) Mi Kolok Tendon"); // 18 characters
	printf("%3c", vline);
    printf("%9s", "13.00"); // 5 characters
	printf("%5c", vline);
    printf("%9s", "16.00"); // 5 characters
	printf("%5c", vline);
	printf("%17s", "Tendon/3.00 each"); // 16 characters
	printf("%2c\n", vline);
	
	printf("%c", edge);
	horizontalline(22);
	printf("%c", edge);
    horizontalline(13);
    printf("%c", edge);
    horizontalline(13);
    printf("%c", edge);
    horizontalline(18);
    printf("%c\n", edge);

}

void horizontalline(int x)
{
	int i;
	char hline = '-';
	
	for(i = 1; i <= x; i++)
	{
		printf("%c", hline);
    }
	
}