#include<stdio.h>
#include <string.h>
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

EN_terminalError_t getTransactionAmount (ST_terminalData_t *terminalData)
{
    printf(" please enter the transaction amount ");
    scanf (" %f",&terminalData->transAmount);
    if (terminalData->transAmount<=0)
    {
        printf("INVALID_AMOUNT");
        return INVALID_AMOUNT;
    }
    else 
    {printf("TERMINAL_OK");
    return TERMINAL_OK;
    }
}



void main (void)
{   char feedback1,i;
    ST_terminalData_t terminaldata;
        printf("\t\t welcome\n");
    char *terminalData = &terminaldata;
    
    feedback1= getTransactionAmount (terminalData);
    //exit(feedback1=0);

 
} 