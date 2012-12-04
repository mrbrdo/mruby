    CASE(OP_ONERR) {
      /* sBx    pc+=sBx on exception */
      if (mrb->rsize <= mrb->ci->ridx) {
        if (mrb->rsize == 0) mrb->rsize = 16;
        else mrb->rsize *= 2;
        mrb->rescue = (mrb_code **)mrb_realloc(mrb, mrb->rescue, sizeof(mrb_code*) * mrb->rsize);
      }
      mrb->rescue[mrb->ci->ridx++] = pc + GETARG_sBx(i);
      NEXT;
    }

    CASE(OP_RESCUE) {
      /* A      R(A) := exc; clear(exc) */
      SET_OBJ_VALUE(regs[GETARG_A(i)], mrb->exc);
      mrb->exc = 0;
      NEXT;
    }

    CASE(OP_POPERR) {
      int a = GETARG_A(i);

      while (a--) {
        mrb->ci->ridx--;
      }
      NEXT;
    }

    CASE(OP_RAISE) {
      /* A      raise(R(A)) */
      mrb->exc = (struct RObject*)mrb_object(regs[GETARG_A(i)]);
      goto L_RAISE;
    }

    CASE(OP_EPUSH) {
      /* Bx     ensure_push(SEQ[Bx]) */
      struct RProc *p;

      p = mrb_closure_new(mrb, mrb->irep[irep->idx+GETARG_Bx(i)]);
      /* push ensure_stack */
      if (mrb->esize <= mrb->ci->eidx) {
        if (mrb->esize == 0) mrb->esize = 16;
        else mrb->esize *= 2;
        mrb->ensure = (struct RProc **)mrb_realloc(mrb, mrb->ensure, sizeof(struct RProc*) * mrb->esize);
      }
      mrb->ensure[mrb->ci->eidx++] = p;
      mrb->arena_idx = ai;
      NEXT;
    }

    CASE(OP_EPOP) {
      /* A      A.times{ensure_pop().call} */
      int n;
      int a = GETARG_A(i);

      for (n=0; n<a; n++) {
        ecall(mrb, --mrb->ci->eidx);
      }
      mrb->arena_idx = ai;
      NEXT;
    }

    CASE(OP_ERR) {
      /* Bx     raise RuntimeError with message Lit(Bx) */
      mrb_value msg = pool[GETARG_Bx(i)];
      mrb_value exc;

      if (GETARG_A(i) == 0) {
  exc = mrb_exc_new3(mrb, E_RUNTIME_ERROR, msg);
      }
      else {
  exc = mrb_exc_new3(mrb, E_LOCALJUMP_ERROR, msg);
      }
      mrb->exc = (struct RObject*)mrb_object(exc);
      goto L_RAISE;
    }
