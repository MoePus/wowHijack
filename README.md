# wowHijack
Run some secret code invisible from debugger single step.(x86 process on x64 windows only)

---
Only do a simple WriteProcessMemory API call。
```C++
//Codes...
WriteProcessMemory((HANDLE)-1, &ctx->Eip, &target, 4, 0);
//Codes...
```
Then a messagebox jumps out!

And No inline/IAT hook && No code self modify.
