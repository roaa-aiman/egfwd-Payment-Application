#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "../Header Files/STD_TYPES.h"
#include "terminal.h"
extern uint8_t Terminate;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	if (!Terminate) {
		printf("Enter the transactionDate : ");
		fseek(stdin, 0, SEEK_END);
		gets(termData->transactionDate);

		uint8_t counter1;
		uint8_t day = (termData->transactionDate[0] - '0') * 10 + (termData->transactionDate[1] - '0');
		uint8_t month = (termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0');
		uint8_t year = (termData->transactionDate[6] - '0') * 1000 + (termData->transactionDate[7] - '0') * 100 + (termData->transactionDate[8] - '0') * 10 + termData->transactionDate[9] - '0';
		counter1 = strlen(termData->transactionDate);
		if ((day < 1 || day >31) || termData->transactionDate[2] != '/' || (month < 1 || month>12) || termData->transactionDate[5] != '/' || (year > 9999 || year < 0))
		{
			printf("WRONG_DATE\n");
			Terminate = 1;
			return WRONG_DATE;
		}
		else if (termData->transactionDate == NULL)
		{
			printf("WRONG_DATE\n");
			Terminate = 1;
			return WRONG_DATE;
		}
		else if (counter1 < 10 || counter1 > 10)
		{
			printf("WRONG_DATE\n");
			Terminate = 1;
			return   WRONG_DATE;
		}
		else return  TERMINAL_OK;

	}
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	if (!Terminate) {
		int card_month = (cardData->cardExpirationDate[0] - '0') * 10 + cardData->cardExpirationDate[1] - '0';
		int card_year = (cardData->cardExpirationDate[3] - '0') * 10 + cardData->cardExpirationDate[4] - '0' + 2000; ;
		int term_month = (termData->transactionDate[3] - '0') * 10 + termData->transactionDate[4] - '0';
		int term_year = (termData->transactionDate[6] - '0') * 1000 + (termData->transactionDate[7] - '0') * 100 + (termData->transactionDate[8] - '0') * 10 + +termData->transactionDate[9] - '0';

		if (term_year > card_year)
		{
			printf("EXPIRED_CARD\n");
			Terminate = 1;
			return EXPIRED_CARD;
		}
		else if (term_month > card_month && card_year == term_year)
		{
			printf("EXPIRED_CARD\n");
			Terminate = 1;
			return  EXPIRED_CARD;
		}
		else return TERMINAL_OK;
	}

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	if (!Terminate) {
		printf("Enter the transtion amount : ");
		scanf("%f", &termData->transAmount);

		if (termData->transAmount <= 0)
		{
			printf("INVALID_AMOUNT\n");
			Terminate = 1;
			return INVALID_AMOUNT;
		}
		else return  TERMINAL_OK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	if (!Terminate)
	{
		float maxTransAmount;
		printf("Enter transaction maximum amount: ");
		scanf("%f", &maxTransAmount);
		if (maxTransAmount <= 0)
		{
			printf("INVALID_MAX_AMOUNT\n");
			Terminate = 1;
			return INVALID_MAX_AMOUNT;
		}
		else
		{
			termData->maxTransAmount = maxTransAmount;
			return TERMINAL_OK;
		}
	}

}

EN_terminalError_t  isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (!Terminate)
	{
		if (termData->transAmount > termData->maxTransAmount)

		{
			printf("EXCEED_MAX_AMOUNT\n");
			Terminate = 1;
			return EXCEED_MAX_AMOUNT;
		}
		else return TERMINAL_OK;
	}

}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{

	uint8_t counter3;
	counter3 = strlen(cardData->primaryAccountNumber);
	uint32_t sum_even = 0;
	uint32_t sum_odd = 0;
	uint32_t total_sum = 0;
	for (uint8_t i = counter3 - 1; i >= 0; i--)
	{
		uint32_t Number;
		Number = cardData->primaryAccountNumber[i] - '0';

		if (i % 2 == 0)
			sum_even += 2 * Number;
		else
			sum_odd += Number;

	}
	total_sum = sum_even + sum_odd;
	if (total_sum % 10 == 0)
		return INVALID_CARD;
	else TERMINAL_OK;

}




void getTransactionDateTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name : getTransactionDate\n");
	uint8_t i;
	for (i = 0; i < 4; i++)
	{
		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t result = getTransactionDate(&termData);
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}

}
void isCardExpriedTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name : isCardExpried\n");
	uint8_t i;
	for (i = 0; i < 4; i++)

	{
		uint32_t input1 = getTransactionDate(&termData);
		uint32_t input2 = getCardExpiryDate(&cardData);
		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t result = isCardExpired(&cardData, &termData);
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}
}

void getTransactionAmountTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name : getTransactionDate\n");
	uint8_t i;
	for (i = 0; i < 4; i++)
	{

		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t result = getTransactionAmount(&termData);
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}
}
void setMaxAmountTest(void)
{

	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name : setMaxAmountTest\n");
	uint8_t i;
	for (i = 0; i < 4; i++)
	{

		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t result = setMaxAmount(&termData);
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}
}

void isBelowMaxAmountTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name : isBelowMaxAmountTest\n");
	uint8_t i;

	for (i = 0; i < 4; i++)
	{
		uint32_t input1 = getTransactionAmount(&termData);
		uint32_t input2 = setMaxAmount(&termData);
		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t result = isBelowMaxAmount(&termData);
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}

}


void isValidCardPANTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name : isValidCardPAN\n");
	uint8_t i;
	for (i = 0; i < 5; i++)
	{
		uint32_t input1 = getCardPAN(&cardData);
		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t result = isValidCardPAN(&cardData);
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}
}