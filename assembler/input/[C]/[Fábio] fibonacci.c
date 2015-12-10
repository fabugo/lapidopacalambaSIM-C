#include "stdio.h"
void main() {
    long long int   c,
                    v[2] = {0,1},
                    i = 1;
    scanf(" %lld", &c);
    if(c!=0 && c!=1){
        for(i; i <= c; i++){
            if(i%2 == 0){
                v[i%2] = v[i%2] + v[i%2+1];
            }
            else if(i%2 == 1){
                v[i%2] = v[i%2] + v[i%2-1];
            }
        }
        if(i%2 == 1)
            printf("\n%lld\n",v[i%2-1]);
        else if(i%2 == 0)
            printf("\n%lld\n",v[i%2+1]);
    }else{
        printf("\n%lld\n", v[c]);
    }
}
