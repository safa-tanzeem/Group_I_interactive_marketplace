#ifndef PRODUCT_FILE_MANAGER_H_INCLUDED
#define PRODUCT_FILE_MANAGER_H_INCLUDED
#include "product.h"

#define PRODUCT_FILE_PATH                                           "C:\\Users\\kaveh\\Desktop\\ftest\\products.txt"

#define PRODUCT_INFO_FORMAT                                         "Name: %s ,Counter: %4d ,Price: %5.2lf ,Discount: %2d ,Discount_Code: %6d \t\t\t\t\t\n"
#define END_LINE_OF_FILE
#define PRODUCT_GET_NAEM_FORMAT                                     "%*s %s %*s %*d %*s %*lf %*s %*d %*s %*d"
#define PRODUCT_GET_DISCOUNT_CODE_FORMAT                            "%*s %*s %*s %*d %*s %*lf %*s %*d %*s %d"
#define PRODUCT_GET_DISCOUNT_FORMAT                                 "%*s %*s %*s %*d %*s %*lf %*s %d %*s %*d"
#define PRODUCT_GET_PRICE_FORMAT                                    "%*s %*s %*s %*d %*s %lf %*s %*d %*s %*d"
#define PRODUCT_GET_COUNTER_FORMAT                                  "%*s %*s %*s %d %*s %*lf %*s %*d %*s %*d"

int set_discount_code(char* key, int code);
int set_discount_percentage(char* key, int percentage);
int set_counter(char* key, int counter);
int set_price(char* key, double price);

int get_discount_code (char* key);
int get_discount_percentage(char* key);
int get_counter (char* key);
double get_price (char * key);

int add_product (struct PRODUCT product);

#endif // PRODUCT_FILE_MANAGER_H_INCLUDED
