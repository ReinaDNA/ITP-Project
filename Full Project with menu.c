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

void displaymenu();
void horizontalline (int x);
struct Order takeOrder();
struct Extra takeExtra();
char validateYesNo();
float getsprice(char name[], char type);
void toLowerAndRemoveSpaces(char*input);
char* validateMee(char *mi);
char validateType(char type);
char validateExtra(char extra);
void displayCurrentTransactions(struct Receipt,int);
int getReceiptNo();

int main(){
	int choice;
	
	displaymenu();
	retake : 
	printf("1. Take order\n"
		   "2. Display Transaction\n"
		   "3. Save and Exit\n");
	scanf("%d", &choice);
	
	FILE *cfPtr;
	
	if(choice == 1){
		int counter;
		struct Receipt receipt;
		receipt.total = 0.0;
		retake1:
		printf("\nEnter number of mee you want to order (Max is 4) : ");
		scanf("%d", &counter);
		
		if(counter > 0 && counter < 5 ){
			int i;
			char choice;
			for( i = 0; i < counter; i++){
				printf("Order >>#%d :\n", i + 1);
				struct Order order;
				getchar();
				order = takeOrder();
				
				receipt.receipt_no = getReceiptNo();
				receipt.orders[i] = order;
				receipt.total += order.price;
				
				printf("Would you like to view all transaction details? (Y/N): ");
				choice = validateYesNo();
				if(choice == 'y'){
					displayCurrentTransactions(receipt,i+1);
				}
				
			}
		if((cfPtr = fopen("transactions.txt", "ab")) == NULL){
				printf("File could not be opened");
			
				} else {
					fwrite(&receipt, sizeof(struct Receipt),1,cfPtr);
					fclose(cfPtr);
					printf("Saving your purchase...\n");
					printf("Your total price for this receipt is RM%.2f\n",receipt.total);
					goto retake;
					
			}
			}else{
				printf("Invalid number, maximum amount is 4 orders.");
				getchar();
				goto retake1;
			}	
		}else if(choice == 2){
			if((cfPtr = fopen("transactions.txt","rb")) == NULL){
				printf("File could not be opened");
			}else{
				struct Receipt receipt;
				float receipts_total = 0;
				while(fread(&receipt, sizeof(struct Receipt),1,cfPtr)){
						printf("\n----------------------------------------------------------\n");
				    	printf("| Receipt Number %d:                                      |\n",receipt.receipt_no);
				    	printf("|--------------------------------------------------------|\n");
					for(int i = 0; i<4; i++){
						if(strcmp(receipt.orders[i].mi_name, "kosong") == 0 || strcmp(receipt.orders[i].mi_name, "ayam") == 0 || strcmp(receipt.orders[i].mi_name, "daging") == 0 || strcmp(receipt.orders[i].mi_name, "tendon") == 0){
							printf("|  Order #%d:  |                                          |\n", i + 1);
							printf("|-------------|                                          |\n");
                			printf("|  Mee Name:  | %-6s                                   |\n", receipt.orders[i].mi_name);
                			printf("|  Type:      | %-c                                        |\n", receipt.orders[i].type);
                			printf("|  Price:     | RM%-5.2f                                  |\n", receipt.orders[i].price);
                			printf("|  Extras:    | Mee=%-d, Chicken=%-d, Meat=%-d, Tendon=%-d       |\n",
                      		receipt.orders[i].extra.mee,
                       		receipt.orders[i].extra.chicken,
                       		receipt.orders[i].extra.meat,
                       		receipt.orders[i].extra.tendon);
                       		printf("|--------------------------------------------------------|\n");
                       		receipts_total += receipt.orders[i].price;
                   		}
					}
				}
				printf("Total sales: RM%.2f\n",receipts_total);
				fclose(cfPtr);
				goto retake;
			}
		}else if(choice == 3){
			printf("Saving and Exit...");
			return 1;
		} 
	else {
			printf("Invalid choice, please try again\n");
			getchar();
			goto retake;
	}
		
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
	float receiptTotal = 0.0;
	for(i=0; i< orderCount; i++){
		struct Order order = receipt.orders[i];
		receiptTotal += order.price;
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
        printf(" Your current receipt total is RM%.2f\n",receiptTotal);
	}
}

int getReceiptNo(){
	struct Receipt receipt;
	int receipt_no = 0;
	FILE *cfPtr;
	if((cfPtr = fopen("transactions.txt","rb")) == NULL){
				return receipt_no = 1;
			}else{
				while(fread(&receipt, sizeof(struct Receipt),1,cfPtr));{
					receipt_no++;
				}
				fclose(cfPtr);
			}
	return receipt_no + 1;
	
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