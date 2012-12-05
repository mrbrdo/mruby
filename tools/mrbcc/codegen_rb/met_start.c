mrb_value MET_NAME(mrb_state *mrb, mrb_value self) {
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
  mrb->ci->nregs = FUNC_NREGS + 2;
  regs = mrb->stack;
  regs[0] = self;
