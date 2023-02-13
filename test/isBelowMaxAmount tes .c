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

EN_terminalError_t setMaxAmount (ST_terminalData_t *terminalData)
{
    printf("please enter the max allowable transfer amount : ");
    scanf(" %f",&terminalData->maxTransAmount);
    if (terminalData->maxTransAmount<=0)
    {
        printf("INVALID_MAX_AMOUNT");
        return INVALID_MAX_AMOUNT;
    }
    else 
    return TERMINAL_OK;
    
}


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
    return TERMINAL_OK;
    
}


EN_terminalError_t isBelowMaxAmount (ST_terminalData_t *terminalData)
{

if (terminalData->transAmount>terminalData->maxTransAmount)
{
    printf("EXCEED_MAX_AMOUNT");
    return EXCEED_MAX_AMOUNT;
}
else 
    return TERMINAL_OK;
    
}



void main (void)
{   char feedback1,i;
    ST_terminalData_t terminaldata;
        printf("\t\t welcome\n");
    char *terminalData = &terminaldata;
    getTransactionAmount (terminalData);
    setMaxAmount (terminalData);
    if (isBelowMaxAmount(terminalData)==TERMINAL_OK)
    printf (" thank you\n%f\n%f ",terminaldata.transAmount,terminaldata.maxTransAmount);
 


    

  
} 