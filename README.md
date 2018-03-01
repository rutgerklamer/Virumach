# Virumach
Virumach is a virtual machine, it has got a stack and a small register

To program something for the vm follow this guide:


### Arguments
| Arguments | Explanation |
| --------- | ----------- |
| N | N is any number you want |
| NS| NS is the same as N, except you can set N directly behind each other (PSH 1 2 3)|
| R | Register number, 10 for stack pointer, 11 for program counter |
|N/A| There should be nothing here |


### Cell manipulation
| Operation | Arguments | Explanation |
| ----------- | ----------- | ----------- |
| PSH |  NS | Push NS to the stack |
| POP | N | POP N amount of values from the top of the stack |
| ADD |  N/A  | Consume the top two values and add them together |
| SUB |  N/A  | Consume the top two values and subtract them from eachother |
| MULT |  N/A  | Consume the top two values and multiply them  |
| DIV |  N/A  | Consume the top two values and divide them  |
| MOD |  N/A  | Consume the top two values and apply modulus to them |
| SWAP | N/A | Swap the place of the top two values on the stack |
| SET | R, N | Set value N to register R |
| MV | R, R | Move the value of register R(1) to R(2) |
| PSHSTCK | R | Push value of register R to the top of the stack |
| PSHREG | R | Push the value of the top of the stack to register R|
| IF | N/A | Goes through this code as long as the top of the stack != 0 |
| IFE | N | Goes through this code as long as the top of the stack == N |
| IFNE | N | Goes through this code as long as the top of the stack != N |
| ENDIF | N/A | End of the if statement |
| PRNTR | N | Print N amount of raw values counting from the top of the stack |
| PRNTA | N | Print N amount of ASCII values counting from the top of the stack |
| HALT | N/A | End the program |
| " | N/A | Use one " to start a string, every raw value of the chars inside will get pushed to the stack (from left to right) till there is another " sign |


### Example program
```Assembly
PSH 36 
PSH 36 
ADD 
PRNTA 
HALT 
```

This is the resulting stack:

|          |  STEP 1 |   STEP 2  |  STEP 3 |  STEP 4 |  STEP 5 |
| :-:      |   :-:   |    :-:    |   :-:   |   :-:   |   :-:   |
| STACK #1 |   0     |    36  <- |   0     |    0    |    0    |
| STACK #0 |   36 <- |    36     |   72 <- |  72 <-  |   72 <- |
| CODE:    | PSH 36  |   PSH 36  |   ADD   |   PRNTA |  HALT   |  
| OUTPUT:  |         |           |         |    H    |    H    |  
