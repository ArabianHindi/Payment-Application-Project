#ifndef _CARD_C_
#define _CARD_C_
#include <string.h>
#include <stdio.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Please Enter Your Name: ");
	fflush(stdin); fflush(stdout);
	gets((char*)cardData->cardHolderName);

	if (strlen((char*)cardData->cardHolderName) > 24 || strlen((char*)cardData->cardHolderName) < 20)
		return WRONG_NAME;

	return OK_CARD;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Enter your card expiration date: ");
	fflush(stdin); fflush(stdout);
	gets((char*)cardData->cardExpirationDate);

	if ((strlen((char*)cardData->cardExpirationDate)) != 5)
		return WRONG_EXP_DATE;

	return OK_CARD;
}



EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Enter the card Number: ");
	gets((char*)cardData->primaryAccountNumber);

	if ((strlen((char*)cardData->primaryAccountNumber) < 16) || (strlen((char*)cardData->primaryAccountNumber) > 19))
		return WRONG_PAN;

	return OK_CARD;
}
#endif