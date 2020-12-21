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

#include "../include/seller.h"
#include "../include/seller_manager.h"
#include "../include/result_code.h"


int show_revenue(struct SELLER* seller)
{
    /**< check validation of input  */
    if(seller == NULL)
    {
        printf("Seller information is invalid, Cant show revenue\n");
        return INVALID_INPUT ;
    }
    if(seller->name[0] == '\0' || seller->pass[0] == '\0' || seller->seller_id == 0 )
    {
        printf("Seller information is invalid, Can't show revenue\n");
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
    if(access(file_path, F_OK) != 0)
    {
        printf("Seller not exist, Can't show information\n");
        return INVALID_INPUT;
    }
    else
    {
        /**< show total revenue of current seller*/
        printf("Total revenue of this seller (Id: %d) is:%f\n",seller->seller_id, seller->total_revenue);
        return SUCCEED_PROCESS ;
    }
}

int update_revenue(int seller_id, float price)
{
    /**< check validation of input  */
    if(seller_id == 0)
    {
        printf("Seller id is invalid, Can't update revenue\n");
        return INVALID_INPUT ;
    }
    /**< convert seller id to string */
    char tmp_str[12];
    sprintf(tmp_str, "%d", seller_id);

    /**< generate file path */
    char file_path[100] = SELLER_ROOT_PATH;
    char tmp_file_path[100] = SELLER_ROOT_PATH;
    strcat(file_path, tmp_str);
    strcat(file_path, ".txt");
    strcat(tmp_file_path, "tmpf");
    strcat(tmp_file_path, ".txt");

    /**< check existence of file */
    if(access(file_path, F_OK) == 0)
    {
        FILE* file;
        FILE* tmp_file;
        file = fopen(file_path, "r");
        tmp_file= fopen(tmp_file_path, "w");

        if (file != NULL && tmp_file!=NULL)
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
                fputs(line, tmp_file);
                line_counter++ ;
            }
            fclose(file);
            fclose(tmp_file);
            remove(file_path);
            if( rename(tmp_file_path, file_path)==0)
            {
                //printf("Total revenue successfully updated for seller id: %d\n",seller_id);
                return SUCCEED_PROCESS ;
            }
            else
            {
                printf("An error occurred while updating the total revenue\n");
                return UNSUCCEED_PROCESS ;
            }

        }
        /**< can't open file */
        else
        {
            printf("Can't Open seller file(unable to update total revenue)\n");
            return UNSUCCEED_PROCESS;
        }
    }
    else
    {
        printf("Seller id is Invalid\n");
        return INVALID_INPUT;
    }
}


struct SELLER * seller_log_in(int seller_id, char * pass)
{
    /**< check validation of input  */
    if(seller_id == 0 || pass == NULL || pass[0] =='\0')
    {
        printf("invalid information, Can't log in\n");
        return NULL ;
    }
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
            struct SELLER* seller = (struct SELLER*)malloc(sizeof(struct SELLER));
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
                    data = strtok(data, "\n");
                    strcpy(tmp_product->phone_number, data);


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
    if(seller->name[0] == '\0' || seller->pass[0] == '\0' || seller->seller_id == 0 )
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
                    // fputs("\n", file);
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
    /**< check validation of input  */
    if(seller_id == 0 || pass[0]=='\0' || name[0] == '\0' )
    {
        printf("Information is invalid, Can't sign up\n");
        return INVALID_INPUT ;
    }
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
        file = fopen(file_path, "w");
        if (file != NULL)
        {
            fprintf(file,STORE_SELLER_INFO_FORMAT,
                    pass,
                    name,
                    0.0);
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
    }
    else
    {
        printf("Sign up failed, this seller id: %d already exist, Please try again.\n",seller_id);
        return DUPLICATE_DATA ;
    }
}
