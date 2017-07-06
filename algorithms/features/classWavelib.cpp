//---------------------------------------------------------------------------
#pragma hdrstop

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "classWavelib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
cWavelib::cWavelib()
	{
	}
//---------------------------------------------------------------------------
void cWavelib::setMemo(TMemo* memo)
	{
	Memo = memo;
	}
//---------------------------------------------------------------------------
void cWavelib::Print(char* msg, ...)
	{
	char    buffer[512];
	int     nsiz;
	va_list argptr;

	va_start(argptr, msg);
	nsiz = vsnprintf(0, 0, msg, argptr);
	if (nsiz >= sizeof(buffer)-2) nsiz = sizeof(buffer)-2;

	vsnprintf(buffer, nsiz, msg, argptr);
	buffer[nsiz] = 0;

	Memo->Lines->Add(buffer);
	va_end(argptr);
	}
//---------------------------------------------------------------------------
/***************************************************************************/
/************************   WAVELIB   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
wave_object cWavelib::wave_init(char* wname) {
	wave_object obj = NULL;
	int retval;
	retval = 0;

	if (wname != NULL) {
		retval = filtlength(wname);
		//obj->filtlength = retval;
		//strcopy(obj->wname, wname);
	}

	obj = (wave_object)malloc(sizeof(struct wave_set) + sizeof(double)* 4 * retval);

	obj->filtlength = retval;
	obj->lpd_len = obj->hpd_len = obj->lpr_len = obj->hpr_len = obj->filtlength;
	strcpy(obj->wname, wname);
	if (wname != NULL) {
		filtcoef(wname,obj->params,obj->params+retval,obj->params+2*retval,obj->params+3*retval);
	}
	obj->lpd = &obj->params[0];
	obj->hpd = &obj->params[retval];
	obj->lpr = &obj->params[2 * retval];
	obj->hpr = &obj->params[3 * retval];
	return obj;
}

wt_object cWavelib::wt_init(wave_object wave,char* method, int siglength,int J) {
	int size,i,MaxIter;
	wt_object obj = NULL;

	size = wave->filtlength;

	if (J > 100) {
		printf("\n The Decomposition Iterations Cannot Exceed 100. Exiting \n");
		exit(-1);
	}

	MaxIter = wmaxiter(siglength, size);

	if (J > MaxIter) {
		printf("\n Error - The Signal Can only be iterated %d times using this wavelet. Exiting\n",MaxIter);
		exit(-1);
	}

	if (method == NULL) {
		obj = (wt_object)malloc(sizeof(struct wt_set) + sizeof(double)* (siglength +  2 * J * (size+1)));
		obj->outlength = siglength + 2 * J * (size + 1); // Default
		strcpy(obj->ext, "sym"); // Default
	}
	else if (!strcmp(method, "dwt") || !strcmp(method, "DWT")) {
		obj = (wt_object)malloc(sizeof(struct wt_set) + sizeof(double)* (siglength + 2 * J * (size + 1)));
		obj->outlength = siglength + 2 * J * (size + 1); // Default
		strcpy(obj->ext, "sym"); // Default
	}
	else if (!strcmp(method, "swt") || !strcmp(method, "SWT")) {
		if (!testSWTlength(siglength, J)) {
			printf("\n For SWT the signal length must be a multiple of 2^J. \n");
			exit(-1);
		}

		obj = (wt_object)malloc(sizeof(struct wt_set) + sizeof(double)* (siglength * (J + 1)));
		obj->outlength = siglength * (J + 1); // Default
		strcpy(obj->ext, "per"); // Default
	}
	else if (!strcmp(method, "modwt") || !strcmp(method, "MODWT")) {

		if (!strstr(wave->wname,"db")) {
			if (!strstr(wave->wname, "sym")) {
				if (!strstr(wave->wname, "coif")) {
					printf("\n MODWT is only implemented for orthogonal wavelet families - db, sym and coif \n");
					exit(-1);
				}
			}
		}

		obj = (wt_object)malloc(sizeof(struct wt_set) + sizeof(double)* (siglength * (J + 1)));
		obj->outlength = siglength * (J + 1); // Default
		strcpy(obj->ext, "per"); // Default
	}

	obj->wave = wave;
	obj->siglength = siglength;
	obj->J = J;
	obj->MaxIter = MaxIter;
	strcpy(obj->method, method);

	if (siglength % 2 == 0) {
		obj->even = 1;
	}
	else {
		obj->even = 0;
	}

	obj->cobj = NULL;

	strcpy(obj->cmethod, "direct"); // Default
	obj->cfftset = 0;
	obj->lenlength = J + 2;
	obj->output = &obj->params[0];
	if (!strcmp(method, "dwt") || !strcmp(method, "DWT")) {
		for (i = 0; i < siglength + 2 * J * (size + 1); ++i) {
			obj->params[i] = 0.0;
		}
	}
	else if (!strcmp(method, "swt") || !strcmp(method, "SWT") || !strcmp(method, "modwt") || !strcmp(method, "MODWT")) {
		for (i = 0; i < siglength * (J + 1); ++i) {
			obj->params[i] = 0.0;
		}
	}

	return obj;
}

wtree_object cWavelib::wtree_init(wave_object wave, int siglength,int J) {
    int size,i,MaxIter,temp,temp2,elength,nodes;
	wtree_object obj = NULL;

	size = wave->filtlength;

	if (J > 100) {
		printf("\n The Decomposition Iterations Cannot Exceed 100. Exiting \n");
		exit(-1);
	}


	MaxIter = wmaxiter(siglength, size);
	if (J > MaxIter) {
		printf("\n Error - The Signal Can only be iterated %d times using this wavelet. Exiting\n", MaxIter);
		exit(-1);
	}
	temp = 1;
	elength = 0;
	nodes = 0;
	for(i = 0; i < J;++i) {
	  temp *= 2;
	  nodes += temp;
	  temp2 = (size - 2) * (temp - 1);
	  elength += temp2;
	}

	obj = (wtree_object)malloc(sizeof(struct wtree_set) + sizeof(double)* (siglength * (J + 1) + elength + nodes + J + 1));
	obj->outlength = siglength * (J + 1) + elength;
	strcpy(obj->ext, "sym");

	obj->wave = wave;
	obj->siglength = siglength;
	obj->J = J;
	obj->MaxIter = MaxIter;
	strcpy(obj->method, "dwt");

	if (siglength % 2 == 0) {
		obj->even = 1;
	}
	else {
		obj->even = 0;
	}

	obj->cobj = NULL;
	obj->nodes = nodes;

	obj->cfftset = 0;
	obj->lenlength = J + 2;
	obj->output = &obj->params[0];
	obj->nodelength = (int*) &obj->params[siglength * (J + 1) + elength];
	obj->coeflength = (int*)&obj->params[siglength * (J + 1) + elength + nodes];

	for (i = 0; i < siglength * (J + 1) + elength + nodes + J + 1; ++i) {
	       obj->params[i] = 0.0;
	}


	return obj;
}

wpt_object cWavelib::wpt_init(wave_object wave, int siglength, int J) {
	int size, i, MaxIter, temp, nodes,elength,p2,N,lp;
	wpt_object obj = NULL;

	size = wave->filtlength;

	if (J > 100) {
		printf("\n The Decomposition Iterations Cannot Exceed 100. Exiting \n");
		exit(-1);
	}


	MaxIter = wmaxiter(siglength, size);
	if (J > MaxIter) {
		printf("\n Error - The Signal Can only be iterated %d times using this wavelet. Exiting\n", MaxIter);
		exit(-1);
	}
	temp = 1;
	nodes = 0;
	for (i = 0; i < J; ++i) {
		temp *= 2;
		nodes += temp;
	}

	i = J;
	p2 = 2;
	N = siglength;
	lp = size;
	elength = 0;
	while (i > 0) {
		N = N + lp - 2;
		N = (int)ceil((double)N / 2.0);
		elength = p2 * N;
		i--;
		p2 *= 2;
	}
	//printf("elength %d", elength);

	obj = (wpt_object)malloc(sizeof(struct wpt_set) + sizeof(double)* (elength + 4 * nodes + 2 * J + 6));
	obj->outlength = siglength + 2 * (J + 1) * (size + 1);
	strcpy(obj->ext, "sym");
	strcpy(obj->entropy, "shannon");
	obj->eparam = 0.0;

	obj->wave = wave;
	obj->siglength = siglength;
	obj->J = J;
	obj->MaxIter = MaxIter;

	if (siglength % 2 == 0) {
		obj->even = 1;
	}
	else {
		obj->even = 0;
	}

	obj->cobj = NULL;
	obj->nodes = nodes;

	obj->lenlength = J + 2;
	obj->output = &obj->params[0];
	obj->costvalues = &obj->params[elength];
	obj->basisvector = &obj->params[elength + nodes + 1];
	obj->nodeindex = (int*)&obj->params[elength + 2*nodes + 2];
	obj->numnodeslevel = (int*)&obj->params[elength + 4 * nodes + 4];
	obj->coeflength = (int*)&obj->params[elength + 4 * nodes + J + 5];

	for (i = 0; i < elength + 4 * nodes + 2 * J + 6; ++i) {
		obj->params[i] = 0.0;
	}


	return obj;
}


void cWavelib::wconv(wt_object wt, double *sig, int N, double *filt, int L, double *oup) {
	if (!strcmp(wt->cmethod,"direct")) {
		conv_direct(sig, N, filt, L, oup);
	}
	else if (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT")) {
		if (wt->cfftset == 0) {
			wt->cobj = conv_init(N, L);
			conv_fft(wt->cobj, sig, filt, oup);
			free_conv(wt->cobj);
		}
		else {
			conv_fft(wt->cobj, sig, filt, oup);
		}
	}
	else {
		printf("Convolution Only accepts two methods - direct and fft");
		exit(-1);
	}
}


void cWavelib::dwt_per(wt_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD) {
	int l,l2,isodd,i,t,len_avg;

	len_avg = wt->wave->lpd_len;
	l2 = len_avg / 2;
	isodd = N % 2;

	for (i = 0; i < len_cA; ++i) {
		t = 2 * i + l2;
		cA[i] = 0.0;
		cD[i] = 0.0;
		for (l = 0; l < len_avg; ++l) {
			if ((t - l) >= l2 && (t - l) < N) {
				cA[i] += wt->wave->lpd[l] * inp[t - l];
				cD[i] += wt->wave->hpd[l] * inp[t - l];
			}
			else if ((t - l) < l2 && (t - l) >= 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - l];
				cD[i] += wt->wave->hpd[l] * inp[t - l];
			}
			else if ((t - l) < 0 && isodd == 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - l + N];
				cD[i] += wt->wave->hpd[l] * inp[t - l + N];
			}
			else if ((t - l) < 0 && isodd == 1) {
				if ((t - l) != -1) {
					cA[i] += wt->wave->lpd[l] * inp[t - l + N + 1];
					cD[i] += wt->wave->hpd[l] * inp[t - l + N + 1];
				}
				else {
					cA[i] += wt->wave->lpd[l] * inp[N - 1];
					cD[i] += wt->wave->hpd[l] * inp[N - 1];
				}
			}
			else if ((t - l) >= N && isodd == 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - l - N];
				cD[i] += wt->wave->hpd[l] * inp[t - l - N];
			}
			else if ((t - l) >= N && isodd == 1) {
				if (t - l != N) {
					cA[i] += wt->wave->lpd[l] * inp[t - l - (N + 1)];
					cD[i] += wt->wave->hpd[l] * inp[t - l - (N + 1)];
				}
				else {
					cA[i] += wt->wave->lpd[l] * inp[N - 1];
					cD[i] += wt->wave->hpd[l] * inp[N - 1];
				}
			}

		}
	}



}

void cWavelib::wtree_per(wtree_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD) {
	int l, l2, isodd, i, t, len_avg;

	len_avg = wt->wave->lpd_len;
	l2 = len_avg / 2;
	isodd = N % 2;

	for (i = 0; i < len_cA; ++i) {
		t = 2 * i + l2;
		cA[i] = 0.0;
		cD[i] = 0.0;
		for (l = 0; l < len_avg; ++l) {
			if ((t - l) >= l2 && (t - l) < N) {
				cA[i] += wt->wave->lpd[l] * inp[t - l];
				cD[i] += wt->wave->hpd[l] * inp[t - l];
			}
			else if ((t - l) < l2 && (t - l) >= 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - l];
				cD[i] += wt->wave->hpd[l] * inp[t - l];
			}
			else if ((t - l) < 0 && isodd == 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - l + N];
				cD[i] += wt->wave->hpd[l] * inp[t - l + N];
			}
			else if ((t - l) < 0 && isodd == 1) {
				if ((t - l) != -1) {
					cA[i] += wt->wave->lpd[l] * inp[t - l + N + 1];
					cD[i] += wt->wave->hpd[l] * inp[t - l + N + 1];
				}
				else {
					cA[i] += wt->wave->lpd[l] * inp[N - 1];
					cD[i] += wt->wave->hpd[l] * inp[N - 1];
				}
			}
			else if ((t - l) >= N && isodd == 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - l - N];
				cD[i] += wt->wave->hpd[l] * inp[t - l - N];
			}
			else if ((t - l) >= N && isodd == 1) {
				if (t - l != N) {
					cA[i] += wt->wave->lpd[l] * inp[t - l - (N + 1)];
					cD[i] += wt->wave->hpd[l] * inp[t - l - (N + 1)];
				}
				else {
					cA[i] += wt->wave->lpd[l] * inp[N - 1];
					cD[i] += wt->wave->hpd[l] * inp[N - 1];
				}
			}

		}
	}



}

void cWavelib::dwpt_per(wpt_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD) {
	int l, l2, isodd, i, t, len_avg;

	len_avg = wt->wave->lpd_len;
	l2 = len_avg / 2;
	isodd = N % 2;

	for (i = 0; i < len_cA; ++i) {
		t = 2 * i + l2;
		cA[i] = 0.0;
		cD[i] = 0.0;
		for (l = 0; l < len_avg; ++l) {
			if ((t - l) >= l2 && (t - l) < N) {
				cA[i] += wt->wave->lpd[l] * inp[t - l];
				cD[i] += wt->wave->hpd[l] * inp[t - l];
			}
			else if ((t - l) < l2 && (t - l) >= 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - l];
				cD[i] += wt->wave->hpd[l] * inp[t - l];
			}
			else if ((t - l) < 0 && isodd == 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - l + N];
				cD[i] += wt->wave->hpd[l] * inp[t - l + N];
			}
			else if ((t - l) < 0 && isodd == 1) {
				if ((t - l) != -1) {
					cA[i] += wt->wave->lpd[l] * inp[t - l + N + 1];
					cD[i] += wt->wave->hpd[l] * inp[t - l + N + 1];
				}
				else {
					cA[i] += wt->wave->lpd[l] * inp[N - 1];
					cD[i] += wt->wave->hpd[l] * inp[N - 1];
				}
			}
			else if ((t - l) >= N && isodd == 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - l - N];
				cD[i] += wt->wave->hpd[l] * inp[t - l - N];
			}
			else if ((t - l) >= N && isodd == 1) {
				if (t - l != N) {
					cA[i] += wt->wave->lpd[l] * inp[t - l - (N + 1)];
					cD[i] += wt->wave->hpd[l] * inp[t - l - (N + 1)];
				}
				else {
					cA[i] += wt->wave->lpd[l] * inp[N - 1];
					cD[i] += wt->wave->hpd[l] * inp[N - 1];
				}
			}

		}
	}



}

void cWavelib::dwt_sym(wt_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD) {
	int i,l, t, len_avg;

	len_avg = wt->wave->lpd_len;

	for (i = 0; i < len_cA; ++i) {
		t = 2 * i + 1;
		cA[i] = 0.0;
		cD[i] = 0.0;
		for (l = 0; l < len_avg; ++l) {
			if ((t - l) >= 0 && (t - l) < N) {
				cA[i] += wt->wave->lpd[l] * inp[t - l];
				cD[i] += wt->wave->hpd[l] * inp[t - l];
			}
			else if ((t - l) < 0) {
				cA[i] += wt->wave->lpd[l] * inp[-t + l - 1];
				cD[i] += wt->wave->hpd[l] * inp[-t + l - 1];
			}
			else if ((t - l) >= N) {
				cA[i] += wt->wave->lpd[l] * inp[2 * N - t + l - 1];
				cD[i] += wt->wave->hpd[l] * inp[2 * N - t + l - 1];
			}

		}
	}


}

void cWavelib::wtree_sym(wtree_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD) {
	int i, l, t, len_avg;

	len_avg = wt->wave->lpd_len;

	for (i = 0; i < len_cA; ++i) {
		t = 2 * i + 1;
		cA[i] = 0.0;
		cD[i] = 0.0;
		for (l = 0; l < len_avg; ++l) {
			if ((t - l) >= 0 && (t - l) < N) {
				cA[i] += wt->wave->lpd[l] * inp[t - l];
				cD[i] += wt->wave->hpd[l] * inp[t - l];
			}
			else if ((t - l) < 0) {
				cA[i] += wt->wave->lpd[l] * inp[-t + l - 1];
				cD[i] += wt->wave->hpd[l] * inp[-t + l - 1];
			}
			else if ((t - l) >= N) {
				cA[i] += wt->wave->lpd[l] * inp[2 * N - t + l - 1];
				cD[i] += wt->wave->hpd[l] * inp[2 * N - t + l - 1];
			}

		}
	}


}

void cWavelib::dwpt_sym(wpt_object wt, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD) {
	int i, l, t, len_avg;

	len_avg = wt->wave->lpd_len;

	for (i = 0; i < len_cA; ++i) {
		t = 2 * i + 1;
		cA[i] = 0.0;
		cD[i] = 0.0;
		for (l = 0; l < len_avg; ++l) {
			if ((t - l) >= 0 && (t - l) < N) {
				cA[i] += wt->wave->lpd[l] * inp[t - l];
				cD[i] += wt->wave->hpd[l] * inp[t - l];
			}
			else if ((t - l) < 0) {
				cA[i] += wt->wave->lpd[l] * inp[-t + l - 1];
				cD[i] += wt->wave->hpd[l] * inp[-t + l - 1];
			}
			else if ((t - l) >= N) {
				cA[i] += wt->wave->lpd[l] * inp[2 * N - t + l - 1];
				cD[i] += wt->wave->hpd[l] * inp[2 * N - t + l - 1];
			}

		}
	}


}

void cWavelib::dwt1(wt_object wt,double *sig,int len_sig, double *cA, int len_cA, double *cD, int len_cD) {
	int len_avg,D,lf;
	double *signal,*cA_undec;
	len_avg = (wt->wave->lpd_len + wt->wave->hpd_len) / 2;
	//len_sig = 2 * (int)ceil((double)len_sig / 2.0);

	D = 2;

	if (!strcmp(wt->ext, "per")) {
		signal = (double*)malloc(sizeof(double)* (len_sig + len_avg + (len_sig % 2)));

		len_sig = per_ext(sig, len_sig, len_avg / 2, signal);

		cA_undec = (double*)malloc(sizeof(double)* (len_sig + len_avg + wt->wave->lpd_len - 1));

		if (wt->wave->lpd_len == wt->wave->hpd_len && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
			wt->cobj = conv_init(len_sig + len_avg, wt->wave->lpd_len);
			wt->cfftset = 1;
		}
		else if (!(wt->wave->lpd_len == wt->wave->hpd_len)) {
			printf("Decomposition Filters must have the same length.");
			exit(-1);
		}

		wconv(wt, signal, len_sig + len_avg, wt->wave->lpd, wt->wave->lpd_len, cA_undec);

		downsamp(cA_undec + len_avg, len_sig, D, cA);

		wconv(wt, signal, len_sig + len_avg, wt->wave->hpd, wt->wave->hpd_len, cA_undec);

		downsamp(cA_undec + len_avg, len_sig, D, cD);
	}
	else if (!strcmp(wt->ext, "sym")) {
		//printf("\n YES %s \n", wt->ext);
		lf = wt->wave->lpd_len;// lpd and hpd have the same length

		signal = (double*)malloc(sizeof(double)* (len_sig + 2 * (lf - 1)));

		len_sig = symm_ext(sig, len_sig, lf - 1, signal);

		cA_undec = (double*)malloc(sizeof(double)* (len_sig + 3 * (lf - 1)));

		if (wt->wave->lpd_len == wt->wave->hpd_len && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
			wt->cobj = conv_init(len_sig + 2 * (lf - 1), lf);
			wt->cfftset = 1;
		}
		else if (!(wt->wave->lpd_len == wt->wave->hpd_len)) {
			printf("Decomposition Filters must have the same length.");
			exit(-1);
		}


		wconv(wt, signal, len_sig + 2 * (lf - 1), wt->wave->lpd, wt->wave->lpd_len, cA_undec);

		downsamp(cA_undec + lf, len_sig + lf - 2, D, cA);

		wconv(wt, signal, len_sig + 2 * (lf - 1), wt->wave->hpd, wt->wave->hpd_len, cA_undec);

		downsamp(cA_undec + lf, len_sig + lf - 2, D, cD);
	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}


	if (wt->wave->lpd_len == wt->wave->hpd_len && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
		free_conv(wt->cobj);
		wt->cfftset = 0;
	}

	free(signal);
	free(cA_undec);
}

void cWavelib::dwt(wt_object wt,double *inp) {
	int i,J,temp_len,iter,N,lp;
	int len_cA;
	double *orig,*orig2;

	temp_len = wt->siglength;
	J = wt->J;
	wt->length[J + 1] = temp_len;
	wt->outlength = 0;
	wt->zpad = 0;
	orig = (double*)malloc(sizeof(double)* temp_len);
	orig2 = (double*)malloc(sizeof(double)* temp_len);
	/*
	if ((temp_len % 2) == 0) {
	wt->zpad = 0;
	orig = (double*)malloc(sizeof(double)* temp_len);
	orig2 = (double*)malloc(sizeof(double)* temp_len);
	}
	else {
	wt->zpad = 1;
	temp_len++;
	orig = (double*)malloc(sizeof(double)* temp_len);
	orig2 = (double*)malloc(sizeof(double)* temp_len);
	}
	*/

	for (i = 0; i < wt->siglength; ++i) {
		orig[i] = inp[i];
	}

	if (wt->zpad == 1) {
		orig[temp_len - 1] = orig[temp_len - 2];
	}

	N = temp_len;
	lp = wt->wave->lpd_len;

	if (!strcmp(wt->ext,"per")) {
		i = J;
		while (i > 0) {
			N = (int)ceil((double)N / 2.0);
			wt->length[i] = N;
			wt->outlength += wt->length[i];
			i--;
		}
		wt->length[0] = wt->length[1];
		wt->outlength += wt->length[0];
		N = wt->outlength;

		for (iter = 0; iter < J; ++iter) {
			len_cA = wt->length[J - iter];
			N -= len_cA;
			if ( !strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT") ) {
				dwt1(wt, orig, temp_len, orig2, len_cA, wt->params + N, len_cA);
			}
			else {
				dwt_per(wt, orig, temp_len, orig2, len_cA, wt->params + N, len_cA);
			}
			temp_len = wt->length[J - iter];
			if (iter == J - 1) {
				for (i = 0; i < len_cA; ++i) {
					wt->params[i] = orig2[i];
				}
			}
			else {
				for (i = 0; i < len_cA; ++i) {
					orig[i] = orig2[i];
				}
			}
		}
	}
	else if (!strcmp(wt->ext,"sym")) {
		//printf("\n YES %s \n", wt->ext);
		i = J;
		while (i > 0) {
			N = N + lp - 2;
			N = (int) ceil((double)N / 2.0);
			wt->length[i] = N;
			wt->outlength += wt->length[i];
			i--;
		}
		wt->length[0] = wt->length[1];
		wt->outlength += wt->length[0];
		N = wt->outlength;

		for (iter = 0; iter < J; ++iter) {
			len_cA = wt->length[J - iter];
			N -= len_cA;
			if (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT")) {
				dwt1(wt, orig, temp_len, orig2, len_cA, wt->params + N, len_cA);
			}
			else {
				dwt_sym(wt, orig, temp_len, orig2, len_cA, wt->params + N, len_cA);
			}
			temp_len = wt->length[J - iter];

			if (iter == J - 1) {
				for (i = 0; i < len_cA; ++i) {
					wt->params[i] = orig2[i];
				}
			}
			else {
				for (i = 0; i < len_cA; ++i) {
					orig[i] = orig2[i];
				}
			}
		}
	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}

	free(orig);
	free(orig2);
}

void cWavelib::wtree(wtree_object wt,double *inp) {
	int i,J,temp_len,iter,N,lp,p2,k,N2,Np;
	int len_cA,t,t2,it1;
	double *orig;

	temp_len = wt->siglength;
	J = wt->J;
	wt->length[J + 1] = temp_len;
	wt->outlength = 0;
	wt->zpad = 0;
	orig = (double*)malloc(sizeof(double)* temp_len);
	/*
	if ((temp_len % 2) == 0) {
		wt->zpad = 0;
		orig = (double*)malloc(sizeof(double)* temp_len);
	}
	else {
		wt->zpad = 1;
		temp_len++;
		orig = (double*)malloc(sizeof(double)* temp_len);
	}
	*/
	for (i = 0; i < wt->siglength; ++i) {
		orig[i] = inp[i];
	}

	if (wt->zpad == 1) {
		orig[temp_len - 1] = orig[temp_len - 2];
	}

	N = temp_len;
	lp = wt->wave->lpd_len;
        p2 = 1;

	if (!strcmp(wt->ext,"per")) {
		i = J;
                p2 = 2;
		while (i > 0) {
			N = (int)ceil((double)N / 2.0);
			wt->length[i] = N;
			wt->outlength += p2 * (wt->length[i]);
			i--;
                        p2 *= 2;
		}
		wt->length[0] = wt->length[1];

		N2 = N = wt->outlength;
                p2 = 1;
		for (iter = 0; iter < J; ++iter) {
			len_cA = wt->length[J - iter];
                        N2 -= 2 * p2 * len_cA;
                        N = N2;
                        for(k = 0; k < p2;++k) {
                            if (iter == 0) {
                               wtree_per(wt, orig, temp_len, wt->params + N, len_cA, wt->params + N + len_cA, len_cA);
                            } else {
                                wtree_per(wt, wt->params + Np + k * temp_len, temp_len, wt->params + N, len_cA, wt->params + N + len_cA, len_cA);
                            }
                            N += 2 * len_cA;
                        }

			temp_len = wt->length[J - iter];
			p2 = 2 * p2;
            Np = N2;
		}
	}
	else if (!strcmp(wt->ext,"sym")) {
		//printf("\n YES %s \n", wt->ext);
		i = J;
                p2 = 2;
		while (i > 0) {
			N = N + lp - 2;
			N = (int) ceil((double)N / 2.0);
			wt->length[i] = N;
			wt->outlength += p2 * (wt->length[i]);
			i--;
                        p2 *= 2;
		}
		wt->length[0] = wt->length[1];

		N2 = N = wt->outlength;
                p2 = 1;

                for (iter = 0; iter < J; ++iter) {
			len_cA = wt->length[J - iter];
                        N2 -= 2 * p2 * len_cA;
                        N = N2;
                        for(k = 0; k < p2;++k) {
                            if (iter == 0) {
                                wtree_sym(wt, orig, temp_len, wt->params + N, len_cA, wt->params + N + len_cA, len_cA);
                            } else {
                                wtree_sym(wt, wt->params + Np + k * temp_len, temp_len, wt->params + N, len_cA, wt->params + N + len_cA, len_cA);
                            }
                            N += 2 * len_cA;
                        }

			temp_len = wt->length[J - iter];
			p2 = 2 * p2;
            Np = N2;
		}

	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}

	J = wt->J;
	t2 = wt->outlength - 2 * wt->length[J];
	p2 = 2;
	it1 = 0;
	for (i = 0; i < J; ++i) {
		t = t2;
		for (k = 0; k < p2; ++k) {
			wt->nodelength[it1] = t;
			it1++;
			t += wt->length[J - i];
		}
		p2 *= 2;
		t2 = t2 - p2 * wt->length[J - i - 1];
	}

	wt->coeflength[0] = wt->siglength;

	for (i = 1; i < J + 1; ++i) {
		wt->coeflength[i] = wt->length[J - i + 1];
	}

	free(orig);
}

int cWavelib::ipow2(int n) {
	int p,i;
	p = 1;

	for (i = 0; i < n; ++i) {
		p *= 2;
	}

	return p;
}

