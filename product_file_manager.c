#include "product_file_manager.h"
#include "product.h"
#include "result_code.h"

#include <stdio.h>
#include <stdlib.h>

int set_discount_code(char* key, int code)
{

    char product[20];
    char line[200];
    int colon_counter = 0 ;

    FILE* file;
    file = fopen(PRODUCT_FILE_PATH, "r+");

    if (file != NULL)
    {
        while(fgets(line,200,file)!= EOF)
        {
            sscanf(line,PRODUCT_GET_NAEM_FORMAT,product);
            if(strcmp(product, key) == 0)
            {
                fseek(file, -3L, SEEK_CUR);
                char tmp ;
                while((tmp=(char)fgetc(file))!= '\n')
                {
                    if(tmp == ':')
                    {
                        colon_counter ++ ;
                        if(colon_counter== 1)
                        {
                            fseek(file, +1L,SEEK_CUR);
                            fprintf(file,"%d",code);
                            break;
                        }
                    }

                    if(tmp != ' ')
                    {
                        fseek(file, -1L, SEEK_CUR);
                        fputc(' ',file);
                    }

                    fseek(file, -2L, SEEK_CUR);
                }
                break;
            }
        }
        fclose(file);
        return SUCCEED_PROCESS ;
    }
    else
    {
        return CANT_OPEN_FILE;
    }
}
int set_discount_percentage(char* key, int percentage)
{
    char product[20];
    char line[200];
    int colon_counter = 0 ;
    int comma_counter = 0 ;

    FILE* file;
    file = fopen(PRODUCT_FILE_PATH, "r+");

    if (file != NULL)
    {
        while(fgets(line,200,file)!= EOF)
        {
            sscanf(line,PRODUCT_GET_NAEM_FORMAT,product);
            if(strcmp(product, key) == 0)
            {
                fseek(file, -3L, SEEK_CUR);
                char tmp ;
                while((tmp=(char)fgetc(file))!= '\n')
                {

                    if(tmp == ',')
                    {
                        comma_counter ++ ;
                        fseek(file, -2L, SEEK_CUR);
                        continue ;
                    }

                    if(comma_counter != 1)
                    {
                        fseek(file, -2L, SEEK_CUR);
                        continue ;
                    }

                    if(tmp == ':')
                    {
                        colon_counter ++ ;
                        if(colon_counter == 1)
                        {
                            fseek(file, +1L,SEEK_CUR);
                            fprintf(file,"%d",percentage);
                            break;
                        }
                    }

                    if(tmp != ' ')
                    {
                        fseek(file, -1L, SEEK_CUR);
                        fputc(' ',file);
                    }

                    fseek(file, -2L, SEEK_CUR);
                }
                break;
            }
        }
        fclose(file);
        return SUCCEED_PROCESS ;
    }
    else
    {
        return CANT_OPEN_FILE;
    }
}
int set_counter(char* key, int counter)
{




    char product[20];
    char line[200];
    int colon_counter = 0 ;
    int comma_counter = 0 ;

    FILE* file;
    file = fopen(PRODUCT_FILE_PATH, "r+");

    if (file != NULL)
    {
        while(fgets(line,200,file)!= EOF)
        {
            sscanf(line,PRODUCT_GET_NAEM_FORMAT,product);
            if(strcmp(product, key) == 0)
            {
                fseek(file, -3L, SEEK_CUR);
                char tmp ;
                while((tmp=(char)fgetc(file))!= '\n')
                {

                    if(tmp == ',')
                    {
                        comma_counter ++ ;
                        fseek(file, -2L, SEEK_CUR);
                        continue ;
                    }

                    if(comma_counter != 3)
                    {
                        fseek(file, -2L, SEEK_CUR);
                        continue ;
                    }

                    if(tmp == ':')
                    {
                        colon_counter ++ ;
                        if(colon_counter == 1)
                        {
                            fseek(file, +1L,SEEK_CUR);
                            fprintf(file,"%d",counter);
                            break;
                        }
                    }

                    if(tmp != ' ')
                    {
                        fseek(file, -1L, SEEK_CUR);
                        fputc(' ',file);
                    }

                    fseek(file, -2L, SEEK_CUR);
                }
                break;
            }
        }
        fclose(file);
        return SUCCEED_PROCESS ;
    }
    else
    {
        return CANT_OPEN_FILE;
    }
}
int set_price(char* key, double price)
{
    char product[20];
    char line[200];
    int colon_counter = 0 ;
    int comma_counter = 0 ;

    FILE* file;
    file = fopen(PRODUCT_FILE_PATH, "r+");

    if (file != NULL)
    {
        while(fgets(line,200,file)!= EOF)
        {
            sscanf(line,PRODUCT_GET_NAEM_FORMAT,product);
            if(strcmp(product, key) == 0)
            {
                fseek(file, -3L, SEEK_CUR);
                char tmp ;
                while((tmp=(char)fgetc(file))!= '\n')
                {

                    if(tmp == ',')
                    {
                        comma_counter ++ ;
                        fseek(file, -2L, SEEK_CUR);
                        continue ;
                    }

                    if(comma_counter != 2)
                    {
                        fseek(file, -2L, SEEK_CUR);
                        continue ;
                    }

                    if(tmp == ':')
                    {
                        colon_counter ++ ;
                        if(colon_counter == 1)
                        {
                            fseek(file, +1L,SEEK_CUR);
                            fprintf(file,"%lf",price);
                            break;
                        }
                    }

                    if(tmp != ' ')
                    {
                        fseek(file, -1L, SEEK_CUR);
                        fputc(' ',file);
                    }

                    fseek(file, -2L, SEEK_CUR);
                }
                break;
            }
        }
        fclose(file);
        return SUCCEED_PROCESS ;
    }
    else
    {
        return CANT_OPEN_FILE;
    }
}


