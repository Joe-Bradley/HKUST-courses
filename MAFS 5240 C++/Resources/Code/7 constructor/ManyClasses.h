#include <string>
using std::string;

class noConstructor {
public:
	int		i;
	double	d;
	string	s;
	char	c[2];
	char*	pc;
};

class noDefConstructor {
public:
	noDefConstructor(int);

	int		i;
	double	d;
};

class memNoConstructor {
public:
	noConstructor noC;
};

class memNoDefConstructor {
public:
	memNoDefConstructor(int i):noDC(i) {}	// must initialize noDC

	noDefConstructor noDC;
};

class withPrivate {
private:
	int		iPrivate;
public:
	double	dPublic;
};

class prvInheritPrv : private withPrivate {
private:
	int		iMyOwn;
};

class pubInheritPrv : public withPrivate {
private:
	int		iMyOwn;
};

class allPublic {
public:
	int		iPrivate;
	double	dPublic;
};

class prvInheritPub : private allPublic {
private:
	int		iMyOwn;
};