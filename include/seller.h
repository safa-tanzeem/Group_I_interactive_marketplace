/*
 * seller.h
 *
 *  Created on: Nov. 29, 2020
 *      Author: safatanzeem
 */

#ifndef SELLER_H_
#define SELLER_H_

#include "common.h"

typedef struct PRODUCT{
  char name[NAME_MAX_LENGTH];
  char category[NAME_MAX_LENGTH];
  int category_num;
  int product_number;
  int stock;
  float price;
  int discount_code;
  float discount_percentage;
  int seller_id;
  int number_selected;
  char flag_code;
  struct PRODUCT* next_product;
} product_t;

typedef struct SELLER_PROD_NUM{
    int value;
    struct SELLER_PROD_NUM *next;
} seller_prod_num_t;


typedef struct SELLER{
    char name[20];
    char pass[20];
    int seller_id;
    float total_revenue;
    struct SELLER_PROD_NUM *products_number;
    struct SOLD_PRODUCT *products_sold;
} seller_t;

typedef struct SOLD_PRODUCT{
    char buyer_name[20];
    char buyer_shipping_address[40];
    char phone_number[10];
    int seller_id;
    int product_number;
    int quantity;
    struct SOLD_PRODUCT* next_sold_product;
} sold_product_t;




#endif /* SELLER_H_ */
