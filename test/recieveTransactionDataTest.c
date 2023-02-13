#include "../STD_types.h"
#include<stdio.h>
#include<string.h>
#include <time.h>

typedef enum EN_transState_t 
    { 
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD,
    FRAUD_CARD, INTERNAL_SERVER_ERROR 
    }EN_transState_t;

typedef enum EN_serverError_t 
    { 
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND,
    ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
    }EN_serverError_t;

typedef enum EN_accountState_t
    { RUNNING, BLOCKED
    }EN_accountState_t;

typedef struct ST_accountsDB_t
    { float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
    }ST_accountsDB_t;

typedef struct ST_terminalData_t
{
     f32_t transAmount;
     f32_t maxTransAmount;
     uint8_t transactionDate[11];
}ST_terminalData_t;

typedef struct ST_cardData_t
{
     uint8_t cardHolderName[25];
     uint8_t cardExpirationDate[6];
     uint8_t primaryAccountNumber[20];
}ST_cardData_t;

typedef struct ST_transaction_t
    {
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    uint32_t transactionSequenceNumber;
    EN_transState_t transState;
    }ST_transaction_t;

typedef enum EN_cardError_t
{
     CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardPAN (ST_cardData_t *cardData)
{   printf ("please enter the PAN number :");
    scanf(" %s",&cardData->primaryAccountNumber);

    if(strlen(cardData->primaryAccountNumber)>19||strlen(cardData->primaryAccountNumber)<16)
    {
    printf("WRONG PAN %s"); 
    return WRONG_PAN;
    }  
     
else
return CARD_OK;

}


EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    FILE *ptr;
    uint8_t i;
   
    ptr=fopen("accounts_DB.txt","r+");
    if (ptr!=NULL)
    {  
        for (i=0;i<=20;i++)
        {   fscanf(ptr," %s %d %f",accountRefrence->primaryAccountNumber,&accountRefrence->state,&accountRefrence->balance);
            if (!strcmp(accountRefrence->primaryAccountNumber,cardData->primaryAccountNumber))
            {   fclose(ptr);
                printf("ACCOUNT IS OK");
                return SERVER_OK;
            }
        }
        printf("ACCOUNT_NOT_FOUND");
        fclose(ptr);
        return ACCOUNT_NOT_FOUND;
    }
}



EN_serverError_t saveTransaction(ST_transaction_t *transData)
{   
    time_t Time = time (NULL);
    struct tm* date = localtime(&Time);
    
    FILE *ptr;
    ptr=fopen("Transactions DB.txt","r+");
    if (ptr!=NULL)
    {  
        fprintf(ptr, "Transaction Date:%d/%d/%d\nTransaction Amount:%.2f\nTransaction State:%s\nTerminal Max Amount:%.2f\nCardholder Name:%.2f\nPAN:%s\nCard Expiration Date:%s\n ",date->tm_mday, date->tm_mon+1, date->tm_year+1900,transData->terminalData.transAmount,transData->transState,transData->terminalData.maxTransAmount,transData->cardHolderData.cardHolderName,transData->cardHolderData.primaryAccountNumber,transData->cardHolderData.cardExpirationDate);
        fclose(ptr);
        return SERVER_OK;
    } 
    else
    {
        printf("SAVING_FAILED");
        return SAVING_FAILED;
    }
    
        
}
      

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    FILE *ptr;
    uint8_t i,status,primaryAccountNumber[20];
    float balance;
   printf("ACCOUNT  OK");
    ptr=fopen("accounts_DB.txt","r+");
    if (ptr!=NULL)
    {  
        for (i=0;i<=20;i++)
        {   fscanf(ptr," %s %d %f",primaryAccountNumber,&status,&balance);
            if (!strcmp(primaryAccountNumber,transData->cardHolderData.primaryAccountNumber))
            {   fclose(ptr);
                printf("ACCOUNT  OK");
                transData->transState==APPROVED;
            }

        }
        printf("ACCOUNT_NOT_FOUND");
        fclose(ptr);
        transData->transState==FRAUD_CARD;
        return ACCOUNT_NOT_FOUND;
    }

if(transData->terminalData.transAmount>balance)
    {
        printf("DECLINED_INSUFFECIENT_FUND");
        transData->transState==DECLINED_INSUFFECIENT_FUND;
    }


if (status==BLOCKED)
    {   printf("card is BLOCKED/STOLEN");
        transData->transState==DECLINED_STOLEN_CARD;
    }

if (saveTransaction(transData)==SAVING_FAILED)
    {
        printf("SAVING_FAILED");
        transData->transState==SAVING_FAILED;
    }

}
      


void main (void)
{  
ST_cardData_t userdata; 
char *cardData = &userdata;
ST_accountsDB_t accdata;
char *accData=&accdata;
ST_transaction_t transdata;
char *transData=&transdata;


    getCardPAN(cardData);

    recieveTransactionData(transData);
}

