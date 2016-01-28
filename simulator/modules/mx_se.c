#include "mx_se.h"
MX_SE mx_se;
void MX_SE_start() {
	strcpy(mx_se.output, ZERO);
}
void SET(int value) {
	if(value) {
		strcpy(mx_se.output, mx_se.input_RB);
	}else{
        strcpy(mx_se.output, mx_se.input_SE);
    }
}
