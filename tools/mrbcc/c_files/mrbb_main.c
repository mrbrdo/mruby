mrb_value mrbb_proc_call(mrb_state *mrb, mrb_value self)
{
  mrb_callinfo *ci;
  mrb_value recv = mrb->stack[0];
  struct RProc *m = mrb_proc_ptr(recv);
  int ai = mrb->arena_idx;

 /* if (!MRB_PROC_CFUNC_P(m)) {
    printf("CALL2\n");
    return mrb_funcall_with_block(mrb, recv, mrb_intern(mrb, "call2"), 1, (mrb->stack + 1), *(mrb->stack + 2));
    printf("CALL22\n");
  }*/

  /* replace callinfo */
  ci = mrb->ci;
  ci->target_class = m->target_class;
  ci->proc = m;
  if (m->env) {
if (m->env->mid) {
ci->mid = m->env->mid;
}
    if (!m->env->stack) {
      m->env->stack = mrb->stack;
    }
  }

  /* prepare stack */
  if (MRB_PROC_CFUNC_P(m)) {
    recv = m->body.func(mrb, m->env->stack[0]);
    mrb->arena_idx = ai;
    if (mrb->exc) mrbb_raise(mrb, 0);
    /* pop stackpos */
    // already done by funcall
//ci = mrb->ci;
    //mrb->stack = mrb->stbase + ci->stackidx;
//regs[ci->acc] = recv;
//pc = ci->pc;
    //cipop(mrb);
  } else {
    mrb_irep *irep = m->body.irep;
    if (!irep) {
      mrb->stack[0] = mrb_nil_value();
      return mrb_nil_value();
    }
    ci->nregs = irep->nregs;
    if (ci->argc < 0) {
      stack_extend(mrb, (irep->nregs < 3) ? 3 : irep->nregs, 3);
    }
    else {
      stack_extend(mrb, irep->nregs,  ci->argc+2);
    }
    mrb->stack[0] = m->env->stack[0];
    recv = mrb_run(mrb, m, recv);
  }
  // TODO: only overwrite this method for Cfunc procs
  // so we let OP_CALL handle interpreted funcs
  return recv;
}
void mrbb_main(mrb_state *mrb) {
  int a = 0;
  mrb_callinfo *ci;
  mrb_value recv = mrb_top_self(mrb);
  struct RProc *p;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp;
  jmp_buf c_jmp;

  if (setjmp(c_jmp) == 0) {
    mrb->jmp = &c_jmp;
  }
  else {
    printf("unexpected exception ");
    mrb_p(mrb, mrb_obj_value(mrb->exc));
    exit(0);
    mrbb_raise(mrb, prev_jmp); // TODO ?
  }

  if (!mrb->stack) {
    stack_init(mrb);
  }

  // TODO: patch Proc
  {
    struct RProc *m = mrb_proc_new_cfunc(mrb, mrbb_proc_call);
    mrb_define_method_raw(mrb, mrb->proc_class, mrb_intern(mrb, "call"), m);
    mrb_define_method_raw(mrb, mrb->proc_class, mrb_intern(mrb, "[]"), m);
  }
  // END TODO

  mrb->stack[0] = recv;
  /* prepare stack */
  ci = cipush(mrb);
  //ci->pc = pc + 1;
  ci->acc = -1;
  ci->mid = 0;
  ci->stackidx = mrb->stack - mrb->stbase;
  ci->argc = 0;
  ci->target_class = mrb_class(mrb, recv);

  /* prepare stack */
  mrb->stack += a;

  p = mrb_proc_new_cfunc(mrb, rb_main);
  // p = mrb_proc_new(mrb, mrb->irep[irep->idx+GETARG_Bx(i)]);
  p->target_class = ci->target_class;
  ci->proc = p;

  // if (MRB_PROC_CFUNC_P(p)) {
  // else part removed since it is always CFUNC

  //mrb_gc_protect(mrb, mrb_obj_value(ci->proc)); // TODO just testing...
  mrb->stack[0] = p->body.func(mrb, recv);
  mrb->arena_idx = ai;
  if (mrb->exc) mrbb_raise(mrb, prev_jmp); // TODO
  /* pop stackpos */
  mrb->stack = mrb->stbase + mrb->ci->stackidx;
  cipop(mrb);
}
