/**
 * seller_maneger.c
 *
 *      Created on: Nov.28.2020
 *          Author: Kaveh Rouhandeh
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "seller.h"
//#include "sold_product.h"
//#include "seller_prod_num.h"
#include "seller_manager.h"
#include "result_code.h"



int show_seller_info(struct SELLER * seller)
{
    /**< check validation of input  */
    if(seller == NULL)
    {
        printf("Seller information is invalid, Can't show information\n");
        return INVALID_INPUT ;
    }
    else
    {
        /**< fetch seller info and show them*/
        printf("Seller Id: %d\n", seller->seller_id);
        printf("Seller Name: %s\n", seller->name);
        printf("Seller Total Revenue: %f\n", seller->total_revenue);

        /**< check existence of products number list in current seller*/
        if(seller->products_number == NULL)
        {
            printf("No products were added by this seller\n");
        }
        else
        {
            /**< iterate to show all */
            printf("Available products for this seller:\n");
            struct SELLER_PROD_NUM* tmp = seller->products_number ;
            while(tmp != NULL)
            {
                printf("%d ,",tmp->value);
                tmp= tmp->next ;
            }
            printf("\n");
        }

        /**< check existence of sold products list in current seller*/
        if(seller->products_sold == NULL)
        {
            printf("No products were sold by this seller\n");
        }
        else
        {
            /**< iterate to show all */
            printf("Products sold by this seller:\n");
            struct SOLD_PRODUCT* tmp = seller->products_sold;
            while (tmp != NULL)
            {
                printf("Product Number: %d, Quantity: %d, Buyer Name: %s, Buyer Address: %s, Phone Number: %s\n",
                       tmp->product_number,
                       tmp->quantity,
                       tmp->buyer_name,
                       tmp->buyer_shipping_address,
                       tmp->phone_number);
                tmp = tmp->next_sold_product;
            }
        }
        return SUCCEED_PROCESS;
    }
}


int show_revenue(struct SELLER* seller)
{
    /**< check validation of input  */
    if(seller == NULL)
    {
        printf("Seller information is invalid, Cant show revenue\n");
        return INVALID_INPUT ;
    }
    else
    {
        /**< show total revenue of current seller*/
        printf("Total revenue of this seller (Id: %d) is:%f\n",seller->seller_id, seller->total_revenue);
        return SUCCEED_PROCESS ;
    }
}


int show_sold_products(struct SELLER* seller)
{
    /**< check validation of input  */
    if(seller == NULL)
    {
        printf("Seller information is invalid, Cant show sold products\n");
        return INVALID_INPUT ;
    }
    else
    {
        printf("Products sold by this seller(id: %d)\n\n",seller->seller_id);
        struct SOLD_PRODUCT* tmp = seller->products_sold;

        /**< check existence of products number list in current seller*/
        if(tmp == NULL)
        {
            printf("No products were sold by this seller.\n");
            return SUCCEED_PROCESS;
        }

        /**< iterate to show all */
        while (tmp != NULL)
        {
            printf("Product Number: %d, Quantity: %d, Buyer Name: %s, Buyer Address: %s, Phone Number: %s\n",
                   tmp->product_number,
                   tmp->quantity,
                   tmp->buyer_name,
                   tmp->buyer_shipping_address,
                   tmp->phone_number);
            tmp = tmp->next_sold_product;
        }
        return SUCCEED_PROCESS ;
    }
}


int seller_change_password(struct SELLER **seller)
{
    /**< check validation of input  */
    if(*seller == NULL)
    {
        printf("Seller information is invalid, Unable to change seller password\n");
        return INVALID_INPUT ;
    }
    char old_pass[20]="";
    char new_pass[20]="";

    /**< Continue the loop until the seller exits or user enter the correct password*/
    while(1)
    {
        /**< seller verification for changing password by ask password again */
        printf("Please Enter old password: ");
        scanf("%s", old_pass);
        if(strcmp(old_pass, (*seller)->pass)!= 0)
        {
            printf("Old password is wrong\nEnter 1 to continue or others for exit:");
            int user_input = 0 ;
            scanf("%d", &user_input);
            if(user_input != 1)
            {
                printf("You have not changed your password\n");
                return UNSUCCEED_PROCESS ;
            }
        }
        else
        {
            break ;
        }

    }

    printf("Please Enter new password: ");
    scanf("%s", new_pass);
    strcpy((*seller)->pass, new_pass);
    printf("You have changed your password successfully\n");
    return SUCCEED_PROCESS;
}


