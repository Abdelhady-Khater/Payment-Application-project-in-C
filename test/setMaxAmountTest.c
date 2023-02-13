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

EN_terminalError_t setMaxAmount (ST_terminalData_t *terminalData,f32_t maxAmount)
{
    if (maxAmount<=0)
    {
        printf("INVALID_MAX_AMOUNT");
        return INVALID_MAX_AMOUNT;
    }
    else 
    {
    terminalData->maxTransAmount=maxAmount;
    printf("TERMINAL_OK");
    return TERMINAL_OK;
    }
}


void main (void)
{   char feedback1,i;
    f32_t maxAmount;    
    ST_terminalData_t terminaldata;
    char *terminalData = &terminaldata;
    printf("\t\t welcome\n");
    printf("please enter the max allowable amount :");
    scanf(" %f",&maxAmount);
    setMaxAmount (terminalData,maxAmount);
} 