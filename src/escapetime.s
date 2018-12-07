    AREA drawASM, CODE, READONLY
    EXPORT escapeTime

; ASM subroutine of escape time algorithm
; R0 contains cx
; R1 contains cy
; R2 contains maxiters
; R3 contains counter
; R4 contains zx
; R5 contains zy
; R6 contains 4 << 24 = 67108864 escape CMP
; R7 Lo
; R8 Hi registers for SMULL for zx^2
; R9 Lo
; R10 Hi registers for SMULL for zy^2
; R11 Lo 
; R12 Hi are scratch registers
escapeTime
    PUSH    {R4, R5, R6, R7, R8, R9, R10, R11, R12}
    MOV     R3, #0
    MOV     R4, R0
    MOV     R5, R1
    MOV     R6, #67108864
iterate_loop_start
    CMP     R3, R2              ; Exit loop if counter >= maxiters
    BGE     iterate_loop_end
    SMULL   R7, R8, R4, R4      ; Compute zx^2 and zy^2
    SMULL   R9, R10, R5, R5     ; R7:R8 = zx^2 R9:R10 = zy^2
    ADD     R12, R8, R10        ; Only check zx^2 + zy^2 < 4 with high-order
    CMP     R12, R6             ; bits. Okay to ignore low order sum and carry
    BGE     iterate_loop_end    ; Escape condition
    SMULL   R11, R12, R4, R5    ; Compute zy = 2*zx*zy + cy
    ASR     R11, #28            ; Perform right shift by 28 places on R11:R12
    BFI     R11, R12, #4, #28
    LSL     R11, #1             ; Multiply by 2
    ADD     R5, R11, R1         ; Add cy and store in R5 
    SUBS    R11, R7, R9         ; Compute zx = zx^2 - zy^2 + cx
    SBC     R12, R8, R10    
    ASR     R11, #28            ; Perform right shift by 28 places on R11:R12
    BFI     R11, R12, #4, #28
    ADD     R4, R11, R0         ; Add cx and store in R4
    ADD     R3, #1              ; Increment counter and loop
    B       iterate_loop_start
iterate_loop_end
    ; Move counter to R0 as the ret value
    MOV     R0, R3
    POP     {R4, R5, R6, R7, R8, R9, R10, R11, R12}
    BX      LR
    END
