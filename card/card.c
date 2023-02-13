#include "card.h"

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


EN_cardError_t getCardHolderName (ST_cardData_t *cardData)
{   
    printf ("please enter your name : \n");
    scanf  (" %[^\n]",&cardData->cardHolderName);      /* i cant overwrite  using fgets(&cardData->cardHolderName, 25 , stdin);  */

if (strlen(cardData->cardHolderName)>25||strlen(cardData->cardHolderName)<20)   
   
    {  printf ("WORNG NAME\n");
        return WRONG_NAME;
    } 
else
return CARD_OK;
}


EN_cardError_t getCardExpiryDate (ST_cardData_t *cardData)
{   char again;


    printf("please enter the card expiry date as MM/YY :\n");
    scanf("%s",&cardData->cardExpirationDate);
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




