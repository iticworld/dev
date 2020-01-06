# RET (RETURN FROM PROCEDURE)

| OPCODE  | INSTRUCTION | OP/EN | 64 BIT MODE | COMPAT/LEG MODE | DESCRIPTION                                                     |
| ------- | ----------- | ----- | ----------- | --------------- | --------------------------------------------------------------- |
| C3      | RET         | ZO    | VALID       | VALID           | NEAR RETURN TO CALLING PROCEDURE                                |
| CB      | RET         | ZO    | VALID       | VALID           | FAR RETURN TO CALLING PROCEDURE                                 |
| C2 _IW_ | RET _IMM16_ | I     | VALID       | VALID           | NEAR RETURN TO CALLING PROCEDURE AND POP IMM16 BYTES FROM STACK |
| CA _IW_ | RET _IMM16_ | I     | VALID       | VALID           | FAR RETURN TO CALLING PROCEDURE AND POP IMM16 BYTES FROM STACK  |

## INSTRUCTION OPERAND ENCODING

| OP/EN | OPERAND[0] | OPERAND[1] | OPERAND[2] | OPERAND[3] |
| ----- | ---------- | ---------- | ---------- | ---------- |
| ZO    | NA         | NA         | NA         | NA         |
| I     | IMM16      | NA         | NA         | NA         |

## DESCRIPTION

Transfers program control to a return address located on the top of the stack.
The address is usually placed on the stack by CALL instruction, and the return is made to the instruction that follows the CALL instruction.

The optional source operand specifies the number of stack bytes to be released after the return address is popped; the default is none.
This operand can be used to release parameters from the stack that were passed to the called procedure and are no longer needed.
It must be used when the CALL instruction used to switch to a new procedure uses a call gate with an non-zero word count to access the new procedure. Here, the source operand for the RET instruction must specify the same number of bytes as is specified in the word count field of the call gate.

- near return - a return to calling procedure within the current code segment (the segment currently pointed to by the CS register), sometimes referred to as an intra-segment return.
- far return - a return to calling procedure located in a different segment that the current code segment, sometimes referred to as an inter-segment return.
- inter-privilege-level far return -  a far return to a different privilege level that of the currently executing program or procedure.

The inter-privilege-level return type can only be executed in protected mode. See the section titled "Call Procedures Using Call and RET" in Chapter 6 of the Intel 64 and IA-32 Architectures Software Developer's Manual, Volume 1, for detailed information on near, far, and inter-privilege-level returns.

When executing a near return, the processor pops the return instruction pointer from the top of the stack into the EIP register and begins program execution at the new instruction pointer. The CS register is unchanged.

When executing a far return, the processor pops the return instruction pointer (offset) from the top of the stack into the EIP register, then pops the segment selector from the top of the stack into the CS register. The processor then begins program execution in the new code segment at the new instruction pointer.

The mechanics of an inter-privilege-level far return are similar to an inter-segment return, except that the processor examines the privilege levels and access rights of the code and stack segments being returned to determine if the control transfer is allowed to be made. The DS, ES, FS, and GS segments registers are cleared by the RET instruction during an inter-privilege-level return if they refer to segments that are not allowed to be accessed at the new privilege level. Since a stack switch also occurs on an inter-privilege level return, the ESP and SS registers are loaded from the stack.

If parameters are passed to the called procedure during an inter-privilege level call, the optional source operand must be used with the RET instruction to release the parameters on the return. Here, the parameters are released both from the called procedure;s stack and the calling procedure's stack (that is, the stack being returned to).

In 64-bit mode, the default operation size of this instruction is the stack-address size, i.e. 64 bits. This applies to near returns, not far returns; the default operation size of far returns is 32 bits.

## OPERATION

```
IF INSTRUCTION == NEAR RETURN THEN
    IF OPERAND SIZE == 32 TEHN
        IF TOP 4 BYTES OF STACK NOT WITHIN STACK LIMITS THEN
            #SS(0)
        END
    ELSE
        IF OPERAND SIZE == 64 THEN
            IF TOP 8 BYTES OF STACK NOT WITHIN STACK LIMITS THEN
                #SS(0)
            END
            RIP = POP()
        ELSE
            IF TOP 2 BYTES OF STACK NOT WITHIN STACK LIMITS THEN
                #SS(0)
            END
            TEMP EIP = POP()
            TEMP EIP = TEMP EIP AND 0000FFFFH
            IF TEMP EIP NOT WITHIN CODE SEGMENT LIMITS THEN
                #GP(0)
            END
            EIP = TEMP EIP
        END
    END
END

IF INSTRUCTION HAS
```
