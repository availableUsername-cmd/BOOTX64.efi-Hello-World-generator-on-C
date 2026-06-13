#include <stdio.h>

int main(){
    FILE* fp = fopen("os.bin","wb");
    for (int i = 0; i < 510; i++)
    {
        fputc(0,fp);
    }
    fputc(0x55,fp);
    fputc(0xAA,fp);
    fclose(fp);
    return 0;
}