/*
* buyer_functions.h
* Author: Muhammad Salman
*/

#ifndef BUYER_FUNCTIONS_H_
#define BUYER_FUNCTIONS_H_

int display_categories();
struct PRODUCT* display_product();
int add_cart(){printf("hrllo");
}
int receipt_exists(const char *receipt_name);
int checkout(struct PRODUCT **buyer_products);


#endif /* BUYER_FUNCTIONS_H_ */
