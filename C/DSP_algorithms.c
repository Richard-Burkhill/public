#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UNSIGNED_CHAR	0
#define UNSIGNED_INT	1
#define UNSIGNED_LONG	2
#define FLOAT		3
#define SIGNED_CHAR	4
#define SIGNED_INT	5
#define SIGNED_LONG	6
#define DOUBLE		7


typedef struct{
	unsigned char type;
	unsigned char element_size;
	unsigned short int records;
	unsigned short int rec_len;
} HEADER;

typedef struct {
	unsigned char type;
	unsigned char element_size;
	unsigned short int records;
	unsigned short int rec_len;
	char *name;
	FILE *fp;
} DSP_FILE;

/****************************************************************************
* open_write - open a DSP data file for write
*
* Returns a pointer to a DSP_FILE structure allocated by the function.
* Allocation errors or improper type causes a call to exit(1).
* A bad file name returns a NULL pointer.
*
* DSP_FILE *open_write(char *file_name, int type, int records, int rec_len)
* 	file_name	pointer to a file name string
* 	type		type of DSP data (0-7 specified in defines)
* 	records		number of records of data to bw written
* 	rec_len		number of elements in each record
****************************************************************************/

DSP_FILE *open_write(file_name,type,records,rec_len)
	char *file_name; 	/* file name string */
	int type;		/* data type 0-7 */
	unsigned short int records;	/* number of records to be written */
	unsigned short int rec_len;	/* elements in each record */
{
	DSP_FILE *dsp_info;
	int status;

/* allocate the DSP data file structure */
	dsp_info = (DSP_FILE*) malloc(sizeof(DSP_FILE));
	if(!dsp_info){
		printf("\nError in open write: structure allocation, file %s\n", file_name);
		exit(1);
	}

/* set the basics */
	dsp_info->type = (unsigned char)type;
	dsp_info->records = records;
	dsp_info->rec_len = rec_len;

/* set element size from data type */
	switch(type){
		case 0:
		case 4:
			dsp_info->element_size = sizeof(char);
			break;
		case 1:
		case 5:
			dsp_info->element_size = sizeof(short int);
			break;
		case 2:
		case 6:
			dsp_info->element_size = sizeof(long int);
			break;
		case 3:
			dsp_info->element_size = sizeof(float);
			break;
		case 7:
			dsp_info->element_size = sizeof(double);
			break;
		default:
			printf("\nUnsupported data type, file %s\n", file_name);
			exit(1);
	}

/* open file for binary write */
	dsp_info->fp = fopen(file_name,"wb");
	if(!dsp_info->fp){
		printf("\nError opening %s in open_write\n", file_name);
		return(NULL);
	}

/* copy and allocate file name string for the DSP_FILE structure */
	dsp_info->name = malloc(strlen(file_name)+1);
	if(!dsp_info->name){
		printf("\nUnable to allocate file_name string in open_write\n");
		exit(1);
	}
	strcpy(dsp_info->name, file_name);

/* write header to file */
	status = fwrite ((char*) dsp_info, sizeof(HEADER), 1, dsp_info->fp);
	if(status != 1){
		printf("\nError writing header of file %s\n", file_name);
		exit(1);
	}

/* return pointer to DSP_FILE structure */
	return(dsp_info);
}

/****************************************************************************
* read_record - read one record of DSP data file
*
* void read_record(char *ptr, DSP_FILE *dsp_info)
*
*	ptr		pointer to previously allocated memory
*			where to put data read from file
*	dsp_info	pointer to DSP data file structure
*
*	No return value.
*	Exits if a read error occurs or if the DSP_file structure is invalid.
****************************************************************************/
void read_record(ptr, dsp_info)
	char *ptr;
	DSP_FILE *dsp_info;
{
	int status;

	if(!dsp_info){
		printf("\nError in DSP_FILE structure passed to read_record\n");
		exit(1);
	}

	status = fread(ptr,dsp_info->element_size, dsp_info->rec_len, dsp_info->fp);
	if(status != dsp_info->rec_len){
		printf("\nError in read_record, file %s\n",dsp_info->name);
		exit(1);
	}
}

