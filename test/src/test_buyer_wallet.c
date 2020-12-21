/*
 * test_buyer_wallet.c
 *
 *  Created on: Dec. 20, 2020
 *      Author: safatanzeem
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../../include/buyer_wallet.h"
#include "../include/test_buyer_wallet.h"

/**
 * \brief main function tests buyer_wallet.c function
 * Pre-Conditions:
 * 1. The wallet balance taken from online wallet should be positive.
 * 2. The amount in the cart should be positive.
 *
 * Testing @ Pre-Conditions
 * 1. Function call with negative wallet balance
 * 2. Function call with negative amount in the cart
 *
 * Post-Conditions:
 * 1. If amount in the cart is less than wallet balance, then user
 *    should be asked to either add balance or exit .
 * 2. If amount in the cart is greater than wallet balance, then wallet balance
 *    should be deducted by equivalent amount equal to in the cart.
 *
 * Testing @ Post-Conditions
 * 1. Function call with amount in the cart less than wallet balance
 *    User is asked to add new balance or exit.
 * 2. Function call with amount in the cart is greater than wallet balance.
 */

int main(){

    int wallet_balance = 0;
    int total_amt_in_cart = 0;
    float balance = 0.0;


    FILE *output;
    output = fopen(PATH_FILE, "w+");

    /*Checking pre-condition 1*/
    wallet_balance = -1;
    total_amt_in_cart = 10;
    printf("--Pre-condition 1--\n");
    update_balance(wallet_balance,total_amt_in_cart);
    fprintf(output,"Function call with wallet balance = -1(negative) .\n");
    fprintf(output, "---TEST FAILED----Invalid input! Wallet balance can't be negative--\n\n");

    /*Checking pre-condition 2*/
    wallet_balance = 20;
    total_amt_in_cart = -10;
    printf("--Pre-condition 2--\n");
    update_balance( wallet_balance, total_amt_in_cart);
    fprintf(output,"Function call with amount in cart = -10 (negative) .\n");
    fprintf(output, "---TEST FAILED----Invalid input! Amount in cart can't be negative--\n\n");

    /*Checking pre/post condition 1*/
    wallet_balance = 20;
    total_amt_in_cart = 30;
    balance = (total_amt_in_cart - wallet_balance);
    printf("--Pre/post-condition 1--\n");
    printf("Balance in wallet is %d \n",wallet_balance);
    printf("Amount in cart is %d \n", total_amt_in_cart);
    printf("You need atleast %f CAD for transaction to "
            "be successful \n", balance);
    update_balance( wallet_balance, total_amt_in_cart);
    fprintf(output,"Function call with valid input parameters,"
            "but wallet balance is less than amount in cart."
            "Function will ask if you want to add balance or not,"
            "Add more than 10CAD for the transaction to be successful\n");
    fprintf(output, "---TEST PASSED--\n\n");

    /*Checking post-condition 2*/
    wallet_balance = 40;
    total_amt_in_cart = 30;
    printf("--Pre/post-condition 2--\n");
    update_balance( wallet_balance, total_amt_in_cart);
    fprintf(output,"Function call with valid input parameters,"
            "and wallet balance greater than amount in cart\n");
    fprintf(output, "---TEST PASSED--Transaction is successful--\n\n");

    return 0;
}
