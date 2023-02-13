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

EN_cardError_t getCardPAN (ST_cardData_t *cardData)
{   printf ("please enter the PAN number :");
    scanf(" %s",&cardData->primaryAccountNumber);

    if(strlen(cardData->primaryAccountNumber)>19||strlen(cardData->primaryAccountNumber)<16)
    {
        printf("WRONG PAN"); 
        return WRONG_PAN;}  
else
{
    printf("CARD OK");
    return CARD_OK;
}}


void main (void)
{   char feedback1;
    ST_cardData_t userdata;
    ST_cardData_t *cardData = &userdata;
    
            printf("\t\t welcome\n");
    getCardPAN (cardData);

} 