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

DSP_FILE *open_write (char *file_name, int type, int records, int rec_len)
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
void read_record (char *ptr, DSP_FILE *dsp_info)
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
float *read_float_record (DSP_FILE *dsp_info)
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
char *read_trailer (DSP_FILE *dsp_info)
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
char *append_trailer (char *string, DSP_FILE *dsp_info)
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

typedef struct{
	unsigned int length; /* size of filter */
	float *history;
	float *coef;
} FILTER;

/****************************************************************************
* fir_filter_array - Filter float array of data
*
* Requires FILTER structure for coefficients.
* Input and output arrays are of equal length and are allocated by the caller.
*
* void fir_filter_array(float *in, float *out, int in_len, FILTER *fir)
*	in		float pointer to input array
* 	out		float pointer to output array
*	in_len		length of input and output arrays
*	FILTER *fir	pointer to FILTER structure
****************************************************************************/
void fir_filter_array (float *in, float *out, int in_len, FILTER *fir)
	float *in,*out;
	int in_len;
	FILTER *fir;
{
	int i,j,coef_len2,acc_length;
	float acc;
	float *in_ptr,*data_ptr,*coef_start,*coef_ptr,*in_end;

/* set up for coefficients */
	coef_start = fir->coef;
	coef_len2 = (fir->length+1)/2;

/* set up input data pointers */
	in_end = in+in_len-1;
	in_ptr = in+coef_len2-1;

/* initial value of accumulation length for startup */
	acc_length = coef_len2;

	for(i=0;i<in_len;i++){
/* set up pointers for accumulation */
		data_ptr = in_ptr;
		coef_ptr = coef_start;

/* do accumulation and write result */
		acc = (*coef_ptr++) * (*data_ptr--);
		for(j=1;j<acc_length;j++)
			acc+=(*coef_ptr++)*(*data_ptr--);
		*out++ = acc;

/* check for end case */

		if(in_ptr == in_end){
			acc_length--;
			coef_start++;
		}

/* if not at end, then check for startup, add to input pointer */
		else{
			if(acc_length < fir->length) acc_length++;
			in_ptr++;
		}
	}
}

/* FILTERS: 3 FIR AND 2 IIR */
/* 35 point lowpass FIR filter cutoff at 0.2 */
float fir_lpf35[35] = {
-6.849167e-003, 1.949014e-003, 1.309874e-002, 1.100677e-002,
-6.661435e-003,-1.321869e-002, 6.8195043-003, 2.292400e-002,
 7.732160e-004,-3.153488e-002,-1.384843e-002, 4.054618e-002,
 3.841148e-002,-4.790497e-002,-8.973017e-002, 5.285565e-002,
 3.126515e-001, 4.454146e-001, 3.126515e-001, 5.285565e-002,
-8.973017e-002,-4.790497e-002, 3.841148e-002, 4.054618e-002,
-1.384843e-002,-3.153488e-002, 7.732160e-004, 2.292400e-002,
 6.8195043-003,-1.321869e-002,-6.661435e-003, 1.100677e-002,
 1.309874e-002, 1.949014e-003,-6.849167e-003};

FILTER fir_lpf = {
	35,
	NULL,
	fir_lpf35
};

/* 35 point highpass FIR filter cutoff at 0.3 same as fir_lpf35
 * except that every other coefficient has a different sign */

float fir_hpf35[35] = {
 6.849167e-003, 1.949014e-003,-1.309874e-002, 1.100677e-002,
 6.661435e-003,-1.321869e-002,-6.8195043-003, 2.292400e-002,
-7.732160e-004,-3.153488e-002, 1.384843e-002, 4.054618e-002,
-3.841148e-002,-4.790497e-002, 8.973017e-002, 5.285565e-002,
-3.126515e-001, 4.454146e-001,-3.126515e-001, 5.285565e-002,
 8.973017e-002,-4.790497e-002,-3.841148e-002, 4.054618e-002,
 1.384843e-002,-3.153488e-002,-7.732160e-004, 2.292400e-002,
-6.8195043-003,-1.321869e-002, 6.661435e-003, 1.100677e-002,
-1.309874e-002, 1.949014e-003, 6.849167e-003};

