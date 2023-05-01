#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct
{
	char* String;
	int StringSize;
}String;

String initString(int size);

String getStringFromKayboard(const char* Massege);

float getFloatFromKayboard(const char* Massege);

int getIntFromKayboard(const char* Massege);