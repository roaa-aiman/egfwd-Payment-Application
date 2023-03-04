#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "../Header Files/STD_TYPES.h"
#include "server.h"
extern uint8_t Terminate;

ST_accountsDB_t accountsDB[MAX_ACCOUNTS] = { {1000, RUNNING,"4567 6543 1423 4321"},
								{5000, RUNNING, "8972 4569 3745 2398"},
								{3000, BLOCKED, "8989 3746 1543 6851"},
								{2000, RUNNING, "7894 5612 3123 6798"},
								{9000, BLOCKED, "6798 4509 3487 2349"},
								{7000, RUNNING, "3216 5498 7456 1327"},
								{6000, BLOCKED, "6547 8912 3654 9873"},
								{1000, BLOCKED, "6458 5413 2168 7874"},
								{4000, RUNNING, "1368 7132 3216 5487"},
								{8000, RUNNING, "4367 6443 1443 4521"} };

ST_transaction  transaction_t[MAX_transaction] = { 0 };
static uint32_t AccountDBIndex = 0;
static uint32_t state;

EN_transStat_t recieveTransactionData(ST_transaction* transData)
{
	if (isValidAccount(&cardData) == ACCOUNT_NOT_FOUND)
	{
		printf("FRAUD_CARD\n");
		state = FRAUD_CARD;
		return FRAUD_CARD;
	}

	else if (isAmountAvailable(&termData) == LOW_BALANCE)
	{
		printf("DECLINED_INSUFFECIENT_FUND\n");
		state = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	else if (isBlockedAccount() == BLOCKED_ACCOUNT)
	{
		printf("DECLINED_STOLEN_CARD\n");
		state = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	else
	{
		if (saveTransaction(transData) == SAVING_FAILED)
		{
			printf("INTERNAL_SERVER_ERROR\n");
			state = INTERNAL_SERVER_ERROR;
			return  INTERNAL_SERVER_ERROR;
		}
		else
		{
			accountsDB[AccountDBIndex].balance -= transData->terminalData.transAmount;
			printf("Transaction is successful!\n");
			printf("the reminder balance %f \n", accountsDB[AccountDBIndex].balance);
			state = APPROVED;
			return APPROVED;
		}
	}

}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	if (!Terminate) {
		uint8_t flag = 0;
		uint8_t j = 0;
		for (j = 0; j < 10; j++)
		{
			if (strcmp(cardData->primaryAccountNumber, accountsDB[j].primaryAccountNumber) == 0)
			{
				AccountDBIndex = j;
				flag = 1;
			}
		}
		if (flag)
		{
			return SERVER_OK;
		}
		else
		{
			printf("ACCOUNT_NOT_FOUND\n");
			Terminate = 1;
			return ACCOUNT_NOT_FOUND;
		}
	}
}

EN_serverError_t isBlockedAccount(void)
{
	if (!Terminate) {
		if (accountsDB[AccountDBIndex].state == BLOCKED)
		{
			Terminate = 1;
			printf("BLOCKED_ACCOUNT\n");
			return BLOCKED_ACCOUNT;
		}
		else
		{
			return SERVER_OK;
		}
	}
}


EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (!Terminate) {
		if ((termData->transAmount) > accountsDB[AccountDBIndex].balance)
		{
			Terminate = 1;
			printf("LOW_BALANCE\n");
			return LOW_BALANCE;
		}
		else
		{
			return SERVER_OK;
		}
	}
}

EN_serverError_t saveTransaction(ST_transaction* transData)
{

	if (!Terminate) {

		memcpy(transData->terminalData.transactionDate, termData.transactionDate, 10);
		transData->terminalData.transAmount = termData.transAmount;
		transData->terminalData.maxTransAmount = termData.maxTransAmount;

		memcpy(transData->cardHolderData.cardHolderName, cardData.cardHolderName, 24);
		memcpy(transData->cardHolderData.primaryAccountNumber, cardData.primaryAccountNumber, 20);
		memcpy(transData->cardHolderData.cardExpirationDate, cardData.cardExpirationDate, 6);

		transData->transactionSequenceNumber++;
		return SERVER_OK;

	}
	else
	{
		Terminate = 1;
		//printf("SAVING_FAILED\n");
		return SAVING_FAILED;
	}

}

