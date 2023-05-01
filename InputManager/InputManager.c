// InputManager.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "InputManager.h"

String initString(int size)
{
	String Res;
	Res.String = calloc(size + 1, sizeof(char));
	Res.StringSize = size;
	return Res;
}

String initStringCharArr(char* charArray)
{
	int Size = 0;
	while (charArray[Size] != '\0')
	{
		Size++;
	}

	String Res = initString(Size);
	for (int i = 0; i < Res.StringSize; i++)
	{
		Res.String[i] = charArray[i];
	}
	Res.String[Res.StringSize] = '\0';

	return Res;
}

String initStringLit(const char* charArray)
{
	int Size = 0;
	while (charArray[Size] != '\0')
	{
		Size++;
	}

	String Res = initString(Size);
	for (int i = 0; i < Res.StringSize; i++)
	{
		Res.String[i] = charArray[i];
	}
	Res.String[Res.StringSize] = '\0';

	return Res;
}

float myFloatPow(float X, float Y)
{
	float result = X;
	if (Y == 0)
	{
		return 1;
	}
	else if (Y > 0)
	{
		for (int i = 1; i < Y; i++)
		{
			result *= X;
		}
	}
	else if (Y < 0)
	{
		result = 1;
		for (int i = 0; i < -Y; i++)
		{
			result /= X;
		}
	}
	return result;
}


int myIntPow(int X, int Y)
{
	int result = X;
	if (Y == 0)
	{
		return 1;
	}
	else if (Y > 0)
	{
		for (int i = 1; i < Y; i++)
		{
			result *= X;
		}
	}
	else if (Y < 0)
	{
		result = 1;
		for (int i = 0; i < -Y; i++)
		{
			result /= X;
		}
	}
	return result;
}

String getStringFromKayboard(const char* Massege)
{
	if (Massege[0] != '\0')
	{
		printf("%s\n", initStringLit(Massege).String);
	}
	rewind(stdin);
	char* rawstr = (char*)calloc(1000, sizeof(char));
	String string = initStringCharArr(gets_s(rawstr, 1000));
	return string;
}

enum WRONG_INPUT_TYPES
{
	NONE = 0,
	ZERO_INPUT = 0b00000001,
	SIGN_PLASE = 0b00000010,
	SIGN_COUNT = 0b00000100,
	DOT_PLASE = 0b00001000,
	DOT_COUNT = 0b00010000,
	WRONG_SYMBOL = 0b00100000,
	TOO_LARGE = 0b01000000,
	DIGITS_AFTER_DOT = 0b10000000,
};

void printErrorMasages(char errBitMask)
{
	if (errBitMask & ZERO_INPUT)
	{
		printf("Write something\n");
	}
	if (errBitMask & SIGN_PLASE)
	{
		printf("You can't plase sign here\n");
	}
	if (errBitMask & SIGN_COUNT)
	{
		printf("Too much signs\n");
	}
	if (errBitMask & DOT_PLASE && !(errBitMask & SIGN_COUNT))
	{
		printf("You can't plase dot here\n");
	}
	if (errBitMask & DOT_COUNT)
	{
		printf("Too much dots\n");
	}
	if (errBitMask & WRONG_SYMBOL)
	{
		printf("Wrong symbols was used\n");
	}
	if (errBitMask & TOO_LARGE && !(errBitMask & WRONG_SYMBOL))
	{
		printf("Too big number\n");
	}
	if (errBitMask & DIGITS_AFTER_DOT)
	{
		printf("You can't plase digits after dot\n");
	}
}

enum WRONG_INPUT_TYPES isZeroInput(String String)
{
	if (String.String[0] == '\0')
	{
		return ZERO_INPUT;
	}
	else if (String.String[1] == '\0' && (String.String[0] == '-' || String.String[0] == '+'))
	{
		return ZERO_INPUT;
	}
	else
	{
		return NONE;
	}
}

enum WRONG_INPUT_TYPES isWrongSignPlase(String String)
{
	for (int i = 1; i < String.StringSize; i++)
	{
		if (String.String[i] == '-' || String.String[i] == '+')
		{
			return SIGN_PLASE;
		}
	}
	return NONE;
}

enum WRONG_INPUT_TYPES isWrongSignCount(String String)
{
	int SignsCount = 0;
	for (int i = 0; i < String.StringSize; i++)
	{
		if (String.String[i] == '-' || String.String[i] == '+')
		{
			SignsCount++;
		}
	}
	if (SignsCount > 1)
	{
		return SIGN_COUNT;
	}
	else
	{
		return NONE;
	}
}

enum WRONG_INPUT_TYPES isWrongDotPlase(String String)
{
	if (String.String[0] == '.' || String.String[0] == ',')
	{
		return DOT_PLASE;
	}
	if (String.String[String.StringSize - 1] == '.' || String.String[String.StringSize - 1] == ',')
	{
		return DOT_PLASE;
	}
	return NONE;
}

enum WRONG_INPUT_TYPES isWrongDotCount(String String)
{
	int DotsCount = 0;
	for (int i = 0; i < String.StringSize; i++)
	{
		if (String.String[i] == '.' || String.String[i] == ',')
		{
			DotsCount++;
		}
	}
	if (DotsCount > 1)
	{
		return DOT_COUNT;
	}
	return NONE;
}

enum WRONG_INPUT_TYPES isWrongSymbol(String String)
{
	for (int i = 0; i < String.StringSize; i++)
	{
		if ('0' <= String.String[i] && String.String[i] <= '9')
		{
			continue;
		}
		if (String.String[i] == '.' || String.String[i] == ',')
		{
			continue;
		}
		if (String.String[i] == '-' || String.String[i] == '+')
		{
			continue;
		}
		return WRONG_SYMBOL;
	}
	return NONE;
}

enum WRONG_INPUT_TYPES isTooLargeForFloat(String string)
{
	String TestString = initStringLit("340000000000000000000000000000000000000");
	int stringSizeBeforDot = 0;
	for (int i = 0; i < string.StringSize; i++)
	{
		if (string.String[i] == '.' || string.String[i] == ',')
		{
			break;
		}
		stringSizeBeforDot++;
	}

	int startIndex = 0;
	if (string.String[0] == '-' || string.String[0] == '+')
	{
		startIndex++;
	}

	if (TestString.StringSize < stringSizeBeforDot - startIndex)
	{
		return TOO_LARGE;
	}


	if (TestString.StringSize > stringSizeBeforDot - startIndex)
	{
		return NONE;
	}

	if (TestString.StringSize = stringSizeBeforDot - startIndex)
	{
		for (int i = 0; i < stringSizeBeforDot - startIndex; i++)
		{
			if (TestString.String[i] < string.String[i])
			{
				return TOO_LARGE;
			}
		}
	}

	return NONE;
}

char isStringTransformableToFloat(String string)
{
	char errBitMask = 0b0000000;

	errBitMask |= isZeroInput(string);

	errBitMask |= isWrongSignPlase(string);

	errBitMask |= isWrongSignCount(string);

	errBitMask |= isWrongDotPlase(string);

	errBitMask |= isWrongDotCount(string);

	errBitMask |= isWrongSymbol(string);

	errBitMask |= isTooLargeForFloat(string);

	return errBitMask;
}
float stringToFloat(String string)
{
	int befCounter = 0;
	int aftCounter = 0;
	short IsAnySign = 0;
	short IsAnyDot = 0;
	if (string.String[0] == '-' || string.String[0] == '+')
	{
		IsAnySign = 1;
	}
	for (int i = 0; i < string.StringSize; i++)
	{
		if (string.String[i] == '.' || string.String[i] == ',')
		{
			befCounter = i;
			aftCounter = string.StringSize - i - 1;
			IsAnyDot = 1;
		}
	}

	if (!IsAnyDot)
	{
		befCounter = string.StringSize;
	}

	float result = 0;
	for (int i = 0; i < (IsAnySign ? befCounter - 1 : befCounter); i++)
	{
		result += (string.String[-i + befCounter - 1] - 48) * myFloatPow(10, i);
	}

	for (int i = befCounter + 1; i < aftCounter + befCounter + 1; i++)
	{
		if (string.String[i] == 0)
		{
			break;
		}
		result += (float)((float)string.String[i] - 48) * (float)myFloatPow(10, befCounter - i);
	}

	if (string.String[0] == '-')
	{
		result = -result;
	}

	return result;
}

float getFloatFromKayboard(const char* Massege)
{
	char errBitMask = 0;
	String string;
	while ((errBitMask = isStringTransformableToFloat(string = getStringFromKayboard(Massege))) != 0)
	{
		printErrorMasages(errBitMask);
		printf("Try again\n");
	}

	return stringToFloat(string);
}

enum WRONG_INPUT_TYPES isNumberAfterIndexInStr(String string)
{
	for (int i = 0; i < string.StringSize; i++)
	{
		if (i > 0 && (string.String[i] == ',' || string.String[i] == '.'))
		{
			for (int j = i + 1; j < string.StringSize; j++)
			{
				if (string.String[j] != '0')
				{
					return DIGITS_AFTER_DOT;
				}
			}
		}
	}
	return NONE;
}

enum WRONG_INPUT_TYPES isTooLargeForInt(String string)
{
	String TestString = initStringLit("2147483646");
	int stringSizeBeforDot = 0;
	for (int i = 0; i < string.StringSize; i++)
	{
		if (string.String[i] == '.' || string.String[i] == ',')
		{
			break;
		}
		stringSizeBeforDot++;
	}

	int startIndex = 0;
	if (string.String[0] == '-' || string.String[0] == '+')
	{
		startIndex++;
	}

	if (TestString.StringSize < stringSizeBeforDot - startIndex)
	{
		return TOO_LARGE;
	}

	if (TestString.StringSize > stringSizeBeforDot - startIndex)
	{
		return NONE;
	}

	if (TestString.StringSize = stringSizeBeforDot - startIndex)
	{
		for (int i = 0; i < stringSizeBeforDot - startIndex; i++)
		{
			if (TestString.String[i] < string.String[i])
			{
				return TOO_LARGE;
			}
		}
	}

	return NONE;
}

char isStringTransformableToInt(String string)
{
	char errBitMask = isStringTransformableToFloat(string);

	errBitMask |= isNumberAfterIndexInStr(string);

	errBitMask |= isTooLargeForInt(string);

	return errBitMask;
}

int stringToInt(String string)
{
	int befCounter = 0;
	short IsAnySign = 0;
	short IsAnyDot = 0;
	if (string.String[0] == '-' || string.String[0] == '+')
	{
		IsAnySign = 1;
	}
	for (int i = 0; i < string.StringSize; i++)
	{
		if (string.String[i] == '.' || string.String[i] == ',')
		{
			befCounter = i;
			IsAnyDot = 1;
		}
	}

	if (!IsAnyDot)
	{
		befCounter = string.StringSize;
	}

	int result = 0;

	for (int i = 0; i < (IsAnySign ? befCounter - 1 : befCounter); i++)
	{
		result += (string.String[-i + befCounter - 1] - '0') * myIntPow(10, i);
	}

	if (string.String[0] == '-')
	{
		result = -result;
	}
	return result;
}

int getIntFromKayboard(const char* Massege)
{
	char errBitMask = 0;
	String string;
	while ((errBitMask = isStringTransformableToInt(string = getStringFromKayboard(Massege))) != 0)
	{
		printErrorMasages(errBitMask);
		printf("Try again\n");
	}

	return stringToInt(string);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
