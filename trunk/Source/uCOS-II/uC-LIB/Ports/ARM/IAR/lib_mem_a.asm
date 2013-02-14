;********************************************************************************************************
;                                               uC/LIB
;                                       CUSTOM LIBRARY MODULES
;
;                          (c) Copyright 2004-2007; Micrium, Inc.; Weston, FL
;
;               All rights reserved.  Protected by international copyright laws.
;
;               uC/LIB is provided in source form for FREE evaluation, for educational
;               use or peaceful research.  If you plan on using uC/LIB in a commercial
;               product you need to contact Micrium to properly license its use in your
;               product.  We provide ALL the source code for your convenience and to
;               help you experience uC/LIB.  The fact that the source code is provided
;               does NOT mean that you can use it without paying a licensing fee.
;
;               Knowledge of the source code may NOT be used to develop a similar product.
;
;               Please help us continue to provide the Embedded community with the finest
;               software available.  Your honesty is greatly appreciated.
;********************************************************************************************************


;********************************************************************************************************
;
;                                     STANDARD MEMORY OPERATIONS
;
;                                               ARM
;                                           IAR Compiler
;
;
; Filename      : lib_mem_a.asm
; Version       : V1.24
; Programmer(s) : JDH
;********************************************************************************************************
; Note(s)       : (1) NO compiler-supplied standard library functions are used in library or product software.
;
;                     (a) ALL standard library functions are implemented in the custom library modules :
;
;                         (1) \<Custom Library Directory>\lib*.*
;
;                         (2) \<Custom Library Directory>\Ports\<cpu>\<compiler>\lib*_a.*
;
;                               where
;                                       <Custom Library Directory>      directory path for custom library software
;                                       <cpu>                           directory name for specific processor (CPU)
;                                       <compiler>                      directory name for specific compiler
;
;                     (b) Product-specific library functions are implemented in individual products.
;
;                 (2) Assumes ARM CPU mode configured for Little Endian.
;********************************************************************************************************


;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

        PUBLIC  Mem_Copy


;********************************************************************************************************
;                                      CODE GENERATION DIRECTIVES
;********************************************************************************************************

        RSEG CODE:CODE:NOROOT(2)
        CODE32


;$PAGE
;********************************************************************************************************
;                                             Mem_Copy()
;
; Description : Copy data octets from one buffer to another buffer.
;
; Argument(s) : pdest       Pointer to destination memory buffer.
;
;               psrc        Pointer to source      memory buffer.
;
;               size        Number of data buffer octets to copy.
;
; Return(s)   : none.
;
; Caller(s)   : various.
;
; Note(s)     : (1) Null copies allowed (i.e. 0-octet size).
;
;               (2) Memory buffers NOT checked for overlapping.
;
;               (3) Modulo arithmetic is used to determine whether a memory buffer starts on a 'CPU_ALIGN'
;                   address boundary.
;********************************************************************************************************

; void  Mem_Copy (void        *pdest,       ;  ==>  R0
;                 void        *psrc,        ;  ==>  R1
;                 CPU_SIZE_T   size)        ;  ==>  R2

Mem_Copy:
        CMP         R0, #0
        BNE         Mem_Copy_1
        BX          LR                      ; return if pdest == NULL

Mem_Copy_1:
        CMP         R1, #0
        BNE         Mem_Copy_2
        BX          LR                      ; return if psrc  == NULL

Mem_Copy_2:
        CMP         R2, #0
        BNE         Mem_Copy_3
        BX          LR                      ; return if size  == 0

Mem_Copy_3:
        STMFD       SP!, {R3-R12}           ; save registers on stack


;$PAGE
Chk_Align_32:                               ; check if both dest & src 32-bit aligned
        AND         R3, R0, #0x03
        AND         R4, R1, #0x03
        CMP         R3, R4
        BNE         Chk_Align_16            ; not 32-bit aligned, check for 16-bit alignment

        RSB         R3, R3, #0x04           ; compute 1-2-3 pre-copy bytes (to align to the next 32-bit boundary)
        AND         R3, R3, #0x03

Pre_Copy_1:
        CMP         R3, #1                  ; copy 1-2-3 bytes (to align to the next 32-bit boundary)
        BCC         Copy_32_1               ; start real 32-bit copy
        CMP         R2, #1                  ; check if any more data to copy
        BCC         Mem_Copy_END            ;           no more data to copy

        LDRB        R4, [R1], #1
        STRB        R4, [R0], #1
        SUB         R3, R3, #1
        SUB         R2, R2, #1
        B           Pre_Copy_1


Chk_Align_16:                               ; check if both dest & src 16-bit aligned
        AND         R3, R0, #0x01
        AND         R4, R1, #0x01
        CMP         R3, R4
        BNE         Copy_08_1               ; not 16-bit aligned, start 8-bit copy

Pre_Copy_2:
        CMP         R3, #1                  ; copy 1 byte (to align to the next 16-bit boundary)
        BCC         Copy_16_1               ; start real 16-bit copy

        LDRB        R4, [R1], #1
        STRB        R4, [R0], #1
        SUB         R3, R3, #1
        SUB         R2, R2, #1
        B           Pre_Copy_2


Copy_32_1:
        CMP         R2, #(04*10*09)         ; Copy 9 chunks of 10 32-bit words (360 octets per loop)
        BCC         Copy_32_2
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        SUB         R2, R2, #(04*10*09)
        B           Copy_32_1

Copy_32_2:
        CMP         R2, #(04*10*01)         ; Copy chunks of 10 32-bit words (40 octets per loop)
        BCC         Copy_32_3
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        SUB         R2, R2, #(04*10*01)
        B           Copy_32_2

Copy_32_3:
        CMP         R2, #(04*01*01)         ; Copy remaining 32-bit words
        BCC         Copy_16_1
        LDR         R3, [R1], #4
        STR         R3, [R0], #4
        SUB         R2, R2, #(04*01*01)
        B           Copy_32_3

;$PAGE
Copy_16_1:
        CMP         R2, #(02*01*16)         ; Copy chunks of 16 16-bit words (32 bytes per loop)
        BCC         Copy_16_2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        SUB         R2, R2, #(02*01*16)
        B           Copy_16_1

Copy_16_2:
        CMP         R2, #(02*01*01)         ; Copy remaining 16-bit words
        BCC         Copy_08_1
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        SUB         R2, R2, #(02*01*01)
        B           Copy_16_2

;$PAGE
Copy_08_1:
        CMP         R2, #(01*01*16)         ; Copy chunks of 16 8-bit words (16 bytes per loop)
        BCC         Copy_08_2
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        SUB         R2, R2, #(01*01*16)
        B           Copy_08_1

Copy_08_2:
        CMP         R2, #(01*01*01)         ; Copy remaining 8-bit words
        BCC         Mem_Copy_END
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        SUB         R2, R2, #(01*01*01)
        B           Copy_08_2


Mem_Copy_END:
        LDMFD       SP!, {R3-R12}           ; restore registers from stack
        BX          LR                      ; return


        END

