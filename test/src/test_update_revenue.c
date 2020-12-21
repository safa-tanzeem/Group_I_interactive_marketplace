/**
 * seller_maneger.c
 *
 *      Created on: Dec.15.2020
 *          Author: Kaveh Rouhandeh
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "../include/test_update_revenue.h"
#include "../../include/seller_manager.h"
#include "../../include/result_code.h

/** \brief this function is prepared  for testing update revenue.
            this function calling update_revenue function with 3 different arguments:
            1.with invalid seller id -> seller_id=0
            2.with nonexistent seller id -> seller_id= 1234
            3.with existent seller id -> seller_id = 5560
 *
 */

void main()
{
    /**< create log file */
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
        int output = 0 ;
        int expected_output = 0 ;

        /**<  call update revenue function using invalid seller id*/
        expected_output = INVALID_INPUT ;
        output = update_revenue(0, 10.0);
        if(output == expected_output)
        {
            fputs("Input: invalid seller id \t\t\t\t\t\t ---Test Passed\n", file);
        }
        else
        {
            fputs("Input: invalid seller id \t\t\t\t\t\t ---Test Failed\n", file);
        }

        /**<  call update revenue function using nonexistent seller id*/
        expected_output = INVALID_INPUT ;
        output = update_revenue(8888, 10.0);
        if(output == expected_output)
        {
            fputs("Input: nonexistent seller \t\t\t\t\t\t ---Test Passed\n", file);
        }
        else
        {
            fputs("Input: nonexistent seller \t\t\t\t\t\t ---Test Failed\n", file);
        }

        /**<  call update revenue function using valid seller id*/
        expected_output = SUCCEED_PROCESS ;
        output = update_revenue(5560, 10.0);
        if(output == expected_output)
        {
            fputs("Input: valid  \t\t\t\t\t\t\t\t ---Test Passed\n", file);
        }
        else
        {
            fputs("Input: valid \t\t\t\t\t\t\t\t ---Test Failed\n", file);
        }

        fclose(file);
    }
}