void cWavelib::dwpt(wpt_object wt, double *inp) {
	int i, J, temp_len, iter, N, lp, p2, k, N2, Np;
	int temp, elength, temp2,size,nodes,llb,n1,j;
	double eparam,v1,v2;
	int len_cA, t, t2, it1,it2;
	double *orig,*tree;
	int *nodelength;

	temp_len = wt->siglength;
	J = wt->J;
	wt->length[J + 1] = temp_len;
	wt->outlength = 0;
	temp = 1;
	elength = 0;
	size = wt->wave->filtlength;
	nodes = wt->nodes;
	n1 = nodes + 1;
	for (i = 0; i < J; ++i) {
		temp *= 2;
		temp2 = (size - 2) * (temp - 1);
		elength += temp2;
	}
	eparam = wt->eparam;
	orig = (double*)malloc(sizeof(double)* temp_len);
	tree = (double*)malloc(sizeof(double)* (temp_len * (J + 1) + elength));
	nodelength = (int*)malloc(sizeof(int)* nodes);

	for (i = 0; i < wt->siglength; ++i) {
		orig[i] = inp[i];
	}

	for (i = 0; i < temp_len * (J + 1) + elength; ++i) {
		tree[i] = 0.0;
	}

	for (i = 0; i < nodes + 1; ++i) {
		wt->basisvector[i] = 0.0;
		wt->costvalues[i] = 0.0;
	}

	N = temp_len;
	lp = wt->wave->lpd_len;
	p2 = 1;

	//set eparam value here
	wt->costvalues[0] = costfunc(orig, wt->siglength, wt->entropy, eparam);
	it2 = 1;
	if (!strcmp(wt->ext, "per")) {
		i = J;
		p2 = 2;
		while (i > 0) {
			N = (int)ceil((double)N / 2.0);
			wt->length[i] = N;
			wt->outlength += p2 * (wt->length[i]);
			i--;
			p2 *= 2;
		}
		wt->length[0] = wt->length[1];

		N2 = N = wt->outlength;
		p2 = 1;
		for (iter = 0; iter < J; ++iter) {
			len_cA = wt->length[J - iter];
			N2 -= 2 * p2 * len_cA;
			N = N2;
			for (k = 0; k < p2; ++k) {
				if (iter == 0) {
					dwpt_per(wt, orig, temp_len, tree + N, len_cA, tree + N + len_cA, len_cA);
				}
				else {
					dwpt_per(wt, tree + Np + k * temp_len, temp_len, tree + N, len_cA, tree + N + len_cA, len_cA);
				}
				wt->costvalues[it2] = costfunc(tree + N, len_cA, wt->entropy, eparam);
				it2++;
				wt->costvalues[it2] = costfunc(tree + N +len_cA, len_cA, wt->entropy, eparam);
				it2++;
				N += 2 * len_cA;
			}

			temp_len = wt->length[J - iter];
			p2 = 2 * p2;
			Np = N2;
		}
	}
	else if (!strcmp(wt->ext, "sym")) {
		//printf("\n YES %s \n", wt->ext);
		i = J;
		p2 = 2;
		while (i > 0) {
			N = N + lp - 2;
			N = (int)ceil((double)N / 2.0);
			wt->length[i] = N;
			wt->outlength += p2 * (wt->length[i]);
			i--;
			p2 *= 2;
		}
		wt->length[0] = wt->length[1];

		N2 = N = wt->outlength;
		p2 = 1;

		for (iter = 0; iter < J; ++iter) {
			len_cA = wt->length[J - iter];
			N2 -= 2 * p2 * len_cA;
			N = N2;
			for (k = 0; k < p2; ++k) {
				if (iter == 0) {
					dwpt_sym(wt, orig, temp_len, tree + N, len_cA, tree + N + len_cA, len_cA);
				}
				else {
					dwpt_sym(wt, tree + Np + k * temp_len, temp_len, tree + N, len_cA, tree + N + len_cA, len_cA);
				}
				wt->costvalues[it2] = costfunc(tree + N, len_cA, wt->entropy, eparam);
				it2++;
				wt->costvalues[it2] = costfunc(tree + N + len_cA, len_cA, wt->entropy, eparam);
				it2++;
				N += 2 * len_cA;
			}

			temp_len = wt->length[J - iter];
			p2 = 2 * p2;
			Np = N2;
		}

	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}

	J = wt->J;
	t2 = wt->outlength - 2 * wt->length[J];
	p2 = 2;
	it1 = 0;
	for (i = 0; i < J; ++i) {
		t = t2;
		for (k = 0; k < p2; ++k) {
			nodelength[it1] = t;
			it1++;
			t += wt->length[J - i];
		}
		p2 *= 2;
		t2 = t2 - p2 * wt->length[J - i - 1];
	}


	J = wt->J;
	llb = 1;
	for (i = 0; i < J; ++i) {
		llb *= 2;
	}

	for (i = n1 - llb; i < n1; ++i) {
		wt->basisvector[i] = 1;
	}

	for (j = J - 1; j >= 0; --j) {
		for (k = ipow2(j) - 1; k < ipow2(j + 1) - 1; ++k) {
			v1 = wt->costvalues[k];
			v2 = wt->costvalues[2 * k + 1] + wt->costvalues[2 * k + 2];
			//printf(" %g %g", v1,v2);
			if (v1 <= v2) {
				wt->basisvector[k] = 1;
			}
			else {
				wt->costvalues[k] = v2;
			}
		}
		//printf("\n");
	}

	for (k = 0; k < nodes / 2; ++k) {
		if (wt->basisvector[k] == 1 || wt->basisvector[k] == 2) {
			wt->basisvector[2 * k + 1] = 2;
			wt->basisvector[2 * k + 2] = 2;
		}
	}

	for (k = 0; k < n1; ++k) {
		if (wt->basisvector[k] == 2) {
			wt->basisvector[k] = 0;
		}
	}

	N2 = 0;
	it1 = n1;
	it2 = 0;
	wt->nodes = 0;
	wt->numnodeslevel[0] = 0;
	//printf("Start \n");

	if (wt->basisvector[0] == 1) {
		wt->outlength = wt->siglength;
		for (i = 0; i < wt->siglength; ++i) {
			wt->output[i] = inp[i];
		}
		wt->nodes = 1;
		wt->nodeindex[0] = 0;
		wt->nodeindex[1] = 0;
		wt->numnodeslevel[0] = 1;
	}
	else {
		for (i = J; i > 0; --i) {
			llb = ipow2(i);
			it1 -= llb;
			wt->numnodeslevel[i] = 0;
			for (j = 0; j < llb; ++j) {
				if (wt->basisvector[it1 + j] == 1) {
					//printf("NODE %d %d %d \n", i, j, wt->length[J - i + 1]);
					wt->nodeindex[2 * wt->nodes] = i;
					wt->nodeindex[2 * wt->nodes + 1] = j;
					wt->nodes += 1;
					wt->numnodeslevel[i] += 1;
					for (k = 0; k < wt->length[J - i + 1]; ++k) {
						wt->output[it2 + k] = tree[nodelength[it1 - 1 + j] + k];// access tree
					}
					it2 += wt->length[J - i + 1];
				}
			}
		}
		wt->outlength = it2;
	}

	wt->coeflength[0] = wt->siglength;

	for (i = 1; i < J + 1; ++i) {
		wt->coeflength[i] = wt->length[J - i + 1];
	}

	free(orig);
	free(tree);
	free(nodelength);
}

int cWavelib::getWTREENodelength(wtree_object wt, int X) {
	int N;
	N = -1;
	/*
	X - Level. All Nodes at any level have the same length
	*/
	if (X <= 0 || X > wt->J) {
		printf("X co-ordinate must be >= 1 and <= %d", wt->J);
		exit(-1);
	}

	N = wt->length[wt->J -X + 1];

	return N;
}

int cWavelib::getDWPTNodelength(wpt_object wt, int X) {
	int N;
	N = -1;
	/*
	X - Level. All Nodes at any level have the same length
	*/
	if (X <= 0 || X > wt->J) {
		printf("X co-ordinate must be >= 1 and <= %d", wt->J);
		exit(-1);
	}

	N = wt->length[wt->J - X + 1];

	return N;
}

void cWavelib::getWTREECoeffs(wtree_object wt, int X,int Y,double *coeffs,int N) {
	int ymax,i,t,t2;

	if (X <= 0 || X > wt->J) {
		printf("X co-ordinate must be >= 1 and <= %d", wt->J);
		exit(-1);
	}
	ymax = 1;
	for (i = 0; i < X; ++i) {
		ymax *= 2;
	}

	ymax -= 1;

	if (Y < 0 ||Y > ymax) {
		printf("Y co-ordinate must be >= 0 and <= %d", ymax);
		exit(-1);
	}

	if (X == 1) {
		t = 0;
	}
	else {
		t = 0;
		t2 = 1;
		for (i = 0; i < X - 1; ++i) {
			t2 *= 2;
			t += t2;
		}
	}

	t += Y;
	t2 = wt->nodelength[t];
	for (i = 0; i < N; ++i) {
		coeffs[i] = wt->output[t2+i];
	}

}

void cWavelib::getDWPTCoeffs(wpt_object wt, int X, int Y, double *coeffs, int N) {
	int ymax, i, t, t2;
	int np,nds,citer;
	int flag;

	if (X <= 0 || X > wt->J) {
		printf("X co-ordinate must be >= 1 and <= %d", wt->J);
		exit(-1);
	}
	ymax = 1;
	for (i = 0; i < X; ++i) {
		ymax *= 2;
	}

	ymax -= 1;

	if (Y < 0 || Y > ymax) {
		printf("Y co-ordinate must be >= 0 and <= %d", ymax);
		exit(-1);
	}

	np = 0;
	citer = 0;

	for (i = wt->J; i > X; --i) {
		np += wt->numnodeslevel[i];
		citer += wt->numnodeslevel[i] * wt->coeflength[i];
	}

	i = 0;
	flag = 0;
	for (i = 0; i < wt->numnodeslevel[X]; ++i) {
		if (wt->nodeindex[2 * np + 1] == Y) {
			flag = 1;
			break;
		}
		np++;
		citer += wt->coeflength[X];
	}

	if (flag == 0) {
		printf("The Node is Not Part Of The Best Basis Tree Use wpt_summary function to list available nodes \n");
		exit(-1);
	}

	for (i = 0; i < N; ++i) {
		coeffs[i] = wt->output[citer + i];
	}

}

void cWavelib::idwt1(wt_object wt,double *temp, double *cA_up,double *cA, int len_cA,double *cD,int len_cD,double *X_lp,double *X_hp,double *X) {
	int len_avg, N, U,N2,i;

	len_avg = (wt->wave->lpr_len + wt->wave->hpr_len) / 2;
	N = 2 * len_cD;
	U = 2;

	upsamp2(cA, len_cA, U, cA_up);

	per_ext(cA_up, 2 * len_cA, len_avg / 2, temp);

	N2 = 2 * len_cA + len_avg;

	if (wt->wave->lpr_len == wt->wave->hpr_len && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
		wt->cobj = conv_init(N2, len_avg);
		wt->cfftset = 1;
	}
	else if (!(wt->wave->lpr_len == wt->wave->hpr_len)) {
		printf("Decomposition Filters must have the same length.");
		exit(-1);
	}

	wconv(wt, temp, N2, wt->wave->lpr, len_avg, X_lp);

	upsamp2(cD, len_cD, U, cA_up);

	per_ext(cA_up, 2 * len_cD, len_avg / 2, temp);

	N2 = 2 * len_cD + len_avg;

	wconv(wt, temp, N2, wt->wave->hpr, len_avg, X_hp);


	for (i = len_avg - 1; i < N + len_avg - 1; ++i) {
		X[i - len_avg + 1] = X_lp[i] + X_hp[i];
	}

	if (wt->wave->lpr_len == wt->wave->hpr_len && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
		free_conv(wt->cobj);
		wt->cfftset = 0;
	}

}

void cWavelib::idwt_per(wt_object wt, double *cA, int len_cA, double *cD, int len_cD,  double *X) {
	int len_avg,i,l,m,n,t,l2;

	len_avg = (wt->wave->lpr_len + wt->wave->hpr_len) / 2;
	l2 = len_avg / 2;
	m = -2;
	n = -1;

	for (i = 0; i < len_cA + l2 - 1; ++i) {
		m += 2;
		n += 2;
		X[m] = 0.0;
		X[n] = 0.0;
		for (l = 0; l < l2; ++l) {
			t = 2 * l;
			if ((i - l) >= 0 && (i - l) < len_cA) {
				X[m] += wt->wave->lpr[t] * cA[i - l] + wt->wave->hpr[t] * cD[i - l];
				X[n] += wt->wave->lpr[t + 1] * cA[i - l] + wt->wave->hpr[t + 1] * cD[i - l];
			}
			else if ((i - l) >= len_cA && (i-l) < len_cA + len_avg - 1) {
				X[m] += wt->wave->lpr[t] * cA[i - l - len_cA] + wt->wave->hpr[t] * cD[i - l - len_cA];
				X[n] += wt->wave->lpr[t + 1] * cA[i - l - len_cA] + wt->wave->hpr[t + 1] * cD[i - l - len_cA];
			}
			else if ((i - l) < 0 && (i-l) > -l2) {
				X[m] += wt->wave->lpr[t] * cA[len_cA + i - l] + wt->wave->hpr[t] * cD[len_cA + i - l];
				X[n] += wt->wave->lpr[t + 1] * cA[len_cA + i - l] + wt->wave->hpr[t + 1] * cD[len_cA + i - l];
			}
		}
	}
}

void cWavelib::idwt_sym(wt_object wt, double *cA, int len_cA, double *cD, int len_cD, double *X) {
	int len_avg, i, l, m, n, t, v;

	len_avg = (wt->wave->lpr_len + wt->wave->hpr_len) / 2;
	m = -2;
	n = -1;

	for (v = 0; v < len_cA; ++v) {
		i = v;
		m += 2;
		n += 2;
		X[m] = 0.0;
		X[n] = 0.0;
		for (l = 0; l < len_avg / 2; ++l) {
			t = 2 * l;
			if ((i - l) >= 0 && (i - l) < len_cA) {
				X[m] += wt->wave->lpr[t] * cA[i - l] + wt->wave->hpr[t] * cD[i - l];
				X[n] += wt->wave->lpr[t + 1] * cA[i - l] + wt->wave->hpr[t + 1] * cD[i - l];
			}
		}
	}
}


void cWavelib::idwt(wt_object wt, double *dwtop) {
	int J,U,i,lf,N,N2,iter,k;
	int app_len, det_len;
	double *cA_up, *X_lp, *X_hp,*out,*temp;

	J = wt->J;
	U = 2;
	app_len = wt->length[0];
	out = (double*)malloc(sizeof(double)* (wt->siglength + 1));
	if (!strcmp(wt->ext, "per") && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
		app_len = wt->length[0];
		det_len = wt->length[1];
		N = 2 * wt->length[J];
		lf = (wt->wave->lpr_len + wt->wave->hpr_len) / 2;

		cA_up = (double*)malloc(sizeof(double)* N);
		temp = (double*)malloc(sizeof(double)* (N + lf));
		X_lp = (double*)malloc(sizeof(double)* (N + 2 * lf - 1));
		X_hp = (double*)malloc(sizeof(double)* (N + 2 * lf - 1));
		iter = app_len;

		for (i = 0; i < app_len; ++i) {
			out[i] = wt->output[i];
		}

		for (i = 0; i < J; ++i) {

			idwt1(wt,temp,cA_up,out,det_len,wt->output+iter,det_len,X_lp,X_hp,out);
			/*
			idwt_per(wt,out, det_len, wt->output + iter, det_len, X_lp);
			for (k = lf/2 - 1; k < 2 * det_len + lf/2 - 1; ++k) {
				out[k - lf/2 + 1] = X_lp[k];
			}
			*/
			iter += det_len;
			det_len = wt->length[i + 2];
		}
		free(cA_up);
		free(X_lp);
		free(X_hp);
		free(temp);

	}
	else if (!strcmp(wt->ext, "per") && !strcmp(wt->cmethod, "direct")) {
		app_len = wt->length[0];
		det_len = wt->length[1];
		N = 2 * wt->length[J];
		lf = (wt->wave->lpr_len + wt->wave->hpr_len) / 2;

		X_lp = (double*)malloc(sizeof(double)* (N + 2 * lf - 1));
		iter = app_len;

		for (i = 0; i < app_len; ++i) {
			out[i] = wt->output[i];
		}

		for (i = 0; i < J; ++i) {

			//idwt1(wt, temp, cA_up, out, det_len, wt->output + iter, det_len, X_lp, X_hp, out);

			idwt_per(wt,out, det_len, wt->output + iter, det_len, X_lp);
			for (k = lf/2 - 1; k < 2 * det_len + lf/2 - 1; ++k) {
			out[k - lf/2 + 1] = X_lp[k];
			}

			iter += det_len;
			det_len = wt->length[i + 2];
		}

		free(X_lp);

	}
	else if (!strcmp(wt->ext, "sym") && !strcmp(wt->cmethod, "direct")) {
		app_len = wt->length[0];
		det_len = wt->length[1];
		N = 2 * wt->length[J] - 1;
		lf = (wt->wave->lpr_len + wt->wave->hpr_len) / 2;

		X_lp = (double*)malloc(sizeof(double)* (N + 2 * lf - 1));
		iter = app_len;

		for (i = 0; i < app_len; ++i) {
			out[i] = wt->output[i];
		}

		for (i = 0; i < J; ++i) {

			//idwt1(wt, temp, cA_up, out, det_len, wt->output + iter, det_len, X_lp, X_hp, out);

			idwt_sym(wt, out, det_len, wt->output + iter, det_len, X_lp);
			for (k = lf-2; k < 2 * det_len; ++k) {
				out[k - lf + 2] = X_lp[k];
			}

			iter += det_len;
			det_len = wt->length[i + 2];
		}

		free(X_lp);

	}
	else if (!strcmp(wt->ext, "sym") && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
		lf = wt->wave->lpd_len;// lpd and hpd have the same length

		N = 2 * wt->length[J] - 1;
		cA_up = (double*)malloc(sizeof(double)* N);
		X_lp = (double*)malloc(sizeof(double)* (N + lf - 1));
		X_hp = (double*)malloc(sizeof(double)* (N + lf - 1));

		for (i = 0; i < app_len; ++i) {
			out[i] = wt->output[i];
		}

		iter = app_len;

		for (i = 0; i < J; ++i) {
			det_len = wt->length[i + 1];
			upsamp(out, det_len, U, cA_up);
			N2 = 2 * wt->length[i + 1] - 1;

			if (wt->wave->lpr_len == wt->wave->hpr_len && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
				wt->cobj = conv_init(N2, lf);
				wt->cfftset = 1;
			}
			else if (!(wt->wave->lpr_len == wt->wave->hpr_len)) {
				printf("Decomposition Filters must have the same length.");
				exit(-1);
			}

			wconv(wt, cA_up, N2, wt->wave->lpr, lf, X_lp);

			upsamp(wt->output + iter, det_len, U, cA_up);

			wconv(wt, cA_up, N2, wt->wave->hpr, lf, X_hp);

			for (k = lf - 2; k < N2 + 1; ++k) {
				out[k - lf + 2] = X_lp[k] + X_hp[k];
			}
			iter += det_len;
			if (wt->wave->lpr_len == wt->wave->hpr_len && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
				free_conv(wt->cobj);
				wt->cfftset = 0;
			}
		}

		free(cA_up);
		free(X_lp);
		free(X_hp);
	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}

	for (i = 0; i < wt->siglength; ++i) {
		dwtop[i] = out[i];
	}


	free(out);

}

void cWavelib::idwpt_per(wpt_object wt, double *cA, int len_cA, double *cD, int len_cD, double *X) {
	int len_avg, i, l, m, n, t, l2;

	len_avg = (wt->wave->lpr_len + wt->wave->hpr_len) / 2;
	l2 = len_avg / 2;
	m = -2;
	n = -1;

	for (i = 0; i < len_cA + l2 - 1; ++i) {
		m += 2;
		n += 2;
		X[m] = 0.0;
		X[n] = 0.0;
		for (l = 0; l < l2; ++l) {
			t = 2 * l;
			if ((i - l) >= 0 && (i - l) < len_cA) {
				X[m] += wt->wave->lpr[t] * cA[i - l] + wt->wave->hpr[t] * cD[i - l];
				X[n] += wt->wave->lpr[t + 1] * cA[i - l] + wt->wave->hpr[t + 1] * cD[i - l];
			}
			else if ((i - l) >= len_cA && (i - l) < len_cA + len_avg - 1) {
				X[m] += wt->wave->lpr[t] * cA[i - l - len_cA] + wt->wave->hpr[t] * cD[i - l - len_cA];
				X[n] += wt->wave->lpr[t + 1] * cA[i - l - len_cA] + wt->wave->hpr[t + 1] * cD[i - l - len_cA];
			}
			else if ((i - l) < 0 && (i - l) > -l2) {
				X[m] += wt->wave->lpr[t] * cA[len_cA + i - l] + wt->wave->hpr[t] * cD[len_cA + i - l];
				X[n] += wt->wave->lpr[t + 1] * cA[len_cA + i - l] + wt->wave->hpr[t + 1] * cD[len_cA + i - l];
			}
		}
	}
}

void cWavelib::idwpt_sym(wpt_object wt, double *cA, int len_cA, double *cD, int len_cD, double *X) {
	int len_avg, i, l, m, n, t, v;

	len_avg = (wt->wave->lpr_len + wt->wave->hpr_len) / 2;
	m = -2;
	n = -1;

	for (v = 0; v < len_cA; ++v) {
		i = v;
		m += 2;
		n += 2;
		X[m] = 0.0;
		X[n] = 0.0;
		for (l = 0; l < len_avg / 2; ++l) {
			t = 2 * l;
			if ((i - l) >= 0 && (i - l) < len_cA) {
				X[m] += wt->wave->lpr[t] * cA[i - l] + wt->wave->hpr[t] * cD[i - l];
				X[n] += wt->wave->lpr[t + 1] * cA[i - l] + wt->wave->hpr[t + 1] * cD[i - l];
			}
		}
	}
}

void cWavelib::idwpt(wpt_object wt, double *dwtop) {
	//original int J, U, i, lf, N, k,p,l;
	int J, i, lf, k,p,l;
	int app_len, det_len, index, n1, llb, index2, index3, index4,indexp,xlen;
	double *X_lp, *X,  *out, *out2;
	int *prep,*ptemp;

	J = wt->J;
	//U = 2;
	app_len = wt->length[0];
	p = ipow2(J);
	lf = (wt->wave->lpr_len + wt->wave->hpr_len) / 2;
	xlen = p * (app_len + 2 * lf);

	X_lp = (double*)malloc(sizeof(double)* 2 * (wt->length[J] + lf));
	X = (double*)malloc(sizeof(double)* xlen);
	out = (double*)malloc(sizeof(double)* wt->length[J]);
	out2 = (double*)malloc(sizeof(double)* wt->length[J]);
	prep = (int*)malloc(sizeof(int)* p);
	ptemp = (int*)malloc(sizeof(int)* p);
	n1 = 1;
	llb = 1;
	index2 = xlen / p;
	indexp = 0;
	for (i = 0; i < J; ++i) {
		llb *= 2;
		n1 += llb;
	}

	for (i = 0; i < xlen; ++i) {
		X[i] = 0.0;
	}

	for (i = 0; i < llb; ++i) {
		prep[i] = (int) wt->basisvector[n1 - llb + i];
		ptemp[i] = 0;
	}

	if (!strcmp(wt->ext, "per")) {
		app_len = wt->length[0];
		det_len = wt->length[1];
		index = 0;


		for (i = 0; i < J; ++i) {
			p = ipow2(J - i - 1);
			det_len = wt->length[i + 1];
			index2 *= 2;
			index3 = 0;
			index4 = 0;
			//idwt1(wt, temp, cA_up, out, det_len, wt->output + iter, det_len, X_lp, X_hp, out);
			n1 -= llb;
			for (l = 0; l < llb; ++l) {
				if (ptemp[l] != 2) {
					prep[l] = (int) wt->basisvector[n1 + l];
				}
				else {
					prep[l] = ptemp[l];
				}
				ptemp[l] = 0;
			}


			for (l = 0; l < p; ++l) {
				if (prep[2 * l] == 1 && prep[2 * l + 1] == 1) {
					for (k = 0; k < det_len; ++k) {
						out[k] = wt->output[index + k];
						out2[k] = wt->output[index + det_len + k];
					}
					idwpt_per(wt, out, det_len, out2, det_len, X_lp);
					for (k = lf / 2 - 1; k < 2 * det_len + lf / 2 - 1; ++k) {
						X[index3 + k - lf / 2 + 1] = X_lp[k];
					}
					index += 2 * det_len;
					index3 += index2;
					index4 += 2 * indexp;
					ptemp[l] = 2;
				}
				else if (prep[2 * l] == 1 && prep[2 * l + 1] == 2) {
					index4 += indexp;
					for (k = 0; k < det_len; ++k) {
						out[k] = wt->output[index + k];
						out2[k] = X[index4 + k];
					}
					idwpt_per(wt, out, det_len, out2, det_len, X_lp);
					for (k = lf / 2 - 1; k < 2 * det_len + lf / 2 - 1; ++k) {
						X[index3 + k - lf / 2 + 1] = X_lp[k];
					}
					index += det_len;
					index3 += index2;
					index4 += indexp;
					ptemp[l] = 2;
				}
				else if (prep[2 * l] == 2 && prep[2 * l + 1] == 1) {
					for (k = 0; k < det_len; ++k) {
						out[k] = X[index4 + k];
						out2[k] = wt->output[index + k];
					}
					idwpt_per(wt, out, det_len, out2, det_len, X_lp);
					for (k = lf / 2 - 1; k < 2 * det_len + lf / 2 - 1; ++k) {
						X[index3 + k - lf / 2 + 1] = X_lp[k];
					}
					index += det_len;
					index3 += index2;
					index4 += 2 * indexp;
					ptemp[l] = 2;
				}
				else if (prep[2 * l] == 2 && prep[2 * l + 1] == 2) {
					for (k = 0; k < det_len; ++k) {
						out[k] = X[index4 + k];
						out2[k] = X[index4 + indexp + k];
					}
					idwpt_per(wt, out, det_len, out2, det_len, X_lp);
					for (k = lf / 2 - 1; k < 2 * det_len + lf / 2 - 1; ++k) {
						X[index3 + k - lf / 2 + 1] = X_lp[k];
					}
					index4 += 2 * indexp;
					index3 += index2;
					ptemp[l] = 2;
				}
				else {
					index3 += index2;
					index4 += 2 * indexp;
				}

			}


			/*
			idwt_per(wt, out, det_len, wt->output + iter, det_len, X_lp);
			for (k = lf / 2 - 1; k < 2 * det_len + lf / 2 - 1; ++k) {
				out[k - lf / 2 + 1] = X_lp[k];
			}

			iter += det_len;
			det_len = wt->length[i + 2];
			*/
			llb /= 2;
			indexp = index2;
		}

		//free(X_lp);

	}
	else if (!strcmp(wt->ext, "sym")) {
		app_len = wt->length[0];
		det_len = wt->length[1];
		//N = 2 * wt->length[J] - 1;

		//X_lp = (double*)malloc(sizeof(double)* (N + 2 * lf - 1));
		index = 0;

		for (i = 0; i < J; ++i) {
			p = ipow2(J - i - 1);
			det_len = wt->length[i + 1];
			index2 *= 2;
			index3 = 0;
			index4 = 0;
			//idwt1(wt, temp, cA_up, out, det_len, wt->output + iter, det_len, X_lp, X_hp, out);
			n1 -= llb;
			for (l = 0; l < llb; ++l) {
				if (ptemp[l] != 2) {
					prep[l] = (int) wt->basisvector[n1 + l];
				}
				else {
					prep[l] = ptemp[l];
				}
				ptemp[l] = 0;
			}


			for (l = 0; l < p; ++l) {
				if (prep[2 * l] == 1 && prep[2 * l + 1] == 1) {
					for (k = 0; k < det_len; ++k) {
						out[k] = wt->output[index + k];
						out2[k] = wt->output[index + det_len + k];
					}
					idwpt_sym(wt, out, det_len, out2, det_len, X_lp);
					for (k = lf - 2; k < 2 * det_len; ++k) {
						X[index3 + k - lf + 2] = X_lp[k];
					}
					index += 2 * det_len;
					index3 += index2;
					index4 += 2 * indexp;
					ptemp[l] = 2;
				}
				else if (prep[2 * l] == 1 && prep[2 * l + 1] == 2) {
					index4 += indexp;
					for (k = 0; k < det_len; ++k) {
						out[k] = wt->output[index + k];
						out2[k] = X[index4 + k];
					}
					idwpt_sym(wt, out, det_len, out2, det_len, X_lp);
					for (k = lf - 2; k < 2 * det_len; ++k) {
						X[index3 + k - lf + 2] = X_lp[k];
					}
					index += det_len;
					index3 += index2;
					index4 += indexp;
					ptemp[l] = 2;
				}
				else if (prep[2 * l] == 2 && prep[2 * l + 1] == 1) {
					for (k = 0; k < det_len; ++k) {
						out[k] = X[index4 + k];
						out2[k] = wt->output[index + k];
					}
					idwpt_sym(wt, out, det_len, out2, det_len, X_lp);
					for (k = lf - 2; k < 2 * det_len; ++k) {
						X[index3 + k - lf + 2] = X_lp[k];
					}
					index += det_len;
					index3 += index2;
					index4 += 2 * indexp;
					ptemp[l] = 2;
				}
				else if (prep[2 * l] == 2 && prep[2 * l + 1] == 2) {
					for (k = 0; k < det_len; ++k) {
						out[k] = X[index4 + k];
						out2[k] = X[index4 + indexp + k];
					}
					idwpt_sym(wt, out, det_len, out2, det_len, X_lp);
					for (k = lf - 2; k < 2 * det_len; ++k) {
						X[index3 + k - lf + 2] = X_lp[k];
					}
					index4 += 2 * indexp;
					index3 += index2;
					ptemp[l] = 2;
				}
				else {
					index3 += index2;
					index4 += 2 * indexp;
				}

			}

			//idwt1(wt, temp, cA_up, out, det_len, wt->output + iter, det_len, X_lp, X_hp, out);
			/*
			idwpt_sym(wt, out, det_len, wt->output + iter, det_len, X_lp);
			for (k = lf - 2; k < 2 * det_len; ++k) {
				out[k - lf + 2] = X_lp[k];
			}

			iter += det_len;
			det_len = wt->length[i + 2];
			*/
			llb /= 2;
			indexp = index2;
		}

		//free(X_lp);

	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}

	for (i = 0; i < wt->siglength; ++i) {
		//printf("%g ", X[i]);
		dwtop[i] = X[i];
	}


	free(out);
	free(X_lp);
	free(X);
	free(out2);
	free(prep);
	free(ptemp);
}


