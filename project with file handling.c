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
	float total;
};

void displayMenu();
struct Order takeOrder();
struct Extra takeExtra();
char validateYesNo();
float getsprice(char name[], char type);
void toLowerAndRemoveSpaces(char*input);
char* validateMee(char *mi);
char validateType(char type);
char validateExtra(char extra);
void displayCurrentTransactions(struct Receipt,int);

int main(){
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
		receipt.total = 0.0;
		
		retake : 
		printf("\nEnter number of mee you want to order (Max is 4) : ");
		scanf("%d", &counter);
		
		if(counter > 0 && counter < 5){
			int i;
			char choice;
			for( i = 0; i < counter; i++){
				printf("Order >>#%d :\n", i + 1);
				struct Order order;
				getchar();
				order = takeOrder();
				
				receipt.orders[i] = order;
				receipt.total += order.price;
				
				printf("Would you like to view all transaction details? (Y/N): ");
				choice = validateYesNo();
				if(choice == 'y'){
					displayCurrentTransactions(receipt,i+1);
				}
				
				if((cfPtr = fopen("receipt.txt", "ab")) == NULL){
				printf("File could not be opened");
			
				} else {
					fwrite(&order, sizeof(struct Order),1,cfPtr);
					fclose(cfPtr);
					printf("Saving your purchase...\n");
					printf("Your total price for this receipt is RM%.2f\n",receipt.total);
					
			}
		}
		if((cfPtr = fopen("transactions.txt", "ab")) == NULL){
				printf("File could not be opened");
			
				} else {
					fwrite(&receipt, sizeof(struct Receipt),1,cfPtr);
					fclose(cfPtr);
					printf("Saving your purchase...\n");
					
			}
		
			}
		}else if(choice == 2){
			if((cfPtr = fopen("transactions.txt","rb")) == NULL){
				printf("File could not be opened");
			}else{
				struct Receipt receipt;
				while(fread(&receipt, sizeof(struct Receipt),1,cfPtr)){
					printf("Receipt Number 1:\n");
					for(int i = 0; i<4; i++){
						if (strlen(receipt.orders[i].mi_name) > 0) {
						printf("  Order #%d:\n", i + 1);
                		printf("    Mee Name: %s\n", receipt.orders[i].mi_name);
                		printf("    Type: %c\n", receipt.orders[i].type);
                		printf("    Price: RM%.2f\n", receipt.orders[i].price);
                		printf("    Extras: Mee=%d, Chicken=%d, Meat=%d, Tendon=%d\n",
                       receipt.orders[i].extra.mee,
                       receipt.orders[i].extra.chicken,
                       receipt.orders[i].extra.meat,
                       receipt.orders[i].extra.tendon);
                   		}
					}
				}
				fclose(cfPtr);
			}
		}else if(choice == 3){
			printf("Saving and Exit...");
			return 1;
		} 
		else {
			printf("Invalid number of mee entered, maximum is 4\n");
			goto retake;
		}
		
}
void displayMenu(){
	printf("Mi Kolok Menu\n");
	printf("Package \t Regular (R) \t Special (S) Extra (RM)\n");
	
}

struct Order takeOrder(){
	struct Order order;
	struct Extra extra;
	char mi[15], type, extraResponse;
	float baseprice = 0.0;
	float finalprice;
	printf("Which mee do you want: Mi kolok ");
	gets(mi);
	toLowerAndRemoveSpaces(mi);
	validateMee(mi);
	if (strcmp(mi, "kosong") != 0){
		printf("What type of mee do you want : ");
		scanf(" %c", &type);
		validateType(type);
	}else{
		type = 'R';
	}
	
	printf("Do you want extra? ");
	scanf(" %c", &extraResponse);
	validateExtra(extraResponse);
	if(extraResponse == 'y' || extraResponse == 'Y'){
		extra = takeExtra();
	}
	
	baseprice = getsprice(mi, type);
	finalprice = baseprice + extra.price;
	strcpy(order.mi_name,mi);
	order.type = type;
	order.price = finalprice;
	order.extra = extra;
	
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
	int valid_extra = 0;
	
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

void displayCurrentTransactions(struct Receipt receipt,int orderCount){
	printf("Current Transaction Details:\n");
	int i;
	for(i=0; i< orderCount; i++){
		struct Order order = receipt.orders[i];
		printf("Order #%d\n",i+1);
		printf("  Mee Name: %s\n", order.mi_name);
        printf("  Type: %c\n", toupper(order.type));
        printf("  Base Price: RM%.2f\n", getsprice(order.mi_name, order.type));
        printf("  Extras:\n");
        printf("    Extra Mee: %s\n", order.extra.mee ? "Yes" : "No");
        printf("    Extra Chicken: %s\n", order.extra.chicken ? "Yes" : "No");
        printf("    Extra Meat: %s\n", order.extra.meat ? "Yes" : "No");
        printf("    Extra Tendon: %s\n", order.extra.tendon ? "Yes" : "No");
        printf("  Order Total: RM%.2f\n", order.price);
	}
}
