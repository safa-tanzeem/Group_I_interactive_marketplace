#include <stdio.h>
#include <stdlib.h>
#include "buyer_functions.h"
#include "product.h"


void buyerMenu(){
/* The functions brings the user to the buyer's perpective.
*Allows the user to pick products to buy, then check them out
*Other functuons include adding funds to their wallets, and pay for products
*/ 
    
    printf("\n---BUYER MENU---\n");
    add_cart();
    
	return;
}

void sellerMenu(){
	printf("seller\n");
}




int main(){

/*Variable that stores user's initial buyer/seller preferance
*Setting to 3, because that is the default quit option*/
int choice = 3; 

do{

	//Introductory Remarks
	printf("-----WELCOME TO THE INTERACTIVE MARKETPLACE!-----\n");
	printf("You have the choice to act as a (1) buyer, (2) seller, or (3) quit marketplace.\n");
	
	//Loop until acceptable value entered 
	do{
		printf("Enter your choice as a numerical integer value: ");
		scanf("%i", &choice);
	}while(choice != 1 && choice != 2 && choice != 3);

	switch(choice){
		case 1:
			buyerMenu();
			break;
		
		case 2:
			sellerMenu();
			break;
	}
	

}while(choice != 3); //Continue marketplace until user chooses to quit


printf("\nHope you enjoyed your experience!\nSee you soon!\n");
printf("-----YOU HAVE LEFT THE INTERACTIVE MARKETPLACE-----");













return 0;
}

