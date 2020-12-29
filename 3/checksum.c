#include<stdio.h>

unsigned short checksum() {
    unsigned  fields[9];
    int i,sum=0;
    for(i=0;i<9;i++) {
        printf("Field %d\n",i+1);
        scanf("%x",&fields[i]);
        sum=sum+(unsigned short) fields[i];
        while(sum>>16)
            sum=(sum & 0xFFFF) + (sum >>16);
    }
    sum=~sum;
    printf("checksum:%x\n",(unsigned short)sum);
    return (unsigned short)~sum;
}

int main() {
    unsigned short check1,check2;
    printf("sender:\n");
    check1=checksum();
    printf("receiver:\n");
    check2=checksum();
    
    if(check1==check2)
        printf("no error\n");
    else
        printf("error\n");
    return 0;
}