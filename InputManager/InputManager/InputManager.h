#pragma once

typedef struct
{
	char* String;
	int StringSize;
}String;

String getStringFromKayboard(const char* Massege);

float getFloatFromKayboard(const char* Massege);

int getIntFromKayboard(const char* Massege);