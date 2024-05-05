EXTERN getLoadLibraryA :proc
.CODE
WorkCallbackA PROC

    call getLoadLibraryA

    sub rsp,(5*8) 
    mov rcx, rdx
    xor rdx, rdx
    call rax
    add rsp,(5*8)
    ret
WorkCallbackA ENDP
END