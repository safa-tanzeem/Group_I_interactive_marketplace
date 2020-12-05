/*
 * product.h
 *
 *  Created on: Nov. 15, 2020
 *      Author: kaveh
 */



#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

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
    int number_selected;
    char flag_code;
    struct PRODUCT* next_product;
}PRODUCT;

#endif // PRODUCT_H_INCLUDED
