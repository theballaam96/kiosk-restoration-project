.n64
.open "rom/dk64-kioskrestoration-dev.z64", 0

.include "asm/symbols.asm" ; Tell armips' linker where to find the game's function(s)

; Patch boot routine to DMA our code from ROM to RAM and run it
.definelabel bootStart, 0x02080000 ; DO NOT CHANGE LOWER 4 BYTES. HAS TO BE 0000
.definelabel codeStart, 0x807C0000

; TODO: This
;.orga 0x1292C ; ROM
;.org 0x805A192C ; RDRAM
;NOP ; CRC Patch ; TODO: Can this be removed if correct gzip footers are written to all compressed files?

.orga 0x1878 ; ROM
.org 0x80590878 ; RDRAM

modifiedBootCode:
	; copyfromrom args
	; arg0 = rom_start
	; arg1 = rdram_start
	; arg2 = &size
	; arg 3, 4, 5 = 0
	; 12 instructions max for entrypoint
	lui $a0, hi(bootStart)
	lui $a1, hi(codeStart)
	addiu $a1, $a1, lo(codeStart)
	lui $a2, 0x4 ; 0x40000 bytes ; todo: stack thing
	sw $a2, 0x20 ($sp)
	addiu $a2, $sp, 0x20
	or $a3, $zero, $zero
	sw $zero, 0x10 ($sp)
	jal 0x805a26e0
	sw $zero, 0x14 ($sp)
	j displacedVanillaBootCode
	nop

resumeVanillaBootCode:

.orga bootStart ; ROM
.org codeStart ; RDRAM

displacedVanillaBootCode:
	; write hook
	lui $t2, hi(mainASMFunctionJump)
	lw $t2, lo(mainASMFunctionJump) ($t2)
	lui $at, 0x8059
	sw $t2, 0x0C14 ($at) ; Store per frame hook
	; vanilla code
	addiu $t2, $zero, 5
	lui $at, 0x8073
	jal 0x805A5020
	sw $t2, 0xCDC4 ($at)
	jal 0x805A1EC0
	nop
	jal 0x80594CD0 ; init audio engine
	nop
	jal 0x806E6550 ; osWritebackDCacheAll
	nop
	lw $ra, 0x1C ($sp)
	addiu $sp, $sp, 0x28
	jr $ra
	nop

mainASMFunction:
	jal	0x80590D00
	nop
	jal cFuncLoop
	nop
	j 0x80590C1C
	nop

mainASMFunctionJump:
	J mainASMFunction ; Instruction copied and used as a hook
	NOP

.align 0x10

.include "asm/objects.asm"
.close