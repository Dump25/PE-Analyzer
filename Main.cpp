 /*****************************
 ** Written by Shell25       **
 ** 1396/11/1                **
 ******************************/
#include <iostream>
#include <fstream>
#include <string>
#include "PeLdr.h"
#include <time.h>

#pragma warning(disable: 4996)
using namespace std;

HexToChar hexToChar;
string    pathFile;

void readAndWrite_file(int size , int pointer,string fileName)
{
	char* buf = new char[size];
	ifstream file2(pathFile, ios::in | ios::binary | ios::ate);
	file2.seekg(pointer);
	file2.read(buf, size);
	file2.close();

	ofstream file3(fileName, ios::out | ios::binary | ios::ate);
	file3.seekp(0);
	file3.write(buf, size);
	file3.close();

	delete buf;
	buf = NULL;
}

string ntHeadersMachine(WORD *machineHEX)
{
	switch (*machineHEX)
	{
	case 0:
		return "IMAGE_FILE_MACHINE_UNKNOWN";
	case 0x014c:
		return "IMAGE_FILE_MACHINE_I386\\Intel 386.";
	case 0x0162:
		return "IMAGE_FILE_MACHINE_R3000\\MIPS little-endian, 0x160 big-endian";
	case 0x0166:
		return "IMAGE_FILE_MACHINE_R4000\\MIPS little-endian";
	case 0x0168:
		return "IMAGE_FILE_MACHINE_R10000\\MIPS little-endian";
	case 0x0169:
		return "IMAGE_FILE_MACHINE_WCEMIPSV2\\MIPS little-endian WCE v2";
	case 0x0184:
		return "IMAGE_FILE_MACHINE_ALPHA\\Alpha_AXP";
	case 0x01a2:
		return "IMAGE_FILE_MACHINE_SH3\\SH3 little-endian";
	case 0x01a3:
		return "IMAGE_FILE_MACHINE_SH3DSP";
	case 0x01a4:
		return "IMAGE_FILE_MACHINE_SH3E\\SH3E little-endian";
	case 0x01a6:
		return "IMAGE_FILE_MACHINE_SH4\\SH4 little-endian";
	case 0x01a8:
		return "IMAGE_FILE_MACHINE_SH5\\SH5";
	case 0x01c0:
		return "IMAGE_FILE_MACHINE_ARM\\ARM Little-Endian";
	case 0x01c2:
		return "IMAGE_FILE_MACHINE_THUMB\\ARM Thumb/Thumb-2 Little-Endian";
	case 0x01c4:
		return "IMAGE_FILE_MACHINE_ARMNT\\ARM Thumb-2 Little-Endian";
	case 0x01d3:
		return "IMAGE_FILE_MACHINE_AM33";
	case 0x01F0:
		return "IMAGE_FILE_MACHINE_POWERPC\\IBM PowerPC Little-Endian";
	case 0x01f1:
		return "IMAGE_FILE_MACHINE_POWERPCFP";
	case 0x0200:
		return "IMAGE_FILE_MACHINE_IA64\\Intel 64";
	case 0x0266:
		return "IMAGE_FILE_MACHINE_MIPS16\\MIPS";
	case 0x0284:
		return "IMAGE_FILE_MACHINE_ALPHA64  or  IMAGE_FILE_MACHINE_AXP64\\ALPHA64";
	case 0x0366:
		return "IMAGE_FILE_MACHINE_MIPSFPU\\MIPS";
	case 0x0466:
		return "IMAGE_FILE_MACHINE_MIPSFPU16\\MIPS";
	case 0x0520:
		return "IMAGE_FILE_MACHINE_TRICORE\\Infineon";
	case 0x0CEF:
		return "IMAGE_FILE_MACHINE_CEF";
	case 0x0EBC:
		return "IMAGE_FILE_MACHINE_EBC\\EFI Byte Code";
	case 0x8664:
		return "IMAGE_FILE_MACHINE_AMD64\\AMD64 (K8)";
	case 0x9041:
		return "IMAGE_FILE_MACHINE_M32R\\M32R little-endian";
	case 0xC0EE:
		return "IMAGE_FILE_MACHINE_CEE";
	default:
		break;
	}
	return "";
}

