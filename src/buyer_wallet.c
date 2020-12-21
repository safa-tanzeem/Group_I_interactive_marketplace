/*
 * buyer_wallet.c
 *
 *  Created on: Dec. 19, 2020
 *      Author: safatanzeem
 */



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/buyer_wallet.h"
#include "../include/common.h"

/**
 * \brief This function adds balance in the online wallet of the buyer
 * @return  balance added in the one wallet of the buyer
 */
float add_balance(){
    int output = 0;
    float balance = 0.0;
    printf("Declare the amount you have in CAD: ");

    do{
        output=scanf("%f", &balance);
    }while(validate(output)!=OK);

    printf("Balance added successfully! \n");
    return balance;
}

/**
 * \brief This function updates balance in the online wallet once the transaction is being made
 * @param[in] wallet_balance is the balance added in the wallet at the start of transaction
 * @param[in] total_amt_in_cart is the amount needed for purchase
 * @return -2 if insufficient balance in wallet,
 * @return -10 if wallet balance or amount in cart  is less than 0
 * @return wallet_balance if transaction is sucessful
 * @return update_balance if insufficient balance in the account and user to want to add new balance
 */
float update_balance(float wallet_balance, float total_amt_in_cart){
    int output = 0;
    int flag = 0;

    if(wallet_balance < 0 || total_amt_in_cart <0){
        printf("Error! Wallet balance and total amount in cart can't be less than zero\n");
        return ERROR_VALUE_ZERO;
    }

    if (wallet_balance < total_amt_in_cart){
        printf("Transaction cannot be completed, Wallet Balance insufficient! \n");
        printf("Enter 1: To add balance \nEnter 0: To exit \n");
        
        do{
            output=scanf("%d", &flag);
        }while(validate(output)!=OK);

        if (flag == 0){
            return -2.0; // Exit the program
        }else if (flag == 1){
            float new_balance = 0.0;
            new_balance = add_balance();
            wallet_balance = wallet_balance + new_balance;
            printf("New wallet balance is %f Dollars \n", wallet_balance);
            return update_balance(wallet_balance, total_amt_in_cart);
        }else{
            printf("Invalid input!\n");
        }
    }else{
        wallet_balance = wallet_balance - total_amt_in_cart;
        printf("Transaction successful, Remaining Balance is: $%.2f \n",
                wallet_balance);
    }

    return wallet_balance;
}
