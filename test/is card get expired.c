#include<time.h>
#include "../STD_types.h"
typedef struct ST_cardData_t
{
     uint8_t cardHolderName[25];
     uint8_t primaryAccountNumber[20];
     uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
     CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

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


void str2int(ST_cardData_t*cardData)
{
    int i;
    for (i=0;i<5;i++)
    {   if (i!=2)
        {
            cardData->cardExpirationDate[i]=cardData->cardExpirationDate[i]-48;
    }
    }
}

EN_cardError_t getCardExpiryDate (ST_cardData_t *cardData)
{   char again;


    printf("please enter the card expiry date as MM/YY :\n");
    scanf("\t\t%s",&cardData->cardExpirationDate);
    str2int(cardData);                             // there is issue if i use &cardData
    if(strlen(cardData->cardExpirationDate)>5||cardData->cardExpirationDate[2]!='/')
    {
    printf("WRONG FORMAT");
    return WRONG_EXP_DATE;
    }   
    
    else if ((cardData->cardExpirationDate[0])*10 + cardData->cardExpirationDate[1]>12||(cardData->cardExpirationDate[0])+cardData->cardExpirationDate[1]<1)
    {
    printf("WRONG DATE");
    return WRONG_EXP_DATE;
    }
    
else
return CARD_OK;
}


EN_terminalError_t getTransactionDate (ST_terminalData_t *terminalData)
{   time_t Time = time (NULL);
     struct tm* date = localtime(&Time);
     
     printf("Current Date: %d / %d / %d\n", date->tm_mday, date->tm_mon+1, date->tm_year+1900);
     
terminalData->transactionDate[0]=date->tm_mday/10;
terminalData->transactionDate[1]=date->tm_mday%10;          // i cant put the time in array 
terminalData->transactionDate[3]=(date->tm_mon+1)/10;
terminalData->transactionDate[4]=(date->tm_mon+1)%10;
terminalData->transactionDate[6]=(date->tm_year+1900)/1000;
terminalData->transactionDate[7]=0;
terminalData->transactionDate[8]=(date->tm_year+1900)%10;
terminalData->transactionDate[9]=(date->tm_year+1900)%10;
}


EN_terminalError_t isCardExpired (ST_cardData_t *cardData,ST_terminalData_t *terminalData)
{   char month_check,year_check;
    month_check=((10*terminalData->transactionDate[3])+terminalData->transactionDate[4])>=(cardData->cardExpirationDate[0])*10 + cardData->cardExpirationDate[1];
    year_check=((10*terminalData->transactionDate[8])+terminalData->transactionDate[9])>=(cardData->cardExpirationDate[3])*10 + cardData->cardExpirationDate[4];
    if (month_check&&year_check)
    {printf ("card is expired");
    return  EXPIRED_CARD;
    }
    else 
    { printf ("card is ok");
    return CARD_OK;
    }
  
}




void main (void)
{

    ST_cardData_t userdata;
    char *cardData = &userdata;

    ST_terminalData_t terminaldata;
    char *terminalData = &terminaldata;

    printf("\t\t welcome\n");
    if (getCardExpiryDate (cardData)==CARD_OK)
    {getTransactionDate (terminalData);
    isCardExpired (cardData,terminalData);
    }

}
