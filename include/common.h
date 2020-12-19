/*
 * common.h
 *
 *  Created on: Dec. 4, 2020
 *      Author: safatanzeem
 */

#ifndef COMMON_H_
#define COMMON_H_



#define NAME_MAX_LENGTH         20
#define ADDRESS_MAX_LENGTH      40
#define PHONE_NUM_MAX_LENGTH    10
#define MAX_ATTEMPTS            10


enum error_codes_e {

  OK                            = 0,
  EOF_REACHED                   = 2,
  ERROR_WRONG_CATEGORY          = -1,
  ERROR_WRONG_NAME              = -2,
  ERROR_NULL_POINTER            = -3,
  ERROR_PRODUCT_NUMBER_DIGITS   = -4,
  ERROR_PRICE                   = -5,
  ERROR_STOCK                   = -6,
  ERROR_INVALID_INPUT           = -7,
  ERROR_INVALID_ADDRESS         = -8,
  ERROR_INVALID_PHONE_NUMBER    = -9,
  ERROR_VALUE_ZERO              = -9


};

int validate(int val);

#endif /* COMMON_H_ */
