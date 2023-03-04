#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "../Header Files/STD_TYPES.h"
#include "app.h"


ST_transaction transaction_t;
uint8_t Terminate = 0;
void appStart(void)
{



	uint32_t input1 = getCardHolderName(&cardData);
	uint32_t input2 = getCardExpiryDate(&cardData);
	uint32_t input3 = getCardPAN(&cardData);
	uint32_t input4 = getTransactionDate(&termData);
	uint32_t input = isCardExpired(&cardData, &termData);
	uint32_t input5 = getTransactionAmount(&termData);
	uint32_t input6 = setMaxAmount(&termData);
	uint32_t input7 = isBelowMaxAmount(&termData);
	//uint32_t input8 = saveTransaction(&transaction_t);
	uint32_t result = recieveTransactionData(&transaction_t);
	Terminate = 0;
	listSavedTransactions();
}