void ntCharacteristics(WORD *characteristics)
{
	WORD number[4];
	number[3] = (*characteristics / (16 * 16 * 16));
	number[2] = ((*characteristics / (16 * 16))) % 16;
	number[1] = (*characteristics / (16)) % 16 % 16;
	number[0] = *characteristics % 16 % 16 % 16;
	switch (number[0])
	{
	case 0x0001:
		cout << "	IMAGE_FILE_RELOCS_STRIPPED" << "\n";;
		break;
	case 0x0002:
		cout << "	IMAGE_FILE_EXECUTABLE_IMAGE" << "\n";;
		break;
	case 0x0004:
		cout << "	IMAGE_FILE_LINE_NUMS_STRIPPED" << "\n";;
		break;
	case 0x0008:
		cout << "	IMAGE_FILE_LOCAL_SYMS_STRIPPED" << "\n";;
		break;
	default:
		break;
	}
	
	switch (number[1])
	{
	case 0x0001:
		cout << "	IMAGE_FILE_AGGRESSIVE_WS_TRIM" << "\n";;
		break;
	case 0x0002:
		cout << "	IMAGE_FILE_LARGE_ADDRESS_ AWARE" << "\n";;
		break;
	case 0x0004:
		cout << "	This flag is reserved for future use" << "\n";;
		break;
	case 0x0008:
		cout << "	IMAGE_FILE_BYTES_REVERSED_LO" << "\n";;
		break;
	default:
		break;
	}
	
	switch (number[2])
	{
	case 0x0001:
		cout << "	IMAGE_FILE_32BIT_MACHINE" << "\n";;
		break;
	case 0x0002:
		cout << "	IMAGE_FILE_DEBUG_STRIPPED" << "\n";;
		break;
	case 0x0004:
		cout << "	IMAGE_FILE_REMOVABLE_RUN_ FROM_SWAP" << "\n";;
		break;
	case 0x0008:
		cout << "	IMAGE_FILE_NET_RUN_FROM_SWAP" << "\n";;
		break;
	default:
		break;
	}
	
	switch (number[3])
	{
	case 0x0001:
		cout << "	IMAGE_FILE_SYSTEM" << "\n";;
		break;
	case 0x0002:
		cout << "	IMAGE_FILE_DLL" << "\n";;
		break;
	case 0x0004:
		cout << "	IMAGE_FILE_UP_SYSTEM_ONLY" << "\n";;
		break;
	case 0x0008:
		cout << "	IMAGE_FILE_BYTES_REVERSED_HI" << "\n";;
		break;
	default:
		break;
	}
}

void ntMagic(WORD *magic)
{
	cout << "Magic                           : ";
	switch (*magic)
	{
	case 0x10b:
		cout << "	IMAGE_NT_OPTIONAL_HDR32_MAGIC\n";
		break;
	case 0x20b:
		cout << "	IMAGE_NT_OPTIONAL_HDR64_MAGIC\n";
		break;
	case 0x107:
		cout << "	IMAGE_ROM_OPTIONAL_HDR_MAGIC\n";
		break;
	default:
		cout << "	Unknown flage Magic\n";
		break;
	}
}

void ntsubsystem(WORD *subsystem)
{
	cout << "Subsystem                       : ";
	switch (*subsystem)
	{
	case 0:
		cout << "IMAGE_SUBSYSTEM_UNKNOWN\n";
		break;
	case 1:
		cout << "IMAGE_SUBSYSTEM_NATIVE\n";
		break;
	case 2:
		cout << "IMAGE_SUBSYSTEM_WINDOWS_GUI\n";
		break;
	case 3:
		cout << "IMAGE_SUBSYSTEM_WINDOWS_CUI\n";
		break;
	case 5:
		cout << "IMAGE_SUBSYSTEM_OS2_CUI\n";
		break;
	case 7:
		cout << "IMAGE_SUBSYSTEM_POSIX_CUI\n";
		break;
	case 9:
		cout << "IMAGE_SUBSYSTEM_WINDOWS_CE_GUI\n";
		break;
	case 10:
		cout << "IMAGE_SUBSYSTEM_EFI_APPLICATION\n";
		break;
	case 11:
		cout << "IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER\n";
		break;
	case 12:
		cout << "IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER\n";
		break;
	case 13:
		cout << "IMAGE_SUBSYSTEM_EFI_ROM\n";
		break;
	case 14:
		cout << "IMAGE_SUBSYSTEM_XBOX\n";
		break;
	case 16:
		cout << "IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION\n";
		break;
	default:
		cout << "Unknown flage Subsystem\n";
		break;
	}
}

void ntDllCharacteristics(WORD *DllCharacteristics)
{
	cout << "Dll Characteristics             : ";
	WORD number[4];
	number[3] = (*DllCharacteristics / (16 * 16 * 16));
	number[2] = ((*DllCharacteristics / (16 * 16))) % 16;
	number[1] = (*DllCharacteristics / (16)) % 16 % 16;
	number[0] = *DllCharacteristics % 16 % 16 % 16;

	cout << "\n";
	switch (number[0])
	{
	case 0x0001:
		cout << "	Reserved." << "\n";
		break;
	case 0x0002:
		cout << "	Reserved." << "\n";
		break;
	case 0x0004:
		cout << "	Reserved." << "\n";
		break;
	case 0x0008:
		cout << "	Reserved." << "\n";
		break;
	default:
		break;
	}
	
	switch (number[1])
	{
	case 0x0004:
		cout << "	IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE" << "\n";
		break;
	case 0x0008:
		cout << "	IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY" << "\n";
		break;
	default:
		break;
	}
	
	switch (number[2])
	{
	case 0x0001:
		cout << "	IMAGE_DLLCHARACTERISTICS_NX_COMPAT" << "\n";
		break;
	case 0x0002:
		cout << "	IMAGE_DLLCHARACTERISTICS_NO_ISOLATION" << "\n";
		break;
	case 0x0004:
		cout << "	IMAGE_DLLCHARACTERISTICS_NO_SEH" << "\n";
		break;
	case 0x0008:
		cout << "	IMAGE_DLLCHARACTERISTICS_NO_BIND" << "\n";
		break;
	default:
		break;
	}

	switch (number[3])
	{
	case 0x0001:
		cout << "	Reserved." << "\n";
		break;
	case 0x0002:
		cout << "	IMAGE_DLLCHARACTERISTICS_WDM_DRIVER" << "\n";
		break;
	case 0x0004:
		cout << "	Reserved." << "\n";
		break;
	case 0x0008:
		cout << "	IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE" << "\n";
		break;
	default:
		break;
	}

}

void ntDataDirectory(IMAGE_DATA_DIRECTORY *DataDirectory)
{
	cout << "Data Directory";
	for (int i = 0; i < 16; i++)
	{
		if (i != 0)
		{
			cout << "              ";
		}
		cout << "    block " << std::dec << i + 1 << " : ";
		cout << "  size :  " << std::dec << DataDirectory[i].Size;
		cout << "  Virtual Address : " << std::hex << "     " << DataDirectory[i].VirtualAddress << "\n";
	}
}

void sectionHeader(PE_LDR_PARAM *peSectionHeader)
{
	//Get data 16 Section Table

	//section
	for (int i = 1; i <= peSectionHeader->pNtHeaders->FileHeader.NumberOfSections; i++)
	{
		peSectionHeader->pNtSectionHeader = (PIMAGE_SECTION_HEADER)(((DWORD)peSectionHeader->pNtHeaders) +
			sizeof(IMAGE_NT_HEADERS) + (peSectionHeader->pNtHeaders->FileHeader.NumberOfSections - i) * sizeof(IMAGE_SECTION_HEADER));

		if ('d' == (BYTE)peSectionHeader->pNtSectionHeader->Name[2] && 'i' == (BYTE)peSectionHeader->pNtSectionHeader->Name[1])
		{
			readAndWrite_file(500, 232/*(int)peSectionHeader->pNtSectionHeader->PointerToRawData*/, "temp");
		}
	readAndWrite_file((int)peSectionHeader->pNtSectionHeader->SizeOfRawData,
		(int)peSectionHeader->pNtSectionHeader->PointerToRawData, (char*)peSectionHeader->pNtSectionHeader->Name);
	}
}

