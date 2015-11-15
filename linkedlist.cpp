#include"linkedlist.h"
#include<iostream>

linkedlist::linkedlist(void)
{
	mainData = NULL;
	typeCount = 0;
	for (int i = 0; i<typeMax; i++)
		objects[i] = 0;
	objectsUniqueCount = 0;
}

linkedlist::~linkedlist(void)
{
	if (mainData != NULL)
	{
		linkedList *p = mainData;
		while (p != NULL)
		{
			p = p->next;
			delete mainData;
			mainData = p;
		}
	}

}

int linkedlist::getTypeId(char *input)
{
	for (int i = 0; i<typeCount; i++)
		if (strcmp(input, typeName[i]) == 0)
			return i;

	return -1;
}

char *linkedlist::getTypeName(int id)
{
	return typeName[id];
}

int linkedlist::addCount(char *sample, char *type)
{
	if (getTypeId(type) == -1)
	{
		if (typeMax == typeCount)
			return -1;
		else
		{
			strcpy_s(typeName[typeCount], type);
			typeCount += 1;
		}
	}

	linkedList *p = mainData;
	while (p != NULL)
	{
		if (strcmp(sample, p->sampleName) == 0)
		{
			p->typeCNT[getTypeId(type)] += 1;
			objects[getTypeId(type)] += 1;
			return 0;
		}
		p = p->next;
	}
	objectsUniqueCount += 1;

	linkedList *tmp = new linkedList;
	strcpy_s(tmp->sampleName, sample);
	for (int i = 0; i<typeMax; i++)
		tmp->typeCNT[i] = 0;
	tmp->typeCNT[getTypeId(type)] = 1;
	tmp->next = NULL;
	objects[getTypeId(type)] += 1;

	if (mainData == NULL)
		mainData = tmp;
	else
	{
		p = mainData;
		while (p->next != NULL)
			p=p->next;
		p->next = tmp;
	}

	return 0;

}

int linkedlist::getTypesCount(void)
{
	return typeCount;
}

int linkedlist::countUniqueObjects(void)
{
	return objectsUniqueCount;
}

int linkedlist::countAll(void)
{
	int ret = 0;
	for (int i = 0; i<typeCount; i++)
		ret += objects[i];
	return ret;
}

int linkedlist::countInType(char *type)
{
	if (getTypeId(type) == -1)
		return -1;
	else
		return objects[getTypeId(type)];
}

int linkedlist::getTotalSamplesOfType(char *sample, char *type)
{
	if (getTypeId(type) == -1)
		return -1;

	linkedList *p = mainData;
	while (p != NULL)
	{
		if (strcmp(p->sampleName, sample) == 0)
			return p->typeCNT[getTypeId(type)];
		p = p->next;
	}
	return 0;
}

