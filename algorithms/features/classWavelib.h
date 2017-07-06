//---------------------------------------------------------------------------
#ifndef classWavelibH
#define classWavelibH
//---------------------------------------------------------------------------
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "../../basics/classBase.h"
//---------------------------------------------------------------------------
#define PI2 6.28318530717958647692528676655900577 //hsfft
#define fft_type double //hsfft
#define MIN(a,b) (((a)<(b))?(a):(b)) //conv
#define MAX(a,b) (((a)>(b))?(a):(b)) //conv
//---------------------------------------------------------------------------
//from hsfft
typedef struct fft_t
	{
	fft_type re;
	fft_type im;
	} fft_data;
typedef struct fft_set* fft_object;
struct fft_set{
	int N;
	int sgn;
	int factors[64];
	int lf;
	int lt;
	fft_data twiddle[1];
	};
//---------------------------------------------------------------------------
//from real
typedef struct fft_real_set* fft_real_object;
struct fft_real_set{
	fft_object cobj;
	fft_data twiddle2[1];
	};
//---------------------------------------------------------------------------
//from conv
typedef struct conv_set* conv_object;
struct conv_set{
	fft_real_object fobj;
	fft_real_object iobj;
	int ilen1;
	int ilen2;
	int clen;
	};
//---------------------------------------------------------------------------
//from wavelib
typedef struct wave_set* wave_object;
struct wave_set{
	char wname[50];
	int filtlength;// When all filters are of the same length. [Matlab uses zero-padding to make all filters of the same length]
	int lpd_len;// Default filtlength = lpd_len = lpr_len = hpd_len = hpr_len
	int hpd_len;
	int lpr_len;
	int hpr_len;
	double *lpd;
	double *hpd;
	double *lpr;
	double *hpr;
	double params[0];
	};
typedef struct wt_set* wt_object;
struct wt_set{
	wave_object wave;
	conv_object cobj;
	char method[10];
	int siglength;// Length of the original signal.
	int outlength;// Length of the output DWT vector
	int lenlength;// Length of the Output Dimension Vector "length"
	int J; // Number of decomposition Levels
	int MaxIter;// Maximum Iterations J <= MaxIter
	int even;// even = 1 if signal is of even length. even = 0 otherwise
	char ext[10];// Type of Extension used - "per" or "sym"
	char cmethod[10]; // Convolution Method - "direct" or "FFT"

	int N; //
	int cfftset;
	int zpad;
	int length[102];
	double *output;
	double params[0];
	};
typedef struct wtree_set* wtree_object;
struct wtree_set{
	wave_object wave;
	conv_object cobj;
	char method[10];
	int siglength;// Length of the original signal.
	int outlength;// Length of the output DWT vector
	int lenlength;// Length of the Output Dimension Vector "length"
	int J; // Number of decomposition Levels
	int MaxIter;// Maximum Iterations J <= MaxIter
	int even;// even = 1 if signal is of even length. even = 0 otherwise
	char ext[10];// Type of Extension used - "per" or "sym"

	int N; //
	int nodes;
	int cfftset;
	int zpad;
	int length[102];
	double *output;
	int *nodelength;
	int *coeflength;
	double params[0];
	};
typedef struct wpt_set* wpt_object;
struct wpt_set{
	wave_object wave;
	conv_object cobj;
	int siglength;// Length of the original signal.
	int outlength;// Length of the output DWT vector
	int lenlength;// Length of the Output Dimension Vector "length"
	int J; // Number of decomposition Levels
	int MaxIter;// Maximum Iterations J <= MaxIter
	int even;// even = 1 if signal is of even length. even = 0 otherwise
	char ext[10];// Type of Extension used - "per" or "sym"
	char entropy[20];
	double eparam;

	int N; //
	int nodes;
	int length[102];
	double *output;
	double *costvalues;
	double *basisvector;
	int *nodeindex;
	int *numnodeslevel;
	int *coeflength;
	double params[0];
	};