void showHederDos_PE(PE_LDR_PARAM *peDosH)
{
	if (peDosH->pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		cout << "DOS Signature invalid";
	}

	hexToChar.twoChar = peDosH->pDosHeader->e_magic;
	cout << "*********************************************************************HederDos" << "\n";
	cout << "Magic number                     : " << hexToChar.character[0] << hexToChar.character[1] << "\n";						//Magic number
	cout << "Bytes on last page of file       : " << std::dec << peDosH->pDosHeader->e_cblp << "\n";								//Bytes on last page of file
	cout << "Pages in file                    : " << std::dec << peDosH->pDosHeader->e_cp << "\n";									//Pages in file
	cout << "Relocations                      : " << std::dec << peDosH->pDosHeader->e_crlc << "\n";								//Relocations
	cout << "Size of header in paragraphs     : " << std::dec << peDosH->pDosHeader->e_cparhdr << "\n";								//Size of header in paragraphs
	cout << "Minimum extra paragraphs needed  : " << std::dec << peDosH->pDosHeader->e_minalloc << "\n";							//Minimum extra paragraphs needed
	cout << "Maximum extra paragraphs needed  : " << std::dec << peDosH->pDosHeader->e_maxalloc << "\n";							//Maximum extra paragraphs needed
	cout << "Initial (relative) SS value      : " << std::dec << peDosH->pDosHeader->e_ss << "\n";									//Initial (relative) SS value
	cout << "Initial SP value                 : " << std::dec << peDosH->pDosHeader->e_sp << "\n";									//Initial SP value
	cout << "Checksum                         : " << std::dec << peDosH->pDosHeader->e_csum << "\n";								//Checksum
	cout << "Initial IP value                 : " << std::dec << peDosH->pDosHeader->e_ip << "\n";									//Initial IP value
	cout << "Initial (relative) CS value      : " << std::dec << peDosH->pDosHeader->e_cs << "\n";									//Initial (relative) CS value
	cout << "File address of relocation table : " << std::dec << peDosH->pDosHeader->e_lfarlc << "\n";								//File address of relocation table
	cout << "Overlay number                   : " << std::dec << peDosH->pDosHeader->e_ovno << "\n";								//Overlay number
	cout << "Reserved words                   : " << std::dec << peDosH->pDosHeader->e_res[0]
		<< peDosH->pDosHeader->e_res[1] << peDosH->pDosHeader->e_res[2] << peDosH->pDosHeader->e_res[3] << "\n";					//Reserved words
	cout << "OEM identifier (for e_oeminfo)   : " << std::dec << peDosH->pDosHeader->e_oemid << "\n";								//OEM identifier (for e_oeminfo)
	cout << "OEM information; e_oemid specific: " << std::dec << peDosH->pDosHeader->e_oeminfo << "\n";								//OEM information; e_oemid specific
	cout << "File address of new exe header   : " << std::dec << peDosH->pDosHeader->e_lfanew << "\n" << "\n";								//File address of new exe header
}

