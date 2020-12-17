/*
 * product.h
 *
 *  Created on: Dec. 5, 2020
 *      Author: kavehr
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_

typedef struct PRODUCT
{
    char name[20];
    char category[20];
    int category_num;
    int product_number;
    int stock;
    float price ;
    int discount_code ;
    float discount_percentage ;
    int seller_id;
    int number_selected;
    char flag_code;
    struct PRODUCT* next_product;
}PRODUCT;

#endif /* PRODUCT_H_ */