FILTER fir_hpf = {
	35,
	NULL,
	fir_hpf35
};

/* 52 point bandpass matched FIR filter for pulse demo */
float fir_pulse52[52] = {
-1.2579e-002, 2.6513e-002,-2.8456e-016,-5.8760e-002,
 7.7212e-002,-1.4313e-015,-1.1906e-001, 1.4253e-001,
-3.7952e-015,-1.9465e-001, 2.2328e-001,-7.7489e-015,
-2.8546e-001, 3.1886e-001,-7.8037e-015,-3.8970e-001,
 4.2685e-001,-6.3138e-015,-5.0365e-001, 5.4285e-001,
-1.2521e-014,-6.2157e-001, 6.6052e-001,-9.0928e-015,
-7.3609e-001, 7.7207e-001,-3.6507e-015,-8.3886e-001,
 8.6905e-001,-1.1165e-014,-9.2156e-001, 9.4336e-001,
-3.8072e-015,-9.7694e-001, 9.8838e-001,-1.1836e-014,
-9.9994e-001, 9.9994e-001,-3.3578e-015,-9.5304e-001,
 8.9670e-001,-9.3099e-015,-7.3609e-001, 6.4111e-001,
-5.9892e-015,-4.4578e-001, 3.5365e-001,-2.8959e-015,
-1.9465e-001, 1.3058e-001,-1.7477e-016,-3.4013e-002};

FILTER fir_pulse = {
	35,
	NULL,
	fir_pulse52
};

/****************************************************************************
* FIRFILT.C - PROGRAM TO FIR FILTER THE RECORDS IN A DSP DATA FILE AND
*	GENERATE A DSP DATA FILE CONTAINING THE NEW FILTERED DATA.
*
* INPUTS: FILE NAMES, FILTER TYPE (LPF, HPF OR PULSE)
*
* OUTPUTS: DSP DATA FILE WITH FILTERED DATA
****************************************************************************/
main()
{
	DSP_FILE *dsp_in,*dsp_out; /* input and output files */
	FILTER *fir_ptr;

	int i,length,type;
	float *signal_in,*signal_out;

	char *trail,*trail_add;

/* open input file */
	dsp_in = open_read(get_string("input file name"));
	if(!dsp_in) exit(1); /* bad filename */

	length = dsp_in->rec_len;

	trail = read_trailer(dsp_in);
	if(trail && *trail) printf("\nFile trailer:\n%s\n",trail);

	signal_out = (float*)calloc(length,sizeof(float));
	if(!signal_out){
		printf("\nUnable to allocate output array\n");
		exit(1);
	}

/* get type of filter to use */
	type = get_int("filter type (0 = LPF, 1 = HPF, 2 = PULSE)",0,2);

	if(type == 0) fir_ptr = &fir_lpf;	/* lowpass filter, 0.2 cutoff */
	if(type == 1) fir_ptr = &fir_hpf;	/* highpass filter, 0.3 cutoff */
	if(type == 2) fir_ptr = &fir_pulse;	/* matched pulse filter */

/* open output records of floats */
	dsp_out = open_write(get_string("output file name"),FLOAT,dsp_in->records,length);

	if(!dsp_out) exit(1);

/* read, filter and write out data */
	 for(i=0;i<dsp_in->records;i++){
		signal_in = read_float_record(dsp_in);
		fir_filter_array(signal_in,signal_out,length,fir_ptr);
		write_record((char*)signal_out,dsp_out);
		free((char*)signal_in);		/* free old space */
	}

/* make descriptive trailer and write to file */
	if(type == 0) trail_add = "\nLowpass filtered using FIRFILT";
	if(type == 1) trail_add = "\nHighpass filtered using FIRFILT";
	if(type == 2) trail_add = "\nMatched pulse filtered using FIRFILT";
	write_trailer(append_trailer(trail_add,dsp_in),dsp_out);
}
