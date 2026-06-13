#include<windows.h>
#include<stdio.h>
#include<winioctl.h>

DWORD WriteDisk(unsigned char* buffer,DWORD start,DWORD size){
    OVERLAPPED over = { 0 };
    DWORD readsize=0; DWORD writesize=0;
    over.Offset = start;

    HANDLE handle_vol = CreateFile(TEXT("\\\\.\\F:"),GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
    if (handle_vol == INVALID_HANDLE_VALUE){
        printf("error0");
        return 0;
    }
    DWORD status;
    //把卷给我锁掉，不让别的进程动
    if (DeviceIoControl(handle_vol, FSCTL_LOCK_VOLUME, NULL,0,NULL,0,&status,NULL) == 0) {CloseHandle(handle_vol); return 0;}
    //把卷给我卸载了，这样别的就不会0x05了啊哈哈哈！！！！
    if (DeviceIoControl(handle_vol, FSCTL_DISMOUNT_VOLUME,NULL,0,NULL,0,&status,NULL) == 0) {CloseHandle(handle_vol); return 0;}

    HANDLE handle_in = CreateFile(TEXT("\\\\.\\PHYSICALDRIVE1"),GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    HANDLE handle_out = CreateFile(TEXT("..\\disk0.bin"),GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
    if (handle_out == INVALID_HANDLE_VALUE || handle_in == INVALID_HANDLE_VALUE){
        printf("error0");
        return 0;
    }
    if (ReadFile(handle_out,buffer,size,&readsize,NULL) == 0){
        CloseHandle(handle_vol);
        CloseHandle(handle_in);
        CloseHandle(handle_out);
        printf("error1");
        return 0;
    }
    if (WriteFile(handle_in,buffer,size,&writesize,NULL) == 0){
        CloseHandle(handle_vol);
        CloseHandle(handle_out);
        CloseHandle(handle_in);
        printf("error2");
        return 0;
    }
    CloseHandle(handle_vol);
    CloseHandle(handle_out);
    CloseHandle(handle_in);
    return size;
}

int main(){
    int size=512;
    unsigned char buffer[size];
    DWORD len=WriteDisk(buffer,0,size);
    printf("\n");
    if (len){
        for (int i = 0; i < size; i++)
        {
            printf("%02X",buffer[i]);
        }
    }
    DWORD err = GetLastError();
    if (err) printf("\nWriteFile failed! Error: %lu (0x%08X)\n", err, err);
    getchar();
    return 0;
}