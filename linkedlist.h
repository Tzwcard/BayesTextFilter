#pragma once

class linkedlist
{
	static const int typeMax = 10;
	typedef struct node
	{
		char sampleName[0x20];
		int typeCNT[typeMax];
		node *next;
	} linkedList;

private:
	int getTypeId(char*);

	linkedList *mainData;
	char typeName[typeMax][0x20];
	int typeCount,
		objectsUniqueCount,
		objects[typeMax];

public:
	linkedlist(void);
	~linkedlist(void);

	int addCount(char*, char*);
	int getTypesCount(void);
	int countUniqueObjects(void);
	int countAll(void);
	int countInType(char*);
	int getTotalSamplesOfType(char*, char*);

	char *getTypeName(int);
};