
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

    CASE(OP_ENTER) {
      /* Ax             arg setup according to flags (24=5:5:1:5:5:1:1) */
      /* number of optional arguments times OP_JMP should follow */
      int ax = GETARG_Ax(i);
      int m1 = (ax>>18)&0x1f;
      int o  = (ax>>13)&0x1f;
      int r  = (ax>>12)&0x1;
      int m2 = (ax>>7)&0x1f;
      /* unused
      int k  = (ax>>2)&0x1f;
      int kd = (ax>>1)&0x1;
      int b  = (ax>>0)& 0x1;
      */
      int argc = mrb->ci->argc;
      mrb_value *argv = regs+1;
      mrb_value *argv0 = argv;
      int len = m1 + o + r + m2;
      mrb_value *blk = &argv[argc < 0 ? 1 : argc];

      if (argc < 0) {
        struct RArray *ary = mrb_ary_ptr(regs[1]);
        argv = ary->ptr;
        argc = ary->len;
  mrb_gc_protect(mrb, regs[1]);
      }
      if (mrb->ci->proc && MRB_PROC_STRICT_P(mrb->ci->proc)) {
        if (argc >= 0) {
          if (argc < m1 + m2 || (r == 0 && argc > len)) {
      argnum_error(mrb, m1+m2);
      goto L_RAISE;
          }
        }
      }
      else if (len > 1 && argc == 1 && mrb_array_p(argv[0])) {
        argc = mrb_ary_ptr(argv[0])->len;
        argv = mrb_ary_ptr(argv[0])->ptr;
      }
      mrb->ci->argc = len;
      if (argc < len) {
        regs[len+1] = *blk; /* move block */
        if (argv0 != argv) {
          memmove(&regs[1], argv, sizeof(mrb_value)*(argc-m2)); /* m1 + o */
        }
        if (m2) {
          memmove(&regs[len-m2+1], &argv[argc-m2], sizeof(mrb_value)*m2); /* m2 */
        }
        if (r) {                  /* r */
          regs[m1+o+1] = mrb_ary_new_capa(mrb, 0);
        }
  if (o == 0) pc++;
  else
    pc += argc - m1 - m2 + 1;
      }
      else {
        if (argv0 != argv) {
          memmove(&regs[1], argv, sizeof(mrb_value)*(m1+o)); /* m1 + o */
        }
        if (r) {                  /* r */
          regs[m1+o+1] = mrb_ary_new_elts(mrb, argc-m1-o-m2, argv+m1+o);
        }
        if (m2) {
          memmove(&regs[m1+o+r+1], &argv[argc-m2], sizeof(mrb_value)*m2);
        }
        regs[len+1] = *blk; /* move block */
        pc += o + 1;
      }
      JUMP;
    }

    CASE(OP_RETURN) {
      /* A      return R(A) */
    L_RETURN:
      if (mrb->exc) {
        mrb_callinfo *ci;
        int eidx;

      L_RAISE:
        ci = mrb->ci;
  eidx = mrb->ci->eidx;
        if (ci == mrb->cibase) goto L_STOP;
        while (ci[0].ridx == ci[-1].ridx) {
          cipop(mrb);
          ci = mrb->ci;
    if (ci[1].acc < 0 && prev_jmp) {
      mrb->jmp = prev_jmp;
      longjmp(*(jmp_buf*)mrb->jmp, 1);
    }
    while (eidx > mrb->ci->eidx) {
      ecall(mrb, --eidx);
    }
          if (ci == mrb->cibase) {
            if (ci->ridx == 0) {
        regs = mrb->stack = mrb->stbase;
        goto L_STOP;
      }
            break;
          }
        }
        irep = ci->proc->body.irep;
        pool = irep->pool;
        syms = irep->syms;
        regs = mrb->stack = mrb->stbase + ci[1].stackidx;
        pc = mrb->rescue[--ci->ridx];
      }
      else {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[GETARG_A(i)];

        switch (GETARG_B(i)) {
        case OP_R_NORMAL:
  NORMAL_RETURN:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            goto L_RAISE;
          }
          ci = mrb->ci;
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            goto L_RAISE;
          }
          ci = mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        case OP_R_RETURN:
    if (!proc->env) goto NORMAL_RETURN;
    if (MRB_PROC_STRICT_P(proc)) goto NORMAL_RETURN;
    else {
      struct REnv *e = top_env(mrb, proc);

      if (e->cioff < 0) {
        localjump_error(mrb, "return");
        goto L_RAISE;
      }
      ci = mrb->ci = mrb->cibase + e->cioff;
    }
          break;
        default:
          /* cannot happen */
          break;
        }
        cipop(mrb);
        acc = ci->acc;
        pc = ci->pc;
        regs = mrb->stack = mrb->stbase + ci->stackidx;
        while (eidx > mrb->ci->eidx) {
          ecall(mrb, --eidx);
        }
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        DEBUG(printf("from :%s\n", mrb_sym2name(mrb, ci->mid)));
        proc = mrb->ci->proc;
        irep = proc->body.irep;
        pool = irep->pool;
        syms = irep->syms;

        regs[acc] = v;
      }
      JUMP;
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
