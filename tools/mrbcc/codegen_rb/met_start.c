mrb_value MET_NAME(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (FUNC_NREGS < 3) ? 3 : FUNC_NREGS, 3);
  }
  else {
    stack_extend(mrb, FUNC_NREGS, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = FUNC_NREGS + 2;
  regs = mrb->stack;
  regs[0] = self;
  // TODO regs[0] = m->env->stack[0]; ? OP_CALL

  {
    jmp_buf c_jmp;

    if (setjmp(c_jmp) == 0) {
      mrb->jmp = &c_jmp;
    }
    else {
      goto *mrb->rescue[--mrb->ci->ridx];
    }
  }

/*
        mrb->jmp = prev_jmp_ensure; // TODO: what about retry?
        mrbb_ecall(mrb, mrbb_proc_new(mrb, GETARG_Bx(i)));
        longjmp(*(jmp_buf*)mrb->jmp, 1);
*/
