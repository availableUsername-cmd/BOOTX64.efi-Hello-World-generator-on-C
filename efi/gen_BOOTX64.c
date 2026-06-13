#include<stdio.h>
#include<stdint.h>



int main(){
    
    struct DOSHeader {
       unsigned char e_magic[2];
       unsigned char stub[0x3A];
       unsigned char e_lfanew[4];
    } DOSHeader = {
        .e_magic = {0x4D,0x5A},
        .stub = {},
        .e_lfanew = {0x40,0x00,0x00,0x00}
    };

    struct COFF {
        unsigned char machine[2];
        unsigned char Num_Sections[2];
        unsigned char TimeDateStamp[4];
        unsigned char PointerToSymbolTable[4];
        unsigned char NumberOfSymbols[4];
        unsigned char SizeOfOptionalHeader[2];
        unsigned char Characteristics[2];
    } COFF = {
        .machine = {0x64,0x86},
        .Num_Sections = {0x02,0x00},
        .TimeDateStamp = {},
        .PointerToSymbolTable = {},
        .NumberOfSymbols = {},
        .SizeOfOptionalHeader = {0xF0,0x00},
        .Characteristics = {0x22,0x02}
    };

    struct OptionalHeader
    {
        unsigned char Magic[2];
        unsigned char LinkerVersion[2];
        unsigned char SizeofCode[4];
        unsigned char SizeofInitializedData[4];
        unsigned char SizeOfUninitializedData[4];
        unsigned char AddressOfEntryPoint[4];
        unsigned char BaseofCode[4];
        unsigned char ImageBase[8];
        unsigned char SectionAlignment[4];
        unsigned char FileAlignment[4];
        unsigned char OperatingSystemVersion[4];
        unsigned char ImageVersion[4];
        unsigned char SubSystemVersion[4];
        unsigned char Win32VersionValue[4];
        unsigned char SizeofImage[4];
        unsigned char SizeofHeaders[4];
        unsigned char CheckSum[4];
        unsigned char SubSystem[2];
        unsigned char DllCharacteristics[2];
        unsigned char SizeofStackReserve[8];
        unsigned char SizeofStackCommit[8];
        unsigned char SizeofHeapReserve[8];
        unsigned char SizeOfHeapCommit[8];
        unsigned char LoaderFlags[4];
        unsigned char Num_RVAandSIZE[4];
        //Data Dict
        unsigned char Export_Table[8];
        unsigned char Import_Table[8];
        unsigned char Resource_Table[8];
        unsigned char Exception_Table[8];
        unsigned char Certificate_Table[8];
        unsigned char Base_Relocation_Table[8];
        unsigned char Debug[8];
        unsigned char Architecture[8];
        unsigned char Global_Ptr[8];
        unsigned char TLS_Talbe[8];
        unsigned char Load_Config_Table[8];
        unsigned char Bound_Import[8];
        unsigned char IAT[8];
        unsigned char Delay_Import_Desc[8];
        unsigned char CLR_Runtime_Header[8];
        unsigned char Reserved[8];
    } OptionalHeader = {
        .Magic = {0x0B,0x02},
        .LinkerVersion = {},
        .SizeofCode = {0x00,0x01,0x00,0x00}, //256字节机器码
        .SizeofInitializedData = {},
        .SizeOfUninitializedData = {},
        .AddressOfEntryPoint = {0x00,0x10,0x00,0x00}, //小明还没写到Text段
        .BaseofCode = {0x00,0x10,0x00,0x00}, //小明还没写到Text段
        .ImageBase = {}, //EFI要是0
        .SectionAlignment = {0x00,0x10,0x00,0x00},
        .FileAlignment = {0x00,0x02,0x00,0x00},
        .OperatingSystemVersion = {},
        .ImageVersion = {},
        .SubSystemVersion = {},
        .Win32VersionValue = {},
        .SizeofImage = {0x00,0x30,0x00,0x00}, //小明还没写到节表
        .SizeofHeaders = {0x00,0x02,0x00,0x00},
        .CheckSum = {},
        .SubSystem = {0x0A,0x00},
        .DllCharacteristics = {},
        .SizeofStackReserve = {},
        .SizeofStackCommit = {},
        .SizeofHeapReserve = {},
        .SizeOfHeapCommit = {},
        .LoaderFlags = {},
        .Num_RVAandSIZE = {0x10,0x00,0x00,0x00},

        .Export_Table = {},
        .Import_Table = {},
        .Resource_Table = {},
        .Exception_Table = {},
        .Certificate_Table = {},
        .Base_Relocation_Table = {0x00,0x20,0x00,0x00,0x0C,0x00,0x00,0x00}, //小明还没有写到reloc段
        .Debug = {},
        .Architecture = {},
        .Global_Ptr = {},
        .TLS_Talbe = {},
        .Load_Config_Table = {},
        .Bound_Import = {},
        .IAT = {},
        .Delay_Import_Desc = {},
        .CLR_Runtime_Header = {},
        .Reserved = {}
    };

    struct SectionTable {
        char Name[8];
        char VirtualSize[4];
        char VirtualAddress[4];
        char SizeofRawData[4];
        char PtrtoRawData[4];
        char PtrtoRelocations[4];
        char PtrtoLinenumbers[4];
        char NumofRelocations[2];
        char NumofLinenumbers[2];
        char Characteristics[4];
    };

    struct SectionTable Sec_text = {
        .Name = {0x2E,0x74,0x65,0x78,0x74,0x00,0x00,0x00}, //.text
        .VirtualSize = {0x00,0x01,0x00,0x00}, //256字节机器码
        .VirtualAddress = {0x00,0x10,0x00,0x00},
        .SizeofRawData = {0x00,0x02,0x00,0x00},
        .PtrtoRawData = {0x00,0x02,0x00,0x00},
        .PtrtoRelocations = {},
        .PtrtoLinenumbers = {},
        .NumofRelocations = {},
        .NumofLinenumbers = {},
        .Characteristics = {0x20,0x00,0x00,0x60}
    };

    struct SectionTable Sec_reloc = {
        .Name = {0x2E,0x72,0x65,0x6C,0x6F,0x63,0x00,0x00}, //.data
        .VirtualSize = {0x0C,0x01,0x00,0x00}, //12字节机器码
        .VirtualAddress = {0x00,0x20,0x00,0x00},
        .SizeofRawData = {0x00,0x02,0x00,0x00},
        .PtrtoRawData = {0x00,0x04,0x00,0x00},
        .PtrtoRelocations = {},
        .PtrtoLinenumbers = {},
        .NumofRelocations = {},
        .NumofLinenumbers = {},
        .Characteristics = {0x40,0x00,0x00,0x40}
    };

    struct SectionTable Sec_rdata = {
        .Name = {0x2E,0x72,0x64,0x61,0x74,0x61,0x00,0x00}, //.rdata
        .VirtualSize = {0x0C,0x00,0x00,0x00},
        .VirtualAddress = {0x00,0x30,0x00,0x00},
        .SizeofRawData = {0x00,0x02,0x00,0x00},
        .PtrtoRawData = {0x00,0x06,0x00,0x00},
        .PtrtoRelocations = {},
        .PtrtoLinenumbers = {},
        .NumofRelocations = {},
        .NumofLinenumbers = {},
        .Characteristics = {0x40,0x00,0x00,0x40}
    };
    /* 00 00 00 00 PageRVA
       0C 00 00 00 BLockSize=12
       00 00 Entry
       00 00 Padding
    */
    sizeof(DOSHeader);
    sizeof(COFF);
    sizeof(OptionalHeader);
    sizeof(Sec_reloc);

    struct BOOTX64
    {
        struct DOSHeader Dos_Header;
        unsigned char PESign[4];
        struct COFF coff;
        struct OptionalHeader OptHeader;
        struct SectionTable sec_text;
        struct SectionTable sec_reloc;
        unsigned char padding[0x68];
        unsigned char text_section[0x200];
        unsigned char reloc_section[0x200];
    } BOOTX64 = {
        DOSHeader,
        {0x50,0x45,0x00,0x00},
        COFF,
        OptionalHeader,
        Sec_text,
        Sec_reloc,
        {},
        .text_section = 
        {
         0x48, 0x83, 0xE4, 0xF0,    //REX(0100WRXB:01001000) AND(imm8) /4,RSP(11-100-100) 0xF0
         0x48, 0x8B, 0x5A, 0x40,    //REX(0100WRXB:01001000) MOV(to_r_from_r/m,64) RBX_[RDX+disp8](01-011-010) 0x40
         0x4C, 0x8B, 0x43, 0x30,    //REX(0100WRXB:01001100) MOV(to_r_from_r/m,64) R8_[RBX+disp8](01-000-011) 0x30
         0x48, 0x89, 0xD9,          //REX(0100WRXB:01001100) MOV(from_r_to_r/m,64) RBX_RCX(11-011-001)
        
         0x48, 0x83, 0xEC, 0x20,    //REX(0100WRXB:01001100) SUB(imm8) /5,RSP(11-101-100) 0x20
         0x41, 0xFF, 0xD0,          //REX(0100WRXB:01000001) call /2,r8(11-010-1000)
         0x48, 0x83, 0xC4, 0x20,    //REX(0100WRXB:01001100) ADD(imm8) /0,RSP(11-000-100) 0x20

         0x4C, 0x8B, 0x43, 0x08,    //REX(0100WRXB:01001100) MOV(to_r_from_r/m,64) R8_[RBX+disp8](01-1000-011) 0x08
         0x48, 0x89, 0xD9,          //REX(0100WRXB:01001100) MOV(from_r_to_r/m,64) RBX_RCX(11-011-001)
         0x48, 0x8D, 0x15, 0x11, 0x00, 0x00, 0x00,  //REX(0100WRXB:01001000) LEA(to_reg_from_r/m) RDX_RIP(00-010-101) 0x11

         0x48, 0x83, 0xEC, 0x20,    //REX(0100WRXB:01001100) SUB(imm8) /5,RSP(11-101-100) 0x20
         0x41, 0xFF, 0xD0,          //REX(0100WRXB:01000001) call /2,r8(11-010-1000)
         0x48, 0x83, 0xC4, 0x20,    //REX(0100WRXB:01001100) ADD(imm8) /0,RSP(11-000-100) 0x20

         0x48, 0x31, 0xC0,          //REX(0100WRXB:01001000) XOR(64) RAX_RAX(11-000-000)
         0xEB, 0xFE,                // JMP(8) -2;
         0xC3,                      //RET

         /* UTF-16_LE "hello, world\r\n"*/
         0x68,0x00, 0x65,0x00, 0x6C,0x00, 0x6C,0x00,
         0x6F,0x00, 0x2C,0x00, 0x20,0x00, 0x77,0x00,
         0x6F,0x00, 0x72,0x00, 0x6C,0x00, 0x64,0x00,
         0x0D,0x00, 0x0A,0x00,
         0x00,0x00
        },
        .reloc_section = {
            0x00,0x00,0x00,0x00,   // PageRVA
            0x0C,0x00,0x00,0x00,   // BlockSize = 12
            0x00,0x00,             // Entry
            0x00,0x00              // Padding
            }
    };

    sizeof(BOOTX64);

    FILE* fp = fopen("BOOTX64.efi","wb");
    fwrite(&BOOTX64,1,sizeof(BOOTX64),fp);
    fclose(fp);

    getchar();
    return 0;
}