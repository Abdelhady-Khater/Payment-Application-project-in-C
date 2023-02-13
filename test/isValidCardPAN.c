#include<stdio.h>
#include <string.h>
#include "../STD_types.h"


typedef struct ST_cardData_t
{
     char cardHolderName[25];
     char primaryAccountNumber[20];
    char cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
     CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

typedef enum EN_terminalError_t
{
     TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD,
     INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

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


EN_terminalError_t isValidCardPAN (ST_cardData_t *cardData)
{

    uint16_t sum = 0;
    uint8_t PANlength;
    uint16_t counter = 1;
    uint16_t PANdigits[20] = { 0 };  // i didnt get it 

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
        printf("Valid card\n");
        return CARD_OK;
    }
    else
    {
        printf("not Valid card\n");
return INVALID_CARD;
    }
        
    
}


void main (void)
{  
ST_cardData_t userdata; 
char *cardData = &userdata;


    getCardPAN(cardData);
    isValidCardPAN(cardData);
}