int get_discount_code (char* key)
{
    char product[20];
    char line[200];

    FILE* file;
    file = fopen(PRODUCT_FILE_PATH, "r+");

    if (file != NULL)
    {
        while(fgets(line,200,file)!= EOF)
        {
            sscanf(line,PRODUCT_GET_NAEM_FORMAT,product);
            if(strcmp(product, key) == 0)
            {
                fclose(file);
                int tmp = 0 ;
                sscanf(line,PRODUCT_GET_DISCOUNT_CODE_FORMAT, &tmp );
                return tmp ;
            }
        }
    }
    else
    {
        return CANT_OPEN_FILE;
    }
}
int get_discount_percentage(char* key)
{
    char product[20];
    char line[200];

    FILE* file;
    file = fopen(PRODUCT_FILE_PATH, "r+");

    if (file != NULL)
    {
        while(fgets(line,200,file)!= EOF)
        {
            sscanf(line,PRODUCT_GET_NAEM_FORMAT,product);
            if(strcmp(product, key) == 0)
            {
                fclose(file);
                int tmp = 0 ;
                sscanf(line,PRODUCT_GET_DISCOUNT_FORMAT, &tmp );
                return tmp ;
            }
        }
    }
    else
    {
        return CANT_OPEN_FILE;
    }
}
int get_counter (char* key)
{
    char product[20];
    char line[200];

    FILE* file;
    file = fopen(PRODUCT_FILE_PATH, "r+");

    if (file != NULL)
    {
        while(fgets(line,200,file)!= EOF)
        {
            sscanf(line,PRODUCT_GET_NAEM_FORMAT,product);
            if(strcmp(product, key) == 0)
            {
                fclose(file);
                int tmp = 0 ;
                sscanf(line,PRODUCT_GET_COUNTER_FORMAT, &tmp );
                return tmp ;
            }
        }
    }
    else
    {
        return CANT_OPEN_FILE;
    }
}
double get_price (char * key)
{
    char product[20];
    char line[200];

    FILE* file;
    file = fopen(PRODUCT_FILE_PATH, "r+");

    if (file != NULL)
    {
        while(fgets(line,200,file)!= EOF)
        {
            sscanf(line,PRODUCT_GET_NAEM_FORMAT,product);
            if(strcmp(product, key) == 0)
            {
                fclose(file);
                double  tmp = 0 ;
                sscanf(line,PRODUCT_GET_PRICE_FORMAT, &tmp );
                return tmp ;
            }
        }
    }
    else
    {
        return CANT_OPEN_FILE;
    }
}

int add_product (struct PRODUCT product)
{
    char tmp_p_name[20];
    char line[200];

    FILE* file;
    file = fopen(PRODUCT_FILE_PATH, "r+");

    if (file != NULL)
    {
        while(fgets(line,200,file)!=NULL)
        {
            sscanf(line,PRODUCT_GET_NAEM_FORMAT,tmp_p_name);
            if(strcmp(tmp_p_name, product.name ) == 0)
            {
                fclose(file);
                return DUPLICATE_DATA ;
            }
        }

        fseek(file, 0L, SEEK_END);
        fprintf(file, PRODUCT_INFO_FORMAT, product.name , product.counter , product.price , product.discount_percentage , product.discount_code);
        fclose(file);
    }
    else
    {
        return CANT_OPEN_FILE;
    }
}
