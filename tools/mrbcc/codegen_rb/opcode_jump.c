    CASE(OP_JMPNOT) {
      /* A sBx  if R(A) pc+=sBx */
      if (!mrb_test(regs[GETARG_A(i)])) {
        JUMP_TO_PC(GETARG_sBx(i));
      }
      NEXT;
    }

    CASE(OP_JMP) {
      /* sBx    pc+=sBx */
      pc += GETARG_sBx(i);
      JUMP;
    }

    CASE(OP_JMPIF) {
      /* A sBx  if R(A) pc+=sBx */
      if (mrb_test(regs[GETARG_A(i)])) {
        JUMP_TO_PC(GETARG_sBx(i));
      }
      NEXT;
    }
