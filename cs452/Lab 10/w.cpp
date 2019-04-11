/************************************************************************************************
* Lab 10 - CIS 452
*
* A windows-focused programming assignment that will explore the memory of a windows machine.
*
* @author Ron Rounsifer
************************************************************************************************/
//#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <stdlib.h>

int main() 
{
	// Page size
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	std::cout << "Page size: " << sys_info.dwPageSize << " Bytes" << std::endl;

	// Allocate memory
	char *allocated_mem;
	allocated_mem = malloc(1024 * 1024);
	std::cout << "1M bytes of memory allocated.\n\n" << std::endl;
	
	// Query system
	// Determine state of allocated memory
	MEMORY_BASIC_INFORMATION mem_info;
	VirtualQuery(allocated_mem, &mem_info, sizeof(mem_info));	
	switch (mem_info.State)
	{
		case MEM_COMMIT:
			std::cout << "Memory state: Committed. " << std::endl;
			break;
		case MEM_RESERVE:
			std::cout << "Memory state: Reserved. " << std::endl;
			break;
		case MEM_FREE:
			std::cout << "Memory state: Free. " << std::endl;			
			break;
	}


	// Free memory
	free(str);
	std::cout << "\n\nMemory freed.\n\n << std::endl;


	// Query system after freeing memory
	// Determine state of allocated memory
	VirtualQuery(allocated_mem, &mem_info, sizeof(mem_info));	
	switch (mem_info.State)
	{
		case MEM_COMMIT:
			std::cout << "Memory state: Committed. " << std::endl;
			break;
		case MEM_RESERVE:
			std::cout << "Memory state: Reserved. " << std::endl;
			break;
		case MEM_FREE:
			std::cout << "Memory state: Free. " << std::endl;			
			break;
	}
	
	return 0;
}
