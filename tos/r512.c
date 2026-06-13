#include<windows.h>
#include<stdio.h>

DWORD ReadDisk(unsigned char* buffer,DWORD start,DWORD size){
    //OVERLAPPED over = { 0 };
    //over.Offset = start;
    HANDLE handle = CreateFile(TEXT("\\\\.\\PHYSICALDRIVE1"),GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
    if (handle == INVALID_HANDLE_VALUE) return 0;
    DWORD readsize;
    if (ReadFile(handle,buffer,size,&readsize,NULL) == 0){
        CloseHandle(handle);
        return 0;
    }
    CloseHandle(handle);
    return size;
}

int main(){
    int size=512;
    unsigned char buffer[size];
    DWORD len=ReadDisk(buffer,0,size);
    if (len){
        for (int i = 0; i < len; i++)
        {
            printf("%02X",buffer[i]);
        }
    }
    getchar();
    return 0;
}