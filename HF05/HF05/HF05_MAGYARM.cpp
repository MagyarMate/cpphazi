//Magyar M�t� Q8C1NV
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

////////////////
// konstansok //
////////////////
/// t�mb m�rete
#define SIZE 720
/// approxim�ci� m�lys�ge
#define PREC 10
/// �rt�k t�pusa
//#define VALTYPE float
#define VALTYPE double
//#define VALTYPE long double

using namespace std;

template<int N, int I, int J, int K>
class SineSeries {
	/// rekurz�v t�rzs
	enum { go = (K + 1 != J) };
public:
	static inline VALTYPE accumulate()
	{
		return 1 - (I * 2 * M_PI / N)*(I * 2 * M_PI / N) / (2 * K + 2) / (2 * K + 3) *
			SineSeries<N*go, I*go, J*go, (K + 1)*go>::accumulate();
	}
};

template<>
class SineSeries<0, 0, 0, 0> {
	/// rekurzi�lez�r� t�rzs
public:
	static inline VALTYPE accumulate()
	{
		return 1;
	}
};

/// k�zvetlen�l h�vott tag
template<int N, int I>
class Sine {
public:
	static inline VALTYPE sin()
	{
		return (I * 2 * M_PI / N) * SineSeries<N, I, PREC, 0>::accumulate();
	}
};

// <EXP>

template<int I, int J, int K>
class ExpSeries {
	/// rekurz�v t�rzs
	enum { go = (K + 1 != J) };
public:
	static inline VALTYPE accumulate()
	{
		return 1 + ((VALTYPE)I / K) *
			ExpSeries<I*go, J*go, (K + 1)*go>::accumulate();
	}
};

template<>
class ExpSeries<0, 0, 0> {
	/// rekurzi�lez�r� t�rzs
public:
	static inline VALTYPE accumulate()
	{
		return 1;
	}
};

/// k�zvetlen�l h�vott tag
template<int I>
class Exp {
public:
	static inline VALTYPE exp()
	{
		return ExpSeries<I, PREC, 1>::accumulate();
	}
};


// </EXP>


template<int I>
class loop {
	/// rekurz�v t�rzs
	/// Az inline fv.-nek legyen egy olyan pointer a param�tere,
	/// ami a sin_t t�mbbe mutat!
	/// Erre a pointerre �rd a sin() �rt�ket,
	/// �s rekurz�v h�v�sn�l l�ptesd a pointert!
private:
	enum { go = (I - 1) != 0 };
public:
	static inline void f(VALTYPE* sin_l) { 
		sin_l[I] = Sine<SIZE, I>::sin();
		loop<go ? (I - 1) : 0>::f(sin_l);
	}
};

template<>
class loop<0> {
	/// rekurzi�lez�r� t�rzs
public:
	static inline void f(VALTYPE* sin_l) { }
};

/// Mivel a loop<> visszafel� sz�molja I-t,
/// sz�ks�ges egy olyan loop-ot is csin�lni,
/// ami el�refel� l�pteti I-t.

template<int N, int I>
class loop_inc {
private:
	enum { go = (I + 1) != N };
public:
	static inline void f(VALTYPE* sin_l) { 
		sin_l[I] = Sine<N, I>::sin();
		loop_inc<N, go ? (I + 1) : N >::f(sin_l);
	}
};
template<>
class loop_inc<SIZE, SIZE> {
public:
	static inline void f(VALTYPE* sin_l) { }
};

template<int N, int I>
class loop_inc_cos {
private:
	enum { go = (I + 1) != N };
public:
	static inline void f(VALTYPE* sin_l) {
		sin_l[I] = Sine<N, I+90>::sin();
		loop_inc<N, go ? (I + 1) : N >::f(sin_l);
	}
};

template<int N, int I>
class loop_inc_exp {
private:
	enum { go = (I + 1) != N };
public:
	static inline void f(VALTYPE* exp_l) {
		exp_l[I] = Exp<I>::exp();
		loop_inc_exp<N, go ? (I + 1) : N >::f(exp_l);
	}
};

template<>
class loop_inc_exp<SIZE, SIZE> {
public:
	static inline void f(VALTYPE* exp_l) { }
};


/// a felt�ltend� t�mb
VALTYPE sin_t[SIZE];
VALTYPE cos_t[SIZE];
VALTYPE exp_t[SIZE];