void cWavelib::swt_per(wt_object wt,int M, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD) {
	int l, l2, isodd, i, t, len_avg,j;

	len_avg = M * wt->wave->lpd_len;
	l2 = len_avg / 2;
	isodd = N % 2;

	for (i = 0; i < len_cA; ++i) {
		t = i + l2;
		cA[i] = 0.0;
		cD[i] = 0.0;
		l = -1;
		for (j = 0; j < len_avg; j+=M) {
			l++;
			while (j >= len_cA) {
				j -= len_cA;
			}
			if ((t - j) >= l2 && (t -j) < N) {
				cA[i] += wt->wave->lpd[l] * inp[t - j];
				cD[i] += wt->wave->hpd[l] * inp[t - j];
			}
			else if ((t - j) < l2 && (t - j) >= 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - j];
				cD[i] += wt->wave->hpd[l] * inp[t - j];
			}
			else if ((t - j) < 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - j + N];
				cD[i] += wt->wave->hpd[l] * inp[t - j + N];
			}
			else if ((t - j) >= N && isodd == 0) {
				cA[i] += wt->wave->lpd[l] * inp[t - j - N];
				cD[i] += wt->wave->hpd[l] * inp[t - j - N];
			}
			else if ((t - j) >= N && isodd == 1) {
				if (t - l != N) {
					cA[i] += wt->wave->lpd[l] * inp[t - j - (N + 1)];
					cD[i] += wt->wave->hpd[l] * inp[t - j - (N + 1)];
				}
				else {
					cA[i] += wt->wave->lpd[l] * inp[N - 1];
					cD[i] += wt->wave->hpd[l] * inp[N - 1];
				}
			}

		}
	}


}

void cWavelib::swt_fft(wt_object wt, double *inp) {
	int i, J, temp_len, iter, M, N, len_filt;
	int lenacc;
	double *low_pass, *high_pass,*sig,*cA,*cD;

	temp_len = wt->siglength;
	J = wt->J;
	wt->length[0] = wt->length[J] = temp_len;
	wt->outlength = wt->length[J+1] = (J + 1) * temp_len;
	M = 1;
	for (iter = 1; iter < J; ++iter) {
		M = 2 * M;
		wt->length[iter] = temp_len;
	}

	len_filt = wt->wave->filtlength;

	low_pass = (double*)malloc(sizeof(double)* M * len_filt);
	high_pass = (double*)malloc(sizeof(double)* M * len_filt);
	sig = (double*)malloc(sizeof(double)* (M * len_filt + temp_len + (temp_len%2)));
	cA = (double*)malloc(sizeof(double)* (2 * M * len_filt + temp_len + (temp_len % 2)) - 1);
	cD = (double*)malloc(sizeof(double)* (2 * M * len_filt + temp_len + (temp_len % 2)) - 1);

	M = 1;

	for (i = 0; i < temp_len; ++i) {
		wt->params[i] = inp[i];
	}

	lenacc = wt->outlength;

	for (iter = 0; iter < J; ++iter) {
		lenacc -= temp_len;
		if (iter > 0) {
			M = 2 * M;
			N = M * len_filt;
			upsamp2(wt->wave->lpd, wt->wave->lpd_len, M, low_pass);
			upsamp2(wt->wave->hpd, wt->wave->hpd_len, M, high_pass);
		}
		else {
			N = len_filt;
			for (i = 0; i < N; ++i) {
				low_pass[i] = wt->wave->lpd[i];
				high_pass[i] = wt->wave->hpd[i];
			}
		}

		//swt_per(wt,M, wt->params, temp_len, cA, temp_len, cD,temp_len);

		per_ext(wt->params, temp_len, N / 2, sig);

		if (wt->wave->lpd_len == wt->wave->hpd_len && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
			wt->cobj = conv_init(N + temp_len + (temp_len % 2), N);
			wt->cfftset = 1;
		}
		else if (!(wt->wave->lpd_len == wt->wave->hpd_len)) {
			printf("Decomposition Filters must have the same length.");
			exit(-1);
		}


		wconv(wt, sig, N + temp_len + (temp_len % 2), low_pass, N, cA);

		wconv(wt, sig, N + temp_len + (temp_len % 2), high_pass, N, cD);

		if (wt->wave->lpd_len == wt->wave->hpd_len && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
			free_conv(wt->cobj);
			wt->cfftset = 0;
		}

		for (i = 0; i < temp_len; ++i) {
			wt->params[i] = cA[N + i];
			wt->params[lenacc + i] = cD[N + i];
		}


	}

	free(low_pass);
	free(high_pass);
	free(sig);
	free(cA);
	free(cD);
}

void cWavelib::swt_direct(wt_object wt, double *inp) {
	//original int i, J, temp_len, iter, M, N;
	//original int lenacc, len_filt;
	int i, J, temp_len, iter, M;
	int lenacc;
	double  *cA, *cD;

	temp_len = wt->siglength;
	J = wt->J;
	wt->length[0] = wt->length[J] = temp_len;
	wt->outlength = wt->length[J + 1] = (J + 1) * temp_len;
	//len_filt = wt->wave->filtlength;
	M = 1;
	for (iter = 1; iter < J; ++iter) {
		M = 2 * M;
		wt->length[iter] = temp_len;
	}


	cA = (double*)malloc(sizeof(double)* temp_len);
	cD = (double*)malloc(sizeof(double)* temp_len);

	M = 1;

	for (i = 0; i < temp_len; ++i) {
		wt->params[i] = inp[i];
	}

	lenacc = wt->outlength;

	for (iter = 0; iter < J; ++iter) {
		lenacc -= temp_len;
		if (iter > 0) {
			M = 2 * M;
			//N = M * len_filt;
		}
		else {
			;//N = len_filt;
		}

		swt_per(wt, M, wt->params, temp_len, cA, temp_len, cD, temp_len);


		for (i = 0; i < temp_len; ++i) {
			wt->params[i] = cA[i];
			wt->params[lenacc + i] = cD[i];
		}

	}

	free(cA);
	free(cD);

}


