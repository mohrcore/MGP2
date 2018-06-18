#include "HardwareInfo.h"

#ifdef WINDOWS
#include <Windows.h>
#endif

m3dfw::HardwareInfo::HardwareInfo() : _cpu_cl_sz(0)
{
}

m3dfw::HardwareInfo::~HardwareInfo()
{
}

m3dfw::HardwareInfo & m3dfw::HardwareInfo::getInstance()
{
	static m3dfw::HardwareInfo hi;

	return hi;
}

#ifdef WINDOWS

unsigned int m3dfw::HardwareInfo::getCPUCacheLineSize()
{
	if (_cpu_cl_sz != 0)
		return _cpu_cl_sz;

	size_t line_size = 0;

	DWORD buffer_sz = 0;

	SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer = nullptr;
	GetLogicalProcessorInformation(0, &buffer_sz);
	buffer = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[buffer_sz / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION)];
	GetLogicalProcessorInformation(buffer, &buffer_sz);

	for(DWORD i = 0; i < buffer_sz / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); i++)
		if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1)
		{
			line_size = buffer[i].Cache.LineSize;
			break;
		}

	_cpu_cl_sz = line_size;

	delete buffer;

	return line_size;
}

#endif