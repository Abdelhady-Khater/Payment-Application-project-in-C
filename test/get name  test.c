#include<stdio.h>
#include <string.h>

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


void main (void)
{   char feedback1;
    ST_cardData_t userdata;
    ST_cardData_t *cardData = &userdata;

    printf("\t\t welcome\n");
    
    getCardHolderName (cardData);
    printf ("the card holder name is %s",userdata.cardHolderName);

  
} 