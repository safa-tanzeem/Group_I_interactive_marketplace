/**
 * seller_maneger.h
 *
 *      Created on: Nov.28.2020
 *          Author: Kaveh Rouhandeh
 *
 */
#ifndef SELLER_MANAGER_H_INCLUDED
#define SELLER_MANAGER_H_INCLUDED

#define SELLER_ROOT_PATH                                            "../data/"

#define FETCH_SELLER_NAME_FORMAT                                    "%s"
#define FETCH_SELLER_PASS_FORMAT                                    "%s"
#define FETCH_SELLER_TOTAL_REVENUE_FORMAT                           "%f"
#define STORE_SELLER_INFO_FORMAT                                    "%s\n%s\n%f\n"

#define SOLD_PRODUCT_INFO_FORMAT                                   "%d,%d,%s,%s,%s"

/** \brief   Use this function to enter the marketplace as a seller.
 *           The function require to know seller id and password to authenticate as a seller.
 * \@param[in]    seller id is key value to access seller info
 * \@param[in]    password of seller for authentication
 * \@return  if every thing goes well it will return instance of SELLER structure
 *          otherwise will show related message and return NULL
 */
struct SELLER * seller_log_in(int seller_id , char * pass);


/** \brief Use this function to logout ,also this function save all info
 *         exist in input argument.
 *
 * \@param[in]   instance of current seller(a pointer to seller structure)
 *
 * \@return  the output is depends on result_code.h:
 * \@return  -1 (CANT_OPEN_FILE) if the function could not open the file for any reason
 * \@return  -3 (INVALID_INPUT)  if each of the inputs has an invalid value
 * \@return  -4 (UNSUCCEED_PROCESS) if process failed because of an unpredicted problem
 * \@return   1 (SUCCEED_PROCESS) if function finish its task correctly
 *
 */
int seller_log_out(struct SELLER * seller);


/** \brief Use this function for create new seller profile
 *
 * \@param[in]  id of new seller
 * \@param[in]  name of new seller
 * \@param[in]  password of new seller
 *
 * \@return  the output is depends on result_code.h:
 * \@return  -1 (CANT_OPEN_FILE) if the function could not open the file for any reason
 * \@return  -2 (DUPLICATE_DATA) if current seller id has signed up before
 * \@return  -3 (INVALID_INPUT)  if each of the inputs has an invalid value
 * \@return   1 (SUCCEED_PROCESS) if function finish its task correctly
 *
 */
int seller_sign_up(int seller_id , char* name ,char * pass);


/** \brief this function will show total revenue of current seller
 * \@param[in]  an instance of SELLER structure
 *
 * \@return  the output is depends on result_code.h:
 * \@return  -3 (INVALID_INPUT)  if each of the inputs has an invalid value
 * \@return   1 (SUCCEED_PROCESS) if function finish its task correctly
 *
 */
int show_revenue(struct SELLER* seller);


/** \brief this function will update total revenue of current seller
 *
 * \@param[in]  an instance of SELLER structure
 * \@param[in]  amount of change in total revenue
 *
 * \@return  the output is depends on result_code.h:
 * \@return  -3 (INVALID_INPUT)  if each of the inputs has an invalid value
 * \@return  -4 (UNSUCCEED_PROCESS) if process failed because of an unpredicted problem
 * \@return   1 (SUCCEED_PROCESS) if function finish its task correctly
 */
int update_revenue(int seller_id, float price);
/** \brief this function will change password of current seller
 *  \@param[in]  an instance of SELLER structure
 *
 * \@return  the output is depends on result_code.h
 * \@return  -3 (INVALID_INPUT)  if each of the inputs has an invalid value
 * \@return  -4 (UNSUCCEED_PROCESS) if process failed because of an unpredicted problem
 * \@return   1 (SUCCEED_PROCESS) if function finish its task correctly
 *
 */
int seller_change_password(struct SELLER **seller);


/** \brief this function will change name of current seller
 *  \@param[in]  an instance of SELLER structure
 *
 * \@return  the output is depends on result_code.h
 * \@return  -3 (INVALID_INPUT)  if each of the inputs has an invalid value
 * \@return  -4 (UNSUCCEED_PROCESS) if process failed because of an unpredicted problem
 * \@return   1 (SUCCEED_PROCESS) if function finish its task correctly
 */
int seller_change_name(struct SELLER ** seller);
#endif // SELLER_MANAGER_H_INCLUDED
