
/**
 * seller_maneger.c
 *
 *      Created on: Dec.14.2020
 *          Author: Kaveh Rouhandeh
 *
 */

#include <stdio.h>

#include "../../include/seller.h"
#include "../../include/seller_manager.h"
#include "../../include/result_code.h"
#include "../include/test_seller_log_in.h"
/** \brief this function is prepared for testing seller log in function.
            this function calling update_revenue function with 3 different arguments:
            1.with invalid password -> pass=NULL
            2.with invalid password -> pass= '\0'
            3.with valid seller id and pass -> seller_id = 5560 , pass ="pass5"
            4.with wrong password -> pass=wrong-pass
            5.with invalid seller id -> seller_id= 0
            6.with nonexistante seller -> seller_id = 8888 , pass ="pass"
 *
 *
 */

void main()
{
    FILE* file;
    file = fopen(PATH, "a");
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    if (file != NULL)
    {
        /**< write current time as the first new line in log file */
        fprintf(file,"\n--------time and date: %s", asctime (timeinfo) );
        struct SELLER * output  ;
        struct SELLER * expected_output ;


        /**<  call seller log in function using invalid password=NULL*/
        expected_output = NULL ;
        output = seller_log_in(5560, NULL);
        if(output == expected_output)
        {
            fputs("Input: invalid seller pass(NULL) \t\t\t\t\t ---Test Passed\n", file);
        }
        else
        {
            fputs("Input: invalid seller pass(NULL) \t\t\t\t\t ---Test Failed\n", file);
        }


        /**<  call seller log in function using invalid password ='\0'*/
        expected_output = NULL ;
        output = seller_log_in(5560, '\0');
        if(output == expected_output)
        {
            fputs("Input: invalid seller pass(empty) \t\t\t\t\t ---Test Passed\n", file);
        }
        else
        {
            fputs("Input: invalid seller pass(empty) \t\t\t\t\t ---Test Failed\n", file);
        }


        /**<  call seller log in function using invalid seller id*/
        expected_output = NULL ;
        output = seller_log_in(0, "pass");
        if(output == expected_output)
        {
            fputs("Input: invalid seller id \t\t\t\t\t\t ---Test Passed\n", file);
        }
        else
        {
            fputs("Input: invalid seller id \t\t\t\t\t\t ---Test Failed\n", file);
        }

        /**<  call seller log in function using nonexistent seller*/
        expected_output = NULL ;
        output = seller_log_in(8888, "pass");
        if(output == expected_output)
        {
            fputs("Input: nonexistent seller \t\t\t\t\t\t ---Test Passed\n", file);
        }
        else
        {
            fputs("Input: nonexistent seller \t\t\t\t\t\t ---Test Failed\n", file);
        }

        /**<  call seller log in function using wrong password*/
        expected_output = NULL ;
        output = seller_log_in(5560, "wrong-pass");
        if(output == expected_output)
        {
            fputs("Input: wrong pass \t\t\t\t\t\t\t ---Test Passed\n", file);
        }
        else
        {
            fputs("Input: wrong pass \t\t\t\t\t\t\t ---Test Failed\n", file);
        }

        /**<  call seller log in function using valid input*/
        output = seller_log_in(5560, "pass5");
        if(output != NULL)
        {
            fputs("Input: valid \t\t\t\t\t\t\t\t ---Test Passed\n", file);
        }
        else
        {
            fputs("Input: valid \t\t\t\t\t\t\t\t ---Test Failed\n", file);
        }

        fclose(file);
    }
}