/// sin(alpha) lek�rdez�se.
/// Egy bemen� �s t�bb kimen� param�tere van.
/// \param alpha sz�g (deg)
/// \param alpha_lo_idx sz�g indexe a t�bl�zatban (als� k�zel�t�s)
/// \param alpha_hi_idx sz�g indexe a t�bl�zatban (fels� k�zel�t�s)
/// \param alpha_lo sz�g als� k�zel�t�s�nek �rt�ke
/// \param alpha_hi sz�g fels� k�zel�t�s�nek �rt�ke
/// \param sin_lo als� k�zel�t�s szinusza
/// \param sin_hi fels� k�zel�t�s szinusza
/// \return egzakt tal�lat
bool sin_lookup(
	const VALTYPE &alpha,
	int &alpha_lo_idx,
	int &alpha_hi_idx,
	VALTYPE &alpha_lo,
	VALTYPE &alpha_hi,
	VALTYPE &sin_lo,
	VALTYPE &sin_hi
	) {
	alpha_lo_idx = (int)((alpha) / 360 * SIZE) % SIZE;
	alpha_lo = alpha_lo_idx*360.0 / SIZE;

	bool alpha_match = (alpha == alpha_lo);

	alpha_hi_idx = alpha_match ?
		alpha_lo_idx :
		(alpha_lo_idx + 1) % SIZE;
	alpha_hi = alpha_hi_idx*360.0 / SIZE;

	sin_lo = sin_t[alpha_lo_idx];
	sin_hi = sin_t[alpha_hi_idx];
	return alpha_match;
}

bool arcsin_lookup(
	const VALTYPE &val,
	int &val_lo_idx,
	int &val_hi_idx,
	VALTYPE &val_lo,
	VALTYPE &val_hi,
	VALTYPE &alpha_lo,
	VALTYPE &alpha_hi
	) {
	for (val_hi_idx = 0;val_hi_idx <= SIZE / 4 && sin_t[val_hi_idx] <= val;val_hi_idx++);
	for (val_lo_idx = SIZE / 4;val_lo_idx >= 0 && sin_t[val_lo_idx] >= val;val_lo_idx--);
	if (!(val_hi_idx == val_lo_idx || val_hi_idx == val_lo_idx + 1)) {
		return false;
	}
	val_lo = 360.0*val_lo_idx / SIZE;
	val_hi = 360.0*val_hi_idx / SIZE;
	alpha_lo = sin_t[val_lo_idx];
	alpha_hi = sin_t[val_hi_idx];
	return true;
}

int main() {
	loop_inc<SIZE, 0>::f(sin_t);
	loop_inc_cos<SIZE, 0>::f(cos_t); //Az�rt �gy csin�ltam, hogy m�k�dj�n az eredeti teszt k�d.
	loop_inc_exp<SIZE, 0>::f(exp_t); //Nagyon �rz�kenny� v�lik a PREC �rt�k�re, �gy a be�ll�tott 10-es kb 5 �rt�kig j�, ut�na m�r nem konverg�l az eredeti f�ggv�nyhez.


	// ellen�rz�s
	//	for (int i=0;i<SIZE;i++)
	//		cout<<"exp("<<(i)<<")="<<exp_t[i]<<endl;

	VALTYPE alpha, val;
	VALTYPE alpha_lo, alpha_hi;
	VALTYPE sin_lo, sin_hi;
	VALTYPE val_lo, val_hi;
	int alpha_lo_idx, alpha_hi_idx;
	int val_lo_idx, val_hi_idx;

	cout << "alpha (deg)?";
	cin >> alpha;

	bool alpha_match = sin_lookup(alpha,
		alpha_lo_idx, alpha_hi_idx, alpha_lo, alpha_hi,
		sin_lo, sin_hi);
	cout << "sin(" << alpha_lo << ")=" << sin_lo << endl;
	if (!alpha_match) {
		cout << "sin(" << alpha_hi << ")=" << sin_hi << endl;
	}

	cout << "sin(alpha)?";
	cin >> val;
	if (arcsin_lookup(val, val_lo_idx, val_hi_idx, val_lo, val_hi, alpha_lo, alpha_hi)) {
		cout << "arcsin(" << val_lo << ")=" << alpha_lo << endl;
		cout << "arcsin(" << val_hi << ")=" << alpha_hi << endl;
	}
	return 0;
}

/*
Tov�bbi ritkas�gok:

cos, exp megval�s�tva, inverz f�ggv�nyek hi�nyoznak.

K�l�nb�z� t�mbm�retek:
A t�mb m�ret�nek n�vel�se megn�veli a ford�t�si id�t, ahogy a pontoss�g n�vel�se is -> mindkett� n�veli a rekurzi� m�lys�g�t.
A pontoss�g n�vel�sekor a sor jobban konverg�l a f�ggv�ny�rt�khez -> cs�kken a hiba (exp-n�l l�tv�nyos a jelens�g).

VALTYPE f�gg�s�g:
Mivel belefordul a k�dba minden l�p�s, �gy size(VALTYPE)*PREC*SIZE*C m�rettel n�vekedik a m�ret.
Az eredm�nyek pontoss�ga pedig a VALTYPE t�pus pontoss�g�t�l f�gg, �gy pl int-n�l felesleges nagy prec-et megadni szinuszn�l, mert �gyis 0 v. 1 lesz.

Matematikai hiba:
Arcsin f�ggv�nyn�l negat�v �rt�kre nem ad vissza �rt�kelhet� v�laszt -> csak 0� �s 180� k�z�tt vizsg�ljuk.

*/