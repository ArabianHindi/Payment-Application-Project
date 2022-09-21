#ifndef _SERVER_C_
#define _SERVER_C_

#include <string.h>
#include <stdio.h>
#include "server.h"


ST_accountsDB_t accountsDatabase[255] = { {2000.0, "8989374615436851"} , {100000.0, "5807007076043875"} ,
									   {3000.0, "8989654136546542"} , {200000.0, "6194026051065108"} ,
									   {4000.0,"9810246516847532"} , {300000.0, "6549840620488651"} ,
									   {5000.0, "6519848789461654"} , {400000.0,"5048401202150842"} ,
									   {6000.0, "3216879846246544"} , {500000.0, "8781954150540650"} };

ST_transaction_t transactionDatabase[255] = {0};

int location,Index;


EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount(&transData->cardHolderData))
	{
		transactionDatabase[Index].transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}

	else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
	{
		transactionDatabase[Index].transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	else if (saveTransaction(transData) == SAVING_FAILED)
	{
		transactionDatabase[Index].transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}

	else
	{
		transactionDatabase[Index].transState = APPROVED;
		accountsDatabase[location].balance -= transData->terminalData.transAmount;
		printf("new balance = %.2f\n", accountsDatabase[location].balance);
		return APPROVED;
	}
}


EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	int flag = 0;
	for (location = 0; location < 255; location++)
	{
		if (strcmp((char*)cardData->primaryAccountNumber, (char*)accountsDatabase[location].primaryAccountNumber) == 0)
		{
			flag = 1;
			break;
		}
	}

	if (flag)
		return OK_SERVER;

	return ACCOUNT_NOT_FOUND;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount > accountsDatabase[location].balance)
		return LOW_BALANCE;

	return OK_SERVER;
}


EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (Index >= 255)
		return SAVING_FAILED;

	transactionDatabase[Index] = *transData;
	transactionDatabase[Index].transactionSequenceNumber = Index;
	transactionDatabase[Index].transState = APPROVED;
	Index++;
	return OK_SERVER;
}


EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	transactionDatabase->transactionSequenceNumber = 5;

	for (int i = 0; i < 255; i++)
	{
		if (transactionSequenceNumber == transactionDatabase[i].transactionSequenceNumber)
		{
			*transData = transactionDatabase[i];
			return OK_SERVER;
		}
	}
	return TRANSACTION_NOT_FOUND;
}

#endif