void showHederNT_PE(PE_LDR_PARAM *peNTH)
{
	peNTH->pNtHeaders = (PIMAGE_NT_HEADERS)(((DWORD)peNTH->dwImage) + peNTH->pDosHeader->e_lfanew);
	if (peNTH->pNtHeaders->Signature != IMAGE_NT_SIGNATURE)
	{
		cout << "NT Signature mismatch";
		return;
	}

	//conver hex data time to standard time
	time_t    timeDateStamp = peNTH->pNtHeaders->FileHeader.TimeDateStamp;
	struct tm tstruct;
	char      buf[80];
	tstruct = *localtime(&timeDateStamp);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	//conver hex to char
	hexToChar.twoChar = peNTH->pNtHeaders->Signature;

	cout << "*********************************************************************HederNT" << "\n";
	cout << "Signature PE                    : " << hexToChar.character[0] << hexToChar.character[1] << "\n";								//Signature

	cout << "\n" << "##########################################FileHeader" << "\n";
	//IMAGE_FILE_HEADER
	cout << "Machine                         : " << ntHeadersMachine(&peNTH->pNtHeaders->FileHeader.Machine) << "\n";						//Machine
	cout << "Number Of Sections              : " << std::dec << peNTH->pNtHeaders->FileHeader.NumberOfSections << "\n";						//Number Of Sections
	cout << "Time Date Stamp                 : " << buf << "\n";																			//Time Date Stamp
	cout << "Pointer To Symbol Table         : " << std::dec << peNTH->pNtHeaders->FileHeader.PointerToSymbolTable << "\n";					//PointerToSymbolTable
	cout << "Number Of Symbols               : " << std::dec << peNTH->pNtHeaders->FileHeader.NumberOfSymbols << "\n";						//Number Of Symbols
	cout << "Size Of Optional Header         : " << std::dec << peNTH->pNtHeaders->FileHeader.SizeOfOptionalHeader << "\n";					//Size Of Optional Header
																																			//show flags Characteristics
	cout << "Characteristics                 : " << "\n";
	ntCharacteristics(&peNTH->pNtHeaders->FileHeader.Characteristics);																		//Characteristics
	cout << "##########################################OptionalHeader" << "\n";
	//IMAGE_OPTIONAL_HEADER
	ntMagic(&peNTH->pNtHeaders->OptionalHeader.Magic);																						//Magic
	cout << "Minor Linker Version            : " << std::dec << (unsigned int)peNTH->pNtHeaders->OptionalHeader.MinorLinkerVersion << "\n"; //Minor Linker Version
	cout << "Major Linker Version            : " << std::dec << (unsigned int)peNTH->pNtHeaders->OptionalHeader.MajorLinkerVersion << "\n"; //Major Linker Version
	cout << "Size Of Code                    : " << std::dec << peNTH->pNtHeaders->OptionalHeader.SizeOfCode << "\n";						//Size Of Code
	cout << "Size Of Initialized Data        : " << std::dec << peNTH->pNtHeaders->OptionalHeader.SizeOfInitializedData << "\n";			//Size Of Initialized Data
	cout << "Size Of Uninitialized Data      : " << std::dec << peNTH->pNtHeaders->OptionalHeader.SizeOfUninitializedData << "\n";			//Size Of Uninitialized Data
	cout << "Address Of Entry Point          : " << std::dec << peNTH->pNtHeaders->OptionalHeader.AddressOfEntryPoint << "\n";				//Address Of Entry Point
	cout << "Base Of Code                    : " << std::dec << peNTH->pNtHeaders->OptionalHeader.BaseOfCode << "\n";						//Base Of Code
	cout << "Image Base                      : " << std::dec << peNTH->pNtHeaders->OptionalHeader.ImageBase << "\n";						//Image Base
	cout << "Section Alignment               : " << std::dec << peNTH->pNtHeaders->OptionalHeader.SectionAlignment << "\n";					//Section Alignment
	cout << "File Alignment                  : " << std::dec << peNTH->pNtHeaders->OptionalHeader.FileAlignment << "\n";					//File Alignment
	cout << "Minor Operating System Version  : " << std::dec << peNTH->pNtHeaders->OptionalHeader.MinorOperatingSystemVersion << "\n";		//Minor Operating System Version
	cout << "Major Operating System Version  : " << std::dec << peNTH->pNtHeaders->OptionalHeader.MajorOperatingSystemVersion << "\n";		//Major Operating System Version
	cout << "Minor Image Version             : " << std::dec << peNTH->pNtHeaders->OptionalHeader.MinorImageVersion << "\n";				//Minor Image Version
	cout << "Major Image Version             : " << std::dec << peNTH->pNtHeaders->OptionalHeader.MajorImageVersion << "\n";				//Major Image Version
	cout << "Major Subsystem Version         : " << std::dec << peNTH->pNtHeaders->OptionalHeader.MajorSubsystemVersion << "\n";			//Major Subsystem Version
	cout << "Minor Subsystem Version         : " << std::dec << peNTH->pNtHeaders->OptionalHeader.MinorSubsystemVersion << "\n";			//Minor Subsystem Version
	cout << "Win32 Version Value             : " << std::dec << peNTH->pNtHeaders->OptionalHeader.Win32VersionValue << "\n";				//Win32 Version Value
	cout << "Size Of Image                   : " << std::dec << peNTH->pNtHeaders->OptionalHeader.SizeOfImage << "\n";						//Size Of Image
	cout << "Size Of Headers                 : " << std::dec << peNTH->pNtHeaders->OptionalHeader.SizeOfHeaders << "\n";					//Size Of Headers
	cout << "CheckSum                        : " << std::dec << peNTH->pNtHeaders->OptionalHeader.CheckSum << "\n";							//CheckSum
	ntsubsystem(&peNTH->pNtHeaders->OptionalHeader.Subsystem);																				//Sub system
	ntDllCharacteristics(&peNTH->pNtHeaders->OptionalHeader.DllCharacteristics);															//Dll Characteristics
	cout << "\n";
	cout << "Size Of Stack Reserve           : " << std::dec << peNTH->pNtHeaders->OptionalHeader.SizeOfStackReserve << "\n";				//Size Of Stack Reserve
	cout << "Size Of Stack Commit            : " << std::dec << peNTH->pNtHeaders->OptionalHeader.SizeOfStackCommit << "\n";				//Size Of Stack Commit
	cout << "Size Of Heap Reserve            : " << std::dec << peNTH->pNtHeaders->OptionalHeader.SizeOfHeapReserve << "\n";				//Size Of Heap Reserve
	cout << "Size Of Heap Commit             : " << std::dec << peNTH->pNtHeaders->OptionalHeader.SizeOfHeapCommit << "\n";					//Size Of Heap Commit
	cout << "Loader Flags                    : " << std::dec << peNTH->pNtHeaders->OptionalHeader.LoaderFlags << "\n";						//Loader Flags
	cout << "Number Of Rva And Sizes         : " << std::dec << peNTH->pNtHeaders->OptionalHeader.NumberOfRvaAndSizes << "\n";				//Number Of Rva And Sizes
	ntDataDirectory(peNTH->pNtHeaders->OptionalHeader.DataDirectory);																		//Data Directory
}

