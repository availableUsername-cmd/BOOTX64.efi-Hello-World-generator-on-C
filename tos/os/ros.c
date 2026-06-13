#include <stdio.h>

int main(){
    FILE* fp = fopen("D:/os.bin","rb");
    unsigned char data;
    printf("     ");
    for (int i = 0; i < 16; i++)
    {
        printf(" %02x ",i);
    }
    printf("\n");
    for (int i = 0; i < 32; i++)
    {
        printf("0x%02x ",i);
        for (int j = 0; j < 16; j++)
        {
            fscanf(fp,"%c",&data);
            printf(" %02x ",data);
        }
        printf("\n");
    }
    getchar();
    fclose(fp);
    return 0;
}