#include <stdlib.h>
#include <stdio.h>
#include "disk.h"
#include "get.h"
#include "filter.h"

/**************************************************************************

FIRITEST.C - PROGRAM TO FILTER AN ARRAY OF INTEGERS.

INPUTS: PRECALCULATED FILTER COEFFICIENTS AND CHKL.DAT FILE.

OUTPUTS: FILTERED FILE CIFIL.DATA

*************************************************************************/

main ()
{
	static signed char in_data [6000]; 
	static short int input[6000], output[6000], fir_int[35]; 
	int i;

/* round the 35 point lowpass filter to 8 bits */
	for(i = 0 ; i < 35 ; i++)
		fir_int[i] = ROUND(127.0*fir_lpf35[i]/0.44541);

/* read in CHKL.DAT and convert to integers */
	read_record(in_data,open_read("chkl.dat"));
	for(i = 0 ; i < 6000 ; i++) 
		input[i] = in_data[i];

	fir_filter_int(input,output,6000,fir_int,35,285);

/* write out the single integer record to CIFIL.DAT */
	write_record((char *)output,open_write("cifil.dat",SIGNED_INT,1,6000));
	return 0;
}
