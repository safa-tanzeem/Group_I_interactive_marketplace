/*
 * buyer_functions.h
 *
 *  Created on: Dec. 5, 2020
 *      Author: muhammadbsalman
 */

#ifndef BUYER_FUNCTIONS_H_
#define BUYER_FUNCTIONS_H_

int display_categories();
struct PRODUCT* display_product();
int receipt_exists(char *receipt_name);
void checkout(struct PRODUCT **buyer_products, float balance);
void add_cart();

#endif /* BUYER_FUNCTIONS_H_ */
