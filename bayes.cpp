#include"bayes.h"
#include"linkedlist.h"
#include<iostream>

double bayes::getPc(char *TypeName)
{
	double ret = 0.0;
	ret = (getSamplesTotalOfType(TypeName)) / (getSamplesTotal()*1.000);
	return ret;
}

double bayes::getPtkc(char *sample, char *TypeName)
{
	double ret = 0.0;
	ret = (getSampleAppearance(sample, TypeName) + 1) / (getSamplesTotalOfType(TypeName) + getV()*1.000);
	return ret;
}

char *bayes::calcType(char *input)
{
	// split
	int samplesInInput = 0, i = 0;
	char **samples = new char*[1024];
	for (i = 0; i < 1024; i++)
		samples[i] = new char[0x20];
	textSplitter(samples, samplesInInput, input);

	// calc
	double *isType = new double[getTotalTypes()],
		tmp = 0;
	int j = 0;

	for (j = 0; j < getTotalTypes(); j++)
		isType[j] = 1.000;

	for (i = 0; i < samplesInInput; i++)
		for (j = 0; j < getTotalTypes(); j++)
		isType[j] *= getPtkc(samples[i], getTypeName(j));

	for (j = 0; j < getTotalTypes(); j++)
		isType[j] *= getPc(getTypeName(j));

	int retID = 0;
	for (i = 0; i < getTotalTypes(); i++)
	{
		if (tmp <= isType[i])
		{
			tmp = isType[i];
			retID = i;
		}
	}

	// testOut
	for (i = 0; i < getTotalTypes();i++)
		printf("P(%s) = %lf\n", getTypeName(i), getPc(getTypeName(i)));

	for (i = 0; i < getTotalTypes(); i++)
	for (j = 0; j < samplesInInput;j++)
		printf("P(%s|%s) = %lf\n", samples[j], getTypeName(i), getPtkc(samples[i], getTypeName(i)));

	for (i = 0; i < getTotalTypes(); i++)
		printf("\tP(%s|d) = %lf\n", getTypeName(i), isType[i]);


	// dispose
	for (i = 0; i < samplesInInput; i++)
		delete[]samples[i];
	delete[]samples;

	delete[]isType;

	return getTypeName(retID);
}

void bayes::train(char *input, char *type)
{
	// split
	int samplesInInput = 0, i = 0;
	char **samples = new char*[1024];
	for (i = 0; i < 1024; i++)
		samples[i] = new char[0x20];
	textSplitter(samples, samplesInInput, input);

	// add
	for (i = 0; i < samplesInInput; i++)
		data.addCount(samples[i], type);

	// dispose
	for (i = 0; i < samplesInInput; i++)
		delete[]samples[i];
	delete[]samples;

}

int bayes::getTotalTypes(void)
{
	return data.getTypesCount();
}

int bayes::getV(void)
{
	/*
	if (stricmp(model,"multinomial")==0)
	return getSamplesUniqueTotal();
	else if (stricmp(model,"bernoulli")==0)
	return 2;
	else
	return -1;
	*/

	return getSamplesUniqueTotal();
}

int bayes::getSamplesUniqueTotal(void)
{
	return data.countUniqueObjects();
}

int bayes::getSamplesTotal(void)
{
	return data.countAll();
}

int bayes::getSamplesTotalOfType(char *input)
{
	return data.countInType(input);
}

int bayes::getSampleAppearance(char *sample, char *TypeName)
{
	return data.getTotalSamplesOfType(sample, TypeName);
}

void bayes::textSplitter(char **output, int &sizen, const char *input)
{

	// simple textSplitter
	int ignore = 0, count = 0, pos = 0, i = 0;

	while (input[pos++] != 0x00);

	char *buffer = new char[pos];
	char *splitter = " ,.*()\"\'&^%$#@!?<>/\\'";
	char *sp;
	memcpy_s(buffer, pos, input, pos);


	// 1st scan
	char *p;
	p = strtok_s(buffer, splitter, &sp);
	while (p)
	{
		count++;
		p = strtok_s(NULL, splitter, &sp);
	}


	// 2nd scan

	memcpy_s(buffer, pos, input, pos);
	pos = 0;
	p = strtok_s(buffer, splitter, &sp);
	while (p)
	{
		memcpy_s(output[pos++], 0x20, p, 0x20);
		p = strtok_s(NULL, splitter, &sp);
	}

	sizen = count;
	delete[]buffer;

}

char *bayes::getTypeName(int i)
{
	return data.getTypeName(i);
}