//---------------------------------------------------------------------------
class PACKAGE cWavelib : public cBase
	{
public:
	cWavelib();
	void setMemo(TMemo* memo);

	// -- Wavelib
	wave_object wave_init(char* wname);
	void wave_summary(wave_object obj);
	void wave_free(wave_object object);

	wt_object wt_init(wave_object wave,char* method, int siglength, int J);
	void dwt(wt_object wt, double *inp); //discrete wavelet transform (decimated)
	void swt(wt_object wt, double *inp); //stationary wavelet transform (undecimated)
	void modwt(wt_object wt, double *inp); //maximal overlap discrete wavelet transform (undecimated)
	void wt_summary(wt_object wt);
	void wt_free(wt_object object);

	wtree_object wtree_init(wave_object wave, int siglength, int J);
	void wtree_summary(wtree_object wt);
	void wtree_free(wtree_object object);

	wpt_object wpt_init(wave_object wave, int siglength, int J);
	void wpt_summary(wpt_object wt);
	void wpt_free(wpt_object object);

private:
	TMemo*		Memo;
	void 		Print(char* msg, ...);

	//-----------------------------------------------------------------------
	//-- WAVELIB ------------------------------------------------------------
	//-----------------------------------------------------------------------
	void idwt(wt_object wt, double *dwtop);
	void wtree(wtree_object wt, double *inp);
	void dwpt(wpt_object wt, double *inp);
	void idwpt(wpt_object wt, double *dwtop);
	void iswt(wt_object wt, double *swtop);
	void imodwt(wt_object wt, double *dwtop);
	void setDWTExtension(wt_object wt, char *extension);
	void setWTREEExtension(wtree_object wt, char *extension);
	void setDWPTExtension(wpt_object wt, char *extension);
	void setDWPTEntropy(wpt_object wt, char *entropy, double eparam);
	void setWTConv(wt_object wt, char *cmethod);
	int getWTREENodelength(wtree_object wt, int X);
	void getWTREECoeffs(wtree_object wt, int X, int Y, double *coeffs, int N);
	int getDWPTNodelength(wpt_object wt, int X);
	void getDWPTCoeffs(wpt_object wt, int X, int Y, double *coeffs, int N);

	void wconv(wt_object wt, double *sig, int N, double *filt, int L, double *oup);
	void dwt_per(wt_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD);
	void dwpt_per(wpt_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD);
	void dwpt_sym(wpt_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD);
	void wtree_per(wtree_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD);
	void dwt_sym(wt_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD);
	void wtree_sym(wtree_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD);
	void dwt1(wt_object wt,double *sig,int len_sig, double *cA, int len_cA, double *cD, int len_cD);
	int ipow2(int n);
	void idwt1(wt_object wt,double *temp, double *cA_up,double *cA, int len_cA,double *cD,int len_cD,double *X_lp,double *X_hp,double *X);
	void idwt_per(wt_object wt, double *cA, int len_cA, double *cD, int len_cD,  double *X);
	void idwt_sym(wt_object wt, double *cA, int len_cA, double *cD, int len_cD, double *X);
	void idwpt_per(wpt_object wt, double *cA, int len_cA, double *cD, int len_cD, double *X);
	void idwpt_sym(wpt_object wt, double *cA, int len_cA, double *cD, int len_cD, double *X);
	void swt_per(wt_object wt,int M, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD);
	void swt_fft(wt_object wt, double *inp);
	void swt_direct(wt_object wt, double *inp);
	void modwt_per(wt_object wt, int M, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD);
	void imodwt_per(wt_object wt,int M, double *cA, int len_cA, double *cD, int len_cD, double *X);

	//-----------------------------------------------------------------------
	//-- WTMATH -------------------------------------------------------------
	//-----------------------------------------------------------------------
	int upsamp(double *x, int lenx, int M, double *y);
	int upsamp2(double *x, int lenx, int M, double *y);
	int downsamp(double *x, int lenx, int M, double *y);
	int per_ext(double *sig, int len, int a,double *oup);
	int symm_ext(double *sig, int len, int a,double *oup);
	void circshift(double *array, int N, int L);
	int testSWTlength(int N, int J);
	int wmaxiter(int sig_len, int filt_len);
	double costfunc(double *x, int N, char *entropy, double p);

	int isign(int N);
	int iabs(int N);
	double entropy_s(double *x,int N);
	double entropy_t(double *x,int N, double t);
	double entropy_n(double *x,int N,double p);
	double entropy_l(double *x,int N);

	//-----------------------------------------------------------------------
	//-- WAVEFILT -----------------------------------------------------------
	//-----------------------------------------------------------------------
	int filtlength(char* name);
	int filtcoef(char* name, double *lp1, double *hp1, double *lp2, double *hp2);

	//-----------------------------------------------------------------------
	//-- CONV ---------------------------------------------------------------
	//-----------------------------------------------------------------------
	conv_object conv_init(int N, int L);
	int factorf(int M);
	int findnext(int M);
	int findnexte(int M);
	void conv_direct(fft_type *inp1,int N, fft_type *inp2, int L,fft_type *oup);
	void conv_directx(fft_type *inp1,int N, fft_type *inp2, int L,fft_type *oup);
	void conv_fft(const conv_object obj,fft_type *inp1,fft_type *inp2,fft_type *oup);
	void free_conv(conv_object object);

	//-----------------------------------------------------------------------
	//-- REAL ---------------------------------------------------------------
	//-----------------------------------------------------------------------
	fft_real_object fft_real_init(int N, int sgn);
	void fft_r2c_exec(fft_real_object obj,fft_type *inp,fft_data *oup);
	void fft_c2r_exec(fft_real_object obj,fft_data *inp,fft_type *oup);
	void free_real_fft(fft_real_object object);

	//-----------------------------------------------------------------------
	//-- HSFFT --------------------------------------------------------------
	//-----------------------------------------------------------------------
	fft_object fft_init(int N, int sgn);
	void fft_exec(fft_object obj,fft_data *inp,fft_data *oup);
	int divideby(int M,int d);
	int dividebyN(int N);
	int factors(int M, int* arr);
	void twiddle(fft_data *sig,int N, int radix);
	void longvectorN(fft_data *sig,int N, int *array, int M);
	void free_fft(fft_object object);

	void mixed_radix_dit_rec(fft_data *op,fft_data *ip,const fft_object obj, int sgn, int N,int l,int inc);
	void bluestein_exp(fft_data *hl, fft_data *hlt, int len, int M);
	void bluestein_fft(fft_data *data, fft_data *oup,fft_object obj,int sgn, int N);
	};
//---------------------------------------------------------------------------
#endif
