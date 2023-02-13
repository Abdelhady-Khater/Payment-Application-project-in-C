#ifndef card
#define card


#include<stdio.h>
#include <string.h>
#include<time.h>
#include "../STD_types.h"


typedef struct ST_cardData_t
{
     uint8_t cardHolderName[25];
     uint8_t cardExpirationDate[6];
     uint8_t primaryAccountNumber[20];
}ST_cardData_t;

typedef enum EN_cardError_t
{
     CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

void str2int(ST_cardData_t*cardData);
EN_cardError_t getCardHolderName (ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate (ST_cardData_t*cardData);
EN_cardError_t getCardPAN (ST_cardData_t *cardData);



#endif