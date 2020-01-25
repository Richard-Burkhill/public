
/* FILTER INFORMATION STRUCTURE FOR FILTER ROUTINES */

typedef struct {
    unsigned int length;       /* size of filter */
    float *history;            /* pointer to history in filter */
    float *coef;               /* pointer to coefficients of filter */
} FILTER;

/* FILTERS: 3 FIR AND 2 IIR */

/* 35 point lowpass FIR filter cutoff at 0.2 */

  float  fir_lpf35[35] = {
  -6.849167e-003F, 1.949014e-003F, 1.309874e-002F, 1.100677e-002F,
  -6.661435e-003F,-1.321869e-002F, 6.819504e-003F, 2.292400e-002F,
   7.732160e-004F,-3.153488e-002F,-1.384843e-002F, 4.054618e-002F,
   3.841148e-002F,-4.790497e-002F,-8.973017e-002F, 5.285565e-002F,
   3.126515e-001F, 4.454146e-001F, 3.126515e-001F, 5.285565e-002F,
  -8.973017e-002F,-4.790497e-002F, 3.841148e-002F, 4.054618e-002F,
  -1.384843e-002F,-3.153488e-002F, 7.732160e-004F, 2.292400e-002F,
   6.819504e-003F,-1.321869e-002F,-6.661435e-003F, 1.100677e-002F,
   1.309874e-002F, 1.949014e-003F,-6.849167e-003F
                          };

    FILTER fir_lpf = {
        35,
        NULL,
        fir_lpf35
    };

/* 35 point highpass FIR filter cutoff at 0.3 same as fir_lpf35
except that every other coefficient has a different sign */

  float  fir_hpf35[35] = {
   6.849167e-003F, 1.949014e-003F,-1.309874e-002F, 1.100677e-002F,
   6.661435e-003F,-1.321869e-002F,-6.819504e-003F, 2.292400e-002F,
  -7.732160e-004F,-3.153488e-002F, 1.384843e-002F, 4.054618e-002F,
  -3.841148e-002F,-4.790497e-002F, 8.973017e-002F, 5.285565e-002F,
  -3.126515e-001F, 4.454146e-001F,-3.126515e-001F, 5.285565e-002F,
   8.973017e-002F,-4.790497e-002F,-3.841148e-002F, 4.054618e-002F,
   1.384843e-002F,-3.153488e-002F,-7.732160e-004F, 2.292400e-002F,
  -6.819504e-003F,-1.321869e-002F, 6.661435e-003F, 1.100677e-002F,
  -1.309874e-002F, 1.949014e-003F, 6.849167e-003F
                          };

    FILTER fir_hpf = {
        35,
        NULL,
        fir_hpf35
    };

/* 52 point bandpass matched FIR filter for pulse demo */

  float  fir_pulse52[52] = {
    -1.2579e-002F, 2.6513e-002F,-2.8456e-016F,-5.8760e-002F,
     7.7212e-002F,-1.4313e-015F,-1.1906e-001F, 1.4253e-001F,
    -3.7952e-015F,-1.9465e-001F, 2.2328e-001F,-7.7489e-015F,
    -2.8546e-001F, 3.1886e-001F,-7.8037e-015F,-3.8970e-001F,
     4.2685e-001F,-6.3138e-015F,-5.0365e-001F, 5.4285e-001F,
    -1.2521e-014F,-6.2157e-001F, 6.6052e-001F,-9.0928e-015F,
    -7.3609e-001F, 7.7207e-001F,-3.6507e-015F,-8.3886e-001F,
     8.6905e-001F,-1.1165e-014F,-9.2156e-001F, 9.4336e-001F,
    -3.8072e-015F,-9.7694e-001F, 9.8838e-001F,-1.1836e-014F,
    -9.9994e-001F, 9.9994e-001F,-3.3578e-015F,-9.5304e-001F,
     8.9670e-001F,-9.3099e-015F,-7.3609e-001F, 6.4111e-001F,
    -5.9892e-015F,-4.4578e-001F, 3.5365e-001F,-2.8959e-015F,
    -1.9465e-001F, 1.3058e-001F,-1.7477e-016F,-3.4013e-002F
                          };

    FILTER fir_pulse = {
        52,
        NULL,
        fir_pulse52
    };

/* IIR lowpass 3 section (5th order) elliptic filter
with 0.28 dB passband ripple and 40 dB stopband attenuation.
The cutoff frequency is 0.25*fs. */

    float iir_lpf5[13] = {
          0.0552961603F,
         -0.4363630712F,  0.0000000000F,  1.0000000000F,  0.0000000000F,
         -0.5233039260F,  0.8604439497F,  0.7039934993F,  1.0000000000F,
         -0.6965782046F,  0.4860509932F, -0.0103216320F,  1.0000000000F
        };

    FILTER iir_lpf = {
        3,                  /* 3 sections */
        NULL,
        iir_lpf5
    };

/* IIR highpass 3 section (6th order) chebyshev filter
with 1 dB passband ripple and cutoff frequency of 0.3*fs. */

    float iir_hpf6[13] = {
        0.0025892381F,
        0.5913599133F, 0.8879900575F,-2.0000000000F, 1.0000000000F,
        0.9156184793F, 0.6796731949F,-2.0000000000F, 1.0000000000F,
        1.3316441774F, 0.5193183422F,-2.0000000000F, 1.0000000000F
        };

    FILTER iir_hpf = {
        3,                  /* 3 sections */
        NULL,
        iir_hpf6
    };

/* filter function prototypes */

    extern void fir_filter_array(float *,float *,int,FILTER *);
    extern void fir_filter_int(short int *,short int *,int,short int *,int,int);

    extern float fir_filter(float,FILTER *);
    extern float iir_filter(float,FILTER *);
