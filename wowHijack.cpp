#include <windows.h>
#include <winternl.h>

CONTEXT* getShadowContext()
{
	auto teb = __readfsdword((DWORD)(&static_cast<NT_TIB*>(nullptr)->Self));
	auto teb64 = teb - 0x2000;
	auto ctx = *(DWORD*)(teb64 + 0x1488) + 4;
	return (CONTEXT*)ctx;
}

long _stdcall hiJackRoutine(DWORD, DWORD, DWORD, DWORD, DWORD)
{
	MessageBoxA(0, "RoutineControlled", "Hi Jack!", 0);
	return 0;
}

int main()
{
	auto ctx = getShadowContext();
	DWORD target = (DWORD)hiJackRoutine;
	WriteProcessMemory((HANDLE)-1, &ctx->Eip, &target, 4, 0);
	ExitProcess(0);
}