void fragmentation()
{
	HANDLE hFile, hFileMap;
	DWORD dwImportDirectoryVA, dwSectionCount, dwSection = 0, dwRawOffset;
	LPVOID lpFile;
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeaders;
	PIMAGE_SECTION_HEADER pSectionHeader;
	PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;
	PIMAGE_THUNK_DATA pThunkData;

	hFile = CreateFile(pathFile.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	hFileMap = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, 0);
	lpFile = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);
	pDosHeader = (PIMAGE_DOS_HEADER)lpFile;
	pNtHeaders = (PIMAGE_NT_HEADERS)((DWORD)lpFile + pDosHeader->e_lfanew);
	dwSectionCount = pNtHeaders->FileHeader.NumberOfSections;
	dwImportDirectoryVA = pNtHeaders->OptionalHeader.DataDirectory[1].VirtualAddress;
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeaders + sizeof(IMAGE_NT_HEADERS));
	for (; dwSection < dwSectionCount && pSectionHeader->VirtualAddress <= dwImportDirectoryVA; pSectionHeader++, dwSection++);
	pSectionHeader--;
	dwRawOffset = (DWORD)lpFile + pSectionHeader->PointerToRawData;
	pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(dwRawOffset + (dwImportDirectoryVA - pSectionHeader->VirtualAddress));
	cout << "\n" << "*************************************************** IAT" << "\n";
	for (; pImportDescriptor->Name != 0; pImportDescriptor++)
	{
		char* temp = (char *)dwRawOffset + (pImportDescriptor->Name - pSectionHeader->VirtualAddress);
		cout << "DLL Name : " << temp << "\n";
		
		pThunkData = (PIMAGE_THUNK_DATA)(dwRawOffset + (pImportDescriptor->FirstThunk - pSectionHeader->VirtualAddress));
		for (; pThunkData->u1.AddressOfData != 0; pThunkData++)
			printf("\tFunction : %s\n", (dwRawOffset + (pThunkData->u1.AddressOfData - pSectionHeader->VirtualAddress + 2)));
	}
	UnmapViewOfFile(lpFile);
	CloseHandle(hFileMap);
	CloseHandle(hFile);
}

int main()
{
	PE_LDR_PARAM peAnliz;
	
	int sizefile;

	cout << "Enter Address your PE file to analyz (example : file.exe) : ";
	cin >> pathFile;

	system("cls");

	//Fill in buffer with pe file
	ifstream file(pathFile, ios::in | ios::binary | ios::ate);
	file.seekg(0, ios::end);
	sizefile = file.tellg();
	file.seekg(0, ios::beg);
	char* buffer = new char[sizefile];
	file.read(buffer, sizefile);
	file.close();

	//Fill in PE_LDR_PARAM
	peAnliz.dwImageSizeOnDisk = sizefile;
	peAnliz.dwImage = (DWORD)buffer;
	peAnliz.pDosHeader = (PIMAGE_DOS_HEADER)peAnliz.dwImage;

	//Call fanction output heder Dos
	showHederDos_PE(&peAnliz);
	//Call fanction output heder NT
	showHederNT_PE(&peAnliz);
	//Call fanction section header
	sectionHeader(&peAnliz);

	fragmentation();

	delete buffer;
	buffer = NULL;

	system("pause");
	return 0;
}