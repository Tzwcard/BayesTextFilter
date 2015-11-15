#include<iostream>
#include"bayes.h"

using namespace std;

int main(int argc, char **argv)
{
	bayes TextFilter;
	TextFilter.train("Chinese Beijing Chinese", "yes");
	TextFilter.train("Chinese Chinese Shanghai", "yes");
	TextFilter.train("Chinese Macao", "yes");
	TextFilter.train("Tokyo Japan Chinese", "no");

	char *digest = "Chinese Chinese Chinese Tokyo Japan",
		*digest1 = "Tokyo Japan";
	printf("message = %s\ntype = %s\n\n", digest, TextFilter.calcType(digest));
	printf("message = %s\ntype = %s\n\n", digest1, TextFilter.calcType(digest1));

	return 0;
}