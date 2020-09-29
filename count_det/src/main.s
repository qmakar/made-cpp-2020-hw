.globl count_det

count_det:
.fnstart


ldr r2, [r0]
ldr r3, [r0, $16]
ldr r4, [r0, $32]
mul r5, r2, r3
mul r5, r4, r5

ldr r2, [r0, $8]
ldr r3, [r0, $12]
ldr r4, [r0, $28]
mul r6, r2, r3
mul r6, r4, r6
add r5, r5, r6

ldr r2, [r0, $4]
ldr r3, [r0, $20]
ldr r4, [r0, $24]
mul r6, r2, r3
mul r6, r4, r6
add r5, r5, r6

ldr r2, [r0, $8]
ldr r3, [r0, $16]
ldr r4, [r0, $24]
mul r6, r2, r3
mul r6, r4, r6
sub r5, r5, r6

ldr r2, [r0, $4]
ldr r3, [r0, $12]
ldr r4, [r0, $32]
mul r6, r2, r3
mul r6, r4, r6
sub r5, r5, r6

ldr r2, [r0]
ldr r3, [r0, $20]
ldr r4, [r0, $28]
mul r6, r2, r3
mul r6, r4, r6
sub r5, r5, r6

mov r0, r5
bx lr
.fnend

