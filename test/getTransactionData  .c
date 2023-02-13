#include<time.h>
#include "../STD_types.h"

typedef struct ST_terminalData_t
{
     f32_t transAmount;
     f32_t maxTransAmount;
     uint8_t transactionDate[10];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
     TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD,
     INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;


EN_terminalError_t getTransactionDate (ST_terminalData_t *terminalData)
{   time_t Time = time (NULL);
     struct tm* date = localtime(&Time);
     
     printf("Transaction Date: %d / %d / %d\n", date->tm_mday, date->tm_mon+1, date->tm_year+1900);
     
terminalData->transactionDate[0]=date->tm_mday/10;
terminalData->transactionDate[1]=date->tm_mday%10;          // i cant put the time in array 
terminalData->transactionDate[3]=(date->tm_mon+1)/10;
terminalData->transactionDate[4]=(date->tm_mon+1)%10;
terminalData->transactionDate[6]=(date->tm_year+1900)/1000;
terminalData->transactionDate[7]=0;
terminalData->transactionDate[8]=(date->tm_year+1900)%10;
terminalData->transactionDate[9]=(date->tm_year+1900)%10;
}


void main (void)
{   char feedback1,i;
    ST_terminalData_t terminaldata;
        printf("\t\t welcome\n");
    char *terminalData = &terminaldata;
    
    feedback1= getTransactionDate (terminalData);
    //exit(feedback1=0);
  
} 