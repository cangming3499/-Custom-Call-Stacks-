#include <windows.h>
#include <stdio.h>

typedef NTSTATUS(NTAPI* TPALLOCWORK)(PTP_WORK* ptpWrk, PTP_WORK_CALLBACK pfnwkCallback, PVOID OptionalArg, PTP_CALLBACK_ENVIRON CallbackEnvironment);
typedef VOID(NTAPI* TPPOSTWORK)(PTP_WORK);
typedef VOID(NTAPI* TPRELEASEWORK)(PTP_WORK);

FARPROC pLoadLibraryA;

EXTERN_C UINT_PTR getLoadLibraryA() {
    return (UINT_PTR)pLoadLibraryA;
}

EXTERN_C VOID CALLBACK WorkCallbackA(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WORK Work);

//VOID CALLBACK WorkCallback(
//    _Inout_     PTP_CALLBACK_INSTANCE Instance,
//    _Inout_opt_ PVOID                 Context,
//    _Inout_     PTP_WORK              Work
//) {
//    LoadLibraryA((LPCSTR)Context);
//}


int main() {
    pLoadLibraryA = GetProcAddress(GetModuleHandleA("kernel32"), "LoadLibraryA");

    //线程池工作项函数

    FARPROC pTpAllocWork = GetProcAddress(GetModuleHandleA("ntdll"), "TpAllocWork");      //    TpAllocWork : 分配一个线程池工作项。
    FARPROC pTpPostWork = GetProcAddress(GetModuleHandleA("ntdll"), "TpPostWork");       //    TpPostWork : 提交线程池工作项，使其排队等待执行。
    FARPROC pTpReleaseWork = GetProcAddress(GetModuleHandleA("ntdll"), "TpReleaseWork"); //    TpReleaseWork : 释放线程池工作项的资源。

    CHAR* libName = (char*)"wininet.dll";
    PTP_WORK WorkReturn = NULL;


    // 创建一个线程池任务，执行回调函数   WorkCallback，回调函数的参数 是libName，创建任务句柄到  WorkReturn
    ((TPALLOCWORK)pTpAllocWork)(&WorkReturn, (PTP_WORK_CALLBACK)WorkCallbackA, libName, NULL);
    ((TPPOSTWORK)pTpPostWork)(WorkReturn);  // 提交任务
    ((TPRELEASEWORK)pTpReleaseWork)(WorkReturn);//释放 任务

    WaitForSingleObject((HANDLE)-1, 0x1000);
    printf("hWininet: %p\n", GetModuleHandleA(libName));   // 检测dll是否被正常加载

    system("pause");
    return 0;
}