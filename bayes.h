/*
  use a cstring(max size = 0x20) to save words and type
*/

#pragma once

#include"linkedlist.h"

class bayes
{
private:
	linkedlist data; // can switch to other method, like SQLite

	int getTotalTypes(void);
	int getV(void);
	int getSamplesUniqueTotal(void);
	int getSamplesTotal(void);
	int getSamplesTotalOfType(char *);
	int getSampleAppearance(char *, char *);

	void textSplitter(char**, int&, const char*);

	char *getTypeName(int);

public:
	/*
	bayes(void);
	~bayes(void);
	*/

	double getPc(char*); // get P(c)
	double getPtkc(char*, char*); // get P(tk|c)

	void train(char*, char*); // trainning samples, simply putting them into data

	char *calcType(char *); // input a sample, output the supposed type

	// int saveTranningData(char *);
	// int loadTranningData(char *);

};