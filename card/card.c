#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "../Header Files/STD_TYPES.h"
#include "card.h"
extern uint8_t Terminate;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	if (!Terminate)
	{
		printf(" Enter your name: ");
		fseek(stdin, 0, SEEK_END);
		gets(cardData->cardHolderName);

		uint8_t counter1 = 0;
		counter1 = strlen(cardData->cardHolderName);

		if (cardData->cardHolderName == NULL)
		{
			printf("WRONG_NAME\n");
			Terminate = 1;
			return  WRONG_NAME;

		}
		else if (counter1 < 20 || counter1 > 24)
		{
			printf("WRONG_NAME\n");
			Terminate = 1;
			return  WRONG_NAME;
		}

		else
			return  CARD_OK;

	}

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	if (!Terminate)
	{
		printf("Enter the card expired date : ");
		fseek(stdin, 0, SEEK_END);
		gets(cardData->cardExpirationDate);

		uint8_t counter2;
		counter2 = strlen(cardData->cardExpirationDate);

		uint8_t month = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
		uint8_t  year = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');

		if (cardData->cardExpirationDate == NULL)
		{
			printf("WRONG_EXP_DATE\n");
			Terminate = 1;
			return  WRONG_EXP_DATE;
		}
		else if ((month < 1 || month>12) || cardData->cardExpirationDate[2] != '/' || (year > 99 || year < 0))
		{
			printf("WRONG_EXP_DATE\n");
			Terminate = 1;
			return WRONG_EXP_DATE;
		}
		else if (counter2 < 5 || counter2 > 5)
		{
			printf("WRONG_EXP_DATE\n");
			Terminate = 1;
			return   WRONG_EXP_DATE;
		}
		else return  CARD_OK;
	}

}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	if (!Terminate)
	{
		printf("Enter the primaryAccountNumber : ");
		fseek(stdin, 0, SEEK_END);
		gets(cardData->primaryAccountNumber);

		uint8_t counter3;
		counter3 = strlen(cardData->primaryAccountNumber);

		for (uint8_t i = 0; i < counter3; i++)
		{
			if (cardData->primaryAccountNumber[i] >= 'a' && cardData->primaryAccountNumber[i] <= 'z' || cardData->primaryAccountNumber[i] >= 'A' && cardData->primaryAccountNumber[i] <= 'Z')
			{
				printf("WRONG_PAN\n");
				Terminate = 1;
				return   WRONG_PAN;
			}
		}
		if (counter3 < 16 || counter3 > 20)
		{
			printf("WRONG_PAN\n");
			Terminate = 1;
			return   WRONG_PAN;
		}
		else if (cardData->primaryAccountNumber == NULL)
		{
			printf("WRONG_PAN\n");
			Terminate = 1;
			return   WRONG_PAN;
		}
		else return  CARD_OK;
	}

}

void getCardHolderNameTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name : getCardHolderName\n");
	uint8_t i;
	for (i = 0; i < 4; i++)
	{
		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t result = getCardHolderName(&cardData);
		printf(" expected result:");
		scanf("%d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}


}

void getCardExpiryDateTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name :  getCardExpiryDate\n");
	uint8_t j;
	for (j = 0; j < 4; j++)
	{
		uint32_t  expected_result;
		printf("Test case %d :\n", j + 1);
		uint32_t result = getCardExpiryDate(&cardData);
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");

	}

}

void getCardPANTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name : getCardPAN\n");
	uint8_t j;
	for (j = 0; j < 4; j++)
	{

		uint32_t  expected_result;
		printf("Test case %d :\n", j + 1);
		uint32_t result = getCardPAN(&cardData);
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");


	}

}