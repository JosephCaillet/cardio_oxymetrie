#include "iirPH.h"

int iirPH(float ac, float acPrec, float acPHPrec){
	return ac - acPrec + ALPHA * acPHPrec;
}
