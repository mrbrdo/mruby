  CASE(OP_SEND) {
      int a = GETARG_A(i);

      regs[a] = mrb_funcall(mrb, regs[a], GETARG_B(i), DYNAMIC_SEND_ARGS);
  }

    CASE(OP_STOP) {
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
