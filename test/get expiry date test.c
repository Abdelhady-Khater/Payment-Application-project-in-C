#include<stdio.h>
#include <string.h>
#include<time.h>
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
    scanf("%s",&cardData->cardExpirationDate);
    printf ("the expiry date is %s\n",cardData->cardExpirationDate);
    str2int(cardData); 
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

void main (void)
{   char feedback1;
    ST_cardData_t userdata;
    ST_cardData_t *cardData = &userdata;
    
    printf("\t\t welcome\n");
    
    getCardExpiryDate (cardData);
 



  
} 