void cWavelib::swt(wt_object wt, double *inp) {
	if (!strcmp(wt->method, "swt") && !strcmp(wt->cmethod, "direct") ) {
		swt_direct(wt,inp);
	}
	else if (!strcmp(wt->method, "swt") &&  (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
		swt_fft(wt, inp);
	}
	else {
		printf("SWT Only accepts two methods - direct and fft");
		exit(-1);
	}
}

void cWavelib::iswt(wt_object wt, double *swtop) {
	int N, lf, iter,i,J,index,value,count,len;
	int index_shift,len0,U,N1,index2;
	double *appx1, *det1,*appx_sig,*det_sig,*cL0,*cH0,*tempx,*oup00L,*oup00H,*oup00,*oup01,*appx2,*det2;

	N = wt->siglength;
	J = wt->J;
	U = 2;
	lf = wt->wave->lpr_len;

	appx_sig = (double*)malloc(sizeof(double)* N);
	det_sig = (double*)malloc(sizeof(double)* N);
	appx1 = (double*)malloc(sizeof(double)* N);
	det1 = (double*)malloc(sizeof(double)* N);
	appx2 = (double*)malloc(sizeof(double)* N);
	det2 = (double*)malloc(sizeof(double)* N);
	tempx = (double*)malloc(sizeof(double)* N);
	cL0 = (double*)malloc(sizeof(double)* (N + (N%2) + lf));
	cH0 = (double*)malloc(sizeof(double)* (N + (N % 2) + lf));
	oup00L = (double*)malloc(sizeof(double)* (N + 2 * lf));
	oup00H = (double*)malloc(sizeof(double)* (N + 2 * lf));
	oup00 = (double*)malloc(sizeof(double)* N);
	oup01 = (double*)malloc(sizeof(double)* N);



	for (iter = 0; iter < J; ++iter) {
		for (i = 0; i < N; ++i) {
			swtop[i] = 0.0;
		}
		if (iter == 0) {
			for (i = 0; i < N; ++i) {
				appx_sig[i] = wt->output[i];
				det_sig[i] = wt->output[N + i];
			}
		}
		else {
			for (i = 0; i < N; ++i) {
				det_sig[i] = wt->output[(iter + 1) * N + i];
			}
		}

		value = (int)pow(2.0, (double) (J - 1 - iter));

		for (count = 0; count < value; count++) {
			len = 0;
			for (index = count; index < N; index += value) {
				appx1[len] = appx_sig[index];
				det1[len] = det_sig[index];
				len++;
			}


			//SHIFT 0
			len0 = 0;

			for (index_shift = 0; index_shift < len; index_shift += 2) {
				appx2[len0] = appx1[index_shift];
				det2[len0] = det1[index_shift];
				len0++;
			}
			upsamp2(appx2, len0, U, tempx);
			per_ext(tempx, 2 * len0, lf / 2, cL0);

			upsamp2(det2, len0, U, tempx);
			per_ext(tempx, 2 * len0, lf / 2, cH0);

			N1 = 2 * len0 + lf;

			if (wt->wave->lpr_len == wt->wave->hpr_len && (!strcmp(wt->cmethod, "fft") || !strcmp(wt->cmethod, "FFT"))) {
				wt->cobj = conv_init(N1, lf);
				wt->cfftset = 1;
			}
			else if (!(wt->wave->lpd_len == wt->wave->hpd_len)) {
				printf("Decomposition Filters must have the same length.");
				exit(-1);
			}

			wconv(wt, cL0, N1, wt->wave->lpr, lf, oup00L);

			wconv(wt, cH0, N1, wt->wave->hpr, lf, oup00H);

			for (i = lf - 1; i < 2 * len0 + lf - 1; ++i) {
				oup00[i - lf + 1] = oup00L[i] + oup00H[i];
			}

			//SHIFT 1

			len0 = 0;

			for (index_shift = 1; index_shift < len; index_shift += 2) {
				appx2[len0] = appx1[index_shift];
				det2[len0] = det1[index_shift];
				len0++;
			}

			upsamp2(appx2, len0, U, tempx);
			per_ext(tempx, 2 * len0, lf / 2, cL0);

			upsamp2(det2, len0, U, tempx);
			per_ext(tempx, 2 * len0, lf / 2, cH0);

			N1 = 2 * len0 + lf;

			wconv(wt, cL0, N1, wt->wave->lpr, lf, oup00L);

			wconv(wt, cH0, N1, wt->wave->hpr, lf, oup00H);

			for (i = lf - 1; i < 2 * len0 + lf - 1; ++i) {
				oup01[i - lf + 1] = oup00L[i] + oup00H[i];
			}

			circshift(oup01, 2*len0, -1);

			index2 = 0;

			for (index = count; index < N; index += value) {
				swtop[index] = (oup00[index2] + oup01[index2]) / 2.0;
				index2++;
			}

		}
		for (i = 0; i < N; ++i) {
			appx_sig[i] = swtop[i];
		}

	}



	free(appx_sig);
	free(det_sig);
	free(appx1);
	free(det1);
	free(tempx);
	free(cL0);
	free(cH0);
	free(oup00L);
	free(oup00H);
	free(oup00);
	free(oup01);
	free(appx2);
	free(det2);
}

void cWavelib::modwt_per(wt_object wt, int M, double *inp, int N, double *cA, int len_cA, double *cD, int len_cD) {
	int l, i, t, len_avg;
	double s;
	double *filt;
	len_avg = wt->wave->lpd_len;

	filt = (double*)malloc(sizeof(double)* 2 * len_avg);
	s = sqrt(2.0);
	for (i = 0; i < len_avg; ++i) {
		filt[i] = wt->wave->lpd[i] / s;
		filt[len_avg + i] = wt->wave->hpd[i] / s;
	}

	for (i = 0; i < len_cA; ++i) {
		t = i;
		cA[i] = filt[0] * inp[t];
		cD[i] = filt[len_avg] * inp[t];
		for (l = 1; l < len_avg; l++) {
			t -= M;
			while (t >= len_cA) {
				t -= len_cA;
			}
			while (t < 0) {
				t += len_cA;
			}

			cA[i] += filt[l] * inp[t];
			cD[i] += filt[len_avg + l] * inp[t];

		}
	}
	free(filt);
}

void cWavelib::modwt(wt_object wt, double *inp) {
	//original int i, J, temp_len, iter, M, N;
	//original int lenacc, len_filt;
	int i, J, temp_len, iter, M;
	int lenacc;
	double  *cA, *cD;

	temp_len = wt->siglength;
	J = wt->J;
	wt->length[0] = wt->length[J] = temp_len;
	wt->outlength = wt->length[J + 1] = (J + 1) * temp_len;
	//len_filt = wt->wave->filtlength;
	M = 1;
	for (iter = 1; iter < J; ++iter) {
		M = 2 * M;
		wt->length[iter] = temp_len;
	}


	cA = (double*)malloc(sizeof(double)* temp_len);
	cD = (double*)malloc(sizeof(double)* temp_len);

	M = 1;

	for (i = 0; i < temp_len; ++i) {
		wt->params[i] = inp[i];
	}

	lenacc = wt->outlength;

	for (iter = 0; iter < J; ++iter) {
		lenacc -= temp_len;
		if (iter > 0) {
			M = 2 * M;
			//N = M * len_filt;
		}
		else {
			;//N = len_filt;
		}

		modwt_per(wt, M, wt->params, temp_len, cA, temp_len, cD, temp_len);


		for (i = 0; i < temp_len; ++i) {
			wt->params[i] = cA[i];
			wt->params[lenacc + i] = cD[i];
		}

	}

	free(cA);
	free(cD);

}

void cWavelib::imodwt_per(wt_object wt,int M, double *cA, int len_cA, double *cD, int len_cD, double *X) {
	int len_avg, i, l, t;
	double s;
	double *filt;
	len_avg = wt->wave->lpd_len;

	filt = (double*)malloc(sizeof(double)* 2 * len_avg);
	s = sqrt(2.0);
	for (i = 0; i < len_avg; ++i) {
		filt[i] = wt->wave->lpd[i] / s;
		filt[len_avg + i] = wt->wave->hpd[i] / s;
	}


	for (i = 0; i < len_cA; ++i) {
		t = i;
		X[i] = (filt[0] * cA[t]) + (filt[len_avg] * cD[t]);
		for (l = 1; l < len_avg; l++) {
			t += M;
			while (t >= len_cA) {
				t -= len_cA;
			}
			while (t < 0) {
				t += len_cA;
			}

			X[i] += (filt[l] * cA[t]) + (filt[len_avg + l] * cD[t]);

		}
	}
	free(filt);
}

void cWavelib::imodwt(wt_object wt, double *dwtop) {
	//original int N, lf, iter, i, J, j, U;
	int N, iter, i, J, j;
	int lenacc,M;
	double *X;

	N = wt->siglength;
	J = wt->J;
	//U = 2;
	//lf = wt->wave->lpr_len;
	lenacc = N;
	M = (int)pow(2.0, (double)J - 1.0);
	//M = 1;
	X = (double*)malloc(sizeof(double)* N);

	for (i = 0; i < N; ++i) {
		dwtop[i] = wt->output[i];
	}

	for (iter = 0; iter < J; ++iter) {
		if (iter > 0) {
			M = M / 2;
		}
		imodwt_per(wt, M, dwtop, N, wt->params + lenacc, N, X);
		/*
		for (j = lf - 1; j < N; ++j) {
			dwtop[j - lf + 1] = X[j];
		}
		for (j = 0; j < lf - 1; ++j) {
			dwtop[N - lf + 1 + j] = X[j];
		}
		*/
		for (j = 0; j < N; ++j) {
			dwtop[j] = X[j];
		}

		lenacc += N;
	}
	free(X);
}

void cWavelib::setDWTExtension(wt_object wt, char *extension) {
	if (!strcmp(extension, "sym")) {
		strcpy(wt->ext, "sym");
	}
	else if (!strcmp(extension, "per")) {
		strcpy(wt->ext, "per");
	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}
}

void cWavelib::setWTREEExtension(wtree_object wt, char *extension) {
	if (!strcmp(extension, "sym")) {
		strcpy(wt->ext, "sym");
	}
	else if (!strcmp(extension, "per")) {
		strcpy(wt->ext, "per");
	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}
}

void cWavelib::setDWPTExtension(wpt_object wt, char *extension) {
	if (!strcmp(extension, "sym")) {
		strcpy(wt->ext, "sym");
	}
	else if (!strcmp(extension, "per")) {
		strcpy(wt->ext, "per");
	}
	else {
		printf("Signal extension can be either per or sym");
		exit(-1);
	}
}

void cWavelib::setDWPTEntropy(wpt_object wt, char *entropy, double eparam) {
	if (!strcmp(entropy, "shannon")) {
		strcpy(wt->entropy, "shannon");
	}
	else if (!strcmp(entropy, "threshold")) {
		strcpy(wt->entropy, "threshold");
		wt ->eparam = eparam;
	}
	else if (!strcmp(entropy, "norm")) {
		strcpy(wt->entropy, "norm");
		wt->eparam = eparam;
	}
	else if (!strcmp(entropy, "logenergy") || !strcmp(entropy, "log energy") || !strcmp(entropy, "energy")) {
		strcpy(wt->entropy, "logenergy");
	}
	else {
		printf("Entropy should be one of shannon, threshold, norm or logenergy");
		exit(-1);
	}
}

void cWavelib::setWTConv(wt_object wt, char *cmethod) {
	if (!strcmp(cmethod, "fft") || !strcmp(cmethod, "FFT")) {
		strcpy(wt->cmethod, "fft");
	}
	else if (!strcmp(cmethod, "direct")) {
		strcpy(wt->cmethod, "direct");
	}
	else {
		printf("Convolution Only accepts two methods - direct and fft");
		exit(-1);
	}
}
//---------------------------------------------------------------------------
void cWavelib::wave_summary(wave_object obj)
	{
	int i,N;
	N = obj->filtlength;
	Print("");
	Print("Wavelet Name : %s ",obj->wname);
	Print("");
	Print("Wavelet Filters ");
	Print("lpd : [");
	for (i = 0; i < N-1; ++i) {
		Print("%g,", obj->lpd[i]);
	}
	Print("%g", obj->lpd[N-1]);
	Print("]");
	Print("");
	Print("hpd : [");
	for (i = 0; i < N-1; ++i) {
		Print("%g,", obj->hpd[i]);
	}
	Print("%g", obj->hpd[N - 1]);
	Print("]");
	Print("");
	Print("lpr : [");
	for (i = 0; i < N-1; ++i) {
		Print("%g,", obj->lpr[i]);
	}
	Print("%g", obj->lpr[N - 1]);
	Print("]");
	Print("");
	Print("hpr : [");
	for (i = 0; i < N-1; ++i) {
		Print("%g,", obj->hpr[i]);
	}
	Print("%g", obj->hpr[N - 1]);
	Print("]");
	Print("");
	}
//---------------------------------------------------------------------------
void cWavelib::wt_summary(wt_object wt) {
	int i;
	int J,t;
	J = wt->J;
	wave_summary(wt->wave);
	Print("");
	Print("Wavelet Transform : %s ", wt->method);
	Print("");
	Print("Signal Extension : %s ", wt->ext);
	Print("");
	Print("Convolutional Method : %s ", wt->cmethod);
	Print("");
	Print("Number of Decomposition Levels %d ", wt->J);
	Print("");
	Print("Length of Input Signal %d ", wt->siglength);
	Print("");
	Print("Length of WT Output Vector %d ", wt->outlength);
	Print("");
	Print("Wavelet Coefficients are contained in vector : %s ", "output");
	Print("");
	Print("Approximation Coefficients ");
	Print("Level %d Access : output[%d] Length : %d ", 1, 0, wt->length[0]);
	Print("");
	Print("Detail Coefficients ");
	t = wt->length[0];
	for (i = 0; i < J; ++i) {
		Print("Level %d Access : output[%d] Length : %d ", i + 1,t,wt->length[i+1]);
		t += wt->length[i+1];
	}
	Print("");

}

void cWavelib::wtree_summary(wtree_object wt) {
	int i,k,p2;
	int J,t;
	J = wt->J;
	wave_summary(wt->wave);
	Print("");
	Print("Wavelet Transform : %s ", wt->method);
	Print("");
	Print("Signal Extension : %s ", wt->ext);
	Print("");
	Print("Number of Decomposition Levels %d ", wt->J);
	Print("");
	Print("Length of Input Signal %d ", wt->siglength);
	Print("");
	Print("Length of WT Output Vector %d ", wt->outlength);
	Print("");
	Print("Wavelet Coefficients are contained in vector : %s ", "output");
	Print("");
	Print("Coefficients Access ");
	t = 0;
	p2 = 2;
	for (i = 0; i < J; ++i) {
		for (k = 0; k < p2; ++k) {
			Print("Node %d %d Access : output[%d] Length : %d ", i + 1, k, wt->nodelength[t], wt->length[J - i]);
			t++;
		}
		p2 *= 2;
	}
	Print("");

}

void cWavelib::wpt_summary(wpt_object wt) {
	int i, k, p2;
	int J, it1,it2;
	J = wt->J;
	wave_summary(wt->wave);
	Print("");
	Print("Signal Extension : %s ", wt->ext);
	Print("");
	Print("Entropy : %s ", wt->entropy);
	Print("");
	Print("Number of Decomposition Levels %d ", wt->J);
	Print("");
	Print("Number of Active Nodes %d ", wt->nodes);
	Print("");
	Print("Length of Input Signal %d ", wt->siglength);
	Print("");
	Print("Length of WT Output Vector %d ", wt->outlength);
	Print("");
	Print("Wavelet Coefficients are contained in vector : %s ", "output");
	Print("");
	Print("Coefficients Access ");
	it1 = 1;
	it2 = 0;
	for (i = 0; i < J; ++i) {
		it1 += ipow2(i + 1);
	}
	for (i = J; i > 0; --i) {
		p2 = ipow2(i);
		it1 -= p2;
		for (k = 0; k < p2; ++k) {
			if (wt->basisvector[it1 + k] == 1) {
				Print("Node %d %d Access : output[%d] Length : %d ", i, k, it2, wt->length[J - i + 1]);
				it2 += wt->length[J - i + 1];
			}
		}
	}

	Print("");

}

void cWavelib::wave_free(wave_object object) {
	free(object);
}

void cWavelib::wt_free(wt_object object) {
	free(object);
}

void cWavelib::wtree_free(wtree_object object) {
	free(object);
}

void cWavelib::wpt_free(wpt_object object) {
	free(object);
}
//---------------------------------------------------------------------------
/***************************************************************************/
/************************   WTMATH   ***************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int cWavelib::upsamp(double *x, int lenx, int M, double *y) {
	int N, i, j, k;

	if (M < 0) {
		return -1;
	}

	if (M == 0) {
		for (i = 0; i < lenx; ++i) {
			y[i] = x[i];
		}
		return lenx;
	}

	N = M * (lenx - 1) + 1;
	j = 1;
	k = 0;

	for (i = 0; i < N; ++i) {
		j--;
		y[i] = 0.0;
		if (j == 0) {
			y[i] = x[k];
			k++;
			j = M;
		}
	}

	return N;
}

int cWavelib::upsamp2(double *x, int lenx, int M, double *y) {
	int N, i, j, k;
	// upsamp2 returns even numbered output. Last value is set to zero
	if (M < 0) {
		return -1;
	}

	if (M == 0) {
		for (i = 0; i < lenx; ++i) {
			y[i] = x[i];
		}
		return lenx;
	}

	N = M * lenx;
	j = 1;
	k = 0;

	for (i = 0; i < N; ++i) {
		j--;
		y[i] = 0.0;
		if (j == 0) {
			y[i] = x[k];
			k++;
			j = M;
		}
	}

	return N;
}

int cWavelib::downsamp(double *x, int lenx, int M, double *y) {
	int N, i;

	if (M < 0) {
		return -1;
	}
	if (M == 0) {
		for (i = 0; i < lenx; ++i) {
			y[i] = x[i];
		}
		return lenx;
	}

	N = (lenx - 1) / M + 1;

	for (i = 0; i < N; ++i) {
		y[i] = x[i*M];
	}

	return N;
}

int cWavelib::per_ext(double *sig, int len, int a, double *oup) {
	int i, len2;
	double temp1;
	double temp2;
	for (i = 0; i < len; ++i) {
		oup[a + i] = sig[i];
	}
	len2 = len;
	if ((len % 2) != 0) {
		len2 = len + 1;
		oup[a + len] = sig[len - 1];
	}
	for (i = 0; i < a; ++i) {
		temp1 = oup[a + i];
		temp2 = oup[a + len2 - 1 - i];
		oup[a - 1 - i] = temp2;
		oup[len2 + a + i] = temp1;
	}
	return len2;
}

int cWavelib::symm_ext(double *sig, int len, int a, double *oup) {
	int i, len2;
	double temp1;
	double temp2;
	// oup is of length len + 2 * a
	for (i = 0; i < len; ++i) {
		oup[a + i] = sig[i];
	}
	len2 = len;
	for (i = 0; i < a; ++i) {
		temp1 = oup[a + i];
		temp2 = oup[a + len2 - 1 - i];
		oup[a - 1 - i] = temp1;
		oup[len2 + a + i] = temp2;
	}

	return len2;

}

int cWavelib::isign(int N) {
	int M;
	if (N >= 0) {
		M = 1;
	}
	else {
		M = -1;
	}

	return M;
}

int cWavelib::iabs(int N) {
	if (N >= 0) {
		return N;
	}
	else {
		return -N;
	}
}

void cWavelib::circshift(double *array, int N, int L) {
	int i;
	double *temp;
	if (iabs(L) > N) {
		L = isign(L) * (iabs(L) % N);
	}
	if (L < 0) {
		L = (N + L) % N;
	}

	temp = (double*)malloc(sizeof(double) * L);

	for (i = 0; i < L; ++i) {
		temp[i] = array[i];
	}

	for (i = 0; i < N - L; ++i) {
		array[i] = array[i + L];
	}

	for (i = 0; i < L; ++i) {
		array[N - L + i] = temp[i];
	}

	free(temp);
}

int cWavelib::testSWTlength(int N, int J) {
	int ret,div,i;
	ret = 1;

	div = 1;
	for (i = 0; i < J; ++i) {
		div *= 2;
	}

	if (N % div) {
		ret = 0;
	}

	return ret;

}

int cWavelib::wmaxiter(int sig_len, int filt_len) {
	int lev;
	double temp;

	temp = log((double)sig_len / ((double)filt_len - 1.0)) / log(2.0);
	lev = (int)temp;

	return lev;
}

double cWavelib::entropy_s(double *x,int N) {
  int i;
  double val,x2;

  val = 0.0;

  for(i = 0; i < N; ++i) {
    if (x[i] != 0) {
      x2 = x[i] * x[i];
      val -= x2 * log(x2);
    }
  }
  return val;
}

double cWavelib::entropy_t(double *x,int N, double t) {
  int i;
  double val,x2;
  if (t < 0) {
    printf("Threshold value must be >= 0");
    exit(1);
  }
  val = 0.0;

  for(i = 0; i < N; ++i) {
    x2 = fabs(x[i]);
    if (x2 > t) {
      val += 1;
    }

  }

  return val;

}

double cWavelib::entropy_n(double *x,int N,double p) {
  int i;
  double val,x2;
  if (p < 1) {
    printf("Norm power value must be >= 1");
    exit(1);
  }
  val = 0.0;
  for(i = 0; i < N; ++i) {
    x2 = fabs(x[i]);
    val += pow(x2,(double)p);

  }

  return val;
}

double cWavelib::entropy_l(double *x,int N) {
  int i;
  double val,x2;

  val = 0.0;

  for(i = 0; i < N; ++i) {
    if (x[i] != 0) {
      x2 = x[i] * x[i];
      val += log(x2);
    }
  }
  return val;
}

double cWavelib::costfunc(double *x, int N ,char *entropy,double p) {
	double val;

	if (!strcmp(entropy, "shannon")) {
		val = entropy_s(x, N);
	}
	else if (!strcmp(entropy, "threshold")) {
		val = entropy_t(x, N,p);
	}
	else if (!strcmp(entropy, "norm")) {
		val = entropy_n(x, N,p);
	}
	else if (!strcmp(entropy, "logenergy") || !strcmp(entropy, "log energy") || !strcmp(entropy, "energy")) {
		val = entropy_l(x, N);
	}
	else {
		printf("Entropy must be one of shannon, threshold, norm or energy");
		exit(-1);
	}

	return val;
}
//---------------------------------------------------------------------------
/***************************************************************************/
/************************   WAVEFILT   *************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int cWavelib::filtlength(char* name) {
	if (!strcmp(name,"haar") || !strcmp(name,"db1")) {
		return 2;
	}
	else if (!strcmp(name,"db2")){
		return 4;
	}
	else if (!strcmp(name,"db3")){
		return 6;
	}
	else if (!strcmp(name,"db4")){
		return 8;
	}
	else if (!strcmp(name,"db5")){
		return 10;
	}
	else if (!strcmp(name,"db6")){
		return 12;
	}
	else if (!strcmp(name,"db7")){
		return 14;
	}
	else if (!strcmp(name,"db8")){
		return 16;
	}
	else if (!strcmp(name,"db9")){
		return 18;
	}

	else if (!strcmp(name,"db10")){
		return 20;
	}

	else if (!strcmp(name,"db12")){
		return 24;
	}
	else if (!strcmp(name,"db13")){
		return 26;
	}

	else if (!strcmp(name,"db11")){
		return 22;
	}

	else if (!strcmp(name,"db14")){
		return 28;
	}
	else if (!strcmp(name,"db15")){
		return 30;
	}
	else if (!strcmp(name,"bior1.1")){
		return 2;
	}

	else if (!strcmp(name,"bior1.3")){
		return 6;
	}

	else if (!strcmp(name,"bior1.5")){
		return 10;
	}

	else if (!strcmp(name,"bior2.2")){
		return 6;
	}

	else if (!strcmp(name,"bior2.4")){
		return 10;
	}

	else if (!strcmp(name,"bior2.6")){
		return 14;
	}
	else if (!strcmp(name,"bior2.8")){
		return 18;
	}

	else if (!strcmp(name,"bior3.1")){
		return 4;
	}
	else if (!strcmp(name,"bior3.3")){
		return 8;
	}
	else if (!strcmp(name,"bior3.5")){
		return 12;
	}

	else if (!strcmp(name,"bior3.7")){
		return 16;
	}
	else if (!strcmp(name,"bior3.9")){
		return 20;
	}
	else if (!strcmp(name,"bior4.4")){
		return 10;
	}
	else if (!strcmp(name,"bior5.5")){
		return 12;
	}
	else if (!strcmp(name,"bior6.8")){
		return 18;
	}

	else if (!strcmp(name,"coif1")){
		return 6;
	}
	else if (!strcmp(name,"coif2")){
		return 12;
	}
	else if (!strcmp(name,"coif3")){
		return 18;
	}
	else if (!strcmp(name,"coif4")){
		return 24;
	}
	else if (!strcmp(name,"coif5")){
		return 30;
	}

	else if (!strcmp(name,"sym2")){
		return 4;
	}

	else if (!strcmp(name,"sym3")){
		return 6;
	}

	else if (!strcmp(name,"sym4")){
		return 8;
	}

	else if (!strcmp(name,"sym5")){
		return 10;
	}

	else if (!strcmp(name,"sym6")){
		return 12;
	}

	else if (!strcmp(name,"sym7")){
		return 14;
	}

	else if (!strcmp(name,"sym8")){
		return 16;
	}

	else if (!strcmp(name,"sym9")){
		return 18;
	}

	else if (!strcmp(name,"sym10")){
		return 20;
	}
	else {
		printf("\n Filter Not in Database \n");
		return -1;
	}

	//return 0;
}

int cWavelib::filtcoef(char* name, double *lp1, double *hp1, double *lp2, double *hp2) {
	int i;
	if (!strcmp(name,"haar") || !strcmp(name,"db1")) {
		double lp1_a[] = { 0.7071067811865475, 0.7071067811865475 };
		double hp1_a[] = { -0.7071067811865475, 0.7071067811865475 };
		double lp2_a[] = { 0.7071067811865475, 0.7071067811865475 };
		double hp2_a[] = { 0.7071067811865475, -0.7071067811865475 };
		for (i = 0; i < 2; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 2;
	}
	else if (!strcmp(name,"db2")){
		double lp1_a[] = { -0.12940952255092145, 0.22414386804185735, 0.83651630373746899,
			0.48296291314469025 };

		double hp1_a[] = { -0.48296291314469025, 0.83651630373746899, -0.22414386804185735,
			-0.12940952255092145 };

		double lp2_a[] = { 0.48296291314469025, 0.83651630373746899, 0.22414386804185735,
			-0.12940952255092145 };

		double hp2_a[] = { -0.12940952255092145, -0.22414386804185735, 0.83651630373746899,
			-0.48296291314469025 };
		for (i = 0; i < 4; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 4;
	}
	else if (!strcmp(name,"db3")){
		double lp1_a[] = { 0.035226291882100656, -0.085441273882241486, -0.13501102001039084,
			0.45987750211933132, 0.80689150931333875, 0.33267055295095688 };

		double hp1_a[] = { -0.33267055295095688, 0.80689150931333875, -0.45987750211933132,
			-0.13501102001039084, 0.085441273882241486, 0.035226291882100656 };

		double lp2_a[] = { 0.33267055295095688, 0.80689150931333875, 0.45987750211933132,
			-0.13501102001039084, -0.085441273882241486, 0.035226291882100656 };

		double hp2_a[] = { 0.035226291882100656, 0.085441273882241486, -0.13501102001039084,
			-0.45987750211933132, 0.80689150931333875, -0.33267055295095688 };
		for (i = 0; i < 6; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 6;
	}
	else if (!strcmp(name,"db4")){
		double lp1_a[] = { -0.010597401784997278, 0.032883011666982945, 0.030841381835986965,
			-0.18703481171888114, -0.027983769416983849, 0.63088076792959036,
			0.71484657055254153, 0.23037781330885523 };

		double hp1_a[] = { -0.23037781330885523, 0.71484657055254153, -0.63088076792959036,
			-0.027983769416983849, 0.18703481171888114, 0.030841381835986965,
			-0.032883011666982945, -0.010597401784997278 };

		double lp2_a[] = { 0.23037781330885523, 0.71484657055254153, 0.63088076792959036,
			-0.027983769416983849, -0.18703481171888114, 0.030841381835986965,
			0.032883011666982945, -0.010597401784997278 };

		double hp2_a[] = { -0.010597401784997278, -0.032883011666982945, 0.030841381835986965,
			0.18703481171888114, -0.027983769416983849, -0.63088076792959036,
			0.71484657055254153, -0.23037781330885523 };
		for (i = 0; i < 8; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 8;
	}
	else if (!strcmp(name,"db5")){
		double lp1_a[] = { 0.0033357252850015492, -0.012580751999015526, -0.0062414902130117052,
			0.077571493840065148, -0.03224486958502952, -0.24229488706619015,
			0.13842814590110342, 0.72430852843857441, 0.60382926979747287,
			0.16010239797412501 };

		double hp1_a[] = { -0.16010239797412501, 0.60382926979747287, -0.72430852843857441,
			0.13842814590110342, 0.24229488706619015, -0.03224486958502952,
			-0.077571493840065148, -0.0062414902130117052, 0.012580751999015526,
			0.0033357252850015492 };

		double lp2_a[] = { 0.16010239797412501, 0.60382926979747287, 0.72430852843857441,
			0.13842814590110342, -0.24229488706619015, -0.03224486958502952,
			0.077571493840065148, -0.0062414902130117052, -0.012580751999015526,
			0.0033357252850015492 };

		double hp2_a[] = { 0.0033357252850015492, 0.012580751999015526, -0.0062414902130117052,
			-0.077571493840065148, -0.03224486958502952, 0.24229488706619015,
			0.13842814590110342, -0.72430852843857441, 0.60382926979747287,
			-0.16010239797412501 };
		for (i = 0; i < 10; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 10;
	}
	else if (!strcmp(name,"db6")){
		double lp1_a[] = { -0.0010773010849955799,
			0.0047772575110106514,
			0.0005538422009938016,
			-0.031582039318031156,
			0.027522865530016288,
			0.097501605587079362,
			-0.12976686756709563,
			-0.22626469396516913,
			0.3152503517092432,
			0.75113390802157753,
			0.49462389039838539,
			0.11154074335008017
		};

		double hp1_a[] = { -0.11154074335008017,
			0.49462389039838539,
			-0.75113390802157753,
			0.3152503517092432,
			0.22626469396516913,
			-0.12976686756709563,
			-0.097501605587079362,
			0.027522865530016288,
			0.031582039318031156,
			0.0005538422009938016,
			-0.0047772575110106514,
			-0.0010773010849955799
		};

		double lp2_a[] = { 0.11154074335008017,
			0.49462389039838539,
			0.75113390802157753,
			0.3152503517092432,
			-0.22626469396516913,
			-0.12976686756709563,
			0.097501605587079362,
			0.027522865530016288,
			-0.031582039318031156,
			0.0005538422009938016,
			0.0047772575110106514,
			-0.0010773010849955799
		};

		double hp2_a[] = { -0.0010773010849955799,
			-0.0047772575110106514,
			0.0005538422009938016,
			0.031582039318031156,
			0.027522865530016288,
			-0.097501605587079362,
			-0.12976686756709563,
			0.22626469396516913,
			0.3152503517092432,
			-0.75113390802157753,
			0.49462389039838539,
			-0.11154074335008017
		};
		for (i = 0; i < 12; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 12;
	}
	else if (!strcmp(name,"db7")){
		double lp1_a[] = { 0.00035371380000103988,
			-0.0018016407039998328,
			0.00042957797300470274,
			0.012550998556013784,
			-0.01657454163101562,
			-0.038029936935034633,
			0.080612609151065898,
			0.071309219267050042,
			-0.22403618499416572,
			-0.14390600392910627,
			0.4697822874053586,
			0.72913209084655506,
			0.39653931948230575,
			0.077852054085062364
		};

		double hp1_a[] = { -0.077852054085062364,
			0.39653931948230575,
			-0.72913209084655506,
			0.4697822874053586,
			0.14390600392910627,
			-0.22403618499416572,
			-0.071309219267050042,
			0.080612609151065898,
			0.038029936935034633,
			-0.01657454163101562,
			-0.012550998556013784,
			0.0004295779730047027,
			0.0018016407039998328,
			0.00035371380000103988
		};

		double lp2_a[] = { 0.077852054085062364,
			0.39653931948230575,
			0.72913209084655506,
			0.4697822874053586,
			-0.14390600392910627,
			-0.22403618499416572,
			0.071309219267050042,
			0.080612609151065898,
			-0.038029936935034633,
			-0.01657454163101562,
			0.012550998556013784,
			0.00042957797300470274,
			-0.0018016407039998328,
			0.00035371380000103988
		};

		double hp2_a[] = { 0.00035371380000103988,
			0.0018016407039998328,
			0.00042957797300470274,
			-0.01255099855601378,
			-0.01657454163101562,
			0.038029936935034633,
			0.080612609151065898,
			-0.071309219267050042,
			-0.22403618499416572,
			0.14390600392910627,
			0.4697822874053586,
			-0.72913209084655506,
			0.39653931948230575,
			-0.077852054085062364
		};
		for (i = 0; i < 14; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 14;
	}
	else if (!strcmp(name,"db8")){
		double lp1_a[] = { -0.00011747678400228192,
			0.00067544940599855677,
			-0.00039174037299597711,
			-0.0048703529930106603,
			0.0087460940470156547,
			0.013981027917015516,
			-0.044088253931064719,
			-0.017369301002022108,
			0.12874742662018601,
			0.00047248457399797254,
			-0.28401554296242809,
			-0.015829105256023893,
			0.58535468365486909,
			0.67563073629801285,
			0.31287159091446592,
			0.054415842243081609
		};

		double hp1_a[] = { -0.054415842243081609,
			0.31287159091446592,
			-0.67563073629801285,
			0.58535468365486909,
			0.015829105256023893,
			-0.28401554296242809,
			-0.00047248457399797254,
			0.12874742662018601,
			0.017369301002022108,
			-0.044088253931064719,
			-0.013981027917015516,
			0.0087460940470156547,
			0.0048703529930106603,
			-0.00039174037299597711,
			-0.00067544940599855677,
			-0.00011747678400228192
		};

		double lp2_a[] = { 0.054415842243081609,
			0.31287159091446592,
			0.67563073629801285,
			0.58535468365486909,
			-0.015829105256023893,
			-0.28401554296242809,
			0.00047248457399797254,
			0.12874742662018601,
			-0.017369301002022108,
			-0.044088253931064719,
			0.013981027917015516,
			0.0087460940470156547,
			-0.0048703529930106603,
			-0.00039174037299597711,
			0.00067544940599855677,
			-0.00011747678400228192
		};

		double hp2_a[] = { -0.00011747678400228192,
			-0.00067544940599855677,
			-0.00039174037299597711,
			0.0048703529930106603,
			0.0087460940470156547,
			-0.013981027917015516,
			-0.044088253931064719,
			0.017369301002022108,
			0.12874742662018601,
			-0.00047248457399797254,
			-0.28401554296242809,
			0.015829105256023893,
			0.58535468365486909,
			-0.67563073629801285,
			0.31287159091446592,
			-0.054415842243081609
		};
		for (i = 0; i < 16; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 16;
	}
	else if (!strcmp(name,"db9")){
		double lp1_a[] = { 3.9347319995026124e-05,
			-0.00025196318899817888,
			0.00023038576399541288,
			0.0018476468829611268,
			-0.0042815036819047227,
			-0.004723204757894831,
			0.022361662123515244,
			0.00025094711499193845,
			-0.067632829059523988,
			0.030725681478322865,
			0.14854074933476008,
			-0.096840783220879037,
			-0.29327378327258685,
			0.13319738582208895,
			0.65728807803663891,
			0.6048231236767786,
			0.24383467463766728,
			0.038077947363167282
		};

		double hp1_a[] = { -0.038077947363167282,
			0.24383467463766728,
			-0.6048231236767786,
			0.65728807803663891,
			-0.13319738582208895,
			-0.29327378327258685,
			0.096840783220879037,
			0.14854074933476008,
			-0.030725681478322865,
			-0.067632829059523988,
			-0.00025094711499193845,
			0.022361662123515244,
			0.004723204757894831,
			-0.0042815036819047227,
			-0.0018476468829611268,
			0.00023038576399541288,
			0.00025196318899817888,
			3.9347319995026124e-05
		};

		double lp2_a[] = { 0.038077947363167282,
			0.24383467463766728,
			0.6048231236767786,
			0.65728807803663891,
			0.13319738582208895,
			-0.29327378327258685,
			-0.096840783220879037,
			0.14854074933476008,
			0.030725681478322865,
			-0.067632829059523988,
			0.00025094711499193845,
			0.022361662123515244,
			-0.004723204757894831,
			-0.0042815036819047227,
			0.0018476468829611268,
			0.00023038576399541288,
			-0.00025196318899817888,
			3.9347319995026124e-05
		};

		double hp2_a[] = { 3.9347319995026124e-05,
			0.00025196318899817888,
			0.00023038576399541288,
			-0.0018476468829611268,
			-0.0042815036819047227,
			0.004723204757894831,
			0.022361662123515244,
			-0.00025094711499193845,
			-0.067632829059523988,
			-0.030725681478322865,
			0.14854074933476008,
			0.096840783220879037,
			-0.29327378327258685,
			-0.13319738582208895,
			0.65728807803663891,
			-0.6048231236767786,
			0.24383467463766728,
			-0.038077947363167282
		};
		for (i = 0; i < 18; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 18;
	}

	else if (!strcmp(name,"db10")){
		double lp1_a[] = { -1.3264203002354869e-05,
			9.3588670001089845e-05,
			-0.0001164668549943862,
			-0.00068585669500468248,
			0.0019924052949908499,
			0.0013953517469940798,
			-0.010733175482979604,
			0.0036065535669883944,
			0.033212674058933238,
			-0.029457536821945671,
			-0.071394147165860775,
			0.093057364603806592,
			0.12736934033574265,
			-0.19594627437659665,
			-0.24984642432648865,
			0.28117234366042648,
			0.68845903945259213,
			0.52720118893091983,
			0.18817680007762133,
			0.026670057900950818
		};

		double hp1_a[] = { -0.026670057900950818,
			0.18817680007762133,
			-0.52720118893091983,
			0.68845903945259213,
			-0.28117234366042648,
			-0.24984642432648865,
			0.19594627437659665,
			0.12736934033574265,
			-0.093057364603806592,
			-0.071394147165860775,
			0.029457536821945671,
			0.033212674058933238,
			-0.0036065535669883944,
			-0.010733175482979604,
			-0.0013953517469940798,
			0.0019924052949908499,
			0.00068585669500468248,
			-0.0001164668549943862,
			-9.3588670001089845e-05,
			-1.3264203002354869e-05
		};

		double lp2_a[] = { 0.026670057900950818,
			0.18817680007762133,
			0.52720118893091983,
			0.68845903945259213,
			0.28117234366042648,
			-0.24984642432648865,
			-0.19594627437659665,
			0.12736934033574265,
			0.093057364603806592,
			-0.071394147165860775,
			-0.029457536821945671,
			0.033212674058933238,
			0.0036065535669883944,
			-0.010733175482979604,
			0.0013953517469940798,
			0.0019924052949908499,
			-0.00068585669500468248,
			-0.0001164668549943862,
			9.3588670001089845e-05,
			-1.3264203002354869e-05
		};

		double hp2_a[] = { -1.3264203002354869e-05,
			-9.3588670001089845e-05,
			-0.0001164668549943862,
			0.00068585669500468248,
			0.0019924052949908499,
			-0.0013953517469940798,
			-0.010733175482979604,
			-0.0036065535669883944,
			0.033212674058933238,
			0.029457536821945671,
			-0.071394147165860775,
			-0.093057364603806592,
			0.12736934033574265,
			0.19594627437659665,
			-0.24984642432648865,
			-0.28117234366042648,
			0.68845903945259213,
			-0.52720118893091983,
			0.18817680007762133,
			-0.026670057900950818
		};
		for (i = 0; i < 20; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 20;
	}

	else if (!strcmp(name,"db12")){
		double lp1_a[] = { -1.5290717580684923e-06,
			1.2776952219379579e-05,
			-2.4241545757030318e-05,
			-8.8504109208203182e-05,
			0.00038865306282092672,
			6.5451282125215034e-06,
			-0.0021795036186277044,
			0.0022486072409952287,
			0.0067114990087955486,
			-0.012840825198299882,
			-0.01221864906974642,
			0.041546277495087637,
			0.010849130255828966,
			-0.09643212009649671,
			0.0053595696743599965,
			0.18247860592758275,
			-0.023779257256064865,
			-0.31617845375277914,
			-0.044763885653777619,
			0.51588647842780067,
			0.65719872257929113,
			0.37735513521420411,
			0.10956627282118277,
			0.013112257957229239
		};

		double hp1_a[] = { -0.013112257957229239,
			0.10956627282118277,
			-0.37735513521420411,
			0.65719872257929113,
			-0.51588647842780067,
			-0.044763885653777619,
			0.31617845375277914,
			-0.023779257256064865,
			-0.18247860592758275,
			0.0053595696743599965,
			0.09643212009649671,
			0.010849130255828966,
			-0.041546277495087637,
			-0.01221864906974642,
			0.012840825198299882,
			0.0067114990087955486,
			-0.0022486072409952287,
			-0.0021795036186277044,
			-6.5451282125215034e-06,
			0.00038865306282092672,
			8.8504109208203182e-05,
			-2.4241545757030318e-05,
			-1.2776952219379579e-05,
			-1.5290717580684923e-06
		};

		double lp2_a[] = { 0.013112257957229239,
			0.10956627282118277,
			0.37735513521420411,
			0.65719872257929113,
			0.51588647842780067,
			-0.044763885653777619,
			-0.31617845375277914,
			-0.023779257256064865,
			0.18247860592758275,
			0.0053595696743599965,
			-0.09643212009649671,
			0.010849130255828966,
			0.041546277495087637,
			-0.01221864906974642,
			-0.012840825198299882,
			0.0067114990087955486,
			0.0022486072409952287,
			-0.0021795036186277044,
			6.5451282125215034e-06,
			0.00038865306282092672,
			-8.8504109208203182e-05,
			-2.4241545757030318e-05,
			1.2776952219379579e-05,
			-1.5290717580684923e-06
		};

		double hp2_a[] = { -1.5290717580684923e-06,
			-1.2776952219379579e-05,
			-2.4241545757030318e-05,
			8.8504109208203182e-05,
			0.00038865306282092672,
			-6.5451282125215034e-06,
			-0.0021795036186277044,
			-0.0022486072409952287,
			0.0067114990087955486,
			0.012840825198299882,
			-0.01221864906974642,
			-0.041546277495087637,
			0.010849130255828966,
			0.09643212009649671,
			0.0053595696743599965,
			-0.18247860592758275,
			-0.023779257256064865,
			0.31617845375277914,
			-0.044763885653777619,
			-0.51588647842780067,
			0.65719872257929113,
			-0.37735513521420411,
			0.10956627282118277,
			-0.013112257957229239
		};
		for (i = 0; i < 24; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 24;
	}
	else if (!strcmp(name,"db13")){
		double lp1_a[] = { 5.2200350984547998e-07,
			-4.7004164793608082e-06,
			1.0441930571407941e-05,
			3.0678537579324358e-05,
			-0.00016512898855650571,
			4.9251525126285676e-05,
			0.00093232613086724904,
			-0.0013156739118922766,
			-0.002761911234656831,
			0.0072555894016171187,
			0.0039239414487955773,
			-0.023831420710327809,
			0.0023799722540522269,
			0.056139477100276156,
			-0.026488406475345658,
			-0.10580761818792761,
			0.072948933656788742,
			0.17947607942935084,
			-0.12457673075080665,
			-0.31497290771138414,
			0.086985726179645007,
			0.58888957043121193,
			0.61105585115878114,
			0.31199632216043488,
			0.082861243872901946,
			0.0092021335389622788
		};

		double hp1_a[] = { -0.0092021335389622788,
			0.082861243872901946,
			-0.31199632216043488,
			0.61105585115878114,
			-0.58888957043121193,
			0.086985726179645007,
			0.31497290771138414,
			-0.12457673075080665,
			-0.17947607942935084,
			0.072948933656788742,
			0.10580761818792761,
			-0.026488406475345658,
			-0.056139477100276156,
			0.0023799722540522269,
			0.023831420710327809,
			0.0039239414487955773,
			-0.0072555894016171187,
			-0.002761911234656831,
			0.0013156739118922766,
			0.00093232613086724904,
			-4.9251525126285676e-05,
			-0.00016512898855650571,
			-3.0678537579324358e-05,
			1.0441930571407941e-05,
			4.7004164793608082e-06,
			5.2200350984547998e-07
		};

		double lp2_a[] = { 0.0092021335389622788,
			0.082861243872901946,
			0.31199632216043488,
			0.61105585115878114,
			0.58888957043121193,
			0.086985726179645007,
			-0.31497290771138414,
			-0.12457673075080665,
			0.17947607942935084,
			0.072948933656788742,
			-0.10580761818792761,
			-0.026488406475345658,
			0.056139477100276156,
			0.0023799722540522269,
			-0.023831420710327809,
			0.0039239414487955773,
			0.0072555894016171187,
			-0.002761911234656831,
			-0.0013156739118922766,
			0.00093232613086724904,
			4.9251525126285676e-05,
			-0.00016512898855650571,
			3.0678537579324358e-05,
			1.0441930571407941e-05,
			-4.7004164793608082e-06,
			5.2200350984547998e-07
		};

		double hp2_a[] = { 5.2200350984547998e-07,
			4.7004164793608082e-06,
			1.0441930571407941e-05,
			-3.0678537579324358e-05,
			-0.00016512898855650571,
			-4.9251525126285676e-05,
			0.00093232613086724904,
			0.0013156739118922766,
			-0.002761911234656831,
			-0.0072555894016171187,
			0.0039239414487955773,
			0.023831420710327809,
			0.0023799722540522269,
			-0.056139477100276156,
			-0.026488406475345658,
			0.10580761818792761,
			0.072948933656788742,
			-0.17947607942935084,
			-0.12457673075080665,
			0.31497290771138414,
			0.086985726179645007,
			-0.58888957043121193,
			0.61105585115878114,
			-0.31199632216043488,
			0.082861243872901946,
			-0.0092021335389622788
		};
		for (i = 0; i < 26; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 26;
	}

	else if (!strcmp(name,"db11")){
		double lp1_a[] = { 4.4942742772363519e-06,
			-3.4634984186983789e-05,
			5.4439074699366381e-05,
			0.00024915252355281426,
			-0.00089302325066623663,
			-0.00030859285881515924,
			0.0049284176560587777,
			-0.0033408588730145018,
			-0.015364820906201324,
			0.020840904360180039,
			0.031335090219045313,
			-0.066438785695020222,
			-0.04647995511667613,
			0.14981201246638268,
			0.066043588196690886,
			-0.27423084681792875,
			-0.16227524502747828,
			0.41196436894789695,
			0.68568677491617847,
			0.44989976435603013,
			0.14406702115061959,
			0.018694297761470441
		};

		double hp1_a[] = { -0.018694297761470441,
			0.14406702115061959,
			-0.44989976435603013,
			0.68568677491617847,
			-0.41196436894789695,
			-0.16227524502747828,
			0.27423084681792875,
			0.066043588196690886,
			-0.14981201246638268,
			-0.04647995511667613,
			0.066438785695020222,
			0.031335090219045313,
			-0.020840904360180039,
			-0.015364820906201324,
			0.0033408588730145018,
			0.0049284176560587777,
			0.00030859285881515924,
			-0.00089302325066623663,
			-0.00024915252355281426,
			5.4439074699366381e-05,
			3.4634984186983789e-05,
			4.4942742772363519e-06
		};

		double lp2_a[] = { 0.018694297761470441,
			0.14406702115061959,
			0.44989976435603013,
			0.68568677491617847,
			0.41196436894789695,
			-0.16227524502747828,
			-0.27423084681792875,
			0.066043588196690886,
			0.14981201246638268,
			-0.04647995511667613,
			-0.066438785695020222,
			0.031335090219045313,
			0.020840904360180039,
			-0.015364820906201324,
			-0.0033408588730145018,
			0.0049284176560587777,
			-0.00030859285881515924,
			-0.00089302325066623663,
			0.00024915252355281426,
			5.4439074699366381e-05,
			-3.4634984186983789e-05,
			4.4942742772363519e-06
		};

		double hp2_a[] = { 4.4942742772363519e-06,
			3.4634984186983789e-05,
			5.4439074699366381e-05,
			-0.00024915252355281426,
			-0.00089302325066623663,
			0.00030859285881515924,
			0.0049284176560587777,
			0.0033408588730145018,
			-0.015364820906201324,
			-0.020840904360180039,
			0.031335090219045313,
			0.066438785695020222,
			-0.04647995511667613,
			-0.14981201246638268,
			0.066043588196690886,
			0.27423084681792875,
			-0.16227524502747828,
			-0.41196436894789695,
			0.68568677491617847,
			-0.44989976435603013,
			0.14406702115061959,
			-0.018694297761470441
		};
		for (i = 0; i < 22; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 22;
	}

	else if (!strcmp(name,"db14")){
		double lp1_a[] = { -1.7871399683109222e-07,
			1.7249946753674012e-06,
			-4.3897049017804176e-06,
			-1.0337209184568496e-05,
			6.875504252695734e-05,
			-4.1777245770370672e-05,
			-0.00038683194731287514,
			0.00070802115423540481,
			0.001061691085606874,
			-0.003849638868019787,
			-0.00074621898926387534,
			0.012789493266340071,
			-0.0056150495303375755,
			-0.030185351540353976,
			0.026981408307947971,
			0.05523712625925082,
			-0.071548955503983505,
			-0.086748411568110598,
			0.13998901658445695,
			0.13839521386479153,
			-0.21803352999321651,
			-0.27168855227867705,
			0.21867068775886594,
			0.63118784910471981,
			0.55430561794077093,
			0.25485026779256437,
			0.062364758849384874,
			0.0064611534600864905
		};

		double hp1_a[] = { -0.0064611534600864905,
			0.062364758849384874,
			-0.25485026779256437,
			0.55430561794077093,
			-0.63118784910471981,
			0.21867068775886594,
			0.27168855227867705,
			-0.21803352999321651,
			-0.13839521386479153,
			0.13998901658445695,
			0.086748411568110598,
			-0.071548955503983505,
			-0.05523712625925082,
			0.026981408307947971,
			0.030185351540353976,
			-0.0056150495303375755,
			-0.012789493266340071,
			-0.00074621898926387534,
			0.003849638868019787,
			0.001061691085606874,
			-0.00070802115423540481,
			-0.00038683194731287514,
			4.1777245770370672e-05,
			6.875504252695734e-05,
			1.0337209184568496e-05,
			-4.3897049017804176e-06,
			-1.7249946753674012e-06,
			-1.7871399683109222e-07
		};

		double lp2_a[] = { 0.0064611534600864905,
			0.062364758849384874,
			0.25485026779256437,
			0.55430561794077093,
			0.63118784910471981,
			0.21867068775886594,
			-0.27168855227867705,
			-0.21803352999321651,
			0.13839521386479153,
			0.13998901658445695,
			-0.086748411568110598,
			-0.071548955503983505,
			0.05523712625925082,
			0.026981408307947971,
			-0.030185351540353976,
			-0.0056150495303375755,
			0.012789493266340071,
			-0.00074621898926387534,
			-0.003849638868019787,
			0.001061691085606874,
			0.00070802115423540481,
			-0.00038683194731287514,
			-4.1777245770370672e-05,
			6.875504252695734e-05,
			-1.0337209184568496e-05,
			-4.3897049017804176e-06,
			1.7249946753674012e-06,
			-1.7871399683109222e-07
		};

		double hp2_a[] = { -1.7871399683109222e-07,
			-1.7249946753674012e-06,
			-4.3897049017804176e-06,
			1.0337209184568496e-05,
			6.875504252695734e-05,
			4.1777245770370672e-05,
			-0.00038683194731287514,
			-0.00070802115423540481,
			0.001061691085606874,
			0.003849638868019787,
			-0.00074621898926387534,
			-0.012789493266340071,
			-0.0056150495303375755,
			0.030185351540353976,
			0.026981408307947971,
			-0.05523712625925082,
			-0.071548955503983505,
			0.086748411568110598,
			0.13998901658445695,
			-0.13839521386479153,
			-0.21803352999321651,
			0.27168855227867705,
			0.21867068775886594,
			-0.63118784910471981,
			0.55430561794077093,
			-0.25485026779256437,
			0.062364758849384874,
			-0.0064611534600864905
		};
		for (i = 0; i < 28; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 28;
	}
	else if (!strcmp(name,"db15")){
		double lp1_a[] = { 6.1333599133037138e-08,
			-6.3168823258794506e-07,
			1.8112704079399406e-06,
			3.3629871817363823e-06,
			-2.8133296266037558e-05,
			2.579269915531323e-05,
			0.00015589648992055726,
			-0.00035956524436229364,
			-0.00037348235413726472,
			0.0019433239803823459,
			-0.00024175649075894543,
			-0.0064877345603061454,
			0.0051010003604228726,
			0.015083918027862582,
			-0.020810050169636805,
			-0.025767007328366939,
			0.054780550584559995,
			0.033877143923563204,
			-0.11112093603713753,
			-0.039666176555733602,
			0.19014671400708816,
			0.065282952848765688,
			-0.28888259656686216,
			-0.19320413960907623,
			0.33900253545462167,
			0.64581314035721027,
			0.49263177170797529,
			0.20602386398692688,
			0.046743394892750617,
			0.0045385373615773762
		};

		double hp1_a[] = { -0.0045385373615773762,
			0.046743394892750617,
			-0.20602386398692688,
			0.49263177170797529,
			-0.64581314035721027,
			0.33900253545462167,
			0.19320413960907623,
			-0.28888259656686216,
			-0.065282952848765688,
			0.19014671400708816,
			0.039666176555733602,
			-0.11112093603713753,
			-0.033877143923563204,
			0.054780550584559995,
			0.025767007328366939,
			-0.020810050169636805,
			-0.015083918027862582,
			0.0051010003604228726,
			0.0064877345603061454,
			-0.00024175649075894543,
			-0.0019433239803823459,
			-0.00037348235413726472,
			0.00035956524436229364,
			0.00015589648992055726,
			-2.579269915531323e-05,
			-2.8133296266037558e-05,
			-3.3629871817363823e-06,
			1.8112704079399406e-06,
			6.3168823258794506e-07,
			6.1333599133037138e-08
		};

		double lp2_a[] = { 0.0045385373615773762,
			0.046743394892750617,
			0.20602386398692688,
			0.49263177170797529,
			0.64581314035721027,
			0.33900253545462167,
			-0.19320413960907623,
			-0.28888259656686216,
			0.065282952848765688,
			0.19014671400708816,
			-0.039666176555733602,
			-0.11112093603713753,
			0.033877143923563204,
			0.054780550584559995,
			-0.025767007328366939,
			-0.020810050169636805,
			0.015083918027862582,
			0.0051010003604228726,
			-0.0064877345603061454,
			-0.00024175649075894543,
			0.0019433239803823459,
			-0.00037348235413726472,
			-0.00035956524436229364,
			0.00015589648992055726,
			2.579269915531323e-05,
			-2.8133296266037558e-05,
			3.3629871817363823e-06,
			1.8112704079399406e-06,
			-6.3168823258794506e-07,
			6.1333599133037138e-08
		};

		double hp2_a[] = { 6.1333599133037138e-08,
			6.3168823258794506e-07,
			1.8112704079399406e-06,
			-3.3629871817363823e-06,
			-2.8133296266037558e-05,
			-2.579269915531323e-05,
			0.00015589648992055726,
			0.00035956524436229364,
			-0.00037348235413726472,
			-0.0019433239803823459,
			-0.00024175649075894543,
			0.0064877345603061454,
			0.0051010003604228726,
			-0.015083918027862582,
			-0.020810050169636805,
			0.025767007328366939,
			0.054780550584559995,
			-0.033877143923563204,
			-0.11112093603713753,
			0.039666176555733602,
			0.19014671400708816,
			-0.065282952848765688,
			-0.28888259656686216,
			0.19320413960907623,
			0.33900253545462167,
			-0.64581314035721027,
			0.49263177170797529,
			-0.20602386398692688,
			0.046743394892750617,
			-0.0045385373615773762
		};
		for (i = 0; i < 30; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 30;
	}
	else if (!strcmp(name,"bior1.1")){
		double lp1_a[] = { 0.70710678118654757,
			0.70710678118654757
		};

		double hp1_a[] = { -0.70710678118654757,
			0.70710678118654757
		};

		double lp2_a[] = { 0.70710678118654757,
			0.70710678118654757
		};

		double hp2_a[] = { 0.70710678118654757,
			-0.70710678118654757
		};
		for (i = 0; i < 2; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 2;
	}

	else if (!strcmp(name,"bior1.3")){
		double lp1_a[] = { -0.088388347648318447,
			0.088388347648318447,
			0.70710678118654757,
			0.70710678118654757,
			0.088388347648318447,
			-0.088388347648318447,
		};

		double hp1_a[] = { 0.0,
			0.0,
			-0.70710678118654757,
			0.70710678118654757,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			0.0,
			0.70710678118654757,
			0.70710678118654757,
			0.0,
			0.0
		};

		double hp2_a[] = { -0.088388347648318447,
			-0.088388347648318447,
			0.70710678118654757,
			-0.70710678118654757,
			0.088388347648318447,
			0.088388347648318447
		};
		for (i = 0; i < 6; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 6;
	}

	else if (!strcmp(name,"bior1.5")){
		double lp1_a[] = { 0.01657281518405971,
			-0.01657281518405971,
			-0.12153397801643787,
			0.12153397801643787,
			0.70710678118654757,
			0.70710678118654757,
			0.12153397801643787,
			-0.12153397801643787,
			-0.01657281518405971,
			0.01657281518405971
		};

		double hp1_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			-0.70710678118654757,
			0.70710678118654757,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			0.70710678118654757,
			0.70710678118654757,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double hp2_a[] = { 0.01657281518405971,
			0.01657281518405971,
			-0.12153397801643787,
			-0.12153397801643787,
			0.70710678118654757,
			-0.70710678118654757,
			0.12153397801643787,
			0.12153397801643787,
			-0.01657281518405971,
			-0.01657281518405971
		};
		for (i = 0; i < 10; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 10;
	}

	else if (!strcmp(name,"bior2.2")){
		double lp1_a[] = { 0.0,
			-0.17677669529663689,
			0.35355339059327379,
			1.0606601717798214,
			0.35355339059327379,
			-0.17677669529663689
		};

		double hp1_a[] = { 0.0,
			0.35355339059327379,
			-0.70710678118654757,
			0.35355339059327379,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			0.35355339059327379,
			0.70710678118654757,
			0.35355339059327379,
			0.0,
			0.0
		};

		double hp2_a[] = { 0.0,
			0.17677669529663689,
			0.35355339059327379,
			-1.0606601717798214,
			0.35355339059327379,
			0.17677669529663689

		};
		for (i = 0; i < 6; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 6;
	}

	else if (!strcmp(name,"bior2.4")){
		double lp1_a[] = { 0.0,
			0.033145630368119419,
			-0.066291260736238838,
			-0.17677669529663689,
			0.4198446513295126,
			0.99436891104358249,
			0.4198446513295126,
			-0.17677669529663689,
			-0.066291260736238838,
			0.033145630368119419
		};

		double hp1_a[] = { 0.0,
			0.0,
			0.0,
			0.35355339059327379,
			-0.70710678118654757,
			0.35355339059327379,
			0.0,
			0.0,
			0.0,
			0.0

		};

		double lp2_a[] = { 0.0,
			0.0,
			0.0,
			0.35355339059327379,
			0.70710678118654757,
			0.35355339059327379,
			0.0,
			0.0,
			0.0,
			0.0

		};

		double hp2_a[] = { 0.0,
			-0.033145630368119419,
			-0.066291260736238838,
			0.17677669529663689,
			0.4198446513295126,
			-0.99436891104358249,
			0.4198446513295126,
			0.17677669529663689,
			-0.066291260736238838,
			-0.033145630368119419
		};
		for (i = 0; i < 10; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 10;
	}

	else if (!strcmp(name,"bior2.6")){
		double lp1_a[] = { 0.0,
			-0.0069053396600248784,
			0.013810679320049757,
			0.046956309688169176,
			-0.10772329869638811,
			-0.16987135563661201,
			0.44746600996961211,
			0.96674755240348298,
			0.44746600996961211,
			-0.16987135563661201,
			-0.10772329869638811,
			0.046956309688169176,
			0.013810679320049757,
			-0.0069053396600248784
		};

		double hp1_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.35355339059327379,
			-0.70710678118654757,
			0.35355339059327379,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.35355339059327379,
			0.70710678118654757,
			0.35355339059327379,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double hp2_a[] = { 0.0,
			0.0069053396600248784,
			0.013810679320049757,
			-0.046956309688169176,
			-0.10772329869638811,
			0.16987135563661201,
			0.44746600996961211,
			-0.96674755240348298,
			0.44746600996961211,
			0.16987135563661201,
			-0.10772329869638811,
			-0.046956309688169176,
			0.013810679320049757,
			0.0069053396600248784
		};
		for (i = 0; i < 14; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 14;
	}
	else if (!strcmp(name,"bior2.8")){
		double lp1_a[] = { 0.0,
			0.0015105430506304422,
			-0.0030210861012608843,
			-0.012947511862546647,
			0.028916109826354178,
			0.052998481890690945,
			-0.13491307360773608,
			-0.16382918343409025,
			0.46257144047591658,
			0.95164212189717856,
			0.46257144047591658,
			-0.16382918343409025,
			-0.13491307360773608,
			0.052998481890690945,
			0.028916109826354178,
			-0.012947511862546647,
			-0.0030210861012608843,
			0.0015105430506304422
		};

		double hp1_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.35355339059327379,
			-0.70710678118654757,
			0.35355339059327379,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.35355339059327379,
			0.70710678118654757,
			0.35355339059327379,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double hp2_a[] = { 0.0,
			-0.0015105430506304422,
			-0.0030210861012608843,
			0.012947511862546647,
			0.028916109826354178,
			-0.052998481890690945,
			-0.13491307360773608,
			0.16382918343409025,
			0.46257144047591658,
			-0.95164212189717856,
			0.46257144047591658,
			0.16382918343409025,
			-0.13491307360773608,
			-0.052998481890690945,
			0.028916109826354178,
			0.012947511862546647,
			-0.0030210861012608843,
			-0.0015105430506304422
		};
		for (i = 0; i < 18; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 18;
	}

	else if (!strcmp(name,"bior3.1")){
		double lp1_a[] = { -0.35355339059327379,
			1.0606601717798214,
			1.0606601717798214,
			-0.35355339059327379
		};

		double hp1_a[] = { -0.17677669529663689,
			0.53033008588991071,
			-0.53033008588991071,
			0.17677669529663689
		};

		double lp2_a[] = { 0.17677669529663689,
			0.53033008588991071,
			0.53033008588991071,
			0.17677669529663689
		};

		double hp2_a[] = { -0.35355339059327379,
			-1.0606601717798214,
			1.0606601717798214,
			0.35355339059327379
		};
		for (i = 0; i < 4; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 4;
	}
	else if (!strcmp(name,"bior3.3")){
		double lp1_a[] = { 0.066291260736238838,
			-0.19887378220871652,
			-0.15467960838455727,
			0.99436891104358249,
			0.99436891104358249,
			-0.15467960838455727,
			-0.19887378220871652,
			0.066291260736238838
		};

		double hp1_a[] = { 0.0,
			0.0,
			-0.17677669529663689,
			0.53033008588991071,
			-0.53033008588991071,
			0.17677669529663689,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			0.0,
			0.17677669529663689,
			0.53033008588991071,
			0.53033008588991071,
			0.17677669529663689,
			0.0,
			0.0
		};

		double hp2_a[] = { 0.066291260736238838,
			0.19887378220871652,
			-0.15467960838455727,
			-0.99436891104358249,
			0.99436891104358249,
			0.15467960838455727,
			-0.19887378220871652,
			-0.066291260736238838
		};
		for (i = 0; i < 8; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 8;
	}
	else if (!strcmp(name,"bior3.5")){
		double lp1_a[] = { -0.013810679320049757,
			0.041432037960149271,
			0.052480581416189075,
			-0.26792717880896527,
			-0.071815532464258744,
			0.96674755240348298,
			0.96674755240348298,
			-0.071815532464258744,
			-0.26792717880896527,
			0.052480581416189075,
			0.041432037960149271,
			-0.013810679320049757
		};

		double hp1_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			-0.17677669529663689,
			0.53033008588991071,
			-0.53033008588991071,
			0.17677669529663689,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			0.17677669529663689,
			0.53033008588991071,
			0.53033008588991071,
			0.17677669529663689,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double hp2_a[] = { -0.013810679320049757,
			-0.041432037960149271,
			0.052480581416189075,
			0.26792717880896527,
			-0.071815532464258744,
			-0.96674755240348298,
			0.96674755240348298,
			0.071815532464258744,
			-0.26792717880896527,
			-0.052480581416189075,
			0.041432037960149271,
			0.013810679320049757
		};
		for (i = 0; i < 12; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 12;
	}

	else if (!strcmp(name,"bior3.7")){
		double lp1_a[] = { 0.0030210861012608843,
			-0.0090632583037826529,
			-0.016831765421310641,
			0.074663985074019001,
			0.031332978707362888,
			-0.301159125922835,
			-0.026499240945345472,
			0.95164212189717856,
			0.95164212189717856,
			-0.026499240945345472,
			-0.301159125922835,
			0.031332978707362888,
			0.074663985074019001,
			-0.016831765421310641,
			-0.0090632583037826529,
			0.0030210861012608843
		};

		double hp1_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			-0.17677669529663689,
			0.53033008588991071,
			-0.53033008588991071,
			0.17677669529663689,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.17677669529663689,
			0.53033008588991071,
			0.53033008588991071,
			0.17677669529663689,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double hp2_a[] = { 0.0030210861012608843,
			0.0090632583037826529,
			-0.016831765421310641,
			-0.074663985074019001,
			0.031332978707362888,
			0.301159125922835,
			-0.026499240945345472,
			-0.95164212189717856,
			0.95164212189717856,
			0.026499240945345472,
			-0.301159125922835,
			-0.031332978707362888,
			0.074663985074019001,
			0.016831765421310641,
			-0.0090632583037826529,
			-0.0030210861012608843
		};
		for (i = 0; i < 16; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 16;
	}
	else if (!strcmp(name,"bior3.9")){
		double lp1_a[] = { -0.00067974437278369901,
			0.0020392331183510968,
			0.0050603192196119811,
			-0.020618912641105536,
			-0.014112787930175846,
			0.09913478249423216,
			0.012300136269419315,
			-0.32019196836077857,
			0.0020500227115698858,
			0.94212570067820678,
			0.94212570067820678,
			0.0020500227115698858,
			-0.32019196836077857,
			0.012300136269419315,
			0.09913478249423216,
			-0.014112787930175846,
			-0.020618912641105536,
			0.0050603192196119811,
			0.0020392331183510968,
			-0.00067974437278369901
		};

		double hp1_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			-0.17677669529663689,
			0.53033008588991071,
			-0.53033008588991071,
			0.17677669529663689,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.17677669529663689,
			0.53033008588991071,
			0.53033008588991071,
			0.17677669529663689,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double hp2_a[] = { -0.00067974437278369901,
			-0.0020392331183510968,
			0.0050603192196119811,
			0.020618912641105536,
			-0.014112787930175846,
			-0.09913478249423216,
			0.012300136269419315,
			0.32019196836077857,
			0.0020500227115698858,
			-0.94212570067820678,
			0.94212570067820678,
			-0.0020500227115698858,
			-0.32019196836077857,
			-0.012300136269419315,
			0.09913478249423216,
			0.014112787930175846,
			-0.020618912641105536,
			-0.0050603192196119811,
			0.0020392331183510968,
			0.00067974437278369901
		};
		for (i = 0; i < 20; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 20;
	}
	else if (!strcmp(name,"bior4.4")){
		double lp1_a[] = { 0.0,
			0.03782845550726404,
			-0.023849465019556843,
			-0.11062440441843718,
			0.37740285561283066,
			0.85269867900889385,
			0.37740285561283066,
			-0.11062440441843718,
			-0.023849465019556843,
			0.03782845550726404
		};

		double hp1_a[] = { 0.0,
			-0.064538882628697058,
			0.040689417609164058,
			0.41809227322161724,
			-0.7884856164055829,
			0.41809227322161724,
			0.040689417609164058,
			-0.064538882628697058,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			-0.064538882628697058,
			-0.040689417609164058,
			0.41809227322161724,
			0.7884856164055829,
			0.41809227322161724,
			-0.040689417609164058,
			-0.064538882628697058,
			0.0,
			0.0
		};

		double hp2_a[] = { 0.0,
			-0.03782845550726404,
			-0.023849465019556843,
			0.11062440441843718,
			0.37740285561283066,
			-0.85269867900889385,
			0.37740285561283066,
			0.11062440441843718,
			-0.023849465019556843,
			-0.03782845550726404
		};
		for (i = 0; i < 10; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 10;
	}
	else if (!strcmp(name,"bior5.5")){
		double lp1_a[] = { 0.0,
			0.0,
			0.03968708834740544,
			0.0079481086372403219,
			-0.054463788468236907,
			0.34560528195603346,
			0.73666018142821055,
			0.34560528195603346,
			-0.054463788468236907,
			0.0079481086372403219,
			0.03968708834740544,
			0.0
		};

		double hp1_a[] = { -0.013456709459118716,
			-0.0026949668801115071,
			0.13670658466432914,
			-0.093504697400938863,
			-0.47680326579848425,
			0.89950610974864842,
			-0.47680326579848425,
			-0.093504697400938863,
			0.13670658466432914,
			-0.0026949668801115071,
			-0.013456709459118716,
			0.0
		};

		double lp2_a[] = { 0.013456709459118716,
			-0.0026949668801115071,
			-0.13670658466432914,
			-0.093504697400938863,
			0.47680326579848425,
			0.89950610974864842,
			0.47680326579848425,
			-0.093504697400938863,
			-0.13670658466432914,
			-0.0026949668801115071,
			0.013456709459118716,
			0.0
		};

		double hp2_a[] = { 0.0,
			0.0,
			0.03968708834740544,
			-0.0079481086372403219,
			-0.054463788468236907,
			-0.34560528195603346,
			0.73666018142821055,
			-0.34560528195603346,
			-0.054463788468236907,
			-0.0079481086372403219,
			0.03968708834740544,
			0.0
		};
		for (i = 0; i < 12; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 12;
	}
	else if (!strcmp(name,"bior6.8")){
		double lp1_a[] = { 0.0,
			0.0019088317364812906,
			-0.0019142861290887667,
			-0.016990639867602342,
			0.01193456527972926,
			0.04973290349094079,
			-0.077263173167204144,
			-0.09405920349573646,
			0.42079628460982682,
			0.82592299745840225,
			0.42079628460982682,
			-0.09405920349573646,
			-0.077263173167204144,
			0.04973290349094079,
			0.01193456527972926,
			-0.016990639867602342,
			-0.0019142861290887667,
			0.0019088317364812906
		};

		double hp1_a[] = { 0.0,
			0.0,
			0.0,
			0.014426282505624435,
			-0.014467504896790148,
			-0.078722001062628819,
			0.040367979030339923,
			0.41784910915027457,
			-0.75890772945365415,
			0.41784910915027457,
			0.040367979030339923,
			-0.078722001062628819,
			-0.014467504896790148,
			0.014426282505624435,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double lp2_a[] = { 0.0,
			0.0,
			0.0,
			0.014426282505624435,
			0.014467504896790148,
			-0.078722001062628819,
			-0.040367979030339923,
			0.41784910915027457,
			0.75890772945365415,
			0.41784910915027457,
			-0.040367979030339923,
			-0.078722001062628819,
			0.014467504896790148,
			0.014426282505624435,
			0.0,
			0.0,
			0.0,
			0.0
		};

		double hp2_a[] = { 0.0,
			-0.0019088317364812906,
			-0.0019142861290887667,
			0.016990639867602342,
			0.01193456527972926,
			-0.04973290349094079,
			-0.077263173167204144,
			0.09405920349573646,
			0.42079628460982682,
			-0.82592299745840225,
			0.42079628460982682,
			0.09405920349573646,
			-0.077263173167204144,
			-0.04973290349094079,
			0.01193456527972926,
			0.016990639867602342,
			-0.0019142861290887667,
			-0.0019088317364812906
		};
		for (i = 0; i < 18; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 18;
	}

	else if (!strcmp(name,"coif1")){
		double lp1_a[] = { -0.01565572813546454,
			-0.072732619512853897,
			0.38486484686420286,
			0.85257202021225542,
			0.33789766245780922,
			-0.072732619512853897
		};

		double hp1_a[] = { 0.072732619512853897,
			0.33789766245780922,
			-0.85257202021225542,
			0.38486484686420286,
			0.072732619512853897,
			-0.01565572813546454
		};

		double lp2_a[] = { -0.072732619512853897,
			0.33789766245780922,
			0.85257202021225542,
			0.38486484686420286,
			-0.072732619512853897,
			-0.01565572813546454
		};

		double hp2_a[] = { -0.01565572813546454,
			0.072732619512853897,
			0.38486484686420286,
			-0.85257202021225542,
			0.33789766245780922,
			0.072732619512853897
		};
		for (i = 0; i < 6; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 6;
	}
	else if (!strcmp(name,"coif2")){
		double lp1_a[] = { -0.00072054944536451221,
			-0.0018232088707029932,
			0.0056114348193944995,
			0.023680171946334084,
			-0.059434418646456898,
			-0.076488599078306393,
			0.41700518442169254,
			0.81272363544554227,
			0.38611006682116222,
			-0.067372554721963018,
			-0.041464936781759151,
			0.016387336463522112
		};

		double hp1_a[] = { -0.016387336463522112,
			-0.041464936781759151,
			0.067372554721963018,
			0.38611006682116222,
			-0.81272363544554227,
			0.41700518442169254,
			0.076488599078306393,
			-0.059434418646456898,
			-0.023680171946334084,
			0.0056114348193944995,
			0.0018232088707029932,
			-0.00072054944536451221
		};

		double lp2_a[] = { 0.016387336463522112,
			-0.041464936781759151,
			-0.067372554721963018,
			0.38611006682116222,
			0.81272363544554227,
			0.41700518442169254,
			-0.076488599078306393,
			-0.059434418646456898,
			0.023680171946334084,
			0.0056114348193944995,
			-0.0018232088707029932,
			-0.00072054944536451221
		};

		double hp2_a[] = { -0.00072054944536451221,
			0.0018232088707029932,
			0.0056114348193944995,
			-0.023680171946334084,
			-0.059434418646456898,
			0.076488599078306393,
			0.41700518442169254,
			-0.81272363544554227,
			0.38611006682116222,
			0.067372554721963018,
			-0.041464936781759151,
			-0.016387336463522112
		};
		for (i = 0; i < 12; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 12;
	}
	else if (!strcmp(name,"coif3")){
		double lp1_a[] = { -3.4599772836212559e-05,
			-7.0983303138141252e-05,
			0.00046621696011288631,
			0.0011175187708906016,
			-0.0025745176887502236,
			-0.0090079761366615805,
			0.015880544863615904,
			0.034555027573061628,
			-0.082301927106885983,
			-0.071799821619312018,
			0.42848347637761874,
			0.79377722262562056,
			0.4051769024096169,
			-0.061123390002672869,
			-0.0657719112818555,
			0.023452696141836267,
			0.0077825964273254182,
			-0.0037935128644910141
		};

		double hp1_a[] = { 0.0037935128644910141,
			0.0077825964273254182,
			-0.023452696141836267,
			-0.0657719112818555,
			0.061123390002672869,
			0.4051769024096169,
			-0.79377722262562056,
			0.42848347637761874,
			0.071799821619312018,
			-0.082301927106885983,
			-0.034555027573061628,
			0.015880544863615904,
			0.0090079761366615805,
			-0.0025745176887502236,
			-0.0011175187708906016,
			0.00046621696011288631,
			7.0983303138141252e-05,
			-3.4599772836212559e-05
		};

		double lp2_a[] = { -0.0037935128644910141,
			0.0077825964273254182,
			0.023452696141836267,
			-0.0657719112818555,
			-0.061123390002672869,
			0.4051769024096169,
			0.79377722262562056,
			0.42848347637761874,
			-0.071799821619312018,
			-0.082301927106885983,
			0.034555027573061628,
			0.015880544863615904,
			-0.0090079761366615805,
			-0.0025745176887502236,
			0.0011175187708906016,
			0.00046621696011288631,
			-7.0983303138141252e-05,
			-3.4599772836212559e-05
		};

		double hp2_a[] = { -3.4599772836212559e-05,
			7.0983303138141252e-05,
			0.00046621696011288631,
			-0.0011175187708906016,
			-0.0025745176887502236,
			0.0090079761366615805,
			0.015880544863615904,
			-0.034555027573061628,
			-0.082301927106885983,
			0.071799821619312018,
			0.42848347637761874,
			-0.79377722262562056,
			0.4051769024096169,
			0.061123390002672869,
			-0.0657719112818555,
			-0.023452696141836267,
			0.0077825964273254182,
			0.0037935128644910141
		};
		for (i = 0; i < 18; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 18;
	}
	else if (!strcmp(name,"coif4")){
		double lp1_a[] = { -1.7849850030882614e-06,
			-3.2596802368833675e-06,
			3.1229875865345646e-05,
			6.2339034461007128e-05,
			-0.00025997455248771324,
			-0.00058902075624433831,
			0.0012665619292989445,
			0.0037514361572784571,
			-0.0056582866866107199,
			-0.015211731527946259,
			0.025082261844864097,
			0.039334427123337491,
			-0.096220442033987982,
			-0.066627474263425038,
			0.4343860564914685,
			0.78223893092049901,
			0.41530840703043026,
			-0.056077313316754807,
			-0.081266699680878754,
			0.026682300156053072,
			0.016068943964776348,
			-0.0073461663276420935,
			-0.0016294920126017326,
			0.00089231366858231456
		};

		double hp1_a[] = { -0.00089231366858231456,
			-0.0016294920126017326,
			0.0073461663276420935,
			0.016068943964776348,
			-0.026682300156053072,
			-0.081266699680878754,
			0.056077313316754807,
			0.41530840703043026,
			-0.78223893092049901,
			0.4343860564914685,
			0.066627474263425038,
			-0.096220442033987982,
			-0.039334427123337491,
			0.025082261844864097,
			0.015211731527946259,
			-0.0056582866866107199,
			-0.0037514361572784571,
			0.0012665619292989445,
			0.00058902075624433831,
			-0.00025997455248771324,
			-6.2339034461007128e-05,
			3.1229875865345646e-05,
			3.2596802368833675e-06,
			-1.7849850030882614e-06
		};

		double lp2_a[] = { 0.00089231366858231456,
			-0.0016294920126017326,
			-0.0073461663276420935,
			0.016068943964776348,
			0.026682300156053072,
			-0.081266699680878754,
			-0.056077313316754807,
			0.41530840703043026,
			0.78223893092049901,
			0.4343860564914685,
			-0.066627474263425038,
			-0.096220442033987982,
			0.039334427123337491,
			0.025082261844864097,
			-0.015211731527946259,
			-0.0056582866866107199,
			0.0037514361572784571,
			0.0012665619292989445,
			-0.00058902075624433831,
			-0.00025997455248771324,
			6.2339034461007128e-05,
			3.1229875865345646e-05,
			-3.2596802368833675e-06,
			-1.7849850030882614e-06
		};

		double hp2_a[] = { -1.7849850030882614e-06,
			3.2596802368833675e-06,
			3.1229875865345646e-05,
			-6.2339034461007128e-05,
			-0.00025997455248771324,
			0.00058902075624433831,
			0.0012665619292989445,
			-0.0037514361572784571,
			-0.0056582866866107199,
			0.015211731527946259,
			0.025082261844864097,
			-0.039334427123337491,
			-0.096220442033987982,
			0.066627474263425038,
			0.4343860564914685,
			-0.78223893092049901,
			0.41530840703043026,
			0.056077313316754807,
			-0.081266699680878754,
			-0.026682300156053072,
			0.016068943964776348,
			0.0073461663276420935,
			-0.0016294920126017326,
			-0.00089231366858231456
		};
		for (i = 0; i < 24; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 24;
	}
	else if (!strcmp(name,"coif5")){
		double lp1_a[] = { -9.517657273819165e-08,
			-1.6744288576823017e-07,
			2.0637618513646814e-06,
			3.7346551751414047e-06,
			-2.1315026809955787e-05,
			-4.1340432272512511e-05,
			0.00014054114970203437,
			0.00030225958181306315,
			-0.00063813134304511142,
			-0.0016628637020130838,
			0.0024333732126576722,
			0.0067641854480530832,
			-0.0091642311624818458,
			-0.019761778942572639,
			0.032683574267111833,
			0.041289208750181702,
			-0.10557420870333893,
			-0.062035963962903569,
			0.43799162617183712,
			0.77428960365295618,
			0.42156620669085149,
			-0.052043163176243773,
			-0.091920010559696244,
			0.02816802897093635,
			0.023408156785839195,
			-0.010131117519849788,
			-0.004159358781386048,
			0.0021782363581090178,
			0.00035858968789573785,
			-0.00021208083980379827
		};

		double hp1_a[] = { 0.00021208083980379827,
			0.00035858968789573785,
			-0.0021782363581090178,
			-0.004159358781386048,
			0.010131117519849788,
			0.023408156785839195,
			-0.02816802897093635,
			-0.091920010559696244,
			0.052043163176243773,
			0.42156620669085149,
			-0.77428960365295618,
			0.43799162617183712,
			0.062035963962903569,
			-0.10557420870333893,
			-0.041289208750181702,
			0.032683574267111833,
			0.019761778942572639,
			-0.0091642311624818458,
			-0.0067641854480530832,
			0.0024333732126576722,
			0.0016628637020130838,
			-0.00063813134304511142,
			-0.00030225958181306315,
			0.00014054114970203437,
			4.1340432272512511e-05,
			-2.1315026809955787e-05,
			-3.7346551751414047e-06,
			2.0637618513646814e-06,
			1.6744288576823017e-07,
			-9.517657273819165e-08
		};

		double lp2_a[] = { -0.00021208083980379827,
			0.00035858968789573785,
			0.0021782363581090178,
			-0.004159358781386048,
			-0.010131117519849788,
			0.023408156785839195,
			0.02816802897093635,
			-0.091920010559696244,
			-0.052043163176243773,
			0.42156620669085149,
			0.77428960365295618,
			0.43799162617183712,
			-0.062035963962903569,
			-0.10557420870333893,
			0.041289208750181702,
			0.032683574267111833,
			-0.019761778942572639,
			-0.0091642311624818458,
			0.0067641854480530832,
			0.0024333732126576722,
			-0.0016628637020130838,
			-0.00063813134304511142,
			0.00030225958181306315,
			0.00014054114970203437,
			-4.1340432272512511e-05,
			-2.1315026809955787e-05,
			3.7346551751414047e-06,
			2.0637618513646814e-06,
			-1.6744288576823017e-07,
			-9.517657273819165e-08
		};

		double hp2_a[] = { -9.517657273819165e-08,
			1.6744288576823017e-07,
			2.0637618513646814e-06,
			-3.7346551751414047e-06,
			-2.1315026809955787e-05,
			4.1340432272512511e-05,
			0.00014054114970203437,
			-0.00030225958181306315,
			-0.00063813134304511142,
			0.0016628637020130838,
			0.0024333732126576722,
			-0.0067641854480530832,
			-0.0091642311624818458,
			0.019761778942572639,
			0.032683574267111833,
			-0.041289208750181702,
			-0.10557420870333893,
			0.062035963962903569,
			0.43799162617183712,
			-0.77428960365295618,
			0.42156620669085149,
			0.052043163176243773,
			-0.091920010559696244,
			-0.02816802897093635,
			0.023408156785839195,
			0.010131117519849788,
			-0.004159358781386048,
			-0.0021782363581090178,
			0.00035858968789573785,
			0.00021208083980379827
		};
		for (i = 0; i < 30; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 30;
	}

	else if (!strcmp(name,"sym2")){
		double lp1_a[] = { -0.12940952255092145,
			0.22414386804185735,
			0.83651630373746899,
			0.48296291314469025
		};

		double hp1_a[] = { -0.48296291314469025,
			0.83651630373746899,
			-0.22414386804185735,
			-0.12940952255092145
		};

		double lp2_a[] = { 0.48296291314469025,
			0.83651630373746899,
			0.22414386804185735,
			-0.12940952255092145
		};

		double hp2_a[] = { -0.12940952255092145,
			-0.22414386804185735,
			0.83651630373746899,
			-0.48296291314469025

		};
		for (i = 0; i < 4; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 4;
	}

	else if (!strcmp(name,"sym3")){
		double lp1_a[] = { 0.035226291882100656,
			-0.085441273882241486,
			-0.13501102001039084,
			0.45987750211933132,
			0.80689150931333875,
			0.33267055295095688

		};

		double hp1_a[] = { -0.33267055295095688,
			0.80689150931333875,
			-0.45987750211933132,
			-0.13501102001039084,
			0.085441273882241486,
			0.035226291882100656
		};

		double lp2_a[] = { 0.33267055295095688,
			0.80689150931333875,
			0.45987750211933132,
			-0.13501102001039084,
			-0.085441273882241486,
			0.035226291882100656
		};

		double hp2_a[] = { 0.035226291882100656,
			0.085441273882241486,
			-0.13501102001039084,
			-0.45987750211933132,
			0.80689150931333875,
			-0.33267055295095688
		};
		for (i = 0; i < 6; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 6;
	}

	else if (!strcmp(name,"sym4")){
		double lp1_a[] = { -0.075765714789273325,
			-0.02963552764599851,
			0.49761866763201545,
			0.80373875180591614,
			0.29785779560527736,
			-0.099219543576847216,
			-0.012603967262037833,
			0.032223100604042702
		};

		double hp1_a[] = { -0.032223100604042702,
			-0.012603967262037833,
			0.099219543576847216,
			0.29785779560527736,
			-0.80373875180591614,
			0.49761866763201545,
			0.02963552764599851,
			-0.075765714789273325
		};

		double lp2_a[] = { 0.032223100604042702,
			-0.012603967262037833,
			-0.099219543576847216,
			0.29785779560527736,
			0.80373875180591614,
			0.49761866763201545,
			-0.02963552764599851,
			-0.075765714789273325
		};

		double hp2_a[] = { -0.075765714789273325,
			0.02963552764599851,
			0.49761866763201545,
			-0.80373875180591614,
			0.29785779560527736,
			0.099219543576847216,
			-0.012603967262037833,
			-0.032223100604042702
		};
		for (i = 0; i < 8; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 8;
	}

	else if (!strcmp(name,"sym5")){
		double lp1_a[] = { 0.027333068345077982,
			0.029519490925774643,
			-0.039134249302383094,
			0.1993975339773936,
			0.72340769040242059,
			0.63397896345821192,
			0.016602105764522319,
			-0.17532808990845047,
			-0.021101834024758855,
			0.019538882735286728
		};

		double hp1_a[] = { -0.019538882735286728,
			-0.021101834024758855,
			0.17532808990845047,
			0.016602105764522319,
			-0.63397896345821192,
			0.72340769040242059,
			-0.1993975339773936,
			-0.039134249302383094,
			-0.029519490925774643,
			0.027333068345077982
		};

		double lp2_a[] = { 0.019538882735286728,
			-0.021101834024758855,
			-0.17532808990845047,
			0.016602105764522319,
			0.63397896345821192,
			0.72340769040242059,
			0.1993975339773936,
			-0.039134249302383094,
			0.029519490925774643,
			0.027333068345077982

		};

		double hp2_a[] = { 0.027333068345077982,
			-0.029519490925774643,
			-0.039134249302383094,
			-0.1993975339773936,
			0.72340769040242059,
			-0.63397896345821192,
			0.016602105764522319,
			0.17532808990845047,
			-0.021101834024758855,
			-0.019538882735286728
		};
		for (i = 0; i < 10; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 10;
	}

	else if (!strcmp(name,"sym6")){
		double lp1_a[] = { 0.015404109327027373,
			0.0034907120842174702,
			-0.11799011114819057,
			-0.048311742585632998,
			0.49105594192674662,
			0.787641141030194,
			0.3379294217276218,
			-0.072637522786462516,
			-0.021060292512300564,
			0.044724901770665779,
			0.0017677118642428036,
			-0.007800708325034148
		};

		double hp1_a[] = { 0.007800708325034148,
			0.0017677118642428036,
			-0.044724901770665779,
			-0.021060292512300564,
			0.072637522786462516,
			0.3379294217276218,
			-0.787641141030194,
			0.49105594192674662,
			0.048311742585632998,
			-0.11799011114819057,
			-0.0034907120842174702,
			0.015404109327027373
		};

		double lp2_a[] = { -0.007800708325034148,
			0.0017677118642428036,
			0.044724901770665779,
			-0.021060292512300564,
			-0.072637522786462516,
			0.3379294217276218,
			0.787641141030194,
			0.49105594192674662,
			-0.048311742585632998,
			-0.11799011114819057,
			0.0034907120842174702,
			0.015404109327027373
		};

		double hp2_a[] = { 0.015404109327027373,
			-0.0034907120842174702,
			-0.11799011114819057,
			0.048311742585632998,
			0.49105594192674662,
			-0.787641141030194,
			0.3379294217276218,
			0.072637522786462516,
			-0.021060292512300564,
			-0.044724901770665779,
			0.0017677118642428036,
			0.007800708325034148
		};
		for (i = 0; i < 12; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 12;
	}

	else if (!strcmp(name,"sym7")){
		double lp1_a[] = { 0.0026818145682578781,
			-0.0010473848886829163,
			-0.01263630340325193,
			0.03051551316596357,
			0.067892693501372697,
			-0.049552834937127255,
			0.017441255086855827,
			0.5361019170917628,
			0.76776431700316405,
			0.28862963175151463,
			-0.14004724044296152,
			-0.10780823770381774,
			0.0040102448715336634,
			0.010268176708511255
		};

		double hp1_a[] = { -0.010268176708511255,
			0.0040102448715336634,
			0.10780823770381774,
			-0.14004724044296152,
			-0.28862963175151463,
			0.76776431700316405,
			-0.5361019170917628,
			0.017441255086855827,
			0.049552834937127255,
			0.067892693501372697,
			-0.03051551316596357,
			-0.01263630340325193,
			0.0010473848886829163,
			0.0026818145682578781

		};

		double lp2_a[] = { 0.010268176708511255,
			0.0040102448715336634,
			-0.10780823770381774,
			-0.14004724044296152,
			0.28862963175151463,
			0.76776431700316405,
			0.5361019170917628,
			0.017441255086855827,
			-0.049552834937127255,
			0.067892693501372697,
			0.03051551316596357,
			-0.01263630340325193,
			-0.0010473848886829163,
			0.0026818145682578781
		};

		double hp2_a[] = { 0.0026818145682578781,
			0.0010473848886829163,
			-0.01263630340325193,
			-0.03051551316596357,
			0.067892693501372697,
			0.049552834937127255,
			0.017441255086855827,
			-0.5361019170917628,
			0.76776431700316405,
			-0.28862963175151463,
			-0.14004724044296152,
			0.10780823770381774,
			0.0040102448715336634,
			-0.010268176708511255
		};
		for (i = 0; i < 14; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 14;
	}

	else if (!strcmp(name,"sym8")){
		double lp1_a[] = { -0.0033824159510061256,
			-0.00054213233179114812,
			0.031695087811492981,
			0.0076074873249176054,
			-0.14329423835080971,
			-0.061273359067658524,
			0.48135965125837221,
			0.77718575170052351,
			0.3644418948353314,
			-0.051945838107709037,
			-0.027219029917056003,
			0.049137179673607506,
			0.0038087520138906151,
			-0.014952258337048231,
			-0.0003029205147213668,
			0.0018899503327594609
		};

		double hp1_a[] = { -0.0018899503327594609,
			-0.0003029205147213668,
			0.014952258337048231,
			0.0038087520138906151,
			-0.049137179673607506,
			-0.027219029917056003,
			0.051945838107709037,
			0.3644418948353314,
			-0.77718575170052351,
			0.48135965125837221,
			0.061273359067658524,
			-0.14329423835080971,
			-0.0076074873249176054,
			0.031695087811492981,
			0.00054213233179114812,
			-0.0033824159510061256
		};

		double lp2_a[] = { 0.0018899503327594609,
			-0.0003029205147213668,
			-0.014952258337048231,
			0.0038087520138906151,
			0.049137179673607506,
			-0.027219029917056003,
			-0.051945838107709037,
			0.3644418948353314,
			0.77718575170052351,
			0.48135965125837221,
			-0.061273359067658524,
			-0.14329423835080971,
			0.0076074873249176054,
			0.031695087811492981,
			-0.00054213233179114812,
			-0.0033824159510061256
		};

		double hp2_a[] = { -0.0033824159510061256,
			0.00054213233179114812,
			0.031695087811492981,
			-0.0076074873249176054,
			-0.14329423835080971,
			0.061273359067658524,
			0.48135965125837221,
			-0.77718575170052351,
			0.3644418948353314,
			0.051945838107709037,
			-0.027219029917056003,
			-0.049137179673607506,
			0.0038087520138906151,
			0.014952258337048231,
			-0.0003029205147213668,
			-0.0018899503327594609
		};
		for (i = 0; i < 16; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 16;
	}

	else if (!strcmp(name,"sym9")){
		double lp1_a[] = { 0.0014009155259146807,
			0.00061978088898558676,
			-0.013271967781817119,
			-0.01152821020767923,
			0.03022487885827568,
			0.00058346274612580684,
			-0.054568958430834071,
			0.238760914607303,
			0.717897082764412,
			0.61733844914093583,
			0.035272488035271894,
			-0.19155083129728512,
			-0.018233770779395985,
			0.06207778930288603,
			0.0088592674934004842,
			-0.010264064027633142,
			-0.00047315449868008311,
			0.0010694900329086053
		};

		double hp1_a[] = { -0.0010694900329086053,
			-0.00047315449868008311,
			0.010264064027633142,
			0.0088592674934004842,
			-0.06207778930288603,
			-0.018233770779395985,
			0.19155083129728512,
			0.035272488035271894,
			-0.61733844914093583,
			0.717897082764412,
			-0.238760914607303,
			-0.054568958430834071,
			-0.00058346274612580684,
			0.03022487885827568,
			0.01152821020767923,
			-0.013271967781817119,
			-0.00061978088898558676,
			0.0014009155259146807
		};

		double lp2_a[] = { 0.0010694900329086053,
			-0.00047315449868008311,
			-0.010264064027633142,
			0.0088592674934004842,
			0.06207778930288603,
			-0.018233770779395985,
			-0.19155083129728512,
			0.035272488035271894,
			0.61733844914093583,
			0.717897082764412,
			0.238760914607303,
			-0.054568958430834071,
			0.00058346274612580684,
			0.03022487885827568,
			-0.01152821020767923,
			-0.013271967781817119,
			0.00061978088898558676,
			0.0014009155259146807
		};

		double hp2_a[] = { 0.0014009155259146807,
			-0.00061978088898558676,
			-0.013271967781817119,
			0.01152821020767923,
			0.03022487885827568,
			-0.00058346274612580684,
			-0.054568958430834071,
			-0.238760914607303,
			0.717897082764412,
			-0.61733844914093583,
			0.035272488035271894,
			0.19155083129728512,
			-0.018233770779395985,
			-0.06207778930288603,
			0.0088592674934004842,
			0.010264064027633142,
			-0.00047315449868008311,
			-0.0010694900329086053
		};
		for (i = 0; i < 18; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 18;
	}

	else if (!strcmp(name,"sym10")){
		double lp1_a[] = { 0.00077015980911449011,
			9.5632670722894754e-05,
			-0.0086412992770224222,
			-0.0014653825813050513,
			0.045927239231092203,
			0.011609893903711381,
			-0.15949427888491757,
			-0.070880535783243853,
			0.47169066693843925,
			0.7695100370211071,
			0.38382676106708546,
			-0.035536740473817552,
			-0.0319900568824278,
			0.049994972077376687,
			0.0057649120335819086,
			-0.02035493981231129,
			-0.00080435893201654491,
			0.0045931735853118284,
			5.7036083618494284e-05,
			-0.00045932942100465878
		};

		double hp1_a[] = { 0.00045932942100465878,
			5.7036083618494284e-05,
			-0.0045931735853118284,
			-0.00080435893201654491,
			0.02035493981231129,
			0.0057649120335819086,
			-0.049994972077376687,
			-0.0319900568824278,
			0.035536740473817552,
			0.38382676106708546,
			-0.7695100370211071,
			0.47169066693843925,
			0.070880535783243853,
			-0.15949427888491757,
			-0.011609893903711381,
			0.045927239231092203,
			0.0014653825813050513,
			-0.0086412992770224222,
			-9.5632670722894754e-05,
			0.00077015980911449011
		};

		double lp2_a[] = { -0.00045932942100465878,
			5.7036083618494284e-05,
			0.0045931735853118284,
			-0.00080435893201654491,
			-0.02035493981231129,
			0.0057649120335819086,
			0.049994972077376687,
			-0.0319900568824278,
			-0.035536740473817552,
			0.38382676106708546,
			0.7695100370211071,
			0.47169066693843925,
			-0.070880535783243853,
			-0.15949427888491757,
			0.011609893903711381,
			0.045927239231092203,
			-0.0014653825813050513,
			-0.0086412992770224222,
			9.5632670722894754e-05,
			0.00077015980911449011
		};

		double hp2_a[] = { 0.00077015980911449011,
			-9.5632670722894754e-05,
			-0.0086412992770224222,
			0.0014653825813050513,
			0.045927239231092203,
			-0.011609893903711381,
			-0.15949427888491757,
			0.070880535783243853,
			0.47169066693843925,
			-0.7695100370211071,
			0.38382676106708546,
			0.035536740473817552,
			-0.0319900568824278,
			-0.049994972077376687,
			0.0057649120335819086,
			0.02035493981231129,
			-0.00080435893201654491,
			-0.0045931735853118284,
			5.7036083618494284e-05,
			0.00045932942100465878
		};
		for (i = 0; i < 20; ++i) {
			lp1[i] = lp1_a[i];
			hp1[i] = hp1_a[i];
			lp2[i] = lp2_a[i];
			hp2[i] = hp2_a[i];
		}
		return 20;
	}


	else {
		printf("\n Filter Not in Database \n");
		return -1;
	}

	//return 0;
}
//---------------------------------------------------------------------------
/***************************************************************************/
/***************************   CONV   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
int cWavelib::factorf(int M) {
	int N;
	N = M;
	while (N%7 == 0){
			N = N/7;
		}
	while (N%3 == 0){
			N = N/3;
		}
	while (N%5 == 0){
			N = N/5;
		}
	while (N%2 == 0){
			N = N/2;
		}

	return N;
}


int cWavelib::findnext(int M) {
	int N;
	N = M;

	while (factorf(N) != 1) {
		++N;
	}

	return N;

}

int cWavelib::findnexte(int M) {
	int N;
	N = M;

	while (factorf(N) != 1 || N%2 != 0) {
		++N;
	}

	return N;

}


conv_object cWavelib::conv_init(int N, int L) {
	
	conv_object obj = NULL;
	int conv_len;
	conv_len = N + L - 1;
		
	obj = (conv_object) malloc (sizeof(struct conv_set));
	 
	//obj->clen = npow2(conv_len);
	//obj->clen = conv_len;
	obj->clen = findnexte(conv_len);
	obj->ilen1 = N;
	obj->ilen2 = L;
	
	obj->fobj = fft_real_init(obj->clen,1);
	obj->iobj = fft_real_init(obj->clen,-1);
	
	return obj;
	
}

void cWavelib::conv_directx(fft_type *inp1,int N, fft_type *inp2, int L,fft_type *oup){
	int M,k,n;
	
	M = N + L - 1;
	
	for (k = 0; k < M;++k) {
		oup[k] = 0.0;
		for ( n = 0; n < N; ++n) {
			if ( (k-n) >= 0 && (k-n) < L ) {
				oup[k]+= inp1[n] * inp2[k-n];
			}
		}
		
	}
		
}

void cWavelib::conv_direct(fft_type *inp1,int N, fft_type *inp2, int L,fft_type *oup) {

	int M,k,m,i;
	fft_type t1,tmin;

	M = N + L -1;
	i = 0;

	if (N >= L) {

		for (k = 0; k < L; k++) {
			oup[k] = 0.0;
			for (m = 0; m <= k;m++) {
				oup[k]+= inp1[m] * inp2[k-m];
			}
		}

		for (k = L; k < M; k++) {
			oup[k] = 0.0;
			i++;
			t1 = L + i;
			tmin = MIN(t1,N);
			for (m = i; m < tmin;m++) {
				oup[k]+= inp1[m] * inp2[k-m];
			}
		}


	} else {
		for (k = 0; k < N; k++) {
			oup[k] = 0.0;
			for (m = 0; m <= k;m++) {
				oup[k]+= inp2[m] * inp1[k-m];
			}
		}

		for (k = N; k < M; k++) {
			oup[k] = 0.0;
			i++;
			t1 = N + i;
			tmin = MIN(t1,L);
			for (m = i; m < tmin;m++) {
				oup[k]+= inp2[m] * inp1[k-m];
			}
		}

	}


}


void cWavelib::conv_fft(const conv_object obj,fft_type *inp1,fft_type *inp2,fft_type *oup) {
	int i,N,L1,L2,ls;
	fft_type* a;
	fft_type* b;
	fft_data* c;
	fft_data* ao;
	fft_data* bo;
	fft_type* co;
	
	N = obj->clen;
	L1 = obj->ilen1;
	L2 = obj->ilen2;
	ls = L1 + L2 - 1;
	
	a = (fft_type*) malloc (sizeof(fft_data) * N);
	b = (fft_type*) malloc (sizeof(fft_data) * N);
	c = (fft_data*) malloc (sizeof(fft_data) * N);
	ao = (fft_data*) malloc (sizeof(fft_data) * N);
	bo = (fft_data*) malloc (sizeof(fft_data) * N);
	co = (fft_type*) malloc (sizeof(fft_data) * N);
	
	for (i = 0; i < N;i++) {
		if (i < L1) {
			a[i] = inp1[i];
		} else {
			a[i] = 0.0;
		}
		
		if (i < L2) {
			b[i] = inp2[i];
		} else {
			b[i] = 0.0;
		}
	
	}
	
	fft_r2c_exec(obj->fobj,a,ao);
	fft_r2c_exec(obj->fobj,b,bo);
	
	for (i = 0; i < N;i++) {
		c[i].re = ao[i].re * bo[i].re - ao[i].im * bo[i].im;
		c[i].im = ao[i].im * bo[i].re + ao[i].re * bo[i].im;
	}
	
	fft_c2r_exec(obj->iobj,c,co);
	
	for (i = 0; i < ls;i++) {
		oup[i] = co[i]/N;
	}
	
	free(a);
	free(b);
	free(c);
	free(ao);
	free(bo);
	free(co);
	
	
}


void cWavelib::free_conv(conv_object object) {
	free(object);
}
//---------------------------------------------------------------------------
/***************************************************************************/
/***************************   REAL   **************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
fft_real_object cWavelib::fft_real_init(int N, int sgn) {
	fft_real_object obj = NULL;
	//original fft_type PI, theta;
	fft_type theta;
	int k;

	//PI = 3.1415926535897932384626433832795;
	
	obj = (fft_real_object) malloc (sizeof(struct fft_real_set) + sizeof(fft_data)* (N/2));
	
	obj->cobj = fft_init(N/2,sgn);
	
	for (k = 0; k < N/2;++k) {
		theta = PI2*k/N;
		obj->twiddle2[k].re = cos(theta);
		obj->twiddle2[k].im = sin(theta);
		
	}


	return obj;
	
	
}

void cWavelib::fft_r2c_exec(fft_real_object obj,fft_type *inp,fft_data *oup) {
	fft_data* cinp;
	fft_data* coup;
	int i,N2,N;
	fft_type temp1,temp2;
	N2 = obj->cobj->N;
	N = N2*2;
	
	cinp = (fft_data*) malloc (sizeof(fft_data) * N2);
	coup = (fft_data*) malloc (sizeof(fft_data) * N2);
	
	for (i = 0; i < N2; ++i) {
		cinp[i].re = inp[2*i];
		cinp[i].im = inp[2*i+1];
	}
	
	fft_exec(obj->cobj,cinp,coup);
	
	oup[0].re = coup[0].re + coup[0].im;
	oup[0].im = 0.0;
	
	for (i = 1; i < N2; ++i) {
		temp1 = coup[i].im + coup[N2-i].im ;
		temp2 = coup[N2-i].re - coup[i].re ;
		oup[i].re = (coup[i].re + coup[N2-i].re + (temp1 * obj->twiddle2[i].re) + (temp2 * obj->twiddle2[i].im)) / 2.0;
		oup[i].im = (coup[i].im - coup[N2-i].im + (temp2 * obj->twiddle2[i].re) - (temp1 * obj->twiddle2[i].im)) / 2.0;
	}
	
	
	
	oup[N2].re = coup[0].re - coup[0].im;
	oup[N2].im = 0.0;
	
	for (i = 1; i < N2;++i) {
		oup[N-i].re = oup[i].re; 
		oup[N-i].im = -oup[i].im; 
	}
	
		
	free(cinp);
	free(coup);

}

void cWavelib::fft_c2r_exec(fft_real_object obj,fft_data *inp,fft_type *oup) {
	
	fft_data* cinp;
	fft_data* coup;
	//original int i,N2,N;
	int i,N2;
	fft_type temp1,temp2;
	N2 = obj->cobj->N;
	//N = N2*2;
	
	cinp = (fft_data*) malloc (sizeof(fft_data) * N2);
	coup = (fft_data*) malloc (sizeof(fft_data) * N2);
	
	for (i = 0; i < N2; ++i) {
		temp1 = -inp[i].im - inp[N2-i].im ;
		temp2 = -inp[N2-i].re + inp[i].re ;
		cinp[i].re = inp[i].re + inp[N2-i].re + (temp1 * obj->twiddle2[i].re) - (temp2 * obj->twiddle2[i].im);
		cinp[i].im = inp[i].im - inp[N2-i].im + (temp2 * obj->twiddle2[i].re) + (temp1 * obj->twiddle2[i].im);
	}
	
	fft_exec(obj->cobj,cinp,coup);
	for (i = 0; i < N2; ++i) {
		oup[2*i] = coup[i].re;
		oup[2*i+1] = coup[i].im;
	}
	free(cinp);
	free(coup);


}

void cWavelib::free_real_fft(fft_real_object object) {
	free(object);
}
//---------------------------------------------------------------------------
/***************************************************************************/
/***************************   HSFFT   *************************************/
/***************************************************************************/
//---------------------------------------------------------------------------
fft_object cWavelib::fft_init(int N, int sgn)
	{
	fft_object obj = NULL;
	// Change N/2 to N-1 for longvector case

	int twi_len,ct,out;
	out = dividebyN(N);

	if (out == 1)
		{
		obj = (fft_object) malloc (sizeof(struct fft_set) + sizeof(fft_data)* (N-1));
		obj->lf = factors(N,obj->factors);
		longvectorN(obj->twiddle,N,obj->factors,obj->lf);
		twi_len = N;
		obj->lt = 0;
		}
	else
		{
		int K,M;
		K = (int) pow(2.0,ceil(log10(N)/log10(2.0)));

		if (K < 2 * N - 2)
			{
			M = K * 2;
			}
		else
			{
			M = K;
			}
		obj = (fft_object) malloc (sizeof(struct fft_set) + sizeof(fft_data)* (M-1));
		obj->lf = factors(M,obj->factors);
		longvectorN(obj->twiddle,M,obj->factors,obj->lf);
		obj->lt = 1;
		twi_len = M;
		}

	obj->N = N;
	obj->sgn = sgn;

	if (sgn == -1)
		{
		for(ct = 0; ct < twi_len;ct++)
			{
			(obj->twiddle+ct)->im = - (obj->twiddle+ct)->im;
			}
		}

	return obj;
	}
//---------------------------------------------------------------------------
void cWavelib::mixed_radix_dit_rec(fft_data *op,fft_data *ip,const fft_object obj, int sgn, int N,int l,int inc) {

	int radix,m,ll;
	if (N > 1) {
		radix = obj->factors[inc];
		//printf("%d \n",radix);
	}

	if (N == 1) {

		op[0].re = ip[0].re;
		op[0].im = ip[0].im;

	} else if (N == 2) {
		fft_type tau1r,tau1i;
		op[0].re = ip[0].re;
		op[0].im = ip[0].im;

		op[1].re = ip[l].re;
		op[1].im = ip[l].im;

		tau1r = op[0].re;
		tau1i = op[0].im;


		op[0].re = tau1r + op[1].re;
		op[0].im = tau1i + op[1].im;

		op[1].re = tau1r - op[1].re;
		op[1].im = tau1i - op[1].im;

	} else if (N == 3) {
		fft_type tau0r,tau0i,tau1r,tau1i,tau2r,tau2i;
		op[0].re = ip[0].re;
		op[0].im = ip[0].im;

		op[1].re = ip[l].re;
		op[1].im = ip[l].im;

		op[2].re = ip[2*l].re;
		op[2].im = ip[2*l].im;

		tau0r = op[1].re + op[2].re;
		tau0i = op[1].im + op[2].im;

		tau1r = sgn * 0.86602540378 * (op[1].re - op[2].re);
		tau1i = sgn * 0.86602540378 * (op[1].im - op[2].im);

		tau2r = op[0].re - tau0r * 0.5000000000;
		tau2i = op[0].im - tau0i * 0.5000000000;

		op[0].re = tau0r + op[0].re ;
		op[0].im = tau0i + op[0].im;

		op[1].re = tau2r + tau1i;
		op[1].im = tau2i - tau1r;

		op[2].re = tau2r - tau1i;
		op[2].im = tau2i + tau1r;

		return;


	} else if (N == 4) {
		fft_type tau0r,tau0i,tau1r,tau1i,tau2r,tau2i,tau3r,tau3i;
		op[0].re = ip[0].re;
		op[0].im = ip[0].im;

		op[1].re = ip[l].re;
		op[1].im = ip[l].im;

		op[2].re = ip[2*l].re;
		op[2].im = ip[2*l].im;

		op[3].re = ip[3*l].re;
		op[3].im = ip[3*l].im;

		tau0r = op[0].re + op[2].re;
		tau0i = op[0].im + op[2].im;

		tau1r = op[0].re - op[2].re;
		tau1i = op[0].im - op[2].im;

		tau2r = op[1].re + op[3].re;
		tau2i = op[1].im + op[3].im;

		tau3r = sgn* (op[1].re - op[3].re);
		tau3i = sgn* (op[1].im - op[3].im);

		op[0].re = tau0r + tau2r ;
		op[0].im = tau0i + tau2i;

		op[1].re = tau1r + tau3i;
		op[1].im = tau1i - tau3r;

		op[2].re = tau0r - tau2r;
		op[2].im = tau0i - tau2i;

		op[3].re = tau1r - tau3i;
		op[3].im = tau1i + tau3r;



	} else if (N == 5) {
		fft_type tau0r,tau0i,tau1r,tau1i,tau2r,tau2i,tau3r,tau3i,tau4r,tau4i,tau5r,tau5i,tau6r,tau6i;
		fft_type c1,c2,s1,s2;
		op[0].re = ip[0].re;
		op[0].im = ip[0].im;

		op[1].re = ip[l].re;
		op[1].im = ip[l].im;

		op[2].re = ip[2*l].re;
		op[2].im = ip[2*l].im;

		op[3].re = ip[3*l].re;
		op[3].im = ip[3*l].im;

		op[4].re = ip[4*l].re;
		op[4].im = ip[4*l].im;

		c1 = 0.30901699437;
		c2 = -0.80901699437;
		s1 = 0.95105651629;
		s2 = 0.58778525229;

		tau0r = op[1].re + op[4].re;
		tau2r = op[1].re - op[4].re;
		tau0i = op[1].im + op[4].im;
		tau2i = op[1].im - op[4].im;

		tau1r = op[2].re + op[3].re;
		tau3r = op[2].re - op[3].re;
		tau1i = op[2].im + op[3].im;
		tau3i = op[2].im - op[3].im;


		tau4r = c1 * tau0r + c2 * tau1r;
		tau4i = c1 * tau0i + c2 * tau1i;

		//tau5r = sgn * ( s1 * tau2r + s2 * tau3r);
		//tau5i = sgn * ( s1 * tau2i + s2 * tau3i);

		if (sgn == 1) {
			tau5r = s1 * tau2r + s2 * tau3r;
			tau5i = s1 * tau2i + s2 * tau3i;

		} else {
			tau5r = -s1 * tau2r - s2 * tau3r;
			tau5i = -s1 * tau2i - s2 * tau3i;

		}

		tau6r = op[0].re + tau4r;
		tau6i = op[0].im + tau4i;

		op[1].re = tau6r + tau5i;
		op[1].im = tau6i - tau5r;

		op[4].re = tau6r - tau5i;
		op[4].im = tau6i + tau5r;

		tau4r = c2 * tau0r + c1 * tau1r;
		tau4i = c2 * tau0i + c1 * tau1i;

		//tau5r = sgn * ( s2 * tau2r - s1 * tau3r);
		//tau5i = sgn * ( s2 * tau2i - s1 * tau3i);

		if (sgn == 1) {
			tau5r = s2 * tau2r - s1 * tau3r;
			tau5i = s2 * tau2i - s1 * tau3i;

		} else {
			tau5r = -s2 * tau2r + s1 * tau3r;
			tau5i = -s2 * tau2i + s1 * tau3i;

		}

		tau6r = op[0].re + tau4r;
		tau6i = op[0].im + tau4i;

		op[2].re = tau6r + tau5i;
		op[2].im = tau6i - tau5r;

		op[3].re = tau6r - tau5i;
		op[3].im = tau6i + tau5r;



		op[0].re += tau0r + tau1r;
		op[0].im += tau0i + tau1i;


	} else if (N == 7) {
		fft_type tau0r,tau0i,tau1r,tau1i,tau2r,tau2i,tau3r,tau3i,tau4r,tau4i,tau5r,tau5i,tau6r,tau6i,tau7r,tau7i;
		fft_type c1,c2,c3,s1,s2,s3;
		op[0].re = ip[0].re;
		op[0].im = ip[0].im;

		op[1].re = ip[l].re;
		op[1].im = ip[l].im;

		op[2].re = ip[2*l].re;
		op[2].im = ip[2*l].im;

		op[3].re = ip[3*l].re;
		op[3].im = ip[3*l].im;

		op[4].re = ip[4*l].re;
		op[4].im = ip[4*l].im;

		op[5].re = ip[5*l].re;
		op[5].im = ip[5*l].im;

		op[6].re = ip[6*l].re;
		op[6].im = ip[6*l].im;

		c1 = 0.62348980185;
		c2 = -0.22252093395;
		c3 = -0.9009688679;
		s1 = 0.78183148246;
		s2 = 0.97492791218;
		s3 = 0.43388373911;

		tau0r = op[1].re + op[6].re;
		tau3r = op[1].re - op[6].re;

		tau0i = op[1].im + op[6].im;
		tau3i = op[1].im - op[6].im;

		tau1r = op[2].re + op[5].re;
		tau4r = op[2].re - op[5].re;

		tau1i = op[2].im + op[5].im;
		tau4i = op[2].im - op[5].im;

		tau2r = op[3].re + op[4].re;
		tau5r = op[3].re - op[4].re;

		tau2i = op[3].im + op[4].im;
		tau5i = op[3].im - op[4].im;


		tau6r = op[0].re + c1 * tau0r + c2 * tau1r + c3 * tau2r;
		tau6i = op[0].im + c1 * tau0i + c2 * tau1i + c3 * tau2i;

		//tau7r = sgn * ( -s1 * tau3r - s2 * tau4r - s3 * tau5r);
		//tau7i = sgn * ( -s1 * tau3i - s2 * tau4i - s3 * tau5i);

		if (sgn == 1) {
			tau7r = -s1 * tau3r - s2 * tau4r - s3 * tau5r;
			tau7i = -s1 * tau3i - s2 * tau4i - s3 * tau5i;

		} else {
			tau7r = s1 * tau3r + s2 * tau4r + s3 * tau5r;
			tau7i = s1 * tau3i + s2 * tau4i + s3 * tau5i;

		}


		op[1].re = tau6r - tau7i;
		op[6].re = tau6r + tau7i;

		op[1].im = tau6i + tau7r;
		op[6].im = tau6i - tau7r;

		tau6r = op[0].re + c2 * tau0r + c3 * tau1r + c1 * tau2r;
		tau6i = op[0].im + c2 * tau0i + c3 * tau1i + c1 * tau2i;

		//tau7r = sgn * ( -s2 * tau3r + s3 * tau4r + s1 * tau5r);
		//tau7i = sgn * ( -s2 * tau3i + s3 * tau4i + s1 * tau5i);

		if (sgn == 1) {
			tau7r = -s2 * tau3r + s3 * tau4r + s1 * tau5r;
			tau7i = -s2 * tau3i + s3 * tau4i + s1 * tau5i;
		} else {
			tau7r = s2 * tau3r - s3 * tau4r - s1 * tau5r;
			tau7i = s2 * tau3i - s3 * tau4i - s1 * tau5i;

		}


		op[2].re = tau6r - tau7i;
		op[5].re = tau6r + tau7i;
		op[2].im = tau6i + tau7r;
		op[5].im = tau6i - tau7r;

		tau6r = op[0].re + c3 * tau0r + c1 * tau1r + c2 * tau2r;
		tau6i = op[0].im + c3 * tau0i + c1 * tau1i + c2 * tau2i;

		//tau7r = sgn * ( -s3 * tau3r + s1 * tau4r - s2 * tau5r);
		//tau7i = sgn * ( -s3 * tau3i + s1 * tau4i - s2 * tau5i);

		if (sgn == 1) {
			tau7r = -s3 * tau3r + s1 * tau4r - s2 * tau5r;
			tau7i = -s3 * tau3i + s1 * tau4i - s2 * tau5i;

		} else {
			tau7r = s3 * tau3r - s1 * tau4r + s2 * tau5r;
			tau7i = s3 * tau3i - s1 * tau4i + s2 * tau5i;

		}


		op[3].re = tau6r - tau7i;
		op[4].re = tau6r + tau7i;
		op[3].im = tau6i + tau7r;
		op[4].im = tau6i - tau7r;

		op[0].re += tau0r + tau1r + tau2r;
		op[0].im += tau0i + tau1i + tau2i;


	} else if (N == 8) {
		fft_type tau0r,tau0i,tau1r,tau1i,tau2r,tau2i,tau3r,tau3i,tau4r,tau4i,tau5r,tau5i,tau6r,tau6i,tau7r,tau7i,tau8r,tau8i,tau9r,tau9i;
		fft_type c1,s1,temp1r,temp1i,temp2r,temp2i;
		op[0].re = ip[0].re;
		op[0].im = ip[0].im;

		op[1].re = ip[l].re;
		op[1].im = ip[l].im;

		op[2].re = ip[2*l].re;
		op[2].im = ip[2*l].im;

		op[3].re = ip[3*l].re;
		op[3].im = ip[3*l].im;

		op[4].re = ip[4*l].re;
		op[4].im = ip[4*l].im;

		op[5].re = ip[5*l].re;
		op[5].im = ip[5*l].im;

		op[6].re = ip[6*l].re;
		op[6].im = ip[6*l].im;
		
		op[7].re = ip[7*l].re;
		op[7].im = ip[7*l].im;
		
		c1 = 0.70710678118654752440084436210485;
		s1 = 0.70710678118654752440084436210485;

		tau0r = op[0].re + op[4].re;
		tau4r = op[0].re - op[4].re;

		tau0i = op[0].im + op[4].im;
		tau4i = op[0].im - op[4].im;

		tau1r = op[1].re + op[7].re;
		tau5r = op[1].re - op[7].re;

		tau1i = op[1].im + op[7].im;
		tau5i = op[1].im - op[7].im;

		tau2r = op[3].re + op[5].re;
		tau6r = op[3].re - op[5].re;

		tau2i = op[3].im + op[5].im;
		tau6i = op[3].im - op[5].im;
		
		tau3r = op[2].re + op[6].re;
		tau7r = op[2].re - op[6].re;

		tau3i = op[2].im + op[6].im;
		tau7i = op[2].im - op[6].im;

		op[0].re = tau0r + tau1r + tau2r + tau3r;
		op[0].im = tau0i + tau1i + tau2i + tau3i;

		op[4].re = tau0r - tau1r - tau2r + tau3r;
		op[4].im = tau0i - tau1i - tau2i + tau3i;

		temp1r = tau1r - tau2r;
		temp1i = tau1i - tau2i;

		temp2r = tau5r + tau6r;
		temp2i = tau5i + tau6i;

		tau8r =  tau4r + c1 * temp1r;
		tau8i =  tau4i + c1 * temp1i;

		//tau9r = sgn * ( -s1 * temp2r - tau7r);
		//tau9i = sgn * ( -s1 * temp2i - tau7i);

		if (sgn == 1) {
			tau9r = -s1 * temp2r - tau7r;
			tau9i = -s1 * temp2i - tau7i;

		} else {
			tau9r = s1 * temp2r + tau7r;
			tau9i = s1 * temp2i + tau7i;

		}


		op[1].re = tau8r - tau9i;
		op[1].im = tau8i + tau9r;

		op[7].re = tau8r + tau9i;
		op[7].im = tau8i - tau9r;

		tau8r = tau0r - tau3r;
		tau8i = tau0i - tau3i;

		//tau9r = sgn * ( -tau5r + tau6r);
		//tau9i = sgn * ( -tau5i + tau6i);

		if (sgn == 1) {
			tau9r = -tau5r + tau6r;
			tau9i = -tau5i + tau6i;

		} else {
			tau9r = tau5r - tau6r;
			tau9i = tau5i - tau6i;

		}


		op[2].re = tau8r - tau9i;
		op[2].im = tau8i + tau9r;

		op[6].re = tau8r + tau9i;
		op[6].im = tau8i - tau9r;

		tau8r = tau4r - c1 * temp1r;
		tau8i = tau4i - c1 * temp1i;

		//tau9r = sgn * ( -s1 * temp2r + tau7r);
		//tau9i = sgn * ( -s1 * temp2i + tau7i);

		if (sgn == 1) {
			tau9r = -s1 * temp2r + tau7r;
			tau9i = -s1 * temp2i + tau7i;

		} else {
			tau9r = s1 * temp2r - tau7r;
			tau9i = s1 * temp2i - tau7i;

		}


		op[3].re = tau8r - tau9i;
		op[3].im = tau8i + tau9r;

		op[5].re = tau8r + tau9i;
		op[5].im = tau8i - tau9r;

		


	} else if (radix == 2) {
		int k,tkm1,ind;
		fft_type wlr,wli;
		fft_type tau1r,tau1i,tau2r,tau2i;
		m = N/2;
		ll = 2*l;
		mixed_radix_dit_rec(op,ip,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+m,ip+l,obj,sgn,m,ll,inc+1);

		for (k = 0; k < m;k++) {
			ind = m-1+k;
			wlr = (obj->twiddle+ind)->re;
			wli = (obj->twiddle+ind)->im;

			tkm1 = k+m;

			tau1r = op[k].re;
			tau1i = op[k].im;

			tau2r = op[tkm1].re * wlr - op[tkm1].im * wli;
			tau2i = op[tkm1].im * wlr + op[tkm1].re * wli;

			op[k].re = tau1r + tau2r;
			op[k].im = tau1i + tau2i;

			op[tkm1].re = tau1r - tau2r;
			op[tkm1].im = tau1i - tau2i;



		}

	} else if (radix == 3) {
		int k,tkm1,tkm2,ind;
		fft_type wlr,wli,wl2r,wl2i;
		fft_type tau0r,tau0i,tau1r,tau1i,tau2r,tau2i;
		fft_type ar,ai,br,bi,cr,ci;
		m = N/3;
		ll = 3*l;
		mixed_radix_dit_rec(op,ip,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+m,ip+l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+2*m,ip+2*l,obj,sgn,m,ll,inc+1);
		//printf("%d \n",inc);
		//mixed_radix3_dit_rec(op,ip,obj,sgn,ll,m);


		for (k = 0; k < m; ++k) {
			ind = m-1+2*k;
			wlr = (obj->twiddle+ind)->re;
			wli = (obj->twiddle+ind)->im;
			ind++;
			wl2r = (obj->twiddle+ind)->re;
			wl2i = (obj->twiddle+ind)->im;
			tkm1 = k + m;
			tkm2 = tkm1 + m;

			ar = op[k].re;
			ai = op[k].im;

			br = op[tkm1].re * wlr - op[tkm1].im * wli;
			bi = op[tkm1].im * wlr + op[tkm1].re * wli;

			cr = op[tkm2].re * wl2r - op[tkm2].im * wl2i;
			ci = op[tkm2].im * wl2r + op[tkm2].re * wl2i;

			tau0r = br + cr;
			tau0i = bi + ci;

			tau1r = sgn * 0.86602540378 * (br - cr);
			tau1i = sgn * 0.86602540378 * (bi - ci);

			tau2r = ar - tau0r * 0.5000000000;
			tau2i = ai - tau0i * 0.5000000000;


			op[k].re = ar + tau0r;
			op[k].im = ai + tau0i;

			op[tkm1].re = tau2r + tau1i;
			op[tkm1].im = tau2i - tau1r;

			op[tkm2].re = tau2r - tau1i;
			op[tkm2].im = tau2i + tau1r;

		}

	} else if (radix == 4) {
		int k,tkm1,tkm2,tkm3,ind;
		fft_type wlr,wli,wl2r,wl2i,wl3r,wl3i;
		fft_type tau0r,tau0i,tau1r,tau1i,tau2r,tau2i,tau3r,tau3i;
		fft_type ar,ai,br,bi,cr,ci,dr,di;
		m = N/4;
		ll = 4*l;
		mixed_radix_dit_rec(op,ip,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+m,ip+l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+2*m,ip+2*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+3*m,ip+3*l,obj,sgn,m,ll,inc+1);

		//mixed_radix4_dit_rec(op,ip,obj,sgn,ll,m);

		tkm1 = m;
		tkm2 = tkm1 + m;
		tkm3 = tkm2 + m;

		ar = op[0].re;
		ai = op[0].im;

		br = op[tkm1].re;
		bi = op[tkm1].im;

		cr = op[tkm2].re;
		ci = op[tkm2].im;

		dr = op[tkm3].re;
		di = op[tkm3].im;

		tau0r = ar + cr;
		tau0i = ai + ci;

		tau1r = ar - cr;
		tau1i = ai - ci;

		tau2r = br + dr;
		tau2i = bi + di;

		tau3r = sgn* (br - dr);
		tau3i = sgn* (bi - di);

		op[0].re = tau0r + tau2r ;
		op[0].im = tau0i + tau2i;

		op[tkm1].re = tau1r + tau3i;
		op[tkm1].im = tau1i - tau3r;

		op[tkm2].re = tau0r - tau2r;
		op[tkm2].im = tau0i - tau2i;

		op[tkm3].re = tau1r - tau3i;
		op[tkm3].im = tau1i + tau3r;


		for (k = 1; k < m; k++) {
			ind = m-1+3*k;
			wlr = (obj->twiddle+ind)->re;
			wli = (obj->twiddle+ind)->im;
			ind++;
			wl2r = (obj->twiddle+ind)->re;
			wl2i = (obj->twiddle+ind)->im;
			ind++;
			wl3r = (obj->twiddle+ind)->re;
			wl3i = (obj->twiddle+ind)->im;

			tkm1 = k+m;
			tkm2 = tkm1 + m;
			tkm3 = tkm2 + m;

			ar = op[k].re;
			ai = op[k].im;

			br = op[tkm1].re * wlr - op[tkm1].im * wli;
			bi = op[tkm1].im * wlr + op[tkm1].re * wli;

			cr = op[tkm2].re * wl2r - op[tkm2].im * wl2i;
			ci = op[tkm2].im * wl2r + op[tkm2].re * wl2i;

			dr = op[tkm3].re * wl3r - op[tkm3].im * wl3i;
			di = op[tkm3].im * wl3r + op[tkm3].re * wl3i;

			tau0r = ar + cr;
			tau0i = ai + ci;

			tau1r = ar - cr;
			tau1i = ai - ci;

			tau2r = br + dr;
			tau2i = bi + di;

			tau3r = sgn* (br - dr);
			tau3i = sgn* (bi - di);

			op[k].re = tau0r + tau2r ;
			op[k].im = tau0i + tau2i;

			op[tkm1].re = tau1r + tau3i;
			op[tkm1].im = tau1i - tau3r;

			op[tkm2].re = tau0r - tau2r;
			op[tkm2].im = tau0i - tau2i;

			op[tkm3].re = tau1r - tau3i;
			op[tkm3].im = tau1i + tau3r;

		}

	} else if (radix == 5) {
		int k,tkm1,tkm2,tkm3,tkm4,ind;
		fft_type wlr,wli,wl2r,wl2i,wl3r,wl3i,wl4r,wl4i;
		fft_type tau0r,tau0i,tau1r,tau1i,tau2r,tau2i,tau3r,tau3i;
		fft_type ar,ai,br,bi,cr,ci,dr,di,er,ei;
		fft_type tau4r,tau4i,tau5r,tau5i,tau6r,tau6i;
		fft_type c1,c2,s1,s2;
		m = N/5;
		ll = 5*l;
		mixed_radix_dit_rec(op,ip,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+m,ip+l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+2*m,ip+2*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+3*m,ip+3*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+4*m,ip+4*l,obj,sgn,m,ll,inc+1);
		//printf("%d \n",inc);
		//mixed_radix3_dit_rec(op,ip,obj,sgn,ll,m);

		c1 = 0.30901699437;
		c2 = -0.80901699437;
		s1 = 0.95105651629;
		s2 = 0.58778525229;

		tkm1 = m;
		tkm2 = tkm1 + m;
		tkm3 = tkm2 + m;
		tkm4 = tkm3 + m;

		ar = op[0].re;
		ai = op[0].im;

		br = op[tkm1].re;
		bi = op[tkm1].im;

		cr = op[tkm2].re;
		ci = op[tkm2].im;

		dr = op[tkm3].re;
		di = op[tkm3].im;

		er = op[tkm4].re;
		ei = op[tkm4].im;

		tau0r = br + er;
		tau0i = bi + ei;

		tau1r = cr + dr;
		tau1i = ci + di;

		tau2r = br - er;
		tau2i = bi - ei;

		tau3r = cr - dr;
		tau3i = ci - di;

		op[0].re = ar + tau0r + tau1r;
		op[0].im = ai + tau0i + tau1i;

		tau4r = c1 * tau0r + c2 * tau1r;
		tau4i = c1 * tau0i + c2 * tau1i;

		tau5r = sgn * ( s1 * tau2r + s2 * tau3r);
		tau5i = sgn * ( s1 * tau2i + s2 * tau3i);

		tau6r = ar + tau4r;
		tau6i = ai + tau4i;

		op[tkm1].re = tau6r + tau5i;
		op[tkm1].im = tau6i - tau5r;

		op[tkm4].re = tau6r - tau5i;
		op[tkm4].im = tau6i + tau5r;

		tau4r = c2 * tau0r + c1 * tau1r;
		tau4i = c2 * tau0i + c1 * tau1i;

		tau5r = sgn * ( s2 * tau2r - s1 * tau3r);
		tau5i = sgn * ( s2 * tau2i - s1 * tau3i);

		tau6r = ar + tau4r;
		tau6i = ai + tau4i;

		op[tkm2].re = tau6r + tau5i;
		op[tkm2].im = tau6i - tau5r;

		op[tkm3].re = tau6r - tau5i;
		op[tkm3].im = tau6i + tau5r;

		for (k = 1; k < m; k++) {
			ind = m-1+4*k;
			wlr = (obj->twiddle+ind)->re;
			wli = (obj->twiddle+ind)->im;
			ind++;
			wl2r = (obj->twiddle+ind)->re;
			wl2i = (obj->twiddle+ind)->im;
			ind++;
			wl3r = (obj->twiddle+ind)->re;
			wl3i = (obj->twiddle+ind)->im;
			ind++;
			wl4r = (obj->twiddle+ind)->re;
			wl4i = (obj->twiddle+ind)->im;

			tkm1 = k + m;
			tkm2 = tkm1 + m;
			tkm3 = tkm2 + m;
			tkm4 = tkm3 + m;

			ar = op[k].re;
			ai = op[k].im;

			br = op[tkm1].re * wlr - op[tkm1].im * wli;
			bi = op[tkm1].im * wlr + op[tkm1].re * wli;

			cr = op[tkm2].re * wl2r - op[tkm2].im * wl2i;
			ci = op[tkm2].im * wl2r + op[tkm2].re * wl2i;

			dr = op[tkm3].re * wl3r - op[tkm3].im * wl3i;
			di = op[tkm3].im * wl3r + op[tkm3].re * wl3i;

			er = op[tkm4].re * wl4r - op[tkm4].im * wl4i;
			ei = op[tkm4].im * wl4r + op[tkm4].re * wl4i;

			tau0r = br + er;
			tau0i = bi + ei;

			tau1r = cr + dr;
			tau1i = ci + di;

			tau2r = br - er;
			tau2i = bi - ei;

			tau3r = cr - dr;
			tau3i = ci - di;

			op[k].re = ar + tau0r + tau1r;
			op[k].im = ai + tau0i + tau1i;

			tau4r = c1 * tau0r + c2 * tau1r;
			tau4i = c1 * tau0i + c2 * tau1i;

			//tau5r = sgn * ( s1 * tau2r + s2 * tau3r);
			//tau5i = sgn * ( s1 * tau2i + s2 * tau3i);

			if (sgn == 1) {
				tau5r = s1 * tau2r + s2 * tau3r;
				tau5i = s1 * tau2i + s2 * tau3i;

			} else {
				tau5r = -s1 * tau2r - s2 * tau3r;
				tau5i = -s1 * tau2i - s2 * tau3i;

			}

			tau6r = ar + tau4r;
			tau6i = ai + tau4i;

			op[tkm1].re = tau6r + tau5i;
			op[tkm1].im = tau6i - tau5r;

			op[tkm4].re = tau6r - tau5i;
			op[tkm4].im = tau6i + tau5r;

			tau4r = c2 * tau0r + c1 * tau1r;
			tau4i = c2 * tau0i + c1 * tau1i;

			//tau5r = sgn * ( s2 * tau2r - s1 * tau3r);
			//tau5i = sgn * ( s2 * tau2i - s1 * tau3i);

			if (sgn == 1) {
				tau5r = s2 * tau2r - s1 * tau3r;
				tau5i = s2 * tau2i - s1 * tau3i;

			} else {
				tau5r = -s2 * tau2r + s1 * tau3r;
				tau5i = -s2 * tau2i + s1 * tau3i;

			}

			tau6r = ar + tau4r;
		    tau6i = ai + tau4i;

			op[tkm2].re = tau6r + tau5i;
			op[tkm2].im = tau6i - tau5r;

			op[tkm3].re = tau6r - tau5i;
			op[tkm3].im = tau6i + tau5r;

		}

	} else if (radix == 7) {
		int k,tkm1,tkm2,tkm3,tkm4,tkm5,tkm6,ind;
		fft_type wlr,wli,wl2r,wl2i,wl3r,wl3i,wl4r,wl4i,wl5r,wl5i,wl6r,wl6i;
		fft_type tau0r,tau0i,tau1r,tau1i,tau2r,tau2i,tau3r,tau3i;
		fft_type ar,ai,br,bi,cr,ci,dr,di,er,ei,fr,fi,gr,gi;
		fft_type tau4r,tau4i,tau5r,tau5i,tau6r,tau6i,tau7r,tau7i;
		fft_type c1,c2,c3,s1,s2,s3;
		m = N/7;
		ll = 7*l;
		mixed_radix_dit_rec(op,ip,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+m,ip+l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+2*m,ip+2*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+3*m,ip+3*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+4*m,ip+4*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+5*m,ip+5*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+6*m,ip+6*l,obj,sgn,m,ll,inc+1);
		//printf("%d \n",inc);
		//mixed_radix3_dit_rec(op,ip,obj,sgn,ll,m);

		c1 = 0.62348980185;
		c2 = -0.22252093395;
		c3 = -0.9009688679;
		s1 = 0.78183148246;
		s2 = 0.97492791218;
		s3 = 0.43388373911;

		tkm1 = m;
		tkm2 = tkm1 + m;
		tkm3 = tkm2 + m;
		tkm4 = tkm3 + m;
		tkm5 = tkm4 + m;
		tkm6 = tkm5 + m;

		ar = op[0].re;
		ai = op[0].im;

		br = op[tkm1].re;
		bi = op[tkm1].im;

		cr = op[tkm2].re;
		ci = op[tkm2].im;

		dr = op[tkm3].re;
		di = op[tkm3].im;

		er = op[tkm4].re;
		ei = op[tkm4].im;

		fr = op[tkm5].re;
		fi = op[tkm5].im;

		gr = op[tkm6].re;
		gi = op[tkm6].im;

		tau0r = br + gr;
		tau3r = br - gr;
		tau0i = bi + gi;
		tau3i = bi - gi;

		tau1r = cr + fr;
		tau4r = cr - fr;
		tau1i = ci + fi;
		tau4i = ci - fi;

		tau2r = dr + er;
		tau5r = dr - er;
		tau2i = di + ei;
		tau5i = di - ei;

		op[0].re = ar + tau0r + tau1r + tau2r;
		op[0].im = ai + tau0i + tau1i + tau2i;

		tau6r = ar + c1 * tau0r + c2 * tau1r + c3 * tau2r;
		tau6i = ai + c1 * tau0i + c2 * tau1i + c3 * tau2i;

		//tau7r = sgn * ( -s1 * tau3r - s2 * tau4r - s3 * tau5r);
		//tau7i = sgn * ( -s1 * tau3i - s2 * tau4i - s3 * tau5i);

		if (sgn == 1) {
			tau7r = -s1 * tau3r - s2 * tau4r - s3 * tau5r;
			tau7i = -s1 * tau3i - s2 * tau4i - s3 * tau5i;

		} else {
			tau7r = s1 * tau3r + s2 * tau4r + s3 * tau5r;
			tau7i = s1 * tau3i + s2 * tau4i + s3 * tau5i;

		}


		op[tkm1].re = tau6r - tau7i;
		op[tkm1].im = tau6i + tau7r;

		op[tkm6].re = tau6r + tau7i;
		op[tkm6].im = tau6i - tau7r;

		tau6r = ar + c2 * tau0r + c3 * tau1r + c1 * tau2r;
		tau6i = ai + c2 * tau0i + c3 * tau1i + c1 * tau2i;

		//tau7r = sgn * ( -s2 * tau3r + s3 * tau4r + s1 * tau5r);
		//tau7i = sgn * ( -s2 * tau3i + s3 * tau4i + s1 * tau5i);

		if (sgn == 1) {
			tau7r = -s2 * tau3r + s3 * tau4r + s1 * tau5r;
			tau7i = -s2 * tau3i + s3 * tau4i + s1 * tau5i;

		} else {
			tau7r = s2 * tau3r - s3 * tau4r - s1 * tau5r;
			tau7i = s2 * tau3i - s3 * tau4i - s1 * tau5i;

		}


		op[tkm2].re = tau6r - tau7i;
		op[tkm2].im = tau6i + tau7r;

		op[tkm5].re = tau6r + tau7i;
		op[tkm5].im = tau6i - tau7r;

		tau6r = ar + c3 * tau0r + c1 * tau1r + c2 * tau2r;
		tau6i = ai + c3 * tau0i + c1 * tau1i + c2 * tau2i;

		//tau7r = sgn * ( -s3 * tau3r + s1 * tau4r - s2 * tau5r);
		//tau7i = sgn * ( -s3 * tau3i + s1 * tau4i - s2 * tau5i);

		if (sgn == 1) {
			tau7r = -s3 * tau3r + s1 * tau4r - s2 * tau5r;
			tau7i = -s3 * tau3i + s1 * tau4i - s2 * tau5i;

		} else {
			tau7r = s3 * tau3r - s1 * tau4r + s2 * tau5r;
			tau7i = s3 * tau3i - s1 * tau4i + s2 * tau5i;

		}


		op[tkm3].re = tau6r - tau7i;
		op[tkm3].im = tau6i + tau7r;

		op[tkm4].re = tau6r + tau7i;
		op[tkm4].im = tau6i - tau7r;


		for (k = 1; k < m; k++) {
			ind = m-1+6*k;
			wlr = (obj->twiddle+ind)->re;
			wli = (obj->twiddle+ind)->im;
			ind++;
			wl2r = (obj->twiddle+ind)->re;
			wl2i = (obj->twiddle+ind)->im;
			ind++;
			wl3r = (obj->twiddle+ind)->re;
			wl3i = (obj->twiddle+ind)->im;
			ind++;
			wl4r = (obj->twiddle+ind)->re;
			wl4i = (obj->twiddle+ind)->im;
			ind++;
			wl5r = (obj->twiddle+ind)->re;
			wl5i = (obj->twiddle+ind)->im;
			ind++;
			wl6r = (obj->twiddle+ind)->re;
			wl6i = (obj->twiddle+ind)->im;

			tkm1 = k + m;
			tkm2 = tkm1 + m;
			tkm3 = tkm2 + m;
			tkm4 = tkm3 + m;
			tkm5 = tkm4 + m;
			tkm6 = tkm5 + m;

			ar = op[k].re;
			ai = op[k].im;

			br = op[tkm1].re * wlr - op[tkm1].im * wli;
			bi = op[tkm1].im * wlr + op[tkm1].re * wli;

			cr = op[tkm2].re * wl2r - op[tkm2].im * wl2i;
			ci = op[tkm2].im * wl2r + op[tkm2].re * wl2i;

			dr = op[tkm3].re * wl3r - op[tkm3].im * wl3i;
			di = op[tkm3].im * wl3r + op[tkm3].re * wl3i;

			er = op[tkm4].re * wl4r - op[tkm4].im * wl4i;
			ei = op[tkm4].im * wl4r + op[tkm4].re * wl4i;

			fr = op[tkm5].re * wl5r - op[tkm5].im * wl5i;
			fi = op[tkm5].im * wl5r + op[tkm5].re * wl5i;

			gr = op[tkm6].re * wl6r - op[tkm6].im * wl6i;
			gi = op[tkm6].im * wl6r + op[tkm6].re * wl6i;

			tau0r = br + gr;
			tau3r = br - gr;
			tau0i = bi + gi;
			tau3i = bi - gi;

			tau1r = cr + fr;
			tau4r = cr - fr;
			tau1i = ci + fi;
			tau4i = ci - fi;

			tau2r = dr + er;
			tau5r = dr - er;
			tau2i = di + ei;
			tau5i = di - ei;

			op[k].re = ar + tau0r + tau1r + tau2r;
			op[k].im = ai + tau0i + tau1i + tau2i;

			tau6r = ar + c1 * tau0r + c2 * tau1r + c3 * tau2r;
			tau6i = ai + c1 * tau0i + c2 * tau1i + c3 * tau2i;

			//tau7r = sgn * ( -s1 * tau3r - s2 * tau4r - s3 * tau5r);
			//tau7i = sgn * ( -s1 * tau3i - s2 * tau4i - s3 * tau5i);

			if (sgn == 1) {
				tau7r = -s1 * tau3r - s2 * tau4r - s3 * tau5r;
				tau7i = -s1 * tau3i - s2 * tau4i - s3 * tau5i;

			} else {
				tau7r = s1 * tau3r + s2 * tau4r + s3 * tau5r;
				tau7i = s1 * tau3i + s2 * tau4i + s3 * tau5i;

			}


			op[tkm1].re = tau6r - tau7i;
			op[tkm1].im = tau6i + tau7r;

			op[tkm6].re = tau6r + tau7i;
			op[tkm6].im = tau6i - tau7r;

			tau6r = ar + c2 * tau0r + c3 * tau1r + c1 * tau2r;
			tau6i = ai + c2 * tau0i + c3 * tau1i + c1 * tau2i;

			//tau7r = sgn * ( -s2 * tau3r + s3 * tau4r + s1 * tau5r);
			//tau7i = sgn * ( -s2 * tau3i + s3 * tau4i + s1 * tau5i);

			if (sgn == 1) {
				tau7r = -s2 * tau3r + s3 * tau4r + s1 * tau5r;
				tau7i = -s2 * tau3i + s3 * tau4i + s1 * tau5i;

			} else {
				tau7r = s2 * tau3r - s3 * tau4r - s1 * tau5r;
				tau7i = s2 * tau3i - s3 * tau4i - s1 * tau5i;

			}


			op[tkm2].re = tau6r - tau7i;
			op[tkm2].im = tau6i + tau7r;

			op[tkm5].re = tau6r + tau7i;
			op[tkm5].im = tau6i - tau7r;

			tau6r = ar + c3 * tau0r + c1 * tau1r + c2 * tau2r;
			tau6i = ai + c3 * tau0i + c1 * tau1i + c2 * tau2i;

			//tau7r = sgn * ( -s3 * tau3r + s1 * tau4r - s2 * tau5r);
			//tau7i = sgn * ( -s3 * tau3i + s1 * tau4i - s2 * tau5i);

			if (sgn == 1) {
				tau7r = -s3 * tau3r + s1 * tau4r - s2 * tau5r;
				tau7i = -s3 * tau3i + s1 * tau4i - s2 * tau5i;

			} else {
				tau7r = s3 * tau3r - s1 * tau4r + s2 * tau5r;
				tau7i = s3 * tau3i - s1 * tau4i + s2 * tau5i;

			}


			op[tkm3].re = tau6r - tau7i;
			op[tkm3].im = tau6i + tau7r;

			op[tkm4].re = tau6r + tau7i;
			op[tkm4].im = tau6i - tau7r;

		}

	} else if (radix == 8) {
		int k,tkm1,tkm2,tkm3,tkm4,tkm5,tkm6,tkm7,ind;
		fft_type wlr,wli,wl2r,wl2i,wl3r,wl3i,wl4r,wl4i,wl5r,wl5i,wl6r,wl6i,wl7r,wl7i;
		fft_type tau0r,tau0i,tau1r,tau1i,tau2r,tau2i,tau3r,tau3i;
		fft_type ar,ai,br,bi,cr,ci,dr,di,er,ei,fr,fi,gr,gi,hr,hi;
		fft_type tau4r,tau4i,tau5r,tau5i,tau6r,tau6i,tau7r,tau7i,tau8r,tau8i,tau9r,tau9i;
		fft_type c1,s1,temp1r,temp1i,temp2r,temp2i;
		m = N/8;
		ll = 8*l;
		mixed_radix_dit_rec(op,ip,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+m,ip+l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+2*m,ip+2*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+3*m,ip+3*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+4*m,ip+4*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+5*m,ip+5*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+6*m,ip+6*l,obj,sgn,m,ll,inc+1);
		mixed_radix_dit_rec(op+7*m,ip+7*l,obj,sgn,m,ll,inc+1);
		//printf("%d \n",inc);
		//mixed_radix3_dit_rec(op,ip,obj,sgn,ll,m);

		c1 = 0.70710678118654752440084436210485;
		s1 = 0.70710678118654752440084436210485;


		for (k = 0; k < m; k++) {
			ind = m-1+7*k;
			wlr = (obj->twiddle+ind)->re;
			wli = (obj->twiddle+ind)->im;
			ind++;
			wl2r = (obj->twiddle+ind)->re;
			wl2i = (obj->twiddle+ind)->im;
			ind++;
			wl3r = (obj->twiddle+ind)->re;
			wl3i = (obj->twiddle+ind)->im;
			ind++;
			wl4r = (obj->twiddle+ind)->re;
			wl4i = (obj->twiddle+ind)->im;
			ind++;
			wl5r = (obj->twiddle+ind)->re;
			wl5i = (obj->twiddle+ind)->im;
			ind++;
			wl6r = (obj->twiddle+ind)->re;
			wl6i = (obj->twiddle+ind)->im;
			ind++;
			wl7r = (obj->twiddle+ind)->re;
			wl7i = (obj->twiddle+ind)->im;

			tkm1 = k + m;
			tkm2 = tkm1 + m;
			tkm3 = tkm2 + m;
			tkm4 = tkm3 + m;
			tkm5 = tkm4 + m;
			tkm6 = tkm5 + m;
			tkm7 = tkm6 + m;

			ar = op[k].re;
			ai = op[k].im;

			br = op[tkm1].re * wlr - op[tkm1].im * wli;
			bi = op[tkm1].im * wlr + op[tkm1].re * wli;

			cr = op[tkm2].re * wl2r - op[tkm2].im * wl2i;
			ci = op[tkm2].im * wl2r + op[tkm2].re * wl2i;

			dr = op[tkm3].re * wl3r - op[tkm3].im * wl3i;
			di = op[tkm3].im * wl3r + op[tkm3].re * wl3i;

			er = op[tkm4].re * wl4r - op[tkm4].im * wl4i;
			ei = op[tkm4].im * wl4r + op[tkm4].re * wl4i;

			fr = op[tkm5].re * wl5r - op[tkm5].im * wl5i;
			fi = op[tkm5].im * wl5r + op[tkm5].re * wl5i;

			gr = op[tkm6].re * wl6r - op[tkm6].im * wl6i;
			gi = op[tkm6].im * wl6r + op[tkm6].re * wl6i;

			hr = op[tkm7].re * wl7r - op[tkm7].im * wl7i;
			hi = op[tkm7].im * wl7r + op[tkm7].re * wl7i;

			tau0r = ar + er;
			tau4r = ar - er;
			tau0i = ai + ei;
			tau4i = ai - ei;

			tau1r = br + hr;
			tau5r = br - hr;
			tau1i = bi + hi;
			tau5i = bi - hi;

			tau2r = dr + fr;
			tau6r = dr - fr;
			tau6i = di - fi;
			tau2i = di + fi;

			tau3r = cr + gr;
			tau7r = cr - gr;
			tau7i = ci - gi;
			tau3i = ci + gi;

			op[k].re = tau0r + tau1r + tau2r + tau3r;
			op[k].im = tau0i + tau1i + tau2i + tau3i;

			op[tkm4].re = tau0r - tau1r - tau2r + tau3r;
			op[tkm4].im = tau0i - tau1i - tau2i + tau3i;

			temp1r = tau1r - tau2r;
			temp1i = tau1i - tau2i;

			temp2r = tau5r + tau6r;
			temp2i = tau5i + tau6i;

			tau8r =  tau4r + c1 * temp1r;
			tau8i =  tau4i + c1 * temp1i;

			//tau9r = sgn * ( -s1 * temp2r - tau7r);
			//tau9i = sgn * ( -s1 * temp2i - tau7i);

			if (sgn == 1) {
				tau9r = -s1 * temp2r - tau7r;
				tau9i = -s1 * temp2i - tau7i;

			} else {
				tau9r = s1 * temp2r + tau7r;
				tau9i = s1 * temp2i + tau7i;

			}


			op[tkm1].re = tau8r - tau9i;
			op[tkm1].im = tau8i + tau9r;

			op[tkm7].re = tau8r + tau9i;
			op[tkm7].im = tau8i - tau9r;

			tau8r = tau0r - tau3r;
			tau8i = tau0i - tau3i;

			//tau9r = sgn * ( -tau5r + tau6r);
			//tau9i = sgn * ( -tau5i + tau6i);

			if (sgn == 1) {
				tau9r = -tau5r + tau6r;
				tau9i = -tau5i + tau6i;

			} else {
				tau9r = tau5r - tau6r;
				tau9i = tau5i - tau6i;

			}


			op[tkm2].re = tau8r - tau9i;
			op[tkm2].im = tau8i + tau9r;

			op[tkm6].re = tau8r + tau9i;
			op[tkm6].im = tau8i - tau9r;

			tau8r = tau4r - c1 * temp1r;
			tau8i = tau4i - c1 * temp1i;

			//tau9r = sgn * ( -s1 * temp2r + tau7r);
			//tau9i = sgn * ( -s1 * temp2i + tau7i);

			if (sgn == 1) {
				tau9r = -s1 * temp2r + tau7r;
				tau9i = -s1 * temp2i + tau7i;

			} else {
				tau9r = s1 * temp2r - tau7r;
				tau9i = s1 * temp2i - tau7i;

			}


			op[tkm3].re = tau8r - tau9i;
			op[tkm3].im = tau8i + tau9r;

			op[tkm5].re = tau8r + tau9i;
			op[tkm5].im = tau8i - tau9r;

		}

	} else {
		int k,i,ind;
		int M,tkm,u,v,t,tt;
		fft_type temp1r,temp1i,temp2r,temp2i;
		fft_type* wlr = (fft_type*) malloc (sizeof(fft_type) * (radix-1));
		fft_type* wli = (fft_type*) malloc (sizeof(fft_type) * (radix-1));
		fft_type* taur = (fft_type*) malloc (sizeof(fft_type) * (radix-1));
		fft_type* taui = (fft_type*) malloc (sizeof(fft_type) * (radix-1));
		fft_type* c1 = (fft_type*) malloc (sizeof(fft_type) * (radix-1));
		fft_type* s1 = (fft_type*) malloc (sizeof(fft_type) * (radix-1));
		fft_type* yr = (fft_type*) malloc (sizeof(fft_type) * (radix));
		fft_type* yi = (fft_type*) malloc (sizeof(fft_type) * (radix));
		
		m = N /radix;
		ll = radix * l;

		for (i = 0; i < radix;++i) {
			mixed_radix_dit_rec(op+i*m,ip+i*l,obj,sgn,m,ll,inc+1);
		}

		M = (radix - 1 )/2;

		for (i = 1; i < M+1;++i) {
			c1[i-1] = cos(i*PI2/radix);
			s1[i-1] = sin(i*PI2/radix);
		}

		for (i = 0; i < M;++i) {
			s1[i+M] = -s1[M-1-i];
			c1[i+M] =  c1[M-1-i];
		}

		for (k = 0; k < m;++k) {
			ind = m-1+(radix-1)*k;
			yr[0] = op[k].re;
			yi[0] = op[k].im;
			for(i =0; i < radix -1;++i) {
				wlr[i] = (obj->twiddle+ind)->re;
				wli[i] = (obj->twiddle+ind)->im;
				tkm = k + (i+1)*m;
				yr[i+1] = op[tkm].re * wlr[i] - op[tkm].im * wli[i];
				yi[i+1] = op[tkm].im * wlr[i] + op[tkm].re * wli[i];
				ind++;
			}

			for (i = 0; i < M; ++i) {
				taur[i] = yr[i+1] + yr[radix-1-i];
				taui[i+M] = yi[i+1] - yi[radix-1-i];
				taui[i] = yi[i+1] + yi[radix-1-i];
				taur[i+M] = yr[i+1] - yr[radix-1-i];
			}

			temp1r = yr[0];
			temp1i = yi[0];

			for (i = 0; i < M; ++i) {
				temp1r+= taur[i];
				temp1i+= taui[i];
			}

			op[k].re = temp1r;
			op[k].im = temp1i;

			for (u = 0; u < M; u++) {
				temp1r = yr[0];
				temp1i = yi[0];
				temp2r = 0.0;
				temp2i = 0.0;
				for (v = 0; v < M; v++) {
					//int ind2 = (u+v)%M;
					t = (u+1)*(v+1);
					while(t >= radix)
						t-=radix;
					tt = t-1;

					temp1r+= c1[tt]*taur[v];
					temp1i+= c1[tt]*taui[v];
					temp2r-= s1[tt]*taur[v+M];
					temp2i-= s1[tt]*taui[v+M];
				}
				temp2r = sgn * temp2r;
				temp2i = sgn * temp2i;


				op[k + (u+1)*m].re = temp1r - temp2i;
				op[k + (u+1)*m].im = temp1i + temp2r;

				op[k + (radix-u-1)*m].re = temp1r + temp2i;
				op[k + (radix-u-1)*m].im = temp1i - temp2r;
			}


		}
		free(wlr);
		free(wli);
		free(taur);
		free(taui);
		free(c1);
		free(s1);
		free(yr);
		free(yi);

	}


}

void cWavelib::bluestein_exp(fft_data *hl, fft_data *hlt, int len, int M) {
	fft_type PI,theta,angle;
	int l2,len2,i;
	PI = 3.1415926535897932384626433832795;
	theta = PI / len;
	l2 = 0;
	len2 = 2 * len;

	for (i = 0 ; i < len; ++i) {
		angle = theta * l2;
		hlt[i].re = cos(angle);
		hlt[i].im = sin(angle);
		hl[i].re = hlt[i].re;
		hl[i].im = hlt[i].im;
		l2+=2*i+1;
		while (l2 > len2) {
			l2-=len2;
		}

	}

	for (i = len; i < M-len+1; i++) {
		hl[i].re = 0.0;
		hl[i].im = 0.0;
	}

	for (i = M - len + 1; i < M; i++) {
		hl[i].re = hlt[M-i].re;
		hl[i].im = hlt[M-i].im;
	}

}

void cWavelib::bluestein_fft(fft_data *data, fft_data *oup,fft_object obj,int sgn, int N) {

	int K,M,ii,i;
	int def_lt,def_N,def_sgn;
	fft_type scale,temp;
	fft_data* yn;
	fft_data* hk;
	fft_data* tempop;
	fft_data* yno;
	fft_data* hlt;
	obj->lt = 0;
	K = (int) pow(2.0,ceil((double) log10((double) N)/log10((double) 2.0)));
	def_lt = 1;
	def_sgn = obj->sgn;
	def_N = obj->N;

	if (K < 2 * N - 2) {
		M = K * 2;
	} else {
		M = K;
	}
	obj->N = M;

	yn = (fft_data*) malloc (sizeof(fft_data) * M);
	hk = (fft_data*) malloc (sizeof(fft_data) * M);
	tempop = (fft_data*) malloc (sizeof(fft_data) * M);
	yno = (fft_data*) malloc (sizeof(fft_data) * M);
    hlt = (fft_data*) malloc (sizeof(fft_data) * N);
    //fft_data* twi = (fft_data*) malloc (sizeof(fft_data) * M);

    bluestein_exp(tempop,hlt,N,M);
    scale = 1.0/M;

    for (ii = 0; ii < M; ++ii) {
		tempop[ii].im *= scale;
		tempop[ii].re *= scale;
	}

	//fft_object obj = initialize_fft2(M,1);
	fft_exec(obj,tempop,hk);

    if (sgn == 1) {
		for (i = 0; i < N; i++) {
			tempop[i].re = data[i].re * hlt[i].re + data[i].im * hlt[i].im;
			tempop[i].im = -data[i].re * hlt[i].im + data[i].im * hlt[i].re;
		}
	} else {
		for (i = 0; i < N; i++) {
			tempop[i].re = data[i].re * hlt[i].re - data[i].im * hlt[i].im;
			tempop[i].im = data[i].re * hlt[i].im + data[i].im * hlt[i].re;
		}
	}

	for (i = N;i < M;i++) {
		tempop[i].re = 0.0;
		tempop[i].im = 0.0;
	}

	fft_exec(obj,tempop,yn);

	if (sgn == 1) {
		for (i = 0; i < M; i++) {
			temp = yn[i].re * hk[i].re - yn[i].im * hk[i].im;
			yn[i].im = yn[i].re * hk[i].im + yn[i].im * hk[i].re;
			yn[i].re = temp;
		}
	} else {
		for (i = 0; i < M; i++) {
			temp = yn[i].re * hk[i].re + yn[i].im * hk[i].im;
			yn[i].im = -yn[i].re * hk[i].im + yn[i].im * hk[i].re;
			yn[i].re = temp;
		}

	}

    //IFFT

    for (ii = 0; ii < M; ++ii) {
		(obj->twiddle+ii)->im = -(obj->twiddle+ii)->im;
	}

	obj->sgn = -1*sgn;

	fft_exec(obj,yn,yno);

	if (sgn == 1) {
		for (i = 0; i < N; i++) {
			oup[i].re = yno[i].re * hlt[i].re + yno[i].im * hlt[i].im;
			oup[i].im = -yno[i].re * hlt[i].im + yno[i].im * hlt[i].re;
		}
	} else {
		for (i = 0; i < N; i++) {
			oup[i].re = yno[i].re * hlt[i].re - yno[i].im * hlt[i].im;
			oup[i].im = yno[i].re * hlt[i].im + yno[i].im * hlt[i].re;
		}

	}

	obj->sgn = def_sgn;
	obj->N = def_N;
	obj->lt = def_lt;
	for (ii = 0; ii < M; ++ii) {
		(obj->twiddle+ii)->im = -(obj->twiddle+ii)->im;
	}

    free(yn);
    free(yno);
    free(tempop);
    free(hk);
    free(hlt);

}



void cWavelib::fft_exec(fft_object obj,fft_data *inp,fft_data *oup) {
	if (obj->lt == 0) {
		//fftct_radix3_dit_rec(inp,oup,obj, obj->sgn, obj->N);
		//fftct_mixed_rec(inp,oup,obj, obj->sgn, obj->N);
		//printf("%f \n", 1.785);
		int l,inc;
		int nn,sgn1;
		nn = obj->N;
		sgn1 = obj->sgn;
		l = 1;
		inc = 0;
		//radix3_dit_rec(oup,inp,obj,sgn1,nn,l);
		mixed_radix_dit_rec(oup,inp,obj,sgn1,nn,l,inc);
	} else if (obj->lt == 1){
		//printf("%f \n", 1.785);
		int nn,sgn1;
		nn = obj->N;
		sgn1 = obj->sgn;
		bluestein_fft(inp,oup,obj,sgn1,nn);

	}

}

int cWavelib::divideby(int M,int d) {
	while (M%d == 0) {
		M = M/d;
	}
	if (M == 1) {
		return 1;
	}
	 return 0;
}

int cWavelib::dividebyN(int N) {
	while (N%53 == 0) {
		N = N/53;
	}
	while (N%47 == 0) {
		N = N/47;
	}
	while (N%43 == 0) {
		N = N/43;
	}
	while (N%41 == 0) {
		N = N/41;
	}
	while (N%37 == 0) {
		N = N/37;
	}
	while (N%31 == 0) {
		N = N/31;
	}
	while (N%29 == 0) {
		N = N/29;
	}
	while (N%23 == 0) {
		N = N/23;
	}
	while (N%17 == 0) {
		N = N/17;
	}
	while (N%13 == 0) {
		N = N/13;
	}
	while (N%11 == 0) {
		N = N/11;
	}
	while (N%8 == 0) {
		N = N/8;
	}
	while (N%7 == 0) {
		N = N/7;
	}
	while (N%5 == 0) {
		N = N/5;
	}
	while (N%4 == 0) {
		N = N/4;
	}
	while (N%3 == 0) {
		N = N/3;
	}
	while (N%2 == 0) {
		N = N/2;
	}
	if (N == 1) {
		return 1;
	}
	 return 0;

}

int cWavelib::factors(int M, int* arr) {
	int i,N,num,mult,m1,m2;
	i = 0;
	N = M;
	while (N%53 == 0) {
		N = N/53;
		arr[i] = 53;
		i++;
	}
	while (N%47 == 0) {
		N = N/47;
		arr[i] = 47;
		i++;
	}
	while (N%43 == 0) {
		N = N/43;
		arr[i] = 43;
		i++;
	}
	while (N%41 == 0) {
		N = N/41;
		arr[i] = 41;
		i++;
	}
	while (N%37 == 0) {
		N = N/37;
		arr[i] = 37;
		i++;
	}
	while (N%31 == 0) {
		N = N/31;
		arr[i] = 31;
		i++;
	}
	while (N%29 == 0) {
		N = N/29;
		arr[i] = 29;
		i++;
	}
	while (N%23 == 0) {
		N = N/23;
		arr[i] = 23;
		i++;
	}
	while (N%19 == 0) {
		N = N/19;
		arr[i] = 19;
		i++;
	}
	while (N%17 == 0) {
		N = N/17;
		arr[i] = 17;
		i++;
	}
	while (N%13 == 0) {
		N = N/13;
		arr[i] = 13;
		i++;
	}
	while (N%11 == 0) {
		N = N/11;
		arr[i] = 11;
		i++;
	}
	while (N%8 == 0) {
		N = N/8;
		arr[i] = 8;
		i++;
	}
	while (N%7 == 0) {
		N = N/7;
		arr[i] = 7;
		i++;
	}
	while (N%5 == 0) {
		N = N/5;
		arr[i] = 5;
		i++;
	}
	while (N%4 == 0) {
		N = N/4;
		arr[i] = 4;
		i++;
	}
	while (N%3 == 0) {
		N = N/3;
		arr[i] = 3;
		i++;
	}
	while (N%2 == 0) {
		N = N/2;
		arr[i] = 2;
		i++;
	}
	if (N > 31) {
		num = 2;

		while (N > 1) {
			mult = num*6;
			m1 = mult-1;
			m2 = mult+1;
			while (N%m1 == 0 ) {
				arr[i] = m1;
				i++;
				N = N / m1;
			}
			while (N%m2 == 0 ) {
				arr[i] = m2;
				i++;
				N = N / m2;
			}
			num+=1;

		}
	}
	return i;

}


void cWavelib::twiddle(fft_data *vec,int N, int radix) {
	int K,KL;
	fft_type theta,theta2;
	theta = PI2/N;
	KL = N/radix;
	vec[0].re = 1.0;
	vec[0].im = 0.0;

	for (K = 1; K < KL;K++) {
		theta2 = theta * K;
		vec[K].re = cos(theta2);
		vec[K].im = -sin(theta2);
	}

}

void cWavelib::longvectorN(fft_data *sig,int N, int *array, int tx) {
	int L,i,Ls,ct,j,k;
	fft_type theta;
	L = 1;
	ct = 0;
	for (i = 0; i < tx; i++) {
		L = L * array[tx-1-i];
		Ls = L / array[tx-1-i];
		theta = -1.0 * PI2/L;
		for (j = 0; j < Ls;j++) {
			for (k = 0; k < array[tx-1-i] -1 ;k++) {
				sig[ct].re = cos((k+1)*j*theta);
				sig[ct].im = sin((k+1)*j*theta);
				ct++;
			}
		}

	}

}




void free_fft(fft_object object) {
	free(object);
}
