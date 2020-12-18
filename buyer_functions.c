/*
 * buyer_functions.c
 *
 *  Created on: Dec. 5, 2020
 *      Author: muhammadbsalman
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/scanner.h"
#include "../include/seller.h"
#include "../include/buyer_functions.h"
#include "../include/buyer_wallet.h"
#include "../include/common.h"
//#include "../include/stock_update.h"
//#include "../include/update_buyer_info.h"
//#include "../include/seller_manager.h"


/**
 * \brief This function diplays the categories of different products
 * @return choice The choice of category represented as an integer
 */

int display_categories(){

    int choice = 100;
    int i = 0;
    int valid =0;
    int output;
    char** categories = get_categories();

    printf("\nPlease select the category you would like to shop in: \n");
    while(!(choice>=1 && choice<=7&&valid==1)){
        
		valid = 0; //reset if entry is valid or not
        
		for(i; i<7; i++){
            printf("%i. %s\n", i+1, categories[i]);
        }

        output=scanf("%i", &choice);
        if(validate(output)==OK){
        	valid=1;
		}
        
        i= 0; //reset counter

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
    int sort_choice;
    int output;


    struct PRODUCT *new_product_head; //declare new node
    new_product_head = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    new_product_head=get_products();

    struct PRODUCT *temp; //declare new node
    temp = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));

    temp = new_product_head;

    choice = display_categories();

    printf("Name - Product Number - Price - Stock #\n----------------------------\n");

    while(temp!= NULL){

        if(temp->category_num == choice){

            printf("%s - ", temp->name);
            printf("%i - ",temp->product_number);
            printf("$%.2f - ",temp->price);
            printf("%i\n",temp->stock);
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

int receipt_exists(char *receipt_name){

    if (receipt_name == NULL){
    	return -1;
	}

    strcat(receipt_name, ".txt");
    FILE *receipt = fopen(receipt_name, "r");

    if (receipt == NULL){
        return 0;
    }
    fclose(receipt);

    return 1;
}

/**
 * \brief This function prints a buyer receipt and "checks out" the buyer, calling to update stock, as well as taking buyer details
 * @param[in] buyer_products List of products selected to be bought by the buyer
 * @param[in] balance Amount of funds in buyer's wallet
 */


void checkout(struct PRODUCT **buyer_products, float balance){

    struct PRODUCT *tracker;
    tracker = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    tracker = (*buyer_products);

    float total_price=0;
    int counter = 1;
    char temp;
    char counter_str[10];
    char receipt_name[20];
    char receipt_def[20];
    char buyer_name[20];
    char buyer_addr [40];
    char buyer_phone[10];

    //take buyer information
    printf("\nBuyer Name: ");
    scanf("%c", &temp);
    scanf("%[^\n]", buyer_name);

    printf("\nBuyer Address: ");
    scanf("%c", &temp);
    scanf("%[^\n]", buyer_addr);

    printf("\nBuyer Phone: ");
    scanf("%s", buyer_phone);

    //generate receipt
    strcpy(receipt_name,"receipt");

    while (1){

        if(receipt_exists(receipt_name)==0)
        {
            break;
        }

        strcpy(receipt_def, "receipt");

        sprintf(counter_str, "%d", counter);

        strcat(receipt_def, counter_str);

        strcpy(receipt_name, receipt_def);

        counter++;

    }

    FILE *output;
    output = fopen(receipt_name, "w+");
    fprintf(output, "Thank you for your purchase today!\n--------------------------------------------------------------------\n");
    fprintf(output, "\nProduct_Name, Product_Number, Product_Quantity, Price_Per_Unit, Discount_Percentage\n");
    while(tracker!=NULL){

        if(tracker->flag_code!='Y'){
            tracker->flag_code = 'N';
        }

        
        fprintf(output, "%s     -      %i      -       %i      -      %.2f      -       %c\n",tracker->name, tracker->product_number, tracker->number_selected, tracker->price, tracker->flag_code);


        total_price += ((tracker->number_selected)*(tracker->price));
        tracker=tracker->next_product;
    }

    balance = update_balance(balance, total_price);
    
    if(balance==-2.0){
        fprintf(output, "NOT ENOUGH FUNDS TO COMPLETE PURCHASE!");
        printf("NOT ENOUGH FUNDS TO COMPLETE PURCHASE!");
        fclose(output);
        return;
    }

    else{
        fprintf(output, "\n\nTOTAL COST OF PRODUCTS: $%.2f", total_price);
        fprintf(output, "\nRemaining funds: $%.2f", balance);
    }


    fclose(output);
    printf("\nThank you for shopping with us! Your receipt has been outputted.\n\n");

    //@SAFATANZEEM, please look here for commented code
    //traverse list to update product inventory descriptions
    tracker = (*buyer_products);

    while(tracker!=NULL){

        float price = 0.0;
        price = (tracker->number_selected)*(tracker->price);

        //printf("%d", tracker->seller_id);
        //printf("\n%s", tracker->name);

        //update_revenue(tracker->seller_id, price);

        //update_stock(tracker->product_number, tracker->number_selected, 0);

        //buyer_info(buyer_name, buyer_addr, buyer_phone, tracker->product_number, tracker->number_selected, tracker->seller_id);

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
    int output;

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
        
		do{
			output=scanf("%i",&product_sel);
    	}while(validate(output)!=OK);

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

		do{
			output=scanf("%i", &dis_code);
    	}while(validate(output)!=OK);

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


