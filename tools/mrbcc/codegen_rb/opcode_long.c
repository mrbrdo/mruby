
    CASE(OP_ARGARY) {
      /* A Bx   R(A) := argument array (16=6:1:5:4) */
      int a = GETARG_A(i);
      int bx = GETARG_Bx(i);
      int m1 = (bx>>10)&0x3f;
      int r  = (bx>>9)&0x1;
      int m2 = (bx>>4)&0x1f;
      int lv = (bx>>0)&0xf;
      mrb_value *stack;

      if (lv == 0) stack = regs + 1;
      else {
        struct REnv *e = uvenv(mrb, lv-1);
        if (!e) {
          mrb_value exc;
          static const char m[] = "super called outside of method";
          exc = mrb_exc_new(mrb, E_NOMETHOD_ERROR, m, sizeof(m) - 1);
          mrb->exc = (struct RObject*)mrb_object(exc);
          goto L_RAISE;
        }
        stack = e->stack + 1;
      }
      if (r == 0) {
        regs[a] = mrb_ary_new_elts(mrb, m1+m2, stack);
      }
      else {
        mrb_value *pp = NULL;
        struct RArray *rest;
        int len = 0;

        if (mrb_array_p(stack[m1])) {
          struct RArray *ary = mrb_ary_ptr(stack[m1]);

          pp = ary->ptr;
          len = ary->len;
        }
        regs[a] = mrb_ary_new_capa(mrb, m1+len+m2);
        rest = mrb_ary_ptr(regs[a]);
        stack_copy(rest->ptr, stack, m1);
        if (len > 0) {
          stack_copy(rest->ptr+m1, pp, len);
        }
        if (m2 > 0) {
          stack_copy(rest->ptr+m1+len, stack+m1+1, m2);
        }
        rest->len = m1+len+m2;
      }
      regs[a+1] = stack[m1+r+m2];
      mrb->arena_idx = ai;
      NEXT;
    }


    CASE(OP_TAILCALL) {
      /* A B C  return call(R(A),Sym(B),R(A+1),... ,R(A+C-1)) */
      int a = GETARG_A(i);
      int n = GETARG_C(i);
      struct RProc *m;
      struct RClass *c;
      mrb_callinfo *ci;
      mrb_value recv;
      mrb_sym mid = syms[GETARG_B(i)];

      recv = regs[a];
      c = mrb_class(mrb, recv);
      m = mrb_method_search_vm(mrb, &c, mid);
      if (!m) {
        mrb_value sym = mrb_symbol_value(mid);

        mid = mrb_intern(mrb, "method_missing");
        m = mrb_method_search_vm(mrb, &c, mid);
        if (n == CALL_MAXARGS) {
          mrb_ary_unshift(mrb, regs[a+1], sym);
        }
        else {
          memmove(regs+a+2, regs+a+1, sizeof(mrb_value)*(n+1));
          regs[a+1] = sym;
          n++;
        }
      }


      /* replace callinfo */
      ci = mrb->ci;
      ci->mid = mid;
      ci->target_class = m->target_class;
      ci->argc = n;
      if (ci->argc == CALL_MAXARGS) ci->argc = -1;

      /* move stack */
      memmove(mrb->stack, &regs[a], (ci->argc+1)*sizeof(mrb_value));

      if (MRB_PROC_CFUNC_P(m)) {
        mrb->stack[0] = m->body.func(mrb, recv);
        mrb->arena_idx = ai;
        goto L_RETURN;
      }
      else {
        /* setup environment for calling method */
        irep = m->body.irep;
        pool = irep->pool;
        syms = irep->syms;
        if (ci->argc < 0) {
          stack_extend(mrb, (irep->nregs < 3) ? 3 : irep->nregs, 3);
        }
        else {
          stack_extend(mrb, irep->nregs,  ci->argc+2);
        }
        regs = mrb->stack;
        pc = irep->iseq;
      }
      JUMP;
    }

    CASE(OP_BLKPUSH) {
      /* A Bx   R(A) := block (16=6:1:5:4) */
      int a = GETARG_A(i);
      int bx = GETARG_Bx(i);
      int m1 = (bx>>10)&0x3f;
      int r  = (bx>>9)&0x1;
      int m2 = (bx>>4)&0x1f;
      int lv = (bx>>0)&0xf;
      mrb_value *stack;

      if (lv == 0) stack = regs + 1;
      else {
        struct REnv *e = uvenv(mrb, lv-1);
  if (!e) {
    localjump_error(mrb, "yield");
    goto L_RAISE;
  }
        stack = e->stack + 1;
      }
      regs[a] = stack[m1+r+m2];
      NEXT;
    }
