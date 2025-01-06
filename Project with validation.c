#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Order{
	char mi_name[15];
	char type;
	float price;
	char extra;
};

struct Receipt{
	int receipt_no;
	struct Order orders[4];
};
	
void displayMenu();
struct Order takeOrder();
float getsprice(char name[], char type);
void toLowerAndRemoveSpaces(char*input);
char* validateMee(char *mi);
char validateType(char type);
char validateExtra(char extra);

void main(){
	int choice;
	
	displayMenu();
	
	printf("1. Take order\n"
		   "2. Display Transaction\n"
		   "3. Save and Exit\n");
	scanf("%d", &choice);
	
	FILE *cfPtr;
	
	if(choice == 1){
		int counter;
		struct Receipt receipt;
		
		retake : 
		printf("\nEnter number of mee you want to order (Max is 4) : ");
		scanf("%d", &counter);
		
		if(counter > 0 && counter < 5){
			int i;
			for( i = 0; i < counter; i++){
				printf("Order >>#%d :\n", i + 1);
				struct Order order;
				getchar();
				order = takeOrder();
				
				strcpy(receipt.orders[i].mi_name, order.mi_name);
				receipt.orders[i].type = order.type;
				receipt.orders[i].price = order.price;
				receipt.orders[i].extra = order.extra;
			}
		} else {
			printf("Invalid number of mee entered, maximum is 4\n");
			goto retake;
		}
		if((cfPtr = fopen("receipt.txt", "w")) == NULL){
			printf("File could not be opened");
			
		} else {
			printf("Saving your purchase...");
			
			int i;
			
			for ( i = 0; i < counter; i++){
				fprintf(cfPtr, "%s\t%c\t%f", receipt.orders[i].mi_name, receipt.orders[i].type, receipt.orders[i].price );
			}
		}
	}
}


void displayMenu(){
	printf("Mi Kolok Menu\n");
	printf("Package\tRegular(R)\tSpecial(S)\tExtra(RM)\n");
}

struct Order takeOrder(){
	struct Order order;
	char mi[15], type, extra;
	float baseprice = 0.0;
	
	printf("Which mee do you want: Mi kolok ");
	gets(mi);
	toLowerAndRemoveSpaces(mi);
	validateMee(mi);
	if (strcmp(mi, "kosong") != 0){
		printf("What type of mee do you want : ");
		scanf(" %c", &type);
		validateType(type);
	}
	
	printf("Do you want extra? ");
	scanf(" %c", &extra);
	validateExtra(extra);
	
	baseprice = getsprice(mi, type);
	
	return order;
}

float getsprice(char name[], char type){
	float baseprice = 0.0;
	
	if (strcmp(name, "kosong") == 0){
			baseprice = 4.50;
	} else{
	switch (type){
		case 'R' :
		case 'r' :
			if (strcmp(name, "ayam") == 0){
				baseprice = 7.00;
			} else if (strcmp(name, "daging") == 0){
				baseprice = 8.00;
			} else if (strcmp(name, "tendon") == 0){
				baseprice = 13.00;
			}
			break;
			
		case 'S' :
		case 's' :
			if (strcmp(name, "ayam") == 0){
				baseprice = 9.00;
			} else if (strcmp(name, "daging") == 0){
				baseprice = 10.00;
			} else if (strcmp(name, "tendon") == 0){
				baseprice = 16.00;
			}
			break;
	}
	}

	return baseprice;
}

char* validateMee(char *mi){
	int valid_mee = 0;

	while ( valid_mee == 0){
		if(strcmp(mi, "kosong") == 0 || strcmp(mi, "ayam") == 0 || strcmp(mi, "daging") == 0 || strcmp(mi, "tendon") == 0){
			valid_mee++;                       
		} else {
			printf("This kind of mee doesn't exist, please retake order\n");
			printf("Which mee do you want: Mi kolok ");
			gets(mi);
			toLowerAndRemoveSpaces(mi);
		} 
	}
	return mi;
}

char validateType(char type){
	int valid_type = 0;
	
	while (valid_type == 0){
		if (type == 'R' || type == 'S' || type == 'r' || type == 's'){
			valid_type++;
		} else {
			printf("This type doesn't exist, please reenter type\n");
			printf("What type of mee do you want : ");
			scanf(" %c", &type);
		}
	}
	return type;
}

char validateExtra(char extra){
	int valid_extra = 0, i;
	
	while (valid_extra == 0){
		if (extra == 'Y' || extra == 'N' || extra == 'y' || extra == 'n'){
			valid_extra++;
		} else {
			printf("This option doesn't exist, only either Y or N\n");
			printf("Do you want extra? ");
			scanf(" %c", &extra);
		}
	}
	return extra;
}
	
void toLowerAndRemoveSpaces(char* input){
	int i, j;
	char output[15];
	
	for (i = 0; i< sizeof(input); i++){
		if(!isspace(input[i])){
			output[j++] = tolower(input[i]);
		}
	}
	output[j] = '\0';
	strcpy(input, output);
}

 