//Magyar Máté Q8C1NV
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

////////////////
// konstansok //
////////////////
/// tömb mérete
#define SIZE 720
/// approximáció mélysége
#define PREC 10
/// érték típusa
//#define VALTYPE float
#define VALTYPE double
//#define VALTYPE long double

using namespace std;

template<int N, int I, int J, int K>
class SineSeries {
	/// rekurzív törzs
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
	/// rekurziólezáró törzs
public:
	static inline VALTYPE accumulate()
	{
		return 1;
	}
};

/// közvetlenül hívott tag
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
	/// rekurzív törzs
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
	/// rekurziólezáró törzs
public:
	static inline VALTYPE accumulate()
	{
		return 1;
	}
};

/// közvetlenül hívott tag
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
	/// rekurzív törzs
	/// Az inline fv.-nek legyen egy olyan pointer a paramétere,
	/// ami a sin_t tömbbe mutat!
	/// Erre a pointerre írd a sin() értéket,
	/// és rekurzív hívásnál léptesd a pointert!
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
	/// rekurziólezáró törzs
public:
	static inline void f(VALTYPE* sin_l) { }
};

/// Mivel a loop<> visszafelé számolja I-t,
/// szükséges egy olyan loop-ot is csinálni,
/// ami elõrefelé lépteti I-t.

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


/// a feltöltendõ tömb
VALTYPE sin_t[SIZE];
VALTYPE cos_t[SIZE];
VALTYPE exp_t[SIZE];

/// sin(alpha) lekérdezése.
/// Egy bemenõ és több kimenõ paramétere van.
/// \param alpha szög (deg)
/// \param alpha_lo_idx szög indexe a táblázatban (alsó közelítés)
/// \param alpha_hi_idx szög indexe a táblázatban (felsõ közelítés)
/// \param alpha_lo szög alsó közelítésének értéke
/// \param alpha_hi szög felsõ közelítésének értéke
/// \param sin_lo alsó közelítés szinusza
/// \param sin_hi felsõ közelítés szinusza
/// \return egzakt találat
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
	loop_inc_cos<SIZE, 0>::f(cos_t); //Azért így csináltam, hogy mûködjön az eredeti teszt kód.
	loop_inc_exp<SIZE, 0>::f(exp_t); //Nagyon érzékennyé válik a PREC értékére, így a beállított 10-es kb 5 értékig jó, utána már nem konvergál az eredeti függvényhez.


	// ellenõrzés
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
További ritkaságok:

cos, exp megvalósítva, inverz függvények hiányoznak.

Különbözõ tömbméretek:
A tömb méretének növelése megnöveli a fordítási idõt, ahogy a pontosság növelése is -> mindkettõ növeli a rekurzió mélységét.
A pontosság növelésekor a sor jobban konvergál a függvényértékhez -> csökken a hiba (exp-nél látványos a jelenség).

VALTYPE függõség:
Mivel belefordul a kódba minden lépés, így size(VALTYPE)*PREC*SIZE*C mérettel növekedik a méret.
Az eredmények pontossága pedig a VALTYPE típus pontosságától függ, így pl int-nél felesleges nagy prec-et megadni szinusznál, mert úgyis 0 v. 1 lesz.

Matematikai hiba:
Arcsin függvénynél negatív értékre nem ad vissza értékelhetõ választ -> csak 0° és 180° között vizsgáljuk.

*/