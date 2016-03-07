#include "iirPH.h"

int iirPH(int ac, int acPrec, int acPHPrec){
	return ac - acPrec + ALPHA * acPHPrec;
}