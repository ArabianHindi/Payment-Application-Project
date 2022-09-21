#ifndef _TERMINAL_C_
#define _TERMINAL_C_
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("Enter the transaction date like format DD/MM/YYYY, e.g 25/06/2022: ");
	gets(termData->transactionDate);

	if (strlen((char*)termData->transactionDate) != 10)
		return WRONG_DATE;

	return OK_TERMINAL;
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	int mon_exp, year_exp, mon_trans, year_trans;

	//get month and year of transaction        21/07/2022
	mon_trans = termData.transactionDate[3] + termData.transactionDate[4] * 10;
	year_trans = termData.transactionDate[8] + termData.transactionDate[9] * 10;

	//get month and year of expiry       04/26
	mon_exp = cardData.cardExpirationDate[0] + (cardData.cardExpirationDate[1]) * 10;
	year_exp = cardData.cardExpirationDate[3] + (cardData.cardExpirationDate[4]) * 10;

	if ((year_trans > year_exp) || ((year_trans == year_exp) && (mon_trans >= mon_exp)))
		return EXPIRED_CARD;

	return OK_TERMINAL;
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Enter the transaction amount: ");
	scanf("%f", &termData->transAmount);

	if (termData->transAmount <= 0)
		return INVALID_AMOUNT;

	return OK_TERMINAL;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;

	return OK_TERMINAL;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Enter the max amount: ");
	scanf("%f", &termData->maxTransAmount);

	if (termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;

	return OK_TERMINAL;
}

#endif