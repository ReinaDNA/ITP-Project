#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Extra{
	int mee;
	int chicken;
	int meat;
	int tendon;
	float price;
};

struct Order{
	char mi_name[15];
	char type;
	float price;
	struct Extra extra;
};

struct Receipt{
	int receipt_no;
	struct Order orders[4];
};

void displayMenu();
struct Order takeOrder();
struct Extra takeExtra();
char validateYesNo();

void main(){
	int choice;
	displayMenu();
	printf("1. Take Order\n2. Display Transaction\n3. Save and Exit\n");
	scanf("%d",&choice);
	
	FILE *cfPtr;

	
	if(choice == 1){
		int counter;
		struct Receipt receipt;
		printf("How many orders do you want to take? (Max is 4)");
		scanf("%d",&counter);
		if(counter > 0 && counter < 5){
			int i;
			for(i=0;i<counter;i++){
				struct Order order;
				order = takeOrder();
				
				strcpy(receipt.orders[i].mi_name, order.mi_name);
				receipt.orders[i].type = order.type;
				receipt.orders[i].price = order.price;
				receipt.orders[i].extra = order.extra;
				
			}	
		}	
		if((cfPtr = fopen("receipts.txt","w")) == NULL){
			printf("File could not be opened");
		}else{
			printf("Saving your purchase...");
		
				int i;
				for(i=0;i<counter;i++){
					fprintf(cfPtr, "%s \t %c \t %f",receipt.orders[i].mi_name,receipt.orders[i].type,receipt.orders[i].price);
				}
				
			}
		}		
	}

void displayMenu(){
	printf("Mi Kolok Menu\n");
	printf("Package \t Regular (R) \t Special (S) Extra (RM)\n");
	
}

struct Order takeOrder(){
	struct Order order;
	struct Extra extra;
	char extraResponse;
	
	getchar(); // Remove whitespace to prevent wrong input of gets()
	printf("Which mee do you want: \n");
	gets(order.mi_name);
	printf("which type\n");
	scanf(" %c",&order.type);
	printf("Do you want extras?\n");
	extraResponse = validateYesNo();
	if(extra == 'y'){
		extra = takeExtra();
	}
	
	order.price = 10.00;      
	
	
	
	return order;

}


	

char validateYesNo(){
	int i = 0;
	char choice;
	while(i == 0){
	scanf(" %c",&choice);
	choice = tolower(choice);

	
		if(choice == 'y' || choice == 'n'){
			i++;
			
		}else{
			printf("Invalid option, please try again\n");
		}
		
	}
	return choice; //Returned a lowercase alphabet
}

struct Extra takeExtra(){
	struct Extra extra;
	char mee,chicken,meat,tendon;
	float tempPrice = 0.0;
	
	printf("Do you want extra mee?\n");
	mee = validateYesNo();
	if(mee == 'y'){
		extra.mee = 1;
		tempPrice = tempPrice + 1.50;
	}else{
		extra.mee = 0;
	}
	
	printf("Do you want extra chicken?\n");
	chicken = validateYesNo();
	if(chicken == 'y'){
		extra.chicken = 1;
		tempPrice = tempPrice + 2.00;
	}else{
		extra.chicken = 0;
	}
	
	printf("Do you want extra meat?\n");
	meat = validateYesNo();
	if(meat == 'y'){
		extra.meat = 1;
		tempPrice = tempPrice + 2.50;
	}else{
		extra.meat = 0;
	}
	
	printf("Do you want extra tendon?\n");
	tendon = validateYesNo();
	if(tendon == 'y'){
		extra.tendon = 1;
		tempPrice = tempPrice + 3.00;
	}else{
		extra.tendon = 0;
	}
	
	extra.price = tempPrice;
	
	return extra;
}