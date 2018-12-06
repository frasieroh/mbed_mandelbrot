    AREA drawASM, CODE, READONLY
    EXPORT escapeTime

; ASM subroutine of escape time algorithm
escapeTime
    ; R0 contains cX
    ; R1 contains cY
    ; R2 contains maxiters
    ; R3 contains counter
    ; R4 contains zX
    ; R5 contains zY
    ; R6 contains temporary zX
    ; R7 Lo
    ; R8 Hi - registers for SMULL/SMLAL
    ; R9 Lo
    ; R10 Hi - registers for SMULL/SMLLA
    ; R11 contains 2: const for FMA
    ; R12 contains 67108864: const for comparison
    PUSH    {R4, R5, R6, R7, R8, R9, R10, R11, R12}
    MOV     R3, #0
    MOV     R4, R0
    MOV     R5, R1
    MOV     R11, #2
    MOV     R12, #67108864
iterate_loop_start
    CMP     R3, R2              ; exit loop if counter >= maxiters
    BGE     iterate_loop_end
    SMULL   R7, R8, R4, R4      ; compute zx = zx * zx - zy * zy + cx
    SMULL   R9, R10, R5, R5
    ; R7:R8 = R7:R8 - R9:R10
    SUBS    R7, R9
    SBC     R8, R10
    LSL     R8, #4              ; perform right shift by 28 places on R7:R8
    ASR     R7, #28
    BFI     R8, R7, #0, #4
    ADD     R6, R8, R0
    SMULL   R7, R8, R4, R5      ; compute zy = 2*zx*zy + cy
    LSL     R8, #4              ; perform right shift by 28 places on R7:R8
    ASR     R7, #28
    BFI     R8, R7, #0, #4
    MLA     R5, R8, R11, R1
    MOV     R4, R6
    SMULL   R7, R8, R4, R4      ; check escape condition
    SMLAL   R7, R8, R5, R5
    CMP     R8, R12             ; sufficient to check only high-order bits
    BGE     iterate_loop_end
    ADD     R3, #1
    B       iterate_loop_start
iterate_loop_end
    ; move counter to R0 as the ret value
    MOV     R0, R3
    POP     {R4, R5, R6, R7, R8, R9, R10, R11, R12}
    BX      LR
    END