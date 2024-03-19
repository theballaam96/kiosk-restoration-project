START_HOOK:
fix_diddy_japes_crash:
    lh $a0, 0x2a ($sp)
    jal getSpawnerFlag_fixed
    addiu $a2, $sp, 0x20
    j 0x806d4de0
    nop

fix_crossmap_crash:
    lbu $t3, 0x1b ($sp)
    beq $t3, $zero, fix_crossmap_crash_not_found
    lw $t5, 0x1c ($sp)
    j 0x805942F4
    lui $t7, 0x8073

    fix_crossmap_crash_not_found:
        lw $ra, 0x14 ($sp)
        addiu $sp, $sp, 0x20
        jr $ra
        addiu $v0, $zero, 0

.align 0x10
END_HOOK: