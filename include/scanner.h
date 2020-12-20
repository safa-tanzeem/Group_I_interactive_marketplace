/*
 * scanner.h
 *
 *  Created on: Dec. 4, 2020
 *      Author: muhammadbsalman
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "../include/seller.h"

char **get_categories();
void sort_products_descend(struct PRODUCT *list_products);
void sort_products_ascend(struct PRODUCT *list_products);
struct PRODUCT* get_products();


#endif /* SCANNER_H_ */
