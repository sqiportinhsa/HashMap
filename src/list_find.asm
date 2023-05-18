section .text
global list_find

list_find:
        mov     r8, QWORD [rdi+8]           ; r8 = list->size
        test    r8, r8
        je      .nullptr_exit               ; if (list->size == 0) return nullptr

        mov     rdi, QWORD [rdi+16]

        vmovdqu ymm0, yword   [rdi]         ; ymm0 = list->nodes[0].key
        vmovdqu ymm1, yword   [rsi]         ; ymm1 = key
        vptest  ymm0, ymm1
        mov eax, 0
        setnc al                            ; if strcmp(ymm0, ymm1) = 0 { eax = 1 } else { eax = 0 }

        test    eax, eax                    ; if (!strcmp(list->nodes[0].key, key))
        je      .exit                       ;      return list->nodes[0].key

        lea     rax, [rdi+40]               ; rax -> list->nodes[1]
        xor     edx, edx                    ; i = 0
        jmp     .check_end_of_loop

    .nodes_loop:
        mov     rdi, rax
        vmovdqu ymm0, yword   [rax]         ; ymm0 = list->nodes[i].key
        vmovdqu ymm1, yword   [rsi]         ; ymm1 = key
        vptest  ymm0, ymm1                  ; strcmp(ymm0, ymm1)
        xor     ecx, ecx
        setnc   cl                          ; if strcmp(ymm0, ymm1) = 0 { ecx = 1 } else { ecx = 0 }

        add     rax, 40                     ; rax to next node
        test    ecx, ecx                    ; if (!strcmp(list->nodes[i].key, key))
        je      .exit                       ;      return list->nodes[i].key

    .check_end_of_loop:                     ; if (i < list->size) break
        inc     rdx                         ; ++i
        cmp     rdx, r8                     ; if (i == list->size) return nullptr
        jne     .nodes_loop

    .nullptr_exit:                          ; return nullptr if node isn't found
        xor     eax, eax
        ret

    .exit:                                  ; return node
        mov     rax, QWORD [rdi+32]
        ret