/*
 * buyer_wallet.c
 *
 *  Created on: Dec. 3, 2020
 *      Author: safatanzeem
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "include/Buyer/buyer_wallet.h"

/**
 * \brief This function adds balance in the online wallet of the buyer
 * @return  balance added in the one wallet of the buyer
 */
float add_balance(){
    float balance = 0.0;
    printf("Enter the amount in dollars: ");
    scanf("%f", &balance);
    printf("Balance added successfully \n");
    return balance;
}

/**
 * \brief This function updates balance in the online wallet once the transaction is being made
 * @param[in] wallet_balance is the balance added in the wallet at the start of transaction
 * @param[in] total_amt_in_cart is the amount needed for purchase
 * @return -2 if insufficient balance in wallet,
 * @return wallet_balance if transaction is sucessful
 * @return update_balance if insufficient balance in the account and user to want to add new balance
 */
float update_balance(float wallet_balance, float total_amt_in_cart){
    int flag = 0;
    if (wallet_balance < total_amt_in_cart){
        printf("Transaction cannot be completed, Wallet Balance insufficient! \n");
        printf("Enter 1: To add balance \nEnter 0: To exit \n");
        scanf("%d", &flag);
        if (flag == 0){
            return -2; // Exit the program
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
        printf("Transaction successful, Remaining Balance is: %f \n",
                wallet_balance);
    }

    return wallet_balance;
}

int main(){
    update_balance(10, 50);

}
