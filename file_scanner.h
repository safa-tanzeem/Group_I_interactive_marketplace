#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

const char **get_categories(){
    int i;
	char **categories = malloc(10 * sizeof(char*));
    for(i =0 ; i < 10; i++){
        categories[i] = malloc(20 * sizeof(char));
	} 
	
    categories[0] = "Beauty and Apparel";
    categories[1] = "Electronics";
    categories[2] = "Automotive";
    categories[3] = "3";
    categories[4] = "4";
    categories[5] = "5";
    categories[6] = "6";
    categories[7] = "7";
    categories[8] = "8";
    categories[9] = "9";
	
	
	return categories;
}

struct PRODUCT *get_products(){
	

	FILE *input; 
    input = fopen("product.txt", "r");

	char line[1024];
	char* data;
	



    struct PRODUCT *head; //declare new node
	head = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
	
	
	struct PRODUCT *new_product_head; //declare new node
	new_product_head = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
	
	head = new_product_head;
	
	if (input == NULL){
		printf("Error occured, could not find file!");
		head = NULL;
		return head;
 	}
	
    while(fgets(line, 1024, input)){
    	
    	struct PRODUCT *new_product; //declare new node
	    new_product = (struct PRODUCT*)malloc(sizeof(struct PRODUCT));
    	
		char* temp_line = strdup(line);
    	
    	data = strtok(line, ",");
    	strcpy(new_product->name, data);
    	
    	data = strtok(NULL, ",");
        strcpy(new_product->category, data);
        
        data = strtok(NULL, ",");
        new_product->category_num = atoi(data);
        
        data = strtok(NULL, ",");
        new_product->product_number = atoi(data);
        
        data = strtok(NULL, ",");
        new_product->stock = atoi(data);
        
        data = strtok(NULL, ",");
        new_product->price = atof(data);
        
        data = strtok(NULL, ",");
        new_product->discount_code = atoi(data);
        
        data = strtok(NULL, ",");
        new_product->discount_percentage = atof(data);
        
        new_product_head->next_product = new_product;
        new_product_head = new_product;
    	
	}
    new_product_head->next_product=NULL;
    head = head->next_product;

    fclose(input);



return head;

}

