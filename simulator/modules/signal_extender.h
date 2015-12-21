#ifndef SIGNAL_EXTENDER_H
#define SIGNAL_EXTENDER_H

struct SIGNAL_EXTENDER {
    char input[17];
    char output[33];
    int OP_SE;
};
typedef struct SIGNAL_EXTENDER SE;

extern SE se;

#endif