#include<windows.h>
#include<winioctl.h>
#include<stdio.h>

ULONGLONG ReadSectorNum(){
    DISK_GEOMETRY_EX IpOutBuffer;
    DWORD nOutBufferSize = sizeof(IpOutBuffer);
    DWORD IpBytesReturned;
    
    HANDLE Upan = CreateFile(TEXT("\\\\.\\PHYSICALDRIVE1"),GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
    DeviceIoControl(Upan,IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,NULL,0,&IpOutBuffer,nOutBufferSize,&IpBytesReturned,NULL);
    
    ULONGLONG result = (IpOutBuffer.DiskSize.QuadPart)/(IpOutBuffer.Geometry.BytesPerSector);
    printf("扇区数量:%llX\n",result);
    return result;
}

LONG crc32(const void* data, size_t length)
{
    LONG crc = 0xFFFFFFFF;
    const LONG* p = (const LONG*)data;

    while (length--) {
        crc ^= *p++;
        for (int i = 0; i < 8; i++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }

    return ~crc;
}

int main(){
    FILE* fp = fopen("lba1.bin","wb+");
    struct LBA1 {
        char Signature[8];
        char GPT_Revision[4];
        char Header_Size[4];
        char CRC32_Header[4];
        char Reserverd[4];  
        char Current_LBA[8];
        char Alternate_LBA[8];
        char First_usable_LBA[8];
        char Last_usable_LBA[8];
        char GUID[16];
        char Entries_Start_LBA[8];
        char Partition_Entries_Num[4];
        char Partition_Entry_Size[4];
        char CRC32_Entires[4];
    } LBA1 = {
        {0x45,0x46,0x49,0x20,0x50,0x41,0x52,0x54},
        {0x00,0x00,0x01,0x00},
        {0x5C,0x00,0x00,0x00},
        {}, //小明同学觉得还是先留空，其他地方填完了再管比较好
        {}, //这个就是必须空了
        {0x01,0x00,0x00,0x00},
        {}, //小明同学还没算好，他已经写了个函数，但是他想先把方便硬编码的部分搞定
        {0x22,0x00,0x00,0x00},
        {}, //小明同学还没算好，他已经写了个函数，但是他想先把方便硬编码的部分搞定
        {0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //DISK GUID可以自己编，所以小明同学就选了一个最独特的
        {0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x80,0x00,0x00,0x00},
        {} //小明同学觉得还是先留空，其他地方填完了再管比较好
    };

    ULONGLONG v = ReadSectorNum() - 1;
    memcpy(LBA1.Alternate_LBA,&v,8);
    v = ReadSectorNum() - 34;
    memcpy(LBA1.Last_usable_LBA,&v,8);

    /*char* ptr = LBA1.Alternate_LBA;
    ULONGLONG v = total_sectors-1;
    for (int i = 0; i < 8; i++)
    {
        *ptr = (v & 0xFF);
        v = v >> 8;
        ptr++;
    }*/
    


    fwrite(&LBA1,1,sizeof(LBA1),fp);
    fclose(fp);

    getchar();
    return 0;
}