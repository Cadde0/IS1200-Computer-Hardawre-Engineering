  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

hexasc: .global
    andi     $t0,$a0,0xF
    
    addi     $v0,$t0,0x30
    
    jr    $ra
    nop
.global delay
delay:

    move    $t1, $a0
    li    $t3, 1000
    
    while:
        blez    $t1, delayExit
        nop
        sub    $t1, $t1, 1
        
    li    $t2, 0
    for:
        bge    $t2, $t3, while
        nop
        addi    $t2, $t2, 1
        j    for
        nop
        
    delayExit:
        jr    $ra
        nop
.global time2string
time2string:
   PUSH    $ra
   PUSH    $s0
   PUSH    $s1
   move    $s1, $a1
   move    $s0, $a0
   
   #Första Siffran
   andi    $t1, $s1, 0xF000
   srl    $a0, $t1, 12
   jal    hexasc
   nop
   sb    $v0, ($s0)
   
   #Andra Siffran
   andi    $t1, $s1, 0x0F00
   srl    $a0, $t1, 8
   jal    hexasc
   nop
   sb    $v0, 1($s0)
   
   #Colon
   li    $t1, 0x3a
   nop
   sb    $t1, 2($s0)
   
   #Tredje Siffran
   andi    $t1, $s1, 0x00F0
   srl    $a0, $t1, 4
   jal    hexasc
   nop
   sb    $v0, 3($s0)
   
   #Fjärde Siffran
   andi    $t1, $s1, 0x000F
   move    $a0, $t1
   jal    hexasc
   nop
   sb    $v0, 4($s0)
   

   #NUll
   li    $t1, 0x00
   sb    $t1, 5($s0)
   
   
   POP    $s1
   POP    $s0
   POP    $ra
   jr    $ra
   nop