/****************************************************************************
* read_float_record - read one record of DSP data file and convert
*	to float array of values.
*
* Returns a pointer to the beginning of the allocated float array of values
* representing the record read from  the DSP_FILE.
*
* Exits if a read or allocation error occurs.
*
* float *read_float_record(DSP_FILE *dsp_info)
****************************************************************************/
float *read_float_record(dsp_info)
	DSP_FILE *dsp_info;
{
	void read_record();
	static long int prev_size = 0; /* previous size in bytes */
	static double *buf;

	float *out;			/* return output pointer */
	float *out_ptr;

	long int byte_size;		/* current size in bytes */
	int i,length;

	length = dsp_info->rec_len;

	byte_size = (long)length*dsp_info->element_size;

/* check to see if we have to allocate the input buffer */
	if (byte_size != prev_size){
		if(prev_size != 0) free(buf); /* free old buffer */

/* allocate input buffer area cast to double for worst case alignment */
		buf = (double*) calloc(length,dsp_info->element_size);

		if(!buf){
			printf("\nAllocation error in input buffer\n");
			exit(1);
		}

		prev_size = byte_size;	/* lattest size */
	}

/* allocate the output pointer only if conversion required */
	if(dsp_info->type != FLOAT){
		out = (float*) calloc(length,sizeof(float));
		if(!out){
			printf("\nAllocation error in read_float_record\n");
			exit(1);
		}
	}

/* read the record into buf */
	read_record((char*)buf,dsp_info);

/* perform conversion to floating point */

	out_ptr = out;

	switch(dsp_info->type){
		case UNSIGNED_CHAR: {
			unsigned char *uc_ptr;
			uc_ptr = (unsigned char*)buf;
			for(i=0; i< length; i++)
				*out_ptr++ = (float)(*uc_ptr++);
			}
			break;
		case SIGNED_CHAR: {
			char *sc_ptr;
			sc_ptr = (char*)buf;
			for(i=0; i<length; i++)
				*out_ptr++ = (float)(*sc_ptr++);
			}
			break;
		case SIGNED_INT: {
			int *si_ptr;
			si_ptr = (int*)buf;
			for(i=0; i<length;i++)
				*out_ptr++ = (float)(*si_ptr++);
			}
			break;
		case UNSIGNED_INT: {
			unsigned int *ui_ptr;
			ui_ptr = (unsigned int*)buf;
			for(i=0;i<length;i++)
				*out_ptr++ = (float)(*ui_ptr++);
			}
			break;
		case UNSIGNED_LONG: {
			unsigned long *ul_ptr;
			ul_ptr = (unsigned long*)buf;
			for(i=0;i<length;i++)
				*out_ptr++ = (float)(*ul_ptr++);
			}
			break;
		case SIGNED_LONG: {
			long *sl_ptr;
			sl_ptr = (long*)buf;
			for(i=0;i<length;i++)
				*out_ptr++ = (float)(*sl_ptr++);
			}
			break;
		case FLOAT: {
			out = (float*)buf; /* no conversion */
			prev_size = 0;
			}
			break;
		case DOUBLE: {
			double *d_ptr;
			d_ptr = (double*)buf;
			for(i=0;i<length;i++)
				*out_ptr++ = (float)(*d_ptr++);
			}
			break;
	}
	return(out);
}

/****************************************************************************
* read_trailer - read trailer from existing DSP data file
*
* char *read_trailer(DSP_FILE *dsp_info)
*
*	dsp_info	pointer to DSP data file structure
*
* Returns pointer to allocated string.
* Exits if read error, file error, or allocation  error.
****************************************************************************/
char *read_trailer(dsp_info)
	DSP_FILE *dsp_info;
{
	int status,len;
	long int position,bytecount,old_pos;
	char *text;

/* get the number of bytes in the data */
	bytecount = (long)dsp_info->element_size * (long)dsp_info->records
						 * (long)dsp_info->rec_len;
	bytecount += sizeof(HEADER);	/* add on the header length */

/* save current position */
	old_pos = ftell(dsp_info->fp);

/* find the end of file location */
	fseek(dsp_info->fp,0L,2);
	position = ftell(dsp_info->fp);

/* check for errors in position */
	if(position <= 0L || position < bytecount){
		printf("\nError in trailer, file %s\n",dsp_info->name);
		exit(1);
	}

/* try to allocate space for the trailer text */
	len = position - bytecount;
	text = malloc(len+1);
	if(!text){
		printf("\nError in allocating trailer space for file %s\n",dsp_info->name);
		exit(1);
	}

/* read trailer */
	fseek(dsp_info->fp,bytecount,0);	/* seek to beginning of trailer */
	status = fread(text,sizeof(char),len,dsp_info->fp);
	if (status != len){
		printf("\nError reading trailer of file %s\n",dsp_info->name);
		return(NULL);
	}

/* restore file position */
	fseek(dsp_info->fp,old_pos,0);

/*make sure the trailer is NULL terminated */
	text[len] = NULL;

	return(text);
}

/****************************************************************************
* append_trailer - read trailer from existing DSP data file
* 		and add on a new string
*
* char *read_trailer(char *string, DSP_FILE *dsp_info)
*	string		pointer to string to add to the trailer
*	dsp_info	pointer to DSP data file structure
*
* Returns pointer to allocated string.
* Exits if read error, file error, or allocation error.
****************************************************************************/
char *append_trailer(string, dsp_info)
	char *string;		/* string to add */
	DSP_FILE *dsp_info;	/* input trailer file */
{
	char *trail;		/* trailer pointer */

	trail = read_trailer(dsp_info);

/* re-allocate the output for the total size */
	trail = realloc(trail,strlen(trail) + strlen(string)+1);
	if(!trail){
		printf("\nError in reallocating trailer space for file %s\n", dsp_info->name);
		exit(1);
	}

/* add on string to trail */
	strcat(trail,string);

	return(trail);
}
