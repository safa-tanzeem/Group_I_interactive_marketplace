/**
 * seller_maneger.h
 *
 *      Created on: Nov.28.2020
 *          Author: Kaveh Rouhandeh
 *
 */
#ifndef SELLER_MANAGER_H_INCLUDED
#define SELLER_MANAGER_H_INCLUDED

#define SELLER_ROOT_PATH                                            "..\\data\\"

#define FETCH_SELLER_NAME_FORMAT                                    "%s"
#define FETCH_SELLER_PASS_FORMAT                                    "%s"
#define FETCH_SELLER_TOTAL_REVENUE_FORMAT                           "%f"
#define STORE_SELLER_INFO_FORMAT                                    "%s\n%s\n%f\n"

#define SOLD_PRODUCT_INFO_FORMAT                                   "%d,%d,%s,%s,%s"

/** \brief  Use this function to enter the marketplace as a seller
 *
 * \param   seller id is key value to access seller info
 * \param   password of seller for user verification
 * \return  if every thing goes well it will return instance of SELLER structer
 *          otherwise will show related message and return NULL
 */
struct SELLER * seller_log_in(int seller_id , char * pass);


/** \brief Use this function to logout also, this function save all info
 *         exist in input argument
 * \param  instance of current seller
 * \return the output is depends on result_code.h
 *
 */
int seller_log_out(struct SELLER * seller);


/** \brief Use this function for create new seller profile
 *
 * \param  id of new seller
 * \param  name of new seller
 * \param  password of new seller
 * \return the output is depends on result_code.h
 *
 */
int seller_sign_up(int seller_id , char* name ,char * pass);


/** \brief this function will show total revenue of current seller
 *  \param  an instance of SELLER structure
 *  \return the output is depends on result_code.h
 *
 */
int show_revenue(struct SELLER* seller);


/** \brief this function will update total revenue of current seller
 *
 * \param  an instance of SELLER structure
 * \param  amount of change in total revenue
 * \return the output is depends on result_code.h
 *
 */
int update_revenue(int seller_id, float price);
#endif // SELLER_MANAGER_H_INCLUDED
