#ifndef APP_C_
#define APP_C_
#include "app.h"

void appStart(void)
{
	ST_transaction_t transactionData;
	ST_cardData_t* cardData = &transactionData.cardHolderData;

	if (getCardHolderName(cardData))
	{
		printf("WRONG_NAME");
		return;
	}

	if (getCardExpiryDate(cardData))
	{
		printf("WRONG_EXP_DATE");
		return;
	}
	if (getCardPAN(cardData))
	{
		printf("WRONG_PAN");
		return;
	}
	

	ST_terminalData_t* termData = &transactionData.terminalData;


	if (getTransactionDate(termData))
	{
		printf("WRONG_DATE");
		return;
	}

	if (isCardExpired(cardData,termData))
	{
		printf("EXPIRED_CARD");
		return;
	}



	if (getTransactionAmount(termData))
	{
		printf("INVALID_AMOUNT");
		return;
	}


	if (setMaxAmount(termData))
	{
		printf("INVALID_MAX_AMOUNT");
		return;
	}

	if (isBelowMaxAmount(termData))
	{
		printf("EXCEED_MAX_AMOUNT");
		return;
	}



	switch (recieveTransactionData(&transactionData))
	{
	case DECLINED_STOLEN_CARD:
		printf("DECLINED_STOLEN_CARD");
		break;

	case DECLINED_INSUFFECIENT_FUND:
		printf("DECLINED_INSUFFECIENT_FUND");
		break;

	case INTERNAL_SERVER_ERROR:
		printf("INTERNAL_SERVER_ERROR");
		break;

	case APPROVED:
		printf("transaction is APPROVED");
		break;
	}

}

#endif