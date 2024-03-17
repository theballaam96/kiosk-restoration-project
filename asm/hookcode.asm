START_HOOK:
fix_diddy_japes_crash:
    lh $a0, 0x2a ($sp)
    jal getSpawnerFlag_fixed
    addiu $a2, $sp, 0x20
    j 0x806d4de0
    nop

.align 0x10
END_HOOK: