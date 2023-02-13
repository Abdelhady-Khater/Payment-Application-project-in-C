#include "server.h"
#define max_length 10000
uint8_t account_state;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (account_state==ACCOUNT_NOT_FOUND) {
		transData->transState = ACCOUNT_NOT_FOUND;
		return DECLINED_STOLEN_CARD;
	}
    if (account_state==BLOCKED_ACCOUNT) {
	transData->transState = DECLINED_STOLEN_CARD;
	return DECLINED_STOLEN_CARD;
    }
	if (account_state==LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
    if (account_state==SAVING_FAILED) {
		transData->transState = SAVING_FAILED;
		return SAVING_FAILED;
	}
	transData->transState = APPROVED;
	return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    FILE *ptr;
    uint8_t i;
   
    ptr=fopen("../accounts_DB.txt","r+");
    if (ptr!=NULL)
    {  
        for (i=0;i<=20;i++)
        {   fscanf(ptr," %s %d %f",accountRefrence->primaryAccountNumber,&accountRefrence->state,&accountRefrence->balance);
            if (!strcmp(accountRefrence->primaryAccountNumber,cardData->primaryAccountNumber))
            {   fclose(ptr);
                return SERVER_OK;
            }
        }
        printf("ACCOUNT_NOT_FOUND");
        fclose(ptr);
        account_state==ACCOUNT_NOT_FOUND;
        return ACCOUNT_NOT_FOUND;
    }
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    if (accountRefrence->state==RUNNING)
        return SERVER_OK; 
    else 
    {
        printf("card is blocked/stolen");
        account_state==BLOCKED_ACCOUNT;
        return BLOCKED_ACCOUNT;
    }
}


EN_serverError_t isAmountAvailable (ST_terminalData_t *terminalData, ST_accountsDB_t *accountRefrence)
{   uint16_t net;
    net=(accountRefrence->balance)-(terminalData->transAmount);
    if(terminalData->transAmount>accountRefrence->balance)
    {
        printf("LOW_BALANCE");
        account_state==LOW_BALANCE;
        return LOW_BALANCE;
    }
    else
    {   printf("the balance before the transaction =%.2f\n",accountRefrence->balance);
        printf("the balance after the transaction =%d\n",net);
            FILE *ptr;
            ptr=fopen("../accounts_DB.txt","r+");
        if (ptr!=NULL)
        {   fseek(ptr,21,SEEK_SET);
            fprintf(ptr, "%d",net);
            fclose(ptr);
            return SERVER_OK;
            }
        return SAVING_FAILED; 
        }
}


EN_serverError_t saveTransaction(ST_transaction_t *transData)
{   time_t Time = time (NULL);
    struct tm* date = localtime(&Time);
    FILE *ptr;
    ptr = fopen("../temp.txt", "r");
	if (!ptr) {
		return SAVING_FAILED;
	}
	int transnum;
	fscanf(ptr, "%d", &transnum);
	fclose(ptr);
	ptr = fopen("../temp.txt", "w");
	fprintf(ptr, "%d", transnum+1);
	fclose(ptr);
	transData->transactionSequenceNumber = transnum+1;
    ptr=fopen("../Transactions DB.txt","a");
    if (ptr!=NULL)
    {   
        fprintf(ptr, "Transaction Sequence Number: %d\n", transData->transactionSequenceNumber);          
        fprintf(ptr, "Transaction Date: %d/%d/%d\t%d:%d:%d\nTransaction Amount: %.2f\nTTransaction Max Amount: %.2f\nCardholder Name: %s\nPAN: %s\n",date->tm_mday, date->tm_mon+1, date->tm_year+1900,date->tm_hour,date->tm_min,date->tm_sec,transData->terminalData.transAmount,transData->terminalData.maxTransAmount,transData->cardHolderData.cardHolderName,transData->cardHolderData.primaryAccountNumber);
        fprintf(ptr, "Transaction State: ");
	    if (transData->transState == APPROVED)
        {
	        fprintf(ptr, "APPROVED\n");
	    }
	    else if (transData->transState == DECLINED_INSUFFECIENT_FUND)
        {
	        fprintf(ptr, "DECLINED_INSUFFECIENT_FUND\n");
	    }
	    else if (transData->transState == DECLINED_STOLEN_CARD)
        {
	    	fprintf(ptr, "DECLINED_STOLEN_CARD\n");
	    }
        else if (transData->transState == ACCOUNT_NOT_FOUND)
        {
	    	fprintf(ptr, "ACCOUNT_NOT_FOUND\n");
	    }
        else if (transData->transState == SAVING_FAILED)
        {
	    	fprintf(ptr, "SAVING_FAILED\n");
	    }
        fprintf(ptr,"----------------------------------------------------------------\n");
        fclose(ptr);
        return SERVER_OK;
    } 
    else
    {
        printf("SAVING_FAILED");
        account_state==SAVING_FAILED;
        return SAVING_FAILED;
    }
    
        
}

void listSavedTransactions (void)
{
    FILE *ptr;
    uint8_t line[max_length];
    ptr=fopen("../Transactions DB.txt","r+");
    if (ptr!=NULL)
    {  
        while(fgets(line, max_length, ptr))
        {
        printf(line);
        }
        fclose(ptr);
    }

}