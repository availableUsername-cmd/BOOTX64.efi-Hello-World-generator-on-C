#include<windows.h>
#include<winioctl.h>
#include<stdio.h>

int main(){
    DISK_GEOMETRY_EX IpOutBuffer;
    DWORD nOutBufferSize = sizeof(IpOutBuffer);
    DWORD IpBytesReturned;
    HANDLE Upan = CreateFile(TEXT("\\\\.\\PHYSICALDRIVE1"),GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
    DeviceIoControl(Upan,IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,NULL,0,&IpOutBuffer,nOutBufferSize,&IpBytesReturned,NULL);
    printf("%llX\n",IpOutBuffer.DiskSize.QuadPart);
    printf("%X\n",IpOutBuffer.Geometry.BytesPerSector);
    LONGLONG result = (IpOutBuffer.DiskSize.QuadPart)/(IpOutBuffer.Geometry.BytesPerSector);
    printf("%llX\n",result);

    getchar();
}
