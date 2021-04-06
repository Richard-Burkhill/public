#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
int funcForThread (char * str, ...)
{
	char* curChar=0;
	int* curInt=0;
	double* curDbl=0;

	char* charParam[1];
	int* intParam[1];
	double* dblParam[1];

    va_list vl;

	int ret = 0;
 	int i = 0;

	int charCount=0;
	int intCount=0;
	int dblCount=0;

 	va_start( vl, str );

 	while (str && str[i])
 	{
		if (str[i] == 'c')
		{
			charCount++;
		}
		else if (str[i] == 'i')
		{
			intCount++;
		}
		else if (str[i] == 'd') 
		{
			dblCount++;
		}
        i++;
	}

	charParam[0] = (char*) calloc(charCount, sizeof(char));
	intParam[0] = (int*) calloc(intCount, sizeof(int));
	dblParam[0] = (double*) calloc(dblCount, sizeof(double));

	curChar=charParam[0];
	curInt=intParam[0];
	curDbl=dblParam[0];

    i=0;
 	while (i<(charCount+intCount+dblCount))
 	{
		if (str[i] == 'c'){
			curChar = va_arg( vl, char* );
			curChar++;
		}
		else if (str[i] == 'i')
		{
			curInt = va_arg( vl, int* );
			curInt++;
		}
		else if (str[i] == 'd') 
		{
			curDbl = va_arg( vl, double* );
			curDbl++;
		}
		i++;
	}

	*(charParam[0])='b';
	*(intParam[0])=1;
	*(dblParam[0])=0.0;

    va_end(vl);
    return ret;
}

int main(int argc, char *argv[])
{
	char c = 'a';
	int i=0;
	double d=1.0;
	char buf[5]="c i d";
	int ret = funcForThread("c i d", &c, &i, &d);
	if ((c != 'b') && (i!=1) && (d!=0.0)){
		printf("Not possible to update values by reference when using varadic arguments\n");
	}
	return ret;
}
