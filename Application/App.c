#include "../card/card.c"
#include "../Terminal/Terminal.c"
#include "../server/server.c"
#include "app.h"


void main (void)
{   uint8_t feedback1,feedback2,feedback3,again;
    f32_t maxAmount;

    ST_cardData_t userdata; 
    uint8_t *cardData = &userdata;

    ST_terminalData_t terminaldata;
    uint8_t *terminalData = &terminaldata;

    ST_accountsDB_t accountdata;
    uint8_t *accountData=&accountdata;
    
    ST_transaction_t transdata;
    uint8_t *transData=&transdata;
    

first:
    printf("\t\t welcome\n");
if(getCardHolderName (cardData)==CARD_OK)
    {
     if(getCardExpiryDate (cardData)==CARD_OK)
        { 
         if(getCardPAN (cardData)==CARD_OK)
            { if (isValidCardPAN(cardData)==CARD_OK)
                { getTransactionDate(terminalData);
               if ( isCardExpired (cardData,terminalData)==CARD_OK)
                    {
                        isValidAccount(cardData,accountData);
                        if (isBlockedAccount(accountData)==SERVER_OK)
                            {getTransactionAmount (terminalData);
                            printf("please enter the max allowable transfer amount : ");
                            scanf(" %f",&maxAmount);
                            setMaxAmount(terminalData,maxAmount);
                            if (isBelowMaxAmount(terminalData)==TERMINAL_OK && isAmountAvailable(terminalData,accountData)==SERVER_OK)
                                {
                                transdata.cardHolderData = userdata;
	                            transdata.terminalData = terminaldata;
                                recieveTransactionData(transData);
                                saveTransaction(transData);
                                printf("\ndo you want to see the saved transcations data ? y/n\n");
                                scanf("%s",&again);
                                if (again == 'y')
                                listSavedTransactions();
                                printf("\ndo you want to exit ? y/n\n");
                                scanf("%s",&again);
                                if (again != 'y')
                                goto first;
                                printf("\t\tTHANK YOU");
                            }  
                        }
                    }
                }
            }
        }
    }
}


     






   