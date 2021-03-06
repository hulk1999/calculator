#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#define MAX_LENGTH 500+2
// The limitation for number of digits is ~500

//Because M_PI doesn't work with some compilers
#define PI 3.14159265359 

//////////////////// Declaration /////////////////////

///// Functionalities /////

// Conversion
void getAbs(char* inputRealNum);
int convertCharToInt(char inputChar);
char convertIntToChar(int inputNum);

double convertStringToDouble(char* inputChar);
void convertDoubleToString(double inputDouble, char* result);

double convertRadianToDegree(double inputNum);
double convertDegreeToRadian(double inputNum);
// Shifting
void shiftLeft(char* inputRealNum);

// Default: inputRealNum[0] = '0'
// Returns 1 if shift successfully
int shiftRight(char* inputRealNum);

int pushBack(char* inputRealNum, char newChar); // returns 1 if push successfully
void popBack(char* inputRealNum);

void eliminateRightZero(char* inputRealNum);
void roundRealNum(char* inputRealNum);
void eliminateLeftZero(char* inputRealNum);
void eliminateAllZeros(char* inputRealNum);

int balanceNumOfDigits(char* realNum1, char* realNum2);

// Others
int isRealNumber(char* inputRealNum);
int isDouble(char* inputRealNum);
int min2Int(int a, int b);
int max2Int(int a, int b);
int compareRealNum(char* realNum1	, char* realNum2);

void multiplyByNum(int Num, char* realNum, char* result);
int multiplyTenfold(char* realNum); // returns 1 if multiply successfully
int divideTenfold(char* realNum);	// returns 1 if divide successfully

void swapDigits(char* digitNum1, char* digitNum2);
void swapStrings(char* realNum1, char* realNum2);

// It's best not to pass literal strings such as ""123.456"" to the parameters!!! 
///// Math Operations /////
void addRealNum(char* realNum1, char* realNum2, char* result); 
void subtractRealNum(char* realNum1, char* realNum2, char* result);
void multiplyRealNum(char* realNum1, char* realNum2, char* result);
void divideRealNum(char* dividend, char* divisor, char* result);
void powerRealNum(char* realNum1, char* realNum2, char* result);
void getFactorial(char* intNum, char* result);

void divideForIntegral(char* strIn1, char* strIn2, char* strOut);
void divideForFractional(char* strIn1, char* strIn2, char* strOut);

///// Trigonometric Functions /////
// Only works with double variables
void getSinRadian(char* realNum, char* result); 
void getCosRadian(char* realNum, char* result);
void getTanRadian(char* realNum, char* result);
void getCotRadian(char* realNum, char* result);

void getSinDegree(char* realNum, char* result); 
void getCosDegree(char* realNum, char* result);
void getTanDegree(char* realNum, char* result);

///// Logarithmic Functions /////
// Only works with double variables
void getLog10(char* realNum, char* result);
void getNaturalLog(char* realNum, char* result);
void getLogN(char* realNum, char* base, char* result);
//////////////////////////////////////////////////////


////////////////////////////////////////////////////// MAIN //////////////////////////////////////////////////////

//int main(int argc, char *argv[]) {
//	char inputNum1[MAX_LENGTH], inputNum2[MAX_LENGTH], result[MAX_LENGTH];
//	strcpy(result, "");
//	do
//	{
//	scanf("%s %s", &inputNum1, &inputNum2);

//	addRealNum(inputNum1, inputNum2, result);
//	printf("%s + %s = %s\n\n", inputNum1, inputNum2, result);
//	subtractRealNum(inputNum1, inputNum2, result);
//	printf("%s - %s = %s\n\n", inputNum1, inputNum2, result);
//	
//	multiplyRealNum(inputNum1, inputNum2, result);
//	printf("%s * %s = %s\n\n", inputNum1, inputNum2, result);
//	
//	divideRealNum(inputNum1, inputNum2, result);
//	printf("%s / %s = %s\n\n", inputNum1, inputNum2, result);
//
//	powerRealNum(inputNum1, inputNum2, result);
//	printf("%s ^ %s = %s\n\n", inputNum1, inputNum2, result);
//	
//	getFactorial(inputNum1, result);
//	printf("%s! = %s\n\n", inputNum1, result);	

