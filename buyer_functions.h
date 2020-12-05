/*
 * buyer_functions.c
 *
 *  Created on: November, 20th , 2020
 *      Author: muhammadbsalman
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_scanner.h"
#include "product.h"
#include "buyer_wallet.h"

/**
 * \brief This function diplays the categories of different products
 * @return choice The choice of category represented as an integer
 */

int display_categories(){
	
	int choice = 100; 
	int i = 0;
	char** categories = get_categories();
	
	printf("\nPlease select the category you would like to shop in: \n");
    while(!(choice>=1 && choice<=10)){
	
	    for(i; i<10; i++){
    	    printf("%i. %s\n", i+1, categories[i]); 
	    }
    
        scanf("%i", &choice);  
		i= 0;
		
		printf("\n");  

    }
	
	choice-=1;
	
	printf("Products in %s: \n",categories[choice]);
	free(categories); 
	return choice;
}


/**
 * \brief This function diplays the products avaiable in the marketplace
 * @return new_product_head A list of products in the marketplace
 */

struct PRODUCT* display_product(){
	
	int choice;
	
    
    struct PRODUCT *new_product_head; //declare new node
	new_product_head = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    new_product_head=get_products();
    
    struct PRODUCT *temp; //declare new node
	temp = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
	
	temp = new_product_head;
	
	choice = display_categories();
	
	printf("Name - Product Number - Price - Stock #\n----------------------------\n");
	
	while(temp!= NULL){
        
        if(temp->category_num==choice){
            
			printf("%s - ", temp->name);	
            printf("%i - ",temp->product_number);
            printf("$%.2f - ",temp->price);
			printf("$%.2f\n",temp->stock);
		}
		
		temp=temp->next_product;
		
	}

    return new_product_head;
    
}

/**
 * \brief This function checks if the receipt name already exists
 * @param[in] receipt_name The filename of the receipt to check if existing
 * @return 0 file with specified name does not exist
 * @return 1 file with specified name exists
 */

int receipt_exists(const char *receipt_name){
	
	
	strcat(receipt_name, ".txt");
	FILE *receipt = fopen(receipt_name, "r");

	if (receipt == NULL){
		return 0;
	}
	fclose(receipt);

	return 1;
}

/**
 * \brief This function prints a buyer receipt and "checks out" the buyer, calling to update stock
 * @param[in] buyer_products List of products selected to be bought by the buyer
 * @param[in] balance Amount of funds in buyer's wallet
 */


void checkout(struct PRODUCT **buyer_products, float balance){

	struct PRODUCT *tracker; 
	tracker = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
	tracker = (*buyer_products);
    
    float total_price=0;
	int counter = 1;
	char counter_str [10];
    char receipt_name [20];
    char receipt_def [20];
    
    strcpy(receipt_name,"receipt");
    
    
	while (1){
		
		if(receipt_exists(receipt_name)==0)
		{
			break;
		}
		
		strcpy(receipt_def,"receipt");
		
		itoa(counter, counter_str, 10);

		strcat(receipt_def, counter_str);
	
		strcpy(receipt_name, receipt_def);

		counter++;

 	}
 	
 	FILE *output; 
    output = fopen(receipt_name, "w+");
    fprintf(output, "Thank you for your purchase today!\n--------------------------------------------------------------------\n");
    
	while(tracker!=NULL){
		
		if(tracker->flag_code!='Y'){
			tracker->flag_code = 'N';
		}
		
		fprintf(output, "Product_Name, Product_Number, Product_Quantity, Price_Per_Unit, Discount_Percentage\n");
    	fprintf(output, "%s     -      %i      -       %i      -      %.2f      -       %c",tracker->name, tracker->product_number, tracker->number_selected, tracker->price, tracker->flag_code);
    	
    	total_price += ((tracker->number_selected)*(tracker->price));
    	tracker=tracker->next_product;
	}
	
	balance = update_balance(balance, total_price);
	
	if(balance==-2.0){
		fprintf(output, "NOT ENOUGH FUNDS TO COMPLETE PURCHASE!");	
	}
	
	else{
		fprintf(output, "\n\nTOTAL COST OF PRODUCTS: $%.2f", total_price);
		fprintf(output, "\nRemaining funds: $%.2f", balance);		
	}
	
		
    fclose(output);
    printf("\nThank you for shopping with us! Your receipt has been outputted.\n\n");
    
    tracker = (*buyer_products);
    while(tracker!=NULL){
        update_stock(tracker->product_number, tracker->number_selected, 0);
    	tracker=tracker->next_product;
	}
    
    
	return;
	
}

/**
 * \brief This function adds products to cart, as well as applying discount codes
 */

void add_cart(){
	
	int product_sel;
	float balance;
	
	balance = add_balance();
	    
    struct PRODUCT *new_product_head; //declare new node
	new_product_head = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    new_product_head=display_product();
    
    struct PRODUCT *tracker; 
	tracker = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
	
	tracker = new_product_head;
	 
	struct PRODUCT *user_list; 
	user_list = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    
    struct PRODUCT *list_products; 
	list_products = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));

    user_list = list_products;
    
    while(1){
	
    	printf("\nSelect products to add to cart. Enter product numbers.\nEnter 0 to end entries, 1 to see categories: \n");
    	scanf("%i",&product_sel);
	    
	    if(product_sel==0){
	    	break;
		}
	    
	    if(product_sel==1){
	    	display_product();
		}

		tracker = new_product_head;
		 
		while(tracker!=NULL){

			int selected = 0;
			if(tracker->product_number==product_sel){
		        
				struct PRODUCT *product; 
		        product = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
	    
	            product=tracker;
	        
	            printf("You added %s to your cart.\n", tracker->name);
	            
				do{
				
					printf("How many would you like? You will be re-prompted if we do not enough stock: ");
	            	scanf("%i",&selected);
	            
				}while(selected>tracker->stock || selected ==0);
	            
	            product->number_selected = selected;
			    
	            list_products->next_product = product;
	            list_products = list_products->next_product;
	            
	            break;
		        
			}
			
	        tracker=tracker->next_product;
	    }
	}
    
    list_products->next_product = NULL;
    user_list = user_list->next_product;
    
    tracker = user_list;
    
    int dis_code=100;
    
    while(1){
	
    	printf("\nPlease enter any discount codes you would like to enter: Enter 0 to exit: ");
    	scanf("%i", &dis_code);
		
		if(dis_code==0){
			break;
		}
		
		while(tracker!=NULL){

			if(tracker->discount_code==dis_code){
		        
		        if(tracker->flag_code != 'Y'){
				
		        	tracker->price = (1-(tracker->discount_percentage))*(tracker->price);
	            	printf("\nYou applied a discount code to %s.\n", tracker->name);
             		printf("You're new price per product is %.2f.\n", tracker->price);
                	tracker->flag_code = 'Y';
	            	break;
		    	}
		    	else{
		    		printf("\nYou have already applied a discount to this product!\n");
				}
			}
			
			tracker=tracker->next_product;
		}
	}
	
	user_list=tracker;
	
	checkout(&user_list, balance);
	return;
	
}