void listSavedTransactions(void)
{

	printf("#########################\n");
	printf("Transaction Sequence Number : %d \n ", transaction_t->transactionSequenceNumber);
	printf("Transaction Date     : %s\n", transaction_t->terminalData.transactionDate);
	printf("Transaction Amount   : %f\n", transaction_t->terminalData.transAmount);
	printf("Transaction State    : %d\n", state);
	printf("Terminal Max Amount  : %f\n", transaction_t->terminalData.maxTransAmount);
	printf("Cardholder Name      : %s\n", transaction_t->cardHolderData.cardHolderName);
	printf("PAN                  : %s\n", transaction_t->cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date : %s\n", transaction_t->cardHolderData.cardExpirationDate);
	printf("#################################\n");


}


void recieveTransactionDataTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name :  recieveTransactionDataTest\n");
	uint8_t i;
	for (i = 0; i < 1; i++)
	{
		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t input1 = getCardHolderName(&cardData);
		uint32_t input2 = getCardExpiryDate(&cardData);
		uint32_t input3 = getCardPAN(&cardData);
		uint32_t input4 = getTransactionDate(&termData);
		uint32_t input = isCardExpired(&cardData, &termData);
		uint32_t input5 = getTransactionAmount(&termData);
		uint32_t input6 = setMaxAmount(&termData);
		uint32_t input7 = isBelowMaxAmount(&termData);
		uint32_t input8 = saveTransaction(&transaction_t);
		uint32_t result = recieveTransactionData(&transaction_t);
		Terminate = 0;
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}

}
void isValidAccountTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name :  isValidAccountTest\n");
	uint8_t i;
	for (i = 0; i < 1; i++)
	{

		uint32_t input = getCardPAN(&cardData);
		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t result = isValidAccount(&cardData);
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}
}

void isBlockedAccountTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name :  isBlockedAccountTest\n");
	uint8_t i;
	for (i = 0; i < 1; i++)
	{
		uint32_t input = getCardPAN(&cardData);
		uint32_t input1 = isValidAccount(&cardData);
		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t result = isBlockedAccount();
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}
}

void isAmountAvailableTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name :  isAmountAvailableTest\n");
	uint8_t i;
	for (i = 0; i < 1; i++)
	{
		uint32_t input1 = getCardPAN(&cardData);
		uint32_t input2 = isValidAccount(&cardData);
		uint32_t input3 = getTransactionAmount(&termData);
		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t result = isAmountAvailable(&termData);
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}
}

void saveTransactionTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name :  saveTransactionTest\n");
	uint8_t i;
	for (i = 0; i < 1; i++)
	{

		uint32_t  expected_result;
		printf("Test case %d :\n", i + 1);
		uint32_t input1 = getCardHolderName(&cardData);
		uint32_t input2 = getCardExpiryDate(&cardData);
		uint32_t input3 = getCardPAN(&cardData);
		uint32_t input4 = getTransactionDate(&termData);
		uint32_t input = isCardExpired(&cardData, &termData);
		uint32_t input5 = getTransactionAmount(&termData);
		uint32_t input6 = setMaxAmount(&termData);
		uint32_t input7 = isBelowMaxAmount(&termData);
		uint32_t result = saveTransaction(&transaction_t);
		Terminate = 0;
		printf(" expected result:");
		scanf(" %d", &expected_result);
		printf("actual result:%d\n", result);
		printf("\n");
	}
}

void listSavedTransactionsTest(void)
{
	printf("Tester NAME : Roaa aiman \n");
	printf("Function Name : listSavedTransactionsTest\n");
	uint8_t i;
	for (i = 0; i < 1; i++)
	{
		printf("Test case %d :\n", i + 1);
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
		printf("\n");
	}
}