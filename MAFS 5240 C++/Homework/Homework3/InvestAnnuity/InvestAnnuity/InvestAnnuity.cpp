#include "../Date/Date.h"
#include "InvestAnnuity.h"
#include <cassert>
#include <math.h>
#include <cmath>

// Returns the payout amount
double InvestAnnuity(
	Date dt,			// Date (1/9/2021 - 31/12/2021) to buy product. 1st payment starts end-of-month
	int investPeriod,	// Investment period (years 1-5)
	int payment,			// monthly payment
	int payoutPeriod,	// Payout period (years 1-15)
	double interest		// Interest rate (%) on accrual amount
	) {

	assert(20210901 <= dt && dt <= 20211231);
	assert(1 <= investPeriod && investPeriod <= 10);
	assert(1 <= payoutPeriod && payoutPeriod <= 15);

	// TODO
	return 0;
	int payout_term = payout_term*12;

	double total_amount;
}

double cal_error(
	double interest, 	// Interest rate (%) on accrual amount
	int payout_term,
	double payment,
	double total_amount
	){
		for(int i = 1;i<=payout_term;i++){
			total_amount = total_amount -  

		}
	

	
}