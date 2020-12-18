/*
 * scanner.h
 *
 *  Created on: Dec. 4, 2020
 *      Author: muhammadbsalman
 */

#ifndef SCANNER_H_
#define SCANNER_H_

struct PRODUCT* get_products();
//void print_list(product_t *n);
void sort_products_descend(struct PRODUCT *list_products);
void sort_products_ascend(struct PRODUCT *list_products);
char **get_categories();


#endif /* SCANNER_H_ */
