#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_scanner.h"
#include "product.h"
#include <unistd.h>
#include <io.h>

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






struct PRODUCT* display_product(){
	
	int choice;
	
    
    struct PRODUCT *new_product_head; //declare new node
	new_product_head = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    new_product_head=get_products();
    
    struct PRODUCT *temp; //declare new node
	temp = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
	
	temp = new_product_head;
	
	choice = display_categories();
	
	printf("Name - Product Number - Price\n----------------------------\n");
	
	while(temp!= NULL){
        
        if(temp->category_num==choice){
            
			printf("%s - ", temp->name);	
            printf("%i - ",temp->product_number);
            printf("$%.2f\n",temp->price);

		}
		
		temp=temp->next_product;
		
	}

    return new_product_head;
    
}

int add_cart(){
	
	int product_sel;
	    
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
		        
		        if(tracker->flag_code != 1){
				
		        	tracker->price = (1-(tracker->discount_percentage))*(tracker->price);
	            	printf("\nYou applied a discount code to %s.\n", tracker->name);
             		printf("You're new price per product is %.2f.\n", tracker->price);
                	tracker->flag_code = 1;
	            	break;
		    	}
		    	else{
		    		printf("You have already applied a discount to this product!\n");
				}
			}
			
			tracker=tracker->next_product;
		}
	}
	
	user_list=tracker;
	
	checkout(user_list);
	return 0;
	
}

int receipt_exists(const char *receipt_name){
	
	
	strcat(receipt_name, ".txt");
	FILE *receipt = fopen(receipt_name, "r");

	if (receipt == NULL){
		return 0;
	}
	fclose(receipt);

	return 1;
}

int checkout(struct PRODUCT buyer_products){
	
	struct PRODUCT *tracker; 
	tracker = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
	tracker = buyer_products;
    
	int counter = 1;
	char counter_str [10];
    char receipt_name [20];
    char receipt_def [20];
    
    strcpy(receipt_name,"receipt");
    
    
	while (1){
		
		if(receipt_exists(receipt_name)==0)
		{
			printf("NULL");
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
    
	while(tracker->next_product!=NULL){
    	fprintf(output, "Thank you for your purchase today!\n--------------------------------------------------------------------\n");
    	
    	
	}
    fclose(output);
    printf("\nThank you for shopping with us! Your receipt has been outputted.\n\n");
    
	return 0;
	
}