int seller_change_name(struct SELLER **seller)
{
    /**< check validation of input  */
    if(*seller == NULL)
    {
        printf("Seller information is invalid, Unable to change seller name\n");
        return INVALID_INPUT ;
    }
    char _pass[20]="";
    /**< Continue the loop until the seller exits or user enter the correct password*/
    while(1)
    {
        /**< seller verification for changing name by ask password again */
        printf("Please enter your password: ");
        scanf("%s", _pass);
        if(strcmp(_pass, (*seller)->pass)!= 0)
        {
            printf("Password is wrong\nEnter 1 to continue or others for exit:");
            int user_input = 0 ;
            scanf("%d", &user_input);
            if(user_input != 1)
            {
                printf("You have not changed your name\n");
                return UNSUCCEED_PROCESS ;
            }
        }
        else
        {
            break;
        }

    }
    printf("Please Enter new name: ");
    scanf("%s", (*seller)->name);
    printf("You have changed your name successfully\n");
    return SUCCEED_PROCESS;
}


int update_revenue(int seller_id, float price)
{
    /**< convert seller id to string */
    char tmp_str[12];
    char file_text[100];
    sprintf(tmp_str, "%d", seller_id);

    /**< generate file path */
    char file_path[100] = SELLER_ROOT_PATH;
    strcat(file_path, tmp_str);
    strcat(file_path, ".txt");

    /**< check existence of file */
    if(access(file_path, F_OK) == 0)
    {
        FILE* file;
        file = fopen(file_path, "r");

        if (file != NULL)
        {
            char line[200];
            int line_counter = 1 ;

            while(fgets(line,200,file)!= NULL)
            {
                /**< get seller total revenue */
                if(line_counter == 3)
                {
                    float revenue;
                    sscanf(line,FETCH_SELLER_TOTAL_REVENUE_FORMAT, &revenue);
                    /**< updating total revenue and then convert it to string format */
                    revenue+=price;
                    sprintf(line, "%f", revenue);
                    strcat(line, "\n");
                }
                line_counter++;
                /**< concatenate all line of the text file */
                strcat(file_text, line);
            }
            fclose(file);
            /**< remove old version file */
            if(remove(file_path)!=0)
            {
                printf("An error occurred while updating the total revenue\n");
                return UNSUCCEED_PROCESS ;
            }

            /**< rewrite text file */
            FILE* file;
            file = fopen(file_path, "w");
            if(file!= NULL)
            {
                fputs(file_text,file);
                printf("Total revenue successfully updated for seller id: %d\n",seller_id);
                fflush(file);
                fclose(file);
                return SUCCEED_PROCESS ;
            }
            else
            {
                printf("Can't Open seller file(unable to update total revenue) \n");
                return CANT_OPEN_FILE;
            }

        }
        /**< can't open file */
        else
        {
            printf("Can't Open seller file(unable to update total revenue)\n");
            return CANT_OPEN_FILE;
        }
    }
    else
    {
        printf("Seller id is Invalid");
        return UNSUCCEED_PROCESS;
    }
}


struct SELLER * seller_log_in(int seller_id, char * pass)
{
    /**< convert seller id to string */
    char tmp_str[12];
    sprintf(tmp_str, "%d", seller_id);
    /**< generate file path */
    char file_path[100] = SELLER_ROOT_PATH;
    strcat(file_path, tmp_str);
    strcat(file_path, ".txt");