//	getSinRadian(inputNum1, result);
//	printf("sin(%s) = %s(Radian)\n\n", inputNum1, result);	
//	getCosRadian(inputNum1, result);
//	printf("cos(%s) = %s(Radian)\n\n", inputNum1, result);	
//	getTanRadian(inputNum1, result);
//	printf("tan(%s) = %s(Radian)\n\n", inputNum1, result);	
//	getCotRadian(inputNum1, result);
//	printf("cot(%s) = %s(Radian)\n\n", inputNum1, result);	
//	
//	getSinDegree(inputNum1, result);
//	printf("sin(%s) = %s(Degree)\n\n", inputNum1, result);	
//	getCosDegree(inputNum1, result);
//	printf("cos(%s) = %s(Degree)\n\n", inputNum1, result);	
//	getTanDegree(inputNum1, result);
//	printf("tan(%s) = %s(Degree)\n\n", inputNum1, result);	
//	
//	getLog10(inputNum1, result);
//	printf("log(%s) = %s\n\n", inputNum1, result);	
//	getNaturalLog(inputNum1, result);
//	printf("logE(%s) = %s\n\n", inputNum1, result);
//	getLogN(inputNum1, inputNum2, result);
//	printf("log(%s,%s) = %s\n\n", inputNum1, inputNum2, result);
//
//	} while(1);
//	return 0;
//}


////////////////////////////////////////////////////// Conversion //////////////////////////////////////////////////////
void getAbs(char* inputRealNum)
{
	if(inputRealNum[0] == '-') shiftLeft(inputRealNum);
}
int convertCharToInt(char inputChar)
{
	return (int)inputChar - 48;
}

char convertIntToChar(int inputNum)
{
	return (char)(inputNum + 48);
}


double convertStringToDouble(char* inputChar)
{
	int count = 0, negative = 0;
	double result = 0;

	if(inputChar[0] == '-')
	{
		negative = 1;
		shiftLeft(inputChar);
		
	}
	if(strcmp(inputChar, "0") == 0) return 0.0;
	if(!isRealNumber(inputChar))
	{
		pushBack(inputChar, '.');
		pushBack(inputChar, '0');
	}
	
	int numLength = strlen(inputChar);
	int multiplyer, dotPosition = isRealNumber(inputChar);;
	for(count = 0; count < numLength; count++) 
	{
		multiplyer = dotPosition - count;
		if(inputChar[count] != '.')
			result += convertCharToInt(inputChar[count]) * pow(10, multiplyer - (multiplyer > 0));
	}
	if(negative)
	{
		result = - result;
		shiftRight(inputChar);
		inputChar[0] = '-';
	}
	return result;
}

void convertDoubleToString(double inputDouble, char* result)
{
	snprintf(result, MAX_LENGTH, "%lf", inputDouble); // stdlib.h
}

double convertRadianToDegree(double inputNum)
{
	return inputNum * PI / 180;
}
double convertDegreeToRadian(double inputNum)
{
	return inputNum / PI * 180;
}
////////////////////////////////////////////////////// Shifting //////////////////////////////////////////////////////

// Shifting string
void shiftLeft(char* inputRealNum)
{
	int numLength = strlen(inputRealNum);
	int count;
	for(count = 0; count < numLength - 1; count++)
	{
		inputRealNum[count] = inputRealNum[count + 1];
	}
	inputRealNum[numLength - 1] = '\0';

}

// inputRealNum[0] = '0' by default
int shiftRight(char* inputRealNum)
{
	int count, numLength = strlen(inputRealNum);
	if(numLength >= MAX_LENGTH) return 0;
	
	char tempRealNum[numLength + 1];
	for(count = 0; count < numLength; count++)
	{
		tempRealNum[count + 1] = inputRealNum[count];
	}
	tempRealNum[numLength + 1] = '\0';
	tempRealNum[0] = '0';
	strcpy(inputRealNum, tempRealNum);
	return 1;
}

int pushBack(char* inputRealNum, char newChar)
{
	char tempNum[MAX_LENGTH];
	int count, numLength = strlen(inputRealNum);
	if(numLength >= MAX_LENGTH) return 0;
	for(count = 0; count < numLength; count++) tempNum[count] = inputRealNum[count];
	tempNum[numLength] = newChar;
	tempNum[numLength + 1] = '\0';
	strcpy(inputRealNum, tempNum);
	return 1;
}
void popBack(char* inputRealNum)
{
	int numLength = strlen(inputRealNum);
	inputRealNum[numLength - 1] = '\0';		
}

