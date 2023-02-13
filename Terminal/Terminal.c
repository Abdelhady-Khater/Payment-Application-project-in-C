#include "Terminal.h"



EN_terminalError_t getTransactionDate (ST_terminalData_t *terminalData)
{   time_t Time = time (NULL);
    struct tm* date = localtime(&Time);
     
printf("Current Date: %d / %d / %d\n", date->tm_mday, date->tm_mon+1, date->tm_year+1900);
     
terminalData->transactionDate[0]=date->tm_mday/10;
terminalData->transactionDate[1]=date->tm_mday%10;          
terminalData->transactionDate[3]=(date->tm_mon+1)/10;
terminalData->transactionDate[4]=(date->tm_mon+1)%10;
terminalData->transactionDate[6]=(date->tm_year+1900)/1000;
terminalData->transactionDate[7]=0;
terminalData->transactionDate[8]=(date->tm_year+1900)%10;
terminalData->transactionDate[9]=(date->tm_year+1900)%10;
return TERMINAL_OK;
}


EN_terminalError_t isCardExpired (ST_cardData_t *cardData,ST_terminalData_t *terminalData)
{     
    uint8_t month_check,year_check;
          month_check=((10*terminalData->transactionDate[3])+terminalData->transactionDate[4])>=(cardData->cardExpirationDate[0])*10 + cardData->cardExpirationDate[1];
          year_check=((10*terminalData->transactionDate[8])+terminalData->transactionDate[9])>=(cardData->cardExpirationDate[3])*10 + cardData->cardExpirationDate[4];
    if (month_check&&year_check)
          {
          printf ("card is expired");
          return  EXPIRED_CARD;
          }
    else 
        return CARD_OK;
        
}


EN_terminalError_t getTransactionAmount (ST_terminalData_t *terminalData)
{
    printf("please enter the transaction amount : ");
    scanf (" %f",&terminalData->transAmount);
    if (terminalData->transAmount<=0)
    {
        printf("INVALID_AMOUNT");
        return INVALID_AMOUNT;
    }
    else 
    return TERMINAL_OK;
    
}


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
    return TERMINAL_OK;
    }
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


EN_terminalError_t isValidCardPAN (ST_cardData_t *cardData)
{

    uint16_t sum = 0;
    uint8_t PANlength;
    uint16_t counter = 1;
    uint16_t PANdigits[20] = { 0 }; 

    PANlength = strlen(cardData->primaryAccountNumber);    

    for (uint16_t i = PANlength-1 ; i > 0; i--)            
    {
        if (counter % 2 == 0)                         
        {
            uint16_t temp = (cardData->primaryAccountNumber[i] - '0') * 2; 

            if ((temp / 10) > 0)    
            {                 
                temp = (temp % 10) + 1;
                PANdigits[i] = temp;
            }
            else
            {
                PANdigits[i] = temp;
            }
        }
        else 
        {
            PANdigits[i] = (cardData->primaryAccountNumber[i] - '0');
        }
        counter++;
    }

    if (counter % 2 == 0)
    {
        uint16_t temp = (cardData->primaryAccountNumber[0] - '0') * 2;;

        if ((temp / 10) > 0)
        {
            temp = (temp % 10) + 1;
            PANdigits[0] = temp;
        }
        else
        {
            PANdigits[0] = temp;
        }
    }
    else
    {
        PANdigits[0] = (cardData->primaryAccountNumber[0] - '0');
    }

    for (uint16_t i = 0; i < PANlength; i++)
    {
        sum += PANdigits[i];
    }

    if (sum % 10 == 0)
    {
        return CARD_OK;
    }
    else
    {
        printf("not Valid card\n");
        return INVALID_CARD;
    }
        
    
}





























