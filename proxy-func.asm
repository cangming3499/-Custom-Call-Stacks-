.CODE
WorkCallback PROC
    mov rax, rdx               
   
    mov rcx, qword ptr [rax + 8h]         
    mov rdx, qword ptr [rax + 10h]       
    xor r8, r8                 
    mov r9, qword ptr [rax + 18h]       


    mov r10, [rax + 20h]       
    mov [rsp+28h], r10        
    mov r10, 3000h             
    mov [rsp+20h], r10        

    mov rax, [rax]
    
    call rax
    
    ret
WorkCallback ENDP
END