// Change 1.000000000 to 1 
void eliminateRightZero(char* inputRealNum)
{
	int numLength = strlen(inputRealNum);
	int negative = (inputRealNum[0] == '-');
	if(!isRealNumber(inputRealNum)) return;
	if(negative) shiftLeft(inputRealNum);
	
	int dotPosition = isRealNumber(inputRealNum);
	while(numLength >= dotPosition && (inputRealNum[numLength] == '0' || inputRealNum[numLength] == '\0' 
										|| inputRealNum[numLength] == '.')) 
	{
		inputRealNum[numLength] = '\0'; 
		numLength--;
	}
	
	if(negative && (strcmp(inputRealNum, "0") != 0) )
	{
		shiftRight(inputRealNum);
		inputRealNum[0] = '-';
	}
}
void roundRealNum(char* inputRealNum)
{
	int dotPosition = isRealNumber(inputRealNum);
	if(!dotPosition) return;
	int numLength = strlen(inputRealNum);
	if(numLength - dotPosition > 10)
	{
		int count = numLength - 1, tempNum = 0, carry = 0;
		while(count > dotPosition + 10)
		{
			if(inputRealNum[count] >= '5') 
			{
				tempNum = convertCharToInt(inputRealNum[count - 1]) + 1 + carry;	
				if(tempNum >= 10) 
				{
					tempNum = 0;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				inputRealNum[count - 1] = convertIntToChar(tempNum);
			}	
			inputRealNum[count] = '\0';
			count--;
		}	
	}	
}
// Change 00001 to 1
void eliminateLeftZero(char* inputRealNum)
{
	int count, negative = 0, numLength = strlen(inputRealNum);
	if(inputRealNum[0] == '-') 
	{
		shiftLeft(inputRealNum);
		negative = 1;
	}
	
	if(inputRealNum[0] == '.') shiftRight(inputRealNum);
	
	while(inputRealNum[0] == '0' &&  isRealNumber(inputRealNum) > 1) shiftLeft(inputRealNum);
	if(!isRealNumber(inputRealNum))
	while(inputRealNum[0] == '0' &&  strlen(inputRealNum) > 1) shiftLeft(inputRealNum);
	
	if(negative)
	{
		shiftRight(inputRealNum);
		inputRealNum[0] = '-'; 
	}
}

void eliminateAllZeros(char* inputRealNum)
{
	eliminateLeftZero(inputRealNum);
	eliminateRightZero(inputRealNum);
}
// change 123.456 + 0 to 123.456 + 000.000
int balanceNumOfDigits(char* realNum1, char* realNum2)
{
	int dotPosition1 = isRealNumber(realNum1);
	int dotPosition2 = isRealNumber(realNum2);
	if(dotPosition1 == 0) dotPosition1 = strlen(realNum1);
	if(dotPosition2 == 0) dotPosition2 = strlen(realNum2);
	if(dotPosition1 + strlen(realNum2) - dotPosition2 >= MAX_LENGTH - 1 
	|| dotPosition2 + strlen(realNum1) - dotPosition1 >= MAX_LENGTH - 1)
	{
		return 0;
	}
	if(realNum1[0] == '-')
	{
		shiftLeft(realNum1);
		balanceNumOfDigits(realNum1, realNum2);
		shiftRight(realNum1);
		realNum1[0] = '-';
		return;
	}
	if(realNum2[0] == '-')
	{
		shiftLeft(realNum2);
		balanceNumOfDigits(realNum1, realNum2);
		shiftRight(realNum2);
		realNum2[0] = '-';
		return;
	}

	if(strlen(realNum1) == 0) strcpy(realNum1, "0");
	if(strlen(realNum2) == 0) strcpy(realNum2, "0");
	if(!isRealNumber(realNum1)) 
	{
		pushBack(realNum1, '.');
		pushBack(realNum1, '0');
	}

	if(!isRealNumber(realNum2))
	{
		pushBack(realNum2, '.');
		pushBack(realNum2, '0');
	}
	// Dealing with integer part
	dotPosition1 = isRealNumber(realNum1);
	dotPosition2 = isRealNumber(realNum2);
	while(dotPosition1 < dotPosition2)
	{
		shiftRight(realNum1);
		dotPosition1++;
	}

	while(dotPosition2 < dotPosition1)
	{
		shiftRight(realNum2);
		dotPosition2++;
	}
	// Dealing with the floating points
	while(strlen(realNum1) < strlen(realNum2)) pushBack(realNum1, '0');
	while(strlen(realNum1) > strlen(realNum2)) pushBack(realNum2, '0');
	return 1;
}

////////////////////////////////////////////////////// Others //////////////////////////////////////////////////////
// Returns the position of '.' 
int isRealNumber(char* inputRealNum)
{
	int count;
	for(count = 0; count < strlen(inputRealNum); count++) 
	{
		if(inputRealNum[count] == '.') return count;
	}
	return 0; // inputRealNum is an integer
}
int isDouble(char* inputRealNum)
{
	return strlen(inputRealNum) < 15;
}
int min2Int(int a, int b)
{
	if (a < b) return a;
	return b;
}

int max2Int(int a, int b)
{
	if (a > b) return a;
	return b;
}

// Returns 1 if realNum1 > realNum2 
// Returns 0 if realNum1 == realNum2;
// Returns -1 if realNum1 < realNum2
int compareRealNum(char* realNum1, char* realNum2)
{
	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		return compareRealNum(realNum2, realNum1);
	}
	if(realNum1[0] == '-') return -1;
	if(realNum2[0] == '-') return 1;
	
	balanceNumOfDigits(realNum1, realNum2);
	int checker = 0, numLength = strlen(realNum1);
	while(checker < numLength)
	{
		if(realNum1[checker] != realNum2[checker])
		{
			if(realNum1[checker] > realNum2[checker]) 
			{
				eliminateAllZeros(realNum1);
				eliminateAllZeros(realNum2);
				return 1;
			}
			else 
			{
				eliminateAllZeros(realNum1);
				eliminateAllZeros(realNum2);

				return -1;
			}
		}
		checker++;
	}
	eliminateAllZeros(realNum1);
	eliminateAllZeros(realNum2);
	return 0;
}

