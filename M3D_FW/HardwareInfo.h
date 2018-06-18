#pragma once


namespace m3dfw
{
	class HardwareInfo
	{
	public:

		static HardwareInfo & getInstance(); //Singleton

		unsigned int getCPUCacheLineSize();

	private:

		HardwareInfo();
		~HardwareInfo();

		unsigned int _cpu_cl_sz;
	};
}