    /**< check existence of file */
    if(access(file_path, F_OK) == 0)
    {
        /**< create file pointer */
        FILE* file;
        file = fopen(file_path, "r");

        if (file != NULL)
        {
            char line[200];
            int line_counter = 1 ;
            struct SELLER* seller = seller = (struct SELLER*)malloc(sizeof(struct SELLER));
            struct SOLD_PRODUCT* sold_product_head = NULL;
            struct SELLER_PROD_NUM* product_number_head = NULL;

            /**< read first line to check pass */
            if(fgets(line,200,file)!= NULL)
            {
                sscanf(line,FETCH_SELLER_PASS_FORMAT,seller->pass);
                if(strcmp( seller->pass, pass) == 0)
                {
                    /**< password is correct */
                    seller->seller_id = seller_id ;
                    line_counter ++ ;
                }
                else
                {
                    /**< pass is incorrect */
                    printf("Password is invalid for this seller id: %d \n",seller_id);
                    return NULL ;
                }
            }

            while(fgets(line,200,file)!= NULL)
            {
                if(line_counter>4)
                {
                    /**< read products */
                    struct SOLD_PRODUCT* tmp_product = (struct SOLD_PRODUCT*)malloc(sizeof(struct SOLD_PRODUCT));
                    char * data ;

                    data = strtok(line, ",");
                    tmp_product->product_number = atoi(data);

                    data = strtok(NULL, ",");
                    tmp_product->quantity = atoi(data);

                    data = strtok(NULL, ",");
                    strcpy(tmp_product->buyer_name, data);

                    data = strtok(NULL, ",");
                    strcpy(tmp_product->buyer_shipping_address, data);

                    data = strtok(NULL, ",");
                    strcpy(tmp_product->phone_number, data);
                    //tmp_product->phone_number = atoi(data);


                    /**< add to list */
                    if ((sold_product_head) == NULL)
                    {
                        tmp_product->next_sold_product = NULL;
                        sold_product_head = tmp_product;
                    }
                    else
                    {
                        struct SOLD_PRODUCT* current;
                        current = sold_product_head;
                        tmp_product->next_sold_product = current->next_sold_product;
                        current->next_sold_product = tmp_product;
                    }
                }
                else
                {
                    /**< get seller name */
                    if(line_counter == 2)
                    {
                        sscanf(line,FETCH_SELLER_NAME_FORMAT,seller->name);
                        line_counter ++ ;
                    }

                    /**< get seller total revenue */
                    else if(line_counter == 3)
                    {
                        sscanf(line,FETCH_SELLER_TOTAL_REVENUE_FORMAT, &(seller->total_revenue));
                        line_counter ++ ;
                    }
                    /**< get available products */
                    else if(line_counter == 4 )
                    {
                        while(strcmp(line, "END") !=0 && strcmp(line, "END\n") !=0)
                        {
                            struct SELLER_PROD_NUM* tmp_container = (struct SELLER_PROD_NUM*)malloc(sizeof(struct SELLER_PROD_NUM));
                            sscanf(line,"%d,%s",&(tmp_container->value),line);
                            /**< add to list */
                            if ((product_number_head) == NULL)
                            {
                                tmp_container->next = NULL;
                                product_number_head = tmp_container;
                            }
                            else
                            {
                                struct SELLER_PROD_NUM* current;
                                current = product_number_head;
                                tmp_container->next = current->next;
                                current->next = tmp_container;
                            }
                        }
                        line_counter ++ ;
                    }

                }
            }
            seller->products_sold = sold_product_head ;
            seller->products_number =  product_number_head;
            fclose(file);
            printf("You have logged in successfully with this seller id: %d\n",seller_id);
            return seller ;
        }
        /**< can't open file */
        else
        {
            printf("Can't Open file (login failed).\n");
            return NULL ;
        }
    }
    /**< file don't exist */
    else
    {
        printf("Seller id is Invalid (id: %d)\n", seller_id);
        return NULL ;
    }

}
int seller_log_out(struct SELLER * seller)
{
    /**< check validation of input  */
    if(seller == NULL)
    {
        printf("Seller information is invalid, logout failed\n");
        return INVALID_INPUT ;
    }

    /**< convert seller id to string */
    char tmp_str[12];
    sprintf(tmp_str, "%d", seller->seller_id);

    /**< generate file path */
    char file_path[100] = SELLER_ROOT_PATH;
    strcat(file_path, tmp_str);
    strcat(file_path, ".txt");
    /**< check existence of file */
    if(access(file_path, F_OK) == 0)
    {
        /**< remove file */
        if(remove(file_path)!=0)
        {
            printf("An error occurred while saving seller information\n");
            return UNSUCCEED_PROCESS ;
        }
        else
        {
            FILE* file;
            file = fopen(file_path, "w");
            if (file != NULL)
            {
                fprintf(file,STORE_SELLER_INFO_FORMAT,
                        seller->pass,
                        seller->name,
                        seller->total_revenue);

                /**< store product numbers */
                struct SELLER_PROD_NUM* product_number = seller->products_number;
                char tmp_line[100]="";
                while(product_number!=NULL)
                {
                    sprintf(tmp_str, "%d", product_number->value);
                    strcat(tmp_line,tmp_str );
                    strcat(tmp_line, ",");
                    product_number = product_number->next;
                }
                strcat(tmp_line, "END\n");
                fputs(tmp_line, file);


                /**< store product list */
                struct SOLD_PRODUCT* sold_product = seller->products_sold;
                while (sold_product != NULL)
                {
                    fprintf(file, SOLD_PRODUCT_INFO_FORMAT,
                            sold_product->product_number,
                            sold_product->quantity,
                            sold_product->buyer_name,
                            sold_product->buyer_shipping_address,
                            sold_product->phone_number);
                    sold_product = sold_product->next_sold_product;
                    fputs("\n", file);
                }
                fclose(file);
                printf("You have logged out successfully\n");
                return SUCCEED_PROCESS ;
            }
            else
            {
                printf("An error occurred while saving seller information\n");
                return CANT_OPEN_FILE;
            }
        }
    }
    else
    {
        /**< ask for user input */
        printf("This seller id: %d doesn't exist.\nEnter 1 for Sign up or others for exit\nUser input is: ", seller->seller_id);
        int user_input = 0 ;
        scanf("%d", &user_input);
        printf("\n");
        if(user_input == 1)
        {
            /**< Sign up */
            FILE* file;
            file = fopen(file_path, "w");
            if (file != NULL)
            {
                fprintf(file,STORE_SELLER_INFO_FORMAT,
                        seller->pass,
                        seller->name,
                        seller->total_revenue);

                /**< store product numbers */
                struct SELLER_PROD_NUM* product_number = seller->products_number;
                char tmp_line[100]="";
                while(product_number!=NULL)
                {
                    sprintf(tmp_str, "%d", product_number->value);
                    strcat(tmp_line,tmp_str );
                    strcat(tmp_line, ",");
                    product_number = product_number->next;
                }
                strcat(tmp_line, "END\n");
                fputs(tmp_line, file);
                /**< store product list */
                struct SOLD_PRODUCT* sold_product = seller->products_sold;
                while (sold_product != NULL)
                {
                    fprintf(file, SOLD_PRODUCT_INFO_FORMAT,
                            sold_product->product_number,
                            sold_product->quantity,
                            sold_product->buyer_name,
                            sold_product->buyer_shipping_address,
                            sold_product->phone_number);
                    sold_product = sold_product->next_sold_product;
                }
                fclose(file);
                printf("You have signed up successfully.\n");
                return SUCCEED_PROCESS ;
            }
            else
            {
                /**< exit */
                printf("An error occurred while saving seller information\n");
                return CANT_OPEN_FILE;
            }
        }
        else
        {
            /**< exit */
            printf("You have not sign up\n");
            return SUCCEED_PROCESS;
        }

    }
}

int seller_sign_up(int seller_id, char * name, char * pass )
{
    /**< convert seller id to string */
    char tmp_str[12];
    sprintf(tmp_str, "%d", seller_id);

    /**< generate file path */
    char file_path[100] = SELLER_ROOT_PATH;
    strcat(file_path, tmp_str);
    strcat(file_path, ".txt");

    /**< check existence of file */
    if(access(file_path, F_OK) != 0)
    {
        /**< create new seller */
        FILE* file;
        //FILE* file_update;
        file = fopen(file_path, "w+");
        //file_update = fopen(file_path,"a+");
        if (file != NULL)
        {
            //fprintf(file, "hello\n");
            fprintf(file,"%s\n%s\n%f\n",pass,name,0.0);
            fputs("END",file);
            fflush(file);
            printf("You have signed up successfully with seller id: %d\n",seller_id);
            return SUCCEED_PROCESS;
        }
        else
        {
            printf("Sign up failed seller id: %d\n",seller_id);
            return CANT_OPEN_FILE ;
        }
        fclose(file);
    }
    else
    {
        printf("Sign up failed, this seller id: %d already exist, Please try again.\n",seller_id);
        return DUPLICATE_DATA ;
    }
}
