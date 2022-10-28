#include "ManyClasses.h"

noConstructor globalNc;					// ok: using synthesized constructor
noConstructor aGlobalNc[3];				// ok: using synthesized constructor

//noDefConstructor noDC;				// error: no appropriate default constructor
noDefConstructor noDC(1);				// ok: using defined constructor
noDefConstructor aNoDC[3]={1,2,3};		// ok: using defined constructor

memNoConstructor memNC;					// ok: using synthesized constructor
memNoConstructor aMemNC[3];				// ok: using synthesized constructor

memNoDefConstructor memNDC(10);			// ok: using defined constructor
memNoDefConstructor aMemNDC[3]={1,2,3};	// ok: using defined constructor

int func() {
	char* pCString = "C-Style String";
	noConstructor localNc1;
	noConstructor localNc2 = { 1, 2.0, "test", {'a', 'b'}, pCString };
	noConstructor localNc3(localNc2);	// using synthesized copy constructor
	localNc1 = localNc2;				// using synthesized assignment operator
	return 0;
}
int main() {
	noConstructor nC;
	memNoDefConstructor memNDC(10);
	func();

	prvInheritPrv	prvIPrv;		// "private" inherit from WithPrivate
	// error: Derive-to-Base Inaccessible
	//withPrivate wP(prvIPrv);

	pubInheritPrv	pubIPrv;		// "public" inherit from WithPrivate
	withPrivate		wP(pubIPrv);	// ok

	prvInheritPub	prvIPub;		// "private" inherit from allPublic
	// error: Derive-to-Base Inaccessible
	//allPublic		aP(prvIPub);

	return 0;
}