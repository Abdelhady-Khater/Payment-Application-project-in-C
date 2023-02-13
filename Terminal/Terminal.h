#ifndef Terminal
#define Terminal


#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../card/card.h"
#include "../STD_types.h"


typedef struct ST_terminalData_t
{
     f32_t transAmount;
     f32_t maxTransAmount;
     uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
     TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD,
     INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate (ST_terminalData_t *terminalData);
EN_terminalError_t isCardExpired (ST_cardData_t *cardData,ST_terminalData_t *terminalData);
EN_terminalError_t getTransactionAmount (ST_terminalData_t *terminalData);
EN_terminalError_t setMaxAmount (ST_terminalData_t *terminalData,f32_t maxAmount);
EN_terminalError_t isBelowMaxAmount (ST_terminalData_t *terminalData);
EN_terminalError_t isValidCardPAN (ST_cardData_t *cardData);  








#endif