void multiplyByNum(int Num, char* realNum, char* result)
{
	eliminateAllZeros(realNum);
	char resultSaver[MAX_LENGTH];
	if(Num == 0) strcpy(result, "0");
	else 
	{
		int count;
		char tempResult[MAX_LENGTH];
		strcpy(tempResult, "0");
		for(count = 0; count < Num; count++) 
		{
			addRealNum(tempResult, realNum, resultSaver);
			if(resultSaver[0] == 'M')
			{
				strcpy(result, "MATH ERROR!");
				return;
			}
			strcpy(tempResult, resultSaver);
		}
		addRealNum(result, tempResult, resultSaver);
		strcpy(result, resultSaver);
	}
}
int multiplyTenfold(char* realNum)
{
	eliminateAllZeros(realNum);
	int dotPosition = isRealNumber(realNum);
	if(dotPosition) 
	{
		swapDigits(&realNum[dotPosition], &realNum[dotPosition + 1]);	
		if(dotPosition + 1 == strlen(realNum) - 1) realNum[dotPosition + 1] = '\0';
	}
	else
	{
		if(!pushBack(realNum, '0')) return 0;
	}
	eliminateAllZeros(realNum);
	return 1;
}

int divideTenfold(char* realNum)
{
	eliminateRightZero(realNum);
	int dotPosition = isRealNumber(realNum);
	if(dotPosition) 
	{
		swapDigits(&realNum[dotPosition], &realNum[dotPosition - 1]);	
		if(realNum[0] == '.') 
		{	
			if (!shiftRight(realNum)) return 0;
		}
	}
	else
	{
		char tempChar = realNum[strlen(realNum) - 1];
		realNum[strlen(realNum) - 1] = '.';
		if(!pushBack(realNum, tempChar)) return 0;
	}
	eliminateAllZeros(realNum);
	return 1;
}

void swapDigits(char* digitNum1, char* digitNum2)
{
	char tempChar = *digitNum1;
	*digitNum1 = *digitNum2;
	*digitNum2 = tempChar;
}

void swapStrings(char* realNum1, char* realNum2)
{
	char tempStr[strlen(realNum1)];
	strcpy(tempStr, realNum1);
	strcpy(realNum1, realNum2);
	strcpy(realNum2, tempStr);
}
////////////////////////////////////////////////////// Math Operations //////////////////////////////////////////////////////

