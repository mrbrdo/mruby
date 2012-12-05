mrb_value rb_main(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp;
  jmp_buf c_jmp;

  if (setjmp(c_jmp) == 0) {
    mrb->jmp = &c_jmp;
  }
  else {
    // TODO goto L_RAISE;
  }
  // TODO: cheap error handling
  if (mrb->exc) {
    mrb_p(mrb, mrb_obj_value(mrb->exc));
    return mrb_nil_value();
  }
  if (!mrb->stack) {
    stack_init(mrb);
  }
  //mrb->ci->proc = proc;
  mrb->ci->nregs = 3 + 2;
  regs = mrb->stack;
  regs[0] = self;

  // 000 OP_LOADL	R2	L(0)
  L_RB_MAIN_0:
  {
      /* A Bx   R(A) := Pool(Bx) */
      regs[2] = pool[L(0)];
      NEXT;
    }
  // 001 OP_MOVE	R1	R2
  L_RB_MAIN_1:
  {
      /* A B    R(A) := R(B) */
      regs[1] = regs[2];
      NEXT;
    }
  // 002 OP_STOP
  L_RB_MAIN_2:
  {
      /*        stop VM */
/*    L_STOP:
      {
  int n = mrb->ci->eidx;

  while (n--) {
    ecall(mrb, n);
  }
      }
      mrb->jmp = prev_jmp;
      if (mrb->exc) {
  return mrb_obj_value(mrb->exc);
      }
      return regs[irep->nlocals];*/
    }
}
