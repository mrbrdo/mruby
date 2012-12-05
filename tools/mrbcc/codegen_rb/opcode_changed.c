  CASE(OP_SEND) {
      int a = GETARG_A(i);
      int n = GETARG_C(i);

      regs[a] = mrb_funcall_fast(mrb, regs[a], syms[GETARG_B(i)], n, &regs[a+1], mrb_nil_value(), regs, a);
      NEXT;
  }
  CASE(OP_SENDB) {
      int a = GETARG_A(i);
      int n = GETARG_C(i);
      regs[a] = mrb_funcall_fast(mrb, regs[a], syms[GETARG_B(i)], n, &regs[a+1], regs[a+n+1], regs, a);
      NEXT;
  }
    CASE(OP_STRING) {
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[GETARG_A(i)] = mrb_str_new_cstr(mrb, GETARG_Bx(i));
      NEXT;
    }

    CASE(OP_METHOD) {
      /* A B            R(A).newmethod(Sym(B),R(A+1)) */
      int a = GETARG_A(i);
      struct RClass *c = mrb_class_ptr(regs[a]);

      mrb_define_method_vm(mrb, c, syms[GETARG_B(i)], regs[a+1]);
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
      // TODO goto L_RAISE;
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

    CASE(OP_RETURN) {
      /* A      return R(A) */
/*    L_RETURN:
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
      else */ {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[GETARG_A(i)];
        return v;

        /*switch (GETARG_B(i)) {
        case OP_R_RETURN:
    if (!proc->env || MRB_PROC_STRICT_P(proc)) {
      // fall through
    } else {
      struct REnv *e = top_env(mrb, proc);

      if (e->cioff < 0) {
        localjump_error(mrb, "return");
        goto L_RAISE;
      }
      ci = mrb->ci = mrb->cibase + e->cioff;
          break;
    }
        case OP_R_NORMAL:
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
        default:
          break;
        }*/
        if (ci == mrb->cibase) {
          //localjump_error(mrb, "return");
          printf("LOCALJUMP_ERROR\n");
          return mrb_nil_value();
        }
        ci = mrb->ci;
        cipop(mrb);
        acc = ci->acc;
        //pc = ci->pc;
        regs = mrb->stack = mrb->stbase + ci->stackidx;
        /* TODO TODO while (eidx > mrb->ci->eidx) {
          ecall(mrb, --eidx);
        }*/
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        DEBUG(printf("from :%s\n", mrb_sym2name(mrb, ci->mid)));
        /*proc = mrb->ci->proc;
        irep = proc->body.irep;
        pool = irep->pool;
        syms = irep->syms;*/

        regs[acc] = v;
        return v;
        //return mrb_run(mrb, mrb->ci->proc, self);
      }
    }