//Calculate the sum of 2 real numbers
void addRealNum(char* realNum1, char* realNum2, char* result)
{
	eliminateAllZeros(realNum1);
	eliminateAllZeros(realNum2);
	
	if(strlen(realNum1) >= MAX_LENGTH - 1 || strlen(realNum2) >= MAX_LENGTH - 1) 
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	char originalValue1[MAX_LENGTH], originalValue2[MAX_LENGTH];
	strcpy(originalValue1, realNum1);
	strcpy(originalValue2, realNum2);

	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		addRealNum(realNum1, realNum2, result);
		shiftRight(result);
		result[0] = '-';
		strcpy(realNum1, originalValue1);
	 	strcpy(realNum2, originalValue2);
		return;
	}
	if(realNum1[0] == '-')
	{
		shiftLeft(realNum1);
		subtractRealNum(realNum2, realNum1, result);
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	if(realNum2[0] == '-')
	{
		shiftLeft(realNum2);
		subtractRealNum(realNum1, realNum2, result);
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	if(strlen(realNum1) == 0) 
	{
		strcpy(result, realNum2);
		return;
	}
	if(!balanceNumOfDigits(realNum1, realNum2))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	int numLength = strlen(realNum1) - 1; 					 // Not calculate '\0' + '\0'			
	int tempNum = 0, carry = 0, resultDotPosition = 0;
	strcpy(result, "");
	char tempResult[MAX_LENGTH];
	tempResult[strlen(realNum1)] = '\0';
	// Caculate Sum
	while(numLength >= 0)
	{
		if(realNum1[numLength] != '.' && realNum2[numLength] != '.')
		{
			tempNum = convertCharToInt(realNum1[numLength]) + convertCharToInt(realNum2[numLength]) + carry;
			if(tempNum > 9) 
			{
				carry = 1;
				tempNum = tempNum % 10;
			}
			else
			{
				carry = 0;
			}
			tempResult[numLength] = convertIntToChar(tempNum);
		}
		else
		{
			tempResult[numLength] = '.';
			resultDotPosition = numLength;
		}
		numLength--;
	}
	if(carry != 0) 
	{
		if(strlen(tempResult) >= MAX_LENGTH)
		{
			strcpy(realNum1, originalValue1);
			strcpy(realNum2, originalValue2);
			strcpy(result, "MATH ERROR!");
			return;
		}
		shiftRight(tempResult);
		tempResult[0] = '1';
	}
	
	strcpy(realNum1, originalValue1);
	strcpy(realNum2, originalValue2);
	
	eliminateAllZeros(tempResult);	
	roundRealNum(tempResult);
	strcpy(result, tempResult);
}

//Calculate realNum1 - realNum2 
void subtractRealNum(char* realNum1, char* realNum2, char* result)
{
	eliminateAllZeros(realNum1);
	eliminateAllZeros(realNum2);

	if(strlen(realNum1) >= MAX_LENGTH - 1 || strlen(realNum2) >= MAX_LENGTH - 1) 
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	char originalValue1[MAX_LENGTH], originalValue2[MAX_LENGTH];
	strcpy(originalValue1, realNum1);
	strcpy(originalValue2, realNum2);

	if(strlen(realNum2) == 0) 
	{
		strcpy(result, realNum1);
		return;
	}
	if(strlen(realNum1) == 0) 
	{
		strcpy(result, realNum2);
		return;
	}
	
	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		subtractRealNum(realNum2, realNum1, result);
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	if(realNum1[0] == '-')
	{
		shiftLeft(realNum1);
		addRealNum(realNum1, realNum2, result);
		shiftRight(result);
		result[0] = '-';
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	if(realNum2[0] == '-')
	{
		shiftLeft(realNum2);
		addRealNum(realNum1, realNum2, result);
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	if(compareRealNum(realNum2, realNum1) == 1) 
	{
		subtractRealNum(realNum2, realNum1, result);
		shiftRight(result);
		result[0] = '-';
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}

	if(!balanceNumOfDigits(realNum1, realNum2))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	int numLength = strlen(realNum1) - 1; 					 // Not calculate '\0' - '\0'			
	int tempNum = 0, carry = 0, resultDotPosition = 0;
	strcpy(result, "");
	char tempResult[MAX_LENGTH];
	tempResult[strlen(realNum1)] = '\0';
	// Caculate difference
	while(numLength >= 0)
	{
		if(realNum1[numLength] != '.' && realNum2[numLength] != '.')
		{
			tempNum = convertCharToInt(realNum1[numLength]) - convertCharToInt(realNum2[numLength]) - carry;
			if(tempNum < 0) 
			{
				carry = 1;
				tempNum = tempNum + 10;
			}
			else
			{
				carry = 0;
			}
			tempResult[numLength] = convertIntToChar(tempNum);
		}
		else
		{
			tempResult[numLength] = '.';
			resultDotPosition = numLength;
		}
		numLength--;
	}
	
	strcpy(realNum1, originalValue1);
	strcpy(realNum2, originalValue2);
	
	eliminateAllZeros(tempResult);
	roundRealNum(tempResult);	
	strcpy(result, tempResult);
}

// Multiply of 2 real numbers
// Change 123.456 * 456.789 to 123456 * 456789 / 1000000
// 123 * 345 = 100 * 345 + 20 * 345 + 3 * 345  
void multiplyRealNum(char* realNum1, char* realNum2, char* result)
{
	eliminateAllZeros(realNum1);
	eliminateAllZeros(realNum2);

	char originalValue1[MAX_LENGTH], originalValue2[MAX_LENGTH];
	strcpy(originalValue1, realNum1);
	strcpy(originalValue2, realNum2);


	if(realNum1[0] == '-' && realNum2[0] == '-')
	{
		shiftLeft(realNum1);
		shiftLeft(realNum2);
		multiplyRealNum(realNum1, realNum2, result);
		strcpy(realNum1, originalValue1);
		strcpy(realNum2, originalValue2);
		return;
	}
	else
	{
		if(realNum1[0] == '-') 
		{
			shiftLeft(realNum1);
			multiplyRealNum(realNum1, realNum2, result);
			if(!shiftRight(result))
			{
				strcpy(result, "MATH ERROR!");
				return;
			};
			result[0] = '-';
			strcpy(realNum1, originalValue1);
			strcpy(realNum2, originalValue2);
			return;
		}
		if(realNum2[0] == '-') 
		{
			shiftLeft(realNum2);
			multiplyRealNum(realNum1, realNum2, result);
			if(!shiftRight(result))
			{
				strcpy(result, "MATH ERROR!");
				return;
			};
			result[0] = '-';
			strcpy(realNum1, originalValue1);
			strcpy(realNum2, originalValue2);
			return;
		}
	}
	if(strcmp(realNum1, "0") == 0 || strcmp(realNum2, "0") == 0)
	{
		strcpy(result, "0"); 
		return;
	}
	int divider = 0;
	while(isRealNumber(realNum1))
	{
		multiplyTenfold(realNum1);
		divider++;
	}
	while(isRealNumber(realNum2))
	{
		multiplyTenfold(realNum2);
		divider++;
	}
	int numLength1 = strlen(realNum1), count, count2;
	char finalResult[MAX_LENGTH], tempResult[MAX_LENGTH], resultSaver[MAX_LENGTH];
	strcpy(finalResult, "0");
	for(count = 0; count < numLength1; count++)
	{
		strcpy(tempResult, "0");
		multiplyByNum(convertCharToInt(realNum1[count]), realNum2, tempResult);	
		if(tempResult[0] == 'M') 
		{
			strcpy(result, "MATH ERROR!");
			return;
		}
		for(count2 = 0; count2 < numLength1 - count -1; count2++) 
		{ 
			if(!multiplyTenfold(tempResult))
			{
				strcpy(result, "MATH ERROR!");
				return;
			}
		}
		addRealNum(finalResult, tempResult, resultSaver);
		if(resultSaver[0] == 'M') 
		{
			strcpy(result, "MATH ERROR!");
			return;
		}
		strcpy(finalResult, resultSaver);
	}	
	for(count = 1; count <= divider; count++) 
	{
	if(!divideTenfold(finalResult))
		{
			strcpy(result, "MATH ERROR!");
			return;
		}
	}
	strcpy(realNum1, originalValue1);
	strcpy(realNum2, originalValue2);
	
	eliminateAllZeros(finalResult);
	roundRealNum(tempResult); 
	strcpy(result, finalResult);
}

void divideRealNum(char* dividend, char* divisor, char* result)
{
	eliminateAllZeros(dividend);
	eliminateAllZeros(divisor);
	
	char originalValue1[MAX_LENGTH], originalValue2[MAX_LENGTH];
	strcpy(originalValue1, dividend);
	strcpy(originalValue2, divisor);
	
	if(dividend[0] == '-' && divisor[0] == '-')
	{
		shiftLeft(dividend);
		shiftLeft(divisor);
		divideRealNum(dividend, divisor, result);
		strcpy(dividend, originalValue1);
		strcpy(divisor, originalValue2);
		return;
	}
	else
	{
		if(dividend[0] == '-') 
		{
			shiftLeft(dividend);
			divideRealNum(dividend, divisor, result);
			if(!shiftRight(result))
			{
				strcpy(result, "MATH ERROR!");
				return;
			};
			result[0] = '-';
			strcpy(dividend, originalValue1);
			strcpy(divisor, originalValue2);
			return;
		}
		if(divisor[0] == '-') 
		{
			shiftLeft(divisor);
			divideRealNum(dividend, divisor, result);
			if(!shiftRight(result))
			{
				strcpy(result, "MATH ERROR!");
				return;
			};
			result[0] = '-';
			strcpy(dividend, originalValue1);
			strcpy(divisor, originalValue2);
			return;
		}
	}
	if(strcmp(divisor, "0") == 0)
	{
		strcpy(result, "MATH ERROR!");
		strcpy(dividend, originalValue1);
		strcpy(divisor, originalValue2);
		return;
	}
	
	int tenFold = 0;
	
	while(isRealNumber(dividend))
	{
		multiplyTenfold(dividend);
		tenFold--;
	}
	while(isRealNumber(divisor))
	{
		multiplyTenfold(divisor);
		tenFold++;
	}
	
	char carrier[MAX_LENGTH], tempResult[MAX_LENGTH], finalResult[MAX_LENGTH];
	int numLength = strlen(dividend);
	int count = 0, quotient = 0;
	strcpy(result, "0");
	strcpy(tempResult, "0");
	strcpy(finalResult, "");
	strcpy(carrier, "0");
	
	while(compareRealNum(divisor, carrier) == 1 && count < numLength && dividend[count] != '\0')
	{
		eliminateAllZeros(dividend);
		if(!pushBack(carrier, dividend[count]))
		{
			strcpy(result, "MATH ERROR!");
			return;
		}
		count++;
		quotient = 0;
		while(compareRealNum(carrier, divisor) != -1) 
		{
			quotient++;
			subtractRealNum(carrier, divisor, tempResult);
			strcpy(carrier, tempResult);
		} 
		if(!pushBack(finalResult, convertIntToChar(quotient)))
		{
			strcpy(result, "MATH ERROR!");
			return;
		}	
	}
	if(carrier[0] != '0') 
	{
		if(!pushBack(finalResult, '.'))
		{
			strcpy(result, "MATH ERROR!");
			return;
		}
		numLength = strlen(finalResult);
		while(compareRealNum(divisor, carrier) == 1 && numLength < MAX_LENGTH && carrier[0] != '0')
		{
			if(!pushBack(carrier, '0'))
			{
				strcpy(result, "MATH ERROR!");
				return;
			}
			numLength++;
			quotient = 0;
			while(compareRealNum(carrier, divisor) != -1) 
			{
				quotient++;
				subtractRealNum(carrier, divisor, tempResult);
				if(tempResult[0] == 'M')
				{
					strcpy(result, "MATH ERROR!");
					return;
				}
				strcpy(carrier, tempResult);
			} 
			if(!pushBack(finalResult, convertIntToChar(quotient)))
			{
				strcpy(result, "MATH ERROR!");
				return;
			}	
		}		
	}
	
	if(tenFold > 0)
	{
		for(count = 0; count < tenFold; count++) 
		{
			if(!multiplyTenfold(finalResult))
			{
				strcpy(result, "MATH ERROR!");
				return;
			}
		}
	}
	else
	{
		for(count = 0; count > tenFold; count--) 
		{
			if(!divideTenfold(finalResult))
			{
				strcpy(result, "MATH ERROR!");
				return;	
			}
		}
	}
	strcpy(dividend, originalValue1);
	strcpy(divisor, originalValue2);
	
	eliminateAllZeros(finalResult);
	roundRealNum(finalResult);
	strcpy(result, finalResult);
}

void powerRealNum(char* realNum1, char* realNum2, char* result)
{
	eliminateAllZeros(realNum1);
	eliminateAllZeros(realNum2);
	if((strcmp(realNum1, "0") == 0) && (strcmp(realNum2, "0") == 0))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	if(isRealNumber(realNum2)) 
	{
		errno = 0; //<errno.h>
		double doubleTempResult = pow(convertStringToDouble(realNum1), convertStringToDouble(realNum2));
		if(errno != 0 || doubleTempResult == INFINITY) 
		{
			strcpy(result, "MATH ERROR!");
			return;
		}
		convertDoubleToString(doubleTempResult, result);
		eliminateAllZeros(result);
		return;
	}
	else
	{
		int negative = 0;
		if(realNum2[0] == '-')
		{
			negative = 1;
			shiftLeft(realNum2);
		}
		char count[MAX_LENGTH];
		char tempResult[MAX_LENGTH], resultSaver[MAX_LENGTH];
		char numberOne[MAX_LENGTH];
		strcpy(count, "0");
		strcpy(tempResult, "1");
		strcpy(numberOne, "1");

		while(compareRealNum(realNum2, count) > 0)
		{
			multiplyRealNum(tempResult, realNum1, resultSaver);
			if(resultSaver[0] == 'M')
			{
				strcpy(result, "MATH ERROR!");
				return;
			}
			strcpy(tempResult, resultSaver);
			addRealNum(count, numberOne, resultSaver);
			if(resultSaver[0] == 'M')
			{
				strcpy(result, "MATH ERROR!");
				return;
			}
			strcpy(count, resultSaver);
		}
		if(negative)
		{
			if(!shiftRight(realNum2))
			{
				strcpy(result, "MATH ERROR!");
				return;
			}
			realNum2[0] = '-';
			divideRealNum(numberOne, tempResult, resultSaver);
			if(resultSaver[0] == 'M')
			{
				strcpy(result, "MATH ERROR!");
				return;
			}
			strcpy(tempResult, resultSaver);
		}
		roundRealNum(tempResult);
		eliminateAllZeros(tempResult);
		strcpy(result, tempResult);
	}	
}
void getFactorial(char* intNum, char* result)
{
	eliminateAllZeros(intNum);
	if(isRealNumber(intNum)) 
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	int negative = 0;
	if(intNum[0] == '-')
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	char numberOne[MAX_LENGTH], tempNum1[MAX_LENGTH], tempNum2[MAX_LENGTH], tempResult[MAX_LENGTH], resultSaver[MAX_LENGTH];
	strcpy(numberOne, "1");
	strcpy(tempNum1, "1");
	strcpy(tempNum2, "1");
	strcpy(tempResult, "1");
	while(compareRealNum(intNum, tempNum1) >= 0)
	{
		addRealNum(tempNum1, numberOne, tempNum2);
		if(tempNum2[0] == 'M')
		{
			strcpy(result, "MATH ERROR!");
			return;
		}
		multiplyRealNum(tempResult, tempNum1, resultSaver);
		if(resultSaver[0] == 'M')
		{
			strcpy(result, "MATH ERROR!");
			return;
		}
		strcpy(tempResult, resultSaver);
		strcpy(tempNum1, tempNum2);
	}
	strcpy(result, tempResult);
}
///////////////////////////////////////////////////// Trigonometric Functions /////////////////////////////////////////////////////

void getSinRadian(char* realNum, char* result)
{
	if(!isDouble(realNum))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	double tempRealNum = convertStringToDouble(realNum);
	convertDoubleToString(sin(tempRealNum), result);
	eliminateAllZeros(result);
}
void getCosRadian(char* realNum, char* result)
{
	if(!isDouble(realNum))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	double tempRealNum = convertStringToDouble(realNum);
	convertDoubleToString(cos(tempRealNum), result);
	eliminateAllZeros(result);
}
void getTanRadian(char* realNum, char* result)
{
	if(!isDouble(realNum))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	char tempResult[MAX_LENGTH], numberZero[MAX_LENGTH];
	getCosRadian(realNum, tempResult);
	eliminateAllZeros(tempResult);
	strcpy(numberZero, "0");
	if(compareRealNum(tempResult, numberZero) == 0)
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	double tempRealNum = convertStringToDouble(realNum);
	convertDoubleToString(tan(tempRealNum), result);
	eliminateAllZeros(result);
}
void getCotRadian(char* realNum, char* result)
{
	if(!isDouble(realNum))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	char tempResult[MAX_LENGTH], numberZero[MAX_LENGTH];
	getSinRadian(realNum, tempResult);
	eliminateAllZeros(tempResult);
	strcpy(numberZero, "0");
	if(compareRealNum(tempResult, numberZero) == 0)
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	double tempRealNum = convertStringToDouble(realNum);
	convertDoubleToString(tan(tempRealNum), tempResult);
	char numberOne[MAX_LENGTH];
	strcpy(numberOne, "1");
	divideRealNum(numberOne, tempResult, result);
	if(result[0] == 'M')
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	eliminateAllZeros(result);
}
void getSinDegree(char* realNum, char* result)
{
	if(!isDouble(realNum))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	double tempRealNum = convertStringToDouble(realNum);
	double tempDegree = convertRadianToDegree(tempRealNum);
	convertDoubleToString(sin(tempDegree), result);
	eliminateAllZeros(result);

} 
void getCosDegree(char* realNum, char* result)
{
	if(!isDouble(realNum))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	double tempRealNum = convertStringToDouble(realNum);
	double tempDegree = convertRadianToDegree(tempRealNum);
	convertDoubleToString(cos(tempDegree), result);
	eliminateAllZeros(result);
}
void getTanDegree(char* realNum, char* result)
{
	if(!isDouble(realNum))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	char tempResult[MAX_LENGTH], numberZero[MAX_LENGTH];
	getCosDegree(realNum, tempResult);
	eliminateAllZeros(tempResult);
	strcpy(numberZero, "0");
	if(compareRealNum(tempResult, numberZero) == 0)
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	double tempRealNum = convertStringToDouble(realNum);
	double tempDegree = convertRadianToDegree(tempRealNum);
	convertDoubleToString(tan(tempDegree), result);
	eliminateAllZeros(result);
}

///////////////////////////////////////////////////// Logarithmic Functions /////////////////////////////////////////////////////

void getLog10(char* realNum, char* result)
{
	if(!isDouble(realNum))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	char tempResult[MAX_LENGTH];
	double tempRealNum = convertStringToDouble(realNum);
	if(tempRealNum <= 0) 
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	convertDoubleToString(log10(tempRealNum), tempResult);
	strcpy(result, tempResult);
}
void getNaturalLog(char* realNum, char* result)
{
	if(!isDouble(realNum))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	char tempResult[MAX_LENGTH];
	double tempRealNum = convertStringToDouble(realNum);
	if(tempRealNum <= 0) 
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	convertDoubleToString(log(tempRealNum), tempResult);
	strcpy(result, tempResult);
}
void getLogN(char* realNum, char* base, char* result)
{
	if(!isDouble(realNum))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	if(!isDouble(base))
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	char tempResult1[MAX_LENGTH], tempResult2[MAX_LENGTH];
	
	double tempRealNum = convertStringToDouble(realNum) ;
	if(tempRealNum <= 0) 
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	convertDoubleToString(log10(tempRealNum), tempResult1);
	
	tempRealNum = convertStringToDouble(base) ;
	if(tempRealNum <= 0 || tempRealNum == 1) 
	{
		strcpy(result, "MATH ERROR!");
		return;
	}
	convertDoubleToString(log10(tempRealNum), tempResult2);
	divideRealNum(tempResult1, tempResult2, result);
}
