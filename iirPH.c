#include "iirPH.h"

float iirPH(float ac, float acPrec, float acPHPrec){
	return ac - acPrec + ALPHA * acPHPrec;
}
