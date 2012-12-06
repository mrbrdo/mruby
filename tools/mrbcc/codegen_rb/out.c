mrb_value met_9c41e26864a307612a65c0efc525d451(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (4 < 3) ? 3 : 4, 3);
  }
  else {
    stack_extend(mrb, 4, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 4 + 2;
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

  // ["OP_LOADSYM", 1, 0, 0]
  L_MET_9C41E26864A307612A65C0EFC525D451_0:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_0\n"); fflush(stdout);
{
      /* A B    R(A) := Sym(B) */
      SET_SYM_VALUE(regs[1], mrb_intern(mrb, "ng"));
      NEXT;
    }

  // ["OP_ONERR", 0, 256, 4]
  L_MET_9C41E26864A307612A65C0EFC525D451_1:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_1\n"); fflush(stdout);
{
      /* sBx    pc+=sBx on exception */
      if (mrb->rsize <= mrb->ci->ridx) {
        if (mrb->rsize == 0) mrb->rsize = 16;
        else mrb->rsize *= 2;
        mrb->rescue = (mrb_code **)mrb_realloc(mrb, mrb->rescue, sizeof(mrb_code*) * mrb->rsize);
      }
      mrb->rescue[mrb->ci->ridx++] = &&L_MET_9C41E26864A307612A65C0EFC525D451_6;

      NEXT;
    }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_9C41E26864A307612A65C0EFC525D451_2:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_2\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_LOADSYM", 3, 0, 2]
  L_MET_9C41E26864A307612A65C0EFC525D451_3:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_3\n"); fflush(stdout);
{
      /* A B    R(A) := Sym(B) */
      SET_SYM_VALUE(regs[3], mrb_intern(mrb, "exception_test14"));
      NEXT;
    }

  // ["OP_SEND", 2, 1, 1]
  L_MET_9C41E26864A307612A65C0EFC525D451_4:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_4\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "send"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMP", 0, 256, 9]
  L_MET_9C41E26864A307612A65C0EFC525D451_5:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_5\n"); fflush(stdout);
goto L_MET_9C41E26864A307612A65C0EFC525D451_15;
  // ["OP_RESCUE", 2, 0, 0]
  L_MET_9C41E26864A307612A65C0EFC525D451_6:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_6\n"); fflush(stdout);
{ // TODO
      /* A      R(A) := exc; clear(exc) */
      mrb->ci = ci;
      SET_OBJ_VALUE(regs[2], mrb->exc);
      mrb->exc = 0;
      NEXT;
    }

  // ["OP_GETCONST", 3, 0, 3]
  L_MET_9C41E26864A307612A65C0EFC525D451_7:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_7\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[3] = mrb_vm_const_get(mrb, mrb_intern(mrb, "StandardError"));
      NEXT;
    }

  // ["OP_MOVE", 4, 2, 0]
  L_MET_9C41E26864A307612A65C0EFC525D451_8:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_8\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[4] = regs[2];
      NEXT;
    }

  // ["OP_SEND", 3, 4, 1]
  L_MET_9C41E26864A307612A65C0EFC525D451_9:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_9\n"); fflush(stdout);
{
      int a = 3;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "==="), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMPIF", 3, 256, 1]
  L_MET_9C41E26864A307612A65C0EFC525D451_10:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_10\n"); fflush(stdout);
{
      /* A sBx  if R(A) pc+=sBx */
      if (mrb_test(regs[3])) {
        goto L_MET_9C41E26864A307612A65C0EFC525D451_12;
      }
      NEXT;
    }

  // ["OP_JMP", 0, 256, 2]
  L_MET_9C41E26864A307612A65C0EFC525D451_11:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_11\n"); fflush(stdout);
goto L_MET_9C41E26864A307612A65C0EFC525D451_14;
  // ["OP_LOADSYM", 1, 0, 5]
  L_MET_9C41E26864A307612A65C0EFC525D451_12:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_12\n"); fflush(stdout);
{
      /* A B    R(A) := Sym(B) */
      SET_SYM_VALUE(regs[1], mrb_intern(mrb, "ok"));
      NEXT;
    }

  // ["OP_JMP", 0, 256, 2]
  L_MET_9C41E26864A307612A65C0EFC525D451_13:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_13\n"); fflush(stdout);
goto L_MET_9C41E26864A307612A65C0EFC525D451_16;
  // ["OP_RAISE", 2, 0, 0]
  L_MET_9C41E26864A307612A65C0EFC525D451_14:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_14\n"); fflush(stdout);
{
      /* A      raise(R(A)) */
      mrb->exc = (struct RObject*)mrb_object(regs[2]);
      mrbb_raise(mrb, prev_jmp);
    }

  // ["OP_POPERR", 1, 0, 0]
  L_MET_9C41E26864A307612A65C0EFC525D451_15:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_15\n"); fflush(stdout);
{
      int a = 1;

      while (a--) {
        mrb->ci->ridx--;
      }
      NEXT;
    }

  // ["OP_MOVE", 2, 1, 0]
  L_MET_9C41E26864A307612A65C0EFC525D451_16:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_16\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[2] = regs[1];
      NEXT;
    }

  // ["OP_LOADSYM", 3, 0, 5]
  L_MET_9C41E26864A307612A65C0EFC525D451_17:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_17\n"); fflush(stdout);
{
      /* A B    R(A) := Sym(B) */
      SET_SYM_VALUE(regs[3], mrb_intern(mrb, "ok"));
      NEXT;
    }

  // ["OP_EQ", 2, 6, 1]
  L_MET_9C41E26864A307612A65C0EFC525D451_18:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_18\n"); fflush(stdout);
{
      /* A B C  R(A) := R(A)<R(A+1) (Syms[B]=:<,C=1)*/
      int a = 2;
      if (mrb_obj_eq(mrb, regs[a], regs[a+1])) {
  SET_TRUE_VALUE(regs[a]);
      }
      else {
  int a = 2; OP_CMP(==);
      }
      NEXT;
    }

  // ["OP_RETURN", 2, 0, 0]
  L_MET_9C41E26864A307612A65C0EFC525D451_19:
    printf("L_MET_9C41E26864A307612A65C0EFC525D451_19\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[2];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_e88725a55dac71cfe4a45fc2b3bdea2c(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (3 < 3) ? 3 : 3, 3);
  }
  else {
    stack_extend(mrb, 3, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 3 + 2;
  regs = mrb->stack;
  regs[0] = self;
  // TODO regs[0] = m->env->stack[0]; ? OP_CALL

  {
    jmp_buf c_jmp;

    if (setjmp(c_jmp) == 0) {
      mrb->jmp = &c_jmp;
    }
    else {
      printf("rescue! %d\n", mrb->ci->ridx);fflush(stdout);
      goto *mrb->rescue[--mrb->ci->ridx];
    }
  }

/*
        mrb->jmp = prev_jmp_ensure; // TODO: what about retry?
        mrbb_ecall(mrb, mrbb_proc_new(mrb, GETARG_Bx(i)));
        longjmp(*(jmp_buf*)mrb->jmp, 1);
*/

  // ["OP_ENTER", 0, 0, 0]
  L_MET_E88725A55DAC71CFE4A45FC2B3BDEA2C_0:
    printf("L_MET_E88725A55DAC71CFE4A45FC2B3BDEA2C_0\n"); fflush(stdout);
{
      /* Ax             arg setup according to flags (24=5:5:1:5:5:1:1) */
      /* number of optional arguments times OP_JMP should follow */
      int ax = 0;
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
      mrbb_raise(mrb, prev_jmp);
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
   goto L_MET_E88725A55DAC71CFE4A45FC2B3BDEA2C_1;
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
        goto L_MET_E88725A55DAC71CFE4A45FC2B3BDEA2C_1;
      }

    }

  // ["OP_GETCONST", 0, 0, 0]
  L_MET_E88725A55DAC71CFE4A45FC2B3BDEA2C_1:
    printf("L_MET_E88725A55DAC71CFE4A45FC2B3BDEA2C_1\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[0] = mrb_vm_const_get(mrb, mrb_intern(mrb, "UnknownConstant"));
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_E88725A55DAC71CFE4A45FC2B3BDEA2C_2:
    printf("L_MET_E88725A55DAC71CFE4A45FC2B3BDEA2C_2\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_af96e0a4b0ea390745b073e911bb8867(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (7 < 3) ? 3 : 7, 3);
  }
  else {
    stack_extend(mrb, 7, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 7 + 2;
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

  // ["OP_ENTER", 8, 0, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_0:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_0\n"); fflush(stdout);
{
      /* Ax             arg setup according to flags (24=5:5:1:5:5:1:1) */
      /* number of optional arguments times OP_JMP should follow */
      int ax = 524288;
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
      mrbb_raise(mrb, prev_jmp);
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
   goto L_MET_AF96E0A4B0EA390745B073E911BB8867_1;
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
        goto L_MET_AF96E0A4B0EA390745B073E911BB8867_1;
      }

    }

  // ["OP_GETCONST", 5, 0, 1]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_1:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_1\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[5] = mrb_vm_const_get(mrb, mrb_intern(mrb, "Math"));
      NEXT;
    }

  // ["OP_GETMCNST", 5, 0, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_2:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_2\n"); fflush(stdout);
{
      /* A B C  R(A) := R(C)::Sym(B) */
      int a = 5;

      regs[a] = mrb_const_get(mrb, regs[a], mrb_intern(mrb, "TOLERANCE"));
      NEXT;
    }

  // ["OP_MOVE", 4, 5, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_3:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_3\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[4] = regs[5];
      NEXT;
    }

  // ["OP_MOVE", 5, 1, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_4:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_4\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[5] = regs[1];
      NEXT;
    }

  // ["OP_SEND", 5, 2, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_5:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_5\n"); fflush(stdout);
{
      int a = 5;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "to_f"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_MOVE", 1, 5, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_6:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_6\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[1] = regs[5];
      NEXT;
    }

  // ["OP_MOVE", 5, 2, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_7:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_7\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[5] = regs[2];
      NEXT;
    }

  // ["OP_SEND", 5, 2, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_8:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_8\n"); fflush(stdout);
{
      int a = 5;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "to_f"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_MOVE", 2, 5, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_9:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_9\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[2] = regs[5];
      NEXT;
    }

  // ["OP_MOVE", 5, 1, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_10:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_10\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[5] = regs[1];
      NEXT;
    }

  // ["OP_SEND", 5, 3, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_11:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_11\n"); fflush(stdout);
{
      int a = 5;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "finite?"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMPNOT", 5, 256, 2]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_12:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_12\n"); fflush(stdout);
{
      /* A sBx  if R(A) pc+=sBx */
      if (!mrb_test(regs[5])) {
        goto L_MET_AF96E0A4B0EA390745B073E911BB8867_15;
      }
      NEXT;
    }

  // ["OP_MOVE", 5, 2, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_13:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_13\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[5] = regs[2];
      NEXT;
    }

  // ["OP_SEND", 5, 3, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_14:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_14\n"); fflush(stdout);
{
      int a = 5;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "finite?"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMPNOT", 5, 256, 7]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_15:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_15\n"); fflush(stdout);
{
      /* A sBx  if R(A) pc+=sBx */
      if (!mrb_test(regs[5])) {
        goto L_MET_AF96E0A4B0EA390745B073E911BB8867_23;
      }
      NEXT;
    }

  // ["OP_MOVE", 5, 1, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_16:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_16\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[5] = regs[1];
      NEXT;
    }

  // ["OP_MOVE", 6, 2, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_17:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_17\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[6] = regs[2];
      NEXT;
    }

  // ["OP_SUB", 5, 4, 1]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_18:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_18\n"); fflush(stdout);
{
      /* A B C  R(A) := R(A)-R(A+1) (Syms[B]=:-,C=1)*/
      int a = 5;

      /* need to check if op is overridden */
      switch (TYPES2(mrb_type(regs[a]),mrb_type(regs[a+1]))) {
      case TYPES2(MRB_TT_FIXNUM,MRB_TT_FIXNUM):
  {
    mrb_int x, y, z;

    x = mrb_fixnum(regs[a]);
    y = mrb_fixnum(regs[a+1]);
    z = x - y;
    if (((x < 0) ^ (y < 0)) == 0 && (x < 0) != (z < 0)) {
      /* integer overflow */
      SET_FLT_VALUE(regs[a], (mrb_float)x - (mrb_float)y);
      break;
    }
    SET_INT_VALUE(regs[a], z);
  }
  break;
      case TYPES2(MRB_TT_FIXNUM,MRB_TT_FLOAT):
  {
    mrb_int x = mrb_fixnum(regs[a]);
    mrb_float y = mrb_float(regs[a+1]);
    SET_FLT_VALUE(regs[a], (mrb_float)x - y);
  }
  break;
      case TYPES2(MRB_TT_FLOAT,MRB_TT_FIXNUM):
  OP_MATH_BODY(-,attr_f,attr_i);
  break;
      case TYPES2(MRB_TT_FLOAT,MRB_TT_FLOAT):
  OP_MATH_BODY(-,attr_f,attr_f);
  break;
      default:
  regs[a] = mrb_funcall_with_block(mrb, regs[a], mrb_intern(mrb, "-"), 1, &regs[a+1], mrb_nil_value());
      }
      NEXT;
    }

  // ["OP_SEND", 5, 5, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_19:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_19\n"); fflush(stdout);
{
      int a = 5;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "abs"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_MOVE", 6, 4, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_20:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_20\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[6] = regs[4];
      NEXT;
    }

  // ["OP_LT", 5, 6, 1]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_21:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_21\n"); fflush(stdout);
{
      /* A B C  R(A) := R(A)<R(A+1) (Syms[B]=:<,C=1)*/
      int a = 5; OP_CMP(<);
      NEXT;
    }

  // ["OP_JMP", 0, 256, 1]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_22:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_22\n"); fflush(stdout);
goto L_MET_AF96E0A4B0EA390745B073E911BB8867_24;
  // ["OP_LOADT", 5, 0, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_23:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_23\n"); fflush(stdout);
{
      /* A      R(A) := true */
      SET_TRUE_VALUE(regs[5]);
      NEXT;
    }

  // ["OP_RETURN", 5, 0, 0]
  L_MET_AF96E0A4B0EA390745B073E911BB8867_24:
    printf("L_MET_AF96E0A4B0EA390745B073E911BB8867_24\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[5];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_f4ede045cd3c1fd06013433f566f48dd(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (9 < 3) ? 3 : 9, 3);
  }
  else {
    stack_extend(mrb, 9, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 9 + 2;
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

  // ["OP_ENTER", 16, 0, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_0:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_0\n"); fflush(stdout);
{
      /* Ax             arg setup according to flags (24=5:5:1:5:5:1:1) */
      /* number of optional arguments times OP_JMP should follow */
      int ax = 1048576;
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
      mrbb_raise(mrb, prev_jmp);
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
   goto L_MET_F4EDE045CD3C1FD06013433F566F48DD_1;
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
        goto L_MET_F4EDE045CD3C1FD06013433F566F48DD_1;
      }

    }

  // ["OP_LOADSELF", 6, 0, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_1:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_1\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[6] = regs[0];
      NEXT;
    }

  // ["OP_MOVE", 7, 1, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_2:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_2\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[7] = regs[1];
      NEXT;
    }

  // ["OP_SEND", 6, 0, 1]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_3:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_3\n"); fflush(stdout);
{
      int a = 6;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 6, 0, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_4:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_4\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[6] = regs[0];
      NEXT;
    }

  // ["OP_MOVE", 7, 2, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_5:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_5\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[7] = regs[2];
      NEXT;
    }

  // ["OP_MOVE", 8, 3, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_6:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_6\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[8] = regs[3];
      NEXT;
    }

  // ["OP_SEND", 6, 1, 2]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_7:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_7\n"); fflush(stdout);
{
      int a = 6;
      int n = 2;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print_assertion_string"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_MOVE", 6, 4, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_8:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_8\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[6] = regs[4];
      NEXT;
    }

  // ["OP_JMPNOT", 6, 256, 7]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_9:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_9\n"); fflush(stdout);
{
      /* A sBx  if R(A) pc+=sBx */
      if (!mrb_test(regs[6])) {
        goto L_MET_F4EDE045CD3C1FD06013433F566F48DD_17;
      }
      NEXT;
    }

  // ["OP_LOADSELF", 6, 0, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_10:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_10\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[6] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 7, 0, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_11:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_11\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[7] = mrb_str_new_cstr(mrb, " => ");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 6, 0, 1]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_12:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_12\n"); fflush(stdout);
{
      int a = 6;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 6, 0, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_13:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_13\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[6] = regs[0];
      NEXT;
    }

  // ["OP_MOVE", 7, 4, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_14:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_14\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[7] = regs[4];
      NEXT;
    }

  // ["OP_SEND", 7, 2, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_15:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_15\n"); fflush(stdout);
{
      int a = 7;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "message"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_SEND", 6, 0, 1]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_16:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_16\n"); fflush(stdout);
{
      int a = 6;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 6, 0, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_17:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_17\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[6] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 7, 0, 1]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_18:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_18\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[7] = mrb_str_new_cstr(mrb, "\n");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 6, 0, 1]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_19:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_19\n"); fflush(stdout);
{
      int a = 6;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_RETURN", 6, 0, 0]
  L_MET_F4EDE045CD3C1FD06013433F566F48DD_20:
    printf("L_MET_F4EDE045CD3C1FD06013433F566F48DD_20\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[6];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_d850708a9e8f210f954ee48c12c1486a(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (5 < 3) ? 3 : 5, 3);
  }
  else {
    stack_extend(mrb, 5, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 5 + 2;
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

  // ["OP_ENTER", 0, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_0:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_0\n"); fflush(stdout);
{
      /* Ax             arg setup according to flags (24=5:5:1:5:5:1:1) */
      /* number of optional arguments times OP_JMP should follow */
      int ax = 0;
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
      mrbb_raise(mrb, prev_jmp);
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
   goto L_MET_D850708A9E8F210F954EE48C12C1486A_1;
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
        goto L_MET_D850708A9E8F210F954EE48C12C1486A_1;
      }

    }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_1:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_1\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_2:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_2\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, "\n");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_3:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_3\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_GETGLOBAL", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_4:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_4\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[2] = mrb_gv_get(mrb, mrb_intern(mrb, "$asserts"));
      NEXT;
    }

  // ["OP_LAMBDA", 3, 0, 6]
  L_MET_D850708A9E8F210F954EE48C12C1486A_5:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_5\n"); fflush(stdout);
{
      /* A b c  R(A) := lambda(SEQ[b],c) (b:c = 14:2) */
      struct RProc *p;
      int c = 2;

      if (c & OP_L_CAPTURE) {
        p = mrbb_closure_new(mrb, met_f4ede045cd3c1fd06013433f566f48dd, (unsigned int)2);
      }
      else {
        p = mrbb_proc_new(mrb, met_f4ede045cd3c1fd06013433f566f48dd);
      }
      p->target_class = (mrb->ci) ? mrb->ci->target_class : 0;
      if (c & OP_L_STRICT) p->flags |= MRB_PROC_STRICT;
      regs[3] = mrb_obj_value(p);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SENDB", 2, 2, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_6:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_6\n"); fflush(stdout);
{
      int a = 2;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "each"), n, &regs[a+1], regs[a+n+1]);
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_GETGLOBAL", 2, 0, 3]
  L_MET_D850708A9E8F210F954EE48C12C1486A_7:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_7\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[2] = mrb_gv_get(mrb, mrb_intern(mrb, "$ok_test"));
      NEXT;
    }

  // ["OP_GETGLOBAL", 3, 0, 5]
  L_MET_D850708A9E8F210F954EE48C12C1486A_8:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_8\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[3] = mrb_gv_get(mrb, mrb_intern(mrb, "$ko_test"));
      NEXT;
    }

  // ["OP_ADD", 2, 4, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_9:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_9\n"); fflush(stdout);
{
      /* A B C  R(A) := R(A)+R(A+1) (Syms[B]=:+,C=1)*/
      int a = 2;

      /* need to check if op is overridden */
      switch (TYPES2(mrb_type(regs[a]),mrb_type(regs[a+1]))) {
      case TYPES2(MRB_TT_FIXNUM,MRB_TT_FIXNUM):
  {
    mrb_int x, y, z;

    x = mrb_fixnum(regs[a]);
    y = mrb_fixnum(regs[a+1]);
    z = x + y;
    if (((x < 0) ^ (y < 0)) == 0 && (x < 0) != (z < 0)) {
      /* integer overflow */
      SET_FLT_VALUE(regs[a], (mrb_float)x + (mrb_float)y);
      break;
    }
    SET_INT_VALUE(regs[a], z);
  }
  break;
      case TYPES2(MRB_TT_FIXNUM,MRB_TT_FLOAT):
  {
    mrb_int x = mrb_fixnum(regs[a]);
    mrb_float y = mrb_float(regs[a+1]);
    SET_FLT_VALUE(regs[a], (mrb_float)x + y);
  }
  break;
      case TYPES2(MRB_TT_FLOAT,MRB_TT_FIXNUM):
  OP_MATH_BODY(+,attr_f,attr_i);
  break;
      case TYPES2(MRB_TT_FLOAT,MRB_TT_FLOAT):
  OP_MATH_BODY(+,attr_f,attr_f);
  break;
      case TYPES2(MRB_TT_STRING,MRB_TT_STRING):
  regs[a] = mrb_str_plus(mrb, regs[a], regs[a+1]);
  break;
      default:
  regs[a] = mrb_funcall_with_block(mrb, regs[a], mrb_intern(mrb, "+"), 1, &regs[a+1], mrb_nil_value());
      }
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SETGLOBAL", 2, 0, 6]
  L_MET_D850708A9E8F210F954EE48C12C1486A_10:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_10\n"); fflush(stdout);
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, "$total_test"), regs[2]);
      NEXT;
    }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_11:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_11\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_12:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_12\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, "Total: ");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_13:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_13\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_14:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_14\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_GETGLOBAL", 3, 0, 6]
  L_MET_D850708A9E8F210F954EE48C12C1486A_15:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_15\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[3] = mrb_gv_get(mrb, mrb_intern(mrb, "$total_test"));
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_16:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_16\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_17:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_17\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 2]
  L_MET_D850708A9E8F210F954EE48C12C1486A_18:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_18\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, "\n");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_19:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_19\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_20:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_20\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 3]
  L_MET_D850708A9E8F210F954EE48C12C1486A_21:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_21\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, "   OK: ");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_22:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_22\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_23:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_23\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_GETGLOBAL", 3, 0, 3]
  L_MET_D850708A9E8F210F954EE48C12C1486A_24:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_24\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[3] = mrb_gv_get(mrb, mrb_intern(mrb, "$ok_test"));
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_25:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_25\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_26:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_26\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 4]
  L_MET_D850708A9E8F210F954EE48C12C1486A_27:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_27\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, "\n");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_28:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_28\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_29:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_29\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 5]
  L_MET_D850708A9E8F210F954EE48C12C1486A_30:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_30\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, "   KO: ");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_31:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_31\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_32:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_32\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_GETGLOBAL", 3, 0, 5]
  L_MET_D850708A9E8F210F954EE48C12C1486A_33:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_33\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[3] = mrb_gv_get(mrb, mrb_intern(mrb, "$ko_test"));
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_34:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_34\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_35:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_35\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 6]
  L_MET_D850708A9E8F210F954EE48C12C1486A_36:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_36\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, "\n");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_37:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_37\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_38:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_38\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 7]
  L_MET_D850708A9E8F210F954EE48C12C1486A_39:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_39\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, "Crash: ");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_40:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_40\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_41:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_41\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_GETGLOBAL", 3, 0, 7]
  L_MET_D850708A9E8F210F954EE48C12C1486A_42:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_42\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[3] = mrb_gv_get(mrb, mrb_intern(mrb, "$kill_test"));
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_43:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_43\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_44:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_44\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 8]
  L_MET_D850708A9E8F210F954EE48C12C1486A_45:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_45\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, "\n");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_46:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_46\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_GETCONST", 2, 0, 8]
  L_MET_D850708A9E8F210F954EE48C12C1486A_47:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_47\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "Object"));
      NEXT;
    }

  // ["OP_LOADSYM", 3, 0, 10]
  L_MET_D850708A9E8F210F954EE48C12C1486A_48:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_48\n"); fflush(stdout);
{
      /* A B    R(A) := Sym(B) */
      SET_SYM_VALUE(regs[3], mrb_intern(mrb, "Time"));
      NEXT;
    }

  // ["OP_SEND", 2, 9, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_49:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_49\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "const_defined?"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMPNOT", 2, 256, 13]
  L_MET_D850708A9E8F210F954EE48C12C1486A_50:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_50\n"); fflush(stdout);
{
      /* A sBx  if R(A) pc+=sBx */
      if (!mrb_test(regs[2])) {
        goto L_MET_D850708A9E8F210F954EE48C12C1486A_64;
      }
      NEXT;
    }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_51:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_51\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 9]
  L_MET_D850708A9E8F210F954EE48C12C1486A_52:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_52\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, " Time: ");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_53:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_53\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_54:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_54\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_GETCONST", 3, 0, 10]
  L_MET_D850708A9E8F210F954EE48C12C1486A_55:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_55\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[3] = mrb_vm_const_get(mrb, mrb_intern(mrb, "Time"));
      NEXT;
    }

  // ["OP_SEND", 3, 11, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_56:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_56\n"); fflush(stdout);
{
      int a = 3;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "now"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_GETGLOBAL", 4, 0, 13]
  L_MET_D850708A9E8F210F954EE48C12C1486A_57:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_57\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[4] = mrb_gv_get(mrb, mrb_intern(mrb, "$test_start"));
      NEXT;
    }

  // ["OP_SUB", 3, 12, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_58:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_58\n"); fflush(stdout);
{
      /* A B C  R(A) := R(A)-R(A+1) (Syms[B]=:-,C=1)*/
      int a = 3;

      /* need to check if op is overridden */
      switch (TYPES2(mrb_type(regs[a]),mrb_type(regs[a+1]))) {
      case TYPES2(MRB_TT_FIXNUM,MRB_TT_FIXNUM):
  {
    mrb_int x, y, z;

    x = mrb_fixnum(regs[a]);
    y = mrb_fixnum(regs[a+1]);
    z = x - y;
    if (((x < 0) ^ (y < 0)) == 0 && (x < 0) != (z < 0)) {
      /* integer overflow */
      SET_FLT_VALUE(regs[a], (mrb_float)x - (mrb_float)y);
      break;
    }
    SET_INT_VALUE(regs[a], z);
  }
  break;
      case TYPES2(MRB_TT_FIXNUM,MRB_TT_FLOAT):
  {
    mrb_int x = mrb_fixnum(regs[a]);
    mrb_float y = mrb_float(regs[a+1]);
    SET_FLT_VALUE(regs[a], (mrb_float)x - y);
  }
  break;
      case TYPES2(MRB_TT_FLOAT,MRB_TT_FIXNUM):
  OP_MATH_BODY(-,attr_f,attr_i);
  break;
      case TYPES2(MRB_TT_FLOAT,MRB_TT_FLOAT):
  OP_MATH_BODY(-,attr_f,attr_f);
  break;
      default:
  regs[a] = mrb_funcall_with_block(mrb, regs[a], mrb_intern(mrb, "-"), 1, &regs[a+1], mrb_nil_value());
      }
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_59:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_59\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_60:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_60\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 3, 0, 10]
  L_MET_D850708A9E8F210F954EE48C12C1486A_61:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_61\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[3] = mrb_str_new_cstr(mrb, " seconds\n");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 2, 0, 1]
  L_MET_D850708A9E8F210F954EE48C12C1486A_62:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_62\n"); fflush(stdout);
{
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADNIL", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_63:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_63\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 2;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 2, 0, 0]
  L_MET_D850708A9E8F210F954EE48C12C1486A_64:
    printf("L_MET_D850708A9E8F210F954EE48C12C1486A_64\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[2];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_9305675390ca13ac95791cbd84fa3430(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (10 < 3) ? 3 : 10, 3);
  }
  else {
    stack_extend(mrb, 10, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 10 + 2;
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

  // ["OP_ENTER", 0, 128, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_0:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_0\n"); fflush(stdout);
{
      /* Ax             arg setup according to flags (24=5:5:1:5:5:1:1) */
      /* number of optional arguments times OP_JMP should follow */
      int ax = 16384;
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
      mrbb_raise(mrb, prev_jmp);
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

    switch(argc) {
  case 0: goto L_MET_9305675390CA13AC95791CBD84FA3430_1;
  case 1: goto L_MET_9305675390CA13AC95791CBD84FA3430_2;
}

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
        goto L_MET_9305675390CA13AC95791CBD84FA3430_3;
      }

    }

  // ["OP_JMP", 0, 256, 2]
  L_MET_9305675390CA13AC95791CBD84FA3430_1:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_1\n"); fflush(stdout);
goto L_MET_9305675390CA13AC95791CBD84FA3430_4;
  // ["OP_JMP", 0, 256, 2]
  L_MET_9305675390CA13AC95791CBD84FA3430_2:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_2\n"); fflush(stdout);
goto L_MET_9305675390CA13AC95791CBD84FA3430_5;
  // ["OP_JMP", 0, 256, 2]
  L_MET_9305675390CA13AC95791CBD84FA3430_3:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_3\n"); fflush(stdout);
goto L_MET_9305675390CA13AC95791CBD84FA3430_6;
  // ["OP_STRING", 1, 0, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_4:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_4\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[1] = mrb_str_new_cstr(mrb, "Assertion failed");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_STRING", 2, 0, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_5:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_5\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[2] = mrb_str_new_cstr(mrb, "");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_ONERR", 0, 256, 24]
  L_MET_9305675390CA13AC95791CBD84FA3430_6:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_6\n"); fflush(stdout);
{
      /* sBx    pc+=sBx on exception */
      if (mrb->rsize <= mrb->ci->ridx) {
        if (mrb->rsize == 0) mrb->rsize = 16;
        else mrb->rsize *= 2;
        mrb->rescue = (mrb_code **)mrb_realloc(mrb, mrb->rescue, sizeof(mrb_code*) * mrb->rsize);
      }
      mrb->rescue[mrb->ci->ridx++] = &&L_MET_9305675390CA13AC95791CBD84FA3430_31;

      NEXT;
    }

  // ["OP_BLKPUSH", 5, 16, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_7:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_7\n"); fflush(stdout);
{
      /* A Bx   R(A) := block (16=6:1:5:4) */
      int a = 5;
      int bx = 2048;
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
    mrbb_raise(mrb, prev_jmp);
  }
        stack = e->stack + 1;
      }
      regs[a] = stack[m1+r+m2];
      NEXT;
    }

  // ["OP_SEND", 5, 0, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_8:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_8\n"); fflush(stdout);
{
      int a = 5;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "call"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_SEND", 5, 1, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_9:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_9\n"); fflush(stdout);
{
      int a = 5;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "!"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMPNOT", 5, 256, 13]
  L_MET_9305675390CA13AC95791CBD84FA3430_10:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_10\n"); fflush(stdout);
{
      /* A sBx  if R(A) pc+=sBx */
      if (!mrb_test(regs[5])) {
        goto L_MET_9305675390CA13AC95791CBD84FA3430_24;
      }
      NEXT;
    }

  // ["OP_GETGLOBAL", 5, 0, 2]
  L_MET_9305675390CA13AC95791CBD84FA3430_11:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_11\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[5] = mrb_gv_get(mrb, mrb_intern(mrb, "$asserts"));
      NEXT;
    }

  // ["OP_STRING", 6, 0, 2]
  L_MET_9305675390CA13AC95791CBD84FA3430_12:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_12\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[6] = mrb_str_new_cstr(mrb, "Fail: ");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_MOVE", 7, 1, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_13:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_13\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[7] = regs[1];
      NEXT;
    }

  // ["OP_MOVE", 8, 2, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_14:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_14\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[8] = regs[2];
      NEXT;
    }

  // ["OP_ARRAY", 6, 6, 3]
  L_MET_9305675390CA13AC95791CBD84FA3430_15:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_15\n"); fflush(stdout);
{
      /* A B C          R(A) := ary_new(R(B),R(B+1)..R(B+C)) */
      regs[6] = mrb_ary_new_from_values(mrb, 3, &regs[6]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 5, 3, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_16:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_16\n"); fflush(stdout);
{
      int a = 5;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "push"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_GETGLOBAL", 5, 0, 4]
  L_MET_9305675390CA13AC95791CBD84FA3430_17:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_17\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[5] = mrb_gv_get(mrb, mrb_intern(mrb, "$ko_test"));
      NEXT;
    }

  // ["OP_ADDI", 5, 5, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_18:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_18\n"); fflush(stdout);
{
      /* A B C  R(A) := R(A)+C (Syms[B]=:+)*/
      int a = 5;

      /* need to check if + is overridden */
      switch (mrb_type(regs[a])) {
      case MRB_TT_FIXNUM:
  {
    mrb_int x = regs[a].attr_i;
    mrb_int y = 1;
    mrb_int z = x + y;

    if (((x < 0) ^ (y < 0)) == 0 && (x < 0) != (z < 0)) {
      /* integer overflow */
      SET_FLT_VALUE(regs[a], (mrb_float)x + (mrb_float)y);
      break;
    }
    regs[a].attr_i = z;
  }
        break;
      case MRB_TT_FLOAT:
        regs[a].attr_f += 1;
        break;
      default:
        SET_INT_VALUE(regs[a+1], 1);

        regs[a] = mrb_funcall_with_block(mrb, regs[a], mrb_intern(mrb, "+"), 1, &regs[a+1], mrb_nil_value());
      }
      NEXT;
    }

  // ["OP_SETGLOBAL", 5, 0, 4]
  L_MET_9305675390CA13AC95791CBD84FA3430_19:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_19\n"); fflush(stdout);
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, "$ko_test"), regs[5]);
      NEXT;
    }

  // ["OP_LOADSELF", 5, 0, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_20:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_20\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[5] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 6, 0, 3]
  L_MET_9305675390CA13AC95791CBD84FA3430_21:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_21\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[6] = mrb_str_new_cstr(mrb, "F");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 5, 6, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_22:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_22\n"); fflush(stdout);
{
      int a = 5;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMP", 0, 256, 6]
  L_MET_9305675390CA13AC95791CBD84FA3430_23:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_23\n"); fflush(stdout);
goto L_MET_9305675390CA13AC95791CBD84FA3430_30;
  // ["OP_GETGLOBAL", 5, 0, 7]
  L_MET_9305675390CA13AC95791CBD84FA3430_24:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_24\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[5] = mrb_gv_get(mrb, mrb_intern(mrb, "$ok_test"));
      NEXT;
    }

  // ["OP_ADDI", 5, 5, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_25:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_25\n"); fflush(stdout);
{
      /* A B C  R(A) := R(A)+C (Syms[B]=:+)*/
      int a = 5;

      /* need to check if + is overridden */
      switch (mrb_type(regs[a])) {
      case MRB_TT_FIXNUM:
  {
    mrb_int x = regs[a].attr_i;
    mrb_int y = 1;
    mrb_int z = x + y;

    if (((x < 0) ^ (y < 0)) == 0 && (x < 0) != (z < 0)) {
      /* integer overflow */
      SET_FLT_VALUE(regs[a], (mrb_float)x + (mrb_float)y);
      break;
    }
    regs[a].attr_i = z;
  }
        break;
      case MRB_TT_FLOAT:
        regs[a].attr_f += 1;
        break;
      default:
        SET_INT_VALUE(regs[a+1], 1);

        regs[a] = mrb_funcall_with_block(mrb, regs[a], mrb_intern(mrb, "+"), 1, &regs[a+1], mrb_nil_value());
      }
      NEXT;
    }

  // ["OP_SETGLOBAL", 5, 0, 7]
  L_MET_9305675390CA13AC95791CBD84FA3430_26:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_26\n"); fflush(stdout);
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, "$ok_test"), regs[5]);
      NEXT;
    }

  // ["OP_LOADSELF", 5, 0, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_27:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_27\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[5] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 6, 0, 4]
  L_MET_9305675390CA13AC95791CBD84FA3430_28:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_28\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[6] = mrb_str_new_cstr(mrb, ".");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 5, 6, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_29:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_29\n"); fflush(stdout);
{
      int a = 5;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMP", 0, 256, 22]
  L_MET_9305675390CA13AC95791CBD84FA3430_30:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_30\n"); fflush(stdout);
goto L_MET_9305675390CA13AC95791CBD84FA3430_53;
  // ["OP_RESCUE", 5, 0, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_31:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_31\n"); fflush(stdout);
{ // TODO
      /* A      R(A) := exc; clear(exc) */
      mrb->ci = ci;
      SET_OBJ_VALUE(regs[5], mrb->exc);
      mrb->exc = 0;
      NEXT;
    }

  // ["OP_GETCONST", 6, 0, 8]
  L_MET_9305675390CA13AC95791CBD84FA3430_32:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_32\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[6] = mrb_vm_const_get(mrb, mrb_intern(mrb, "Exception"));
      NEXT;
    }

  // ["OP_MOVE", 7, 5, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_33:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_33\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[7] = regs[5];
      NEXT;
    }

  // ["OP_SEND", 6, 9, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_34:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_34\n"); fflush(stdout);
{
      int a = 6;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "==="), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMPIF", 6, 256, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_35:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_35\n"); fflush(stdout);
{
      /* A sBx  if R(A) pc+=sBx */
      if (mrb_test(regs[6])) {
        goto L_MET_9305675390CA13AC95791CBD84FA3430_37;
      }
      NEXT;
    }

  // ["OP_JMP", 0, 256, 15]
  L_MET_9305675390CA13AC95791CBD84FA3430_36:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_36\n"); fflush(stdout);
goto L_MET_9305675390CA13AC95791CBD84FA3430_52;
  // ["OP_MOVE", 4, 5, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_37:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_37\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[4] = regs[5];
      NEXT;
    }

  // ["OP_GETGLOBAL", 5, 0, 2]
  L_MET_9305675390CA13AC95791CBD84FA3430_38:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_38\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[5] = mrb_gv_get(mrb, mrb_intern(mrb, "$asserts"));
      NEXT;
    }

  // ["OP_STRING", 6, 0, 5]
  L_MET_9305675390CA13AC95791CBD84FA3430_39:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_39\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[6] = mrb_str_new_cstr(mrb, "Error: ");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_MOVE", 7, 1, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_40:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_40\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[7] = regs[1];
      NEXT;
    }

  // ["OP_MOVE", 8, 2, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_41:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_41\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[8] = regs[2];
      NEXT;
    }

  // ["OP_MOVE", 9, 4, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_42:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_42\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[9] = regs[4];
      NEXT;
    }

  // ["OP_ARRAY", 6, 6, 4]
  L_MET_9305675390CA13AC95791CBD84FA3430_43:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_43\n"); fflush(stdout);
{
      /* A B C          R(A) := ary_new(R(B),R(B+1)..R(B+C)) */
      regs[6] = mrb_ary_new_from_values(mrb, 4, &regs[6]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 5, 3, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_44:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_44\n"); fflush(stdout);
{
      int a = 5;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "push"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_GETGLOBAL", 5, 0, 10]
  L_MET_9305675390CA13AC95791CBD84FA3430_45:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_45\n"); fflush(stdout);
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[5] = mrb_gv_get(mrb, mrb_intern(mrb, "$kill_test"));
      NEXT;
    }

  // ["OP_ADDI", 5, 5, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_46:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_46\n"); fflush(stdout);
{
      /* A B C  R(A) := R(A)+C (Syms[B]=:+)*/
      int a = 5;

      /* need to check if + is overridden */
      switch (mrb_type(regs[a])) {
      case MRB_TT_FIXNUM:
  {
    mrb_int x = regs[a].attr_i;
    mrb_int y = 1;
    mrb_int z = x + y;

    if (((x < 0) ^ (y < 0)) == 0 && (x < 0) != (z < 0)) {
      /* integer overflow */
      SET_FLT_VALUE(regs[a], (mrb_float)x + (mrb_float)y);
      break;
    }
    regs[a].attr_i = z;
  }
        break;
      case MRB_TT_FLOAT:
        regs[a].attr_f += 1;
        break;
      default:
        SET_INT_VALUE(regs[a+1], 1);

        regs[a] = mrb_funcall_with_block(mrb, regs[a], mrb_intern(mrb, "+"), 1, &regs[a+1], mrb_nil_value());
      }
      NEXT;
    }

  // ["OP_SETGLOBAL", 5, 0, 10]
  L_MET_9305675390CA13AC95791CBD84FA3430_47:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_47\n"); fflush(stdout);
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, "$kill_test"), regs[5]);
      NEXT;
    }

  // ["OP_LOADSELF", 5, 0, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_48:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_48\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[5] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 6, 0, 6]
  L_MET_9305675390CA13AC95791CBD84FA3430_49:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_49\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[6] = mrb_str_new_cstr(mrb, "X");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 5, 6, 1]
  L_MET_9305675390CA13AC95791CBD84FA3430_50:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_50\n"); fflush(stdout);
{
      int a = 5;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMP", 0, 256, 2]
  L_MET_9305675390CA13AC95791CBD84FA3430_51:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_51\n"); fflush(stdout);
goto L_MET_9305675390CA13AC95791CBD84FA3430_54;
  // ["OP_RAISE", 5, 0, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_52:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_52\n"); fflush(stdout);
{
      /* A      raise(R(A)) */
      mrb->exc = (struct RObject*)mrb_object(regs[5]);
      mrbb_raise(mrb, prev_jmp);
    }

  // ["OP_POPERR", 1, 0, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_53:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_53\n"); fflush(stdout);
{
      int a = 1;

      while (a--) {
        mrb->ci->ridx--;
      }
      NEXT;
    }

  // ["OP_RETURN", 5, 0, 0]
  L_MET_9305675390CA13AC95791CBD84FA3430_54:
    printf("L_MET_9305675390CA13AC95791CBD84FA3430_54\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[5];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_1718f7e893b5498d22c7a398c86ddcc3(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (6 < 3) ? 3 : 6, 3);
  }
  else {
    stack_extend(mrb, 6, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 6 + 2;
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

  // ["OP_ENTER", 8, 0, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_0:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_0\n"); fflush(stdout);
{
      /* Ax             arg setup according to flags (24=5:5:1:5:5:1:1) */
      /* number of optional arguments times OP_JMP should follow */
      int ax = 524288;
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
      mrbb_raise(mrb, prev_jmp);
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
   goto L_MET_1718F7E893B5498D22C7A398C86DDCC3_1;
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
        goto L_MET_1718F7E893B5498D22C7A398C86DDCC3_1;
      }

    }

  // ["OP_LOADSELF", 4, 0, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_1:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_1\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[4] = regs[0];
      NEXT;
    }

  // ["OP_MOVE", 5, 1, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_2:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_2\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[5] = regs[1];
      NEXT;
    }

  // ["OP_SEND", 4, 0, 1]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_3:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_3\n"); fflush(stdout);
{
      int a = 4;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_MOVE", 4, 2, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_4:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_4\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[4] = regs[2];
      NEXT;
    }

  // ["OP_STRING", 5, 0, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_5:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_5\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[5] = mrb_str_new_cstr(mrb, "");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 4, 1, 1]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_6:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_6\n"); fflush(stdout);
{
      int a = 4;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "!="), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMPNOT", 4, 256, 10]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_7:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_7\n"); fflush(stdout);
{
      /* A sBx  if R(A) pc+=sBx */
      if (!mrb_test(regs[4])) {
        goto L_MET_1718F7E893B5498D22C7A398C86DDCC3_18;
      }
      NEXT;
    }

  // ["OP_LOADSELF", 4, 0, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_8:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_8\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[4] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 5, 0, 1]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_9:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_9\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[5] = mrb_str_new_cstr(mrb, " [");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 4, 0, 1]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_10:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_10\n"); fflush(stdout);
{
      int a = 4;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 4, 0, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_11:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_11\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[4] = regs[0];
      NEXT;
    }

  // ["OP_MOVE", 5, 2, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_12:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_12\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[5] = regs[2];
      NEXT;
    }

  // ["OP_SEND", 4, 0, 1]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_13:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_13\n"); fflush(stdout);
{
      int a = 4;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 4, 0, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_14:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_14\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[4] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 5, 0, 2]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_15:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_15\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[5] = mrb_str_new_cstr(mrb, "]");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SEND", 4, 0, 1]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_16:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_16\n"); fflush(stdout);
{
      int a = 4;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "print"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADNIL", 4, 0, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_17:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_17\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 4;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 4, 0, 0]
  L_MET_1718F7E893B5498D22C7A398C86DDCC3_18:
    printf("L_MET_1718F7E893B5498D22C7A398C86DDCC3_18\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[4];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_aea80e2db87abe00360a855d947cdb60(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_AEA80E2DB87ABE00360A855D947CDB60_0:
    printf("L_MET_AEA80E2DB87ABE00360A855D947CDB60_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_AEA80E2DB87ABE00360A855D947CDB60_1:
    printf("L_MET_AEA80E2DB87ABE00360A855D947CDB60_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_57f280f1d71162b253088e091c13aceb(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_57F280F1D71162B253088E091C13ACEB_0:
    printf("L_MET_57F280F1D71162B253088E091C13ACEB_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_57F280F1D71162B253088E091C13ACEB_1:
    printf("L_MET_57F280F1D71162B253088E091C13ACEB_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_ae1682ed047769c9346bcb0ac804c2e4(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_AE1682ED047769C9346BCB0AC804C2E4_0:
    printf("L_MET_AE1682ED047769C9346BCB0AC804C2E4_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_AE1682ED047769C9346BCB0AC804C2E4_1:
    printf("L_MET_AE1682ED047769C9346BCB0AC804C2E4_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_0f22b35e6bed74c3a67e67daee70b7d1(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_0F22B35E6BED74C3A67E67DAEE70B7D1_0:
    printf("L_MET_0F22B35E6BED74C3A67E67DAEE70B7D1_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_0F22B35E6BED74C3A67E67DAEE70B7D1_1:
    printf("L_MET_0F22B35E6BED74C3A67E67DAEE70B7D1_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_dd0b648293af44a4013c7b9d4e62c07b(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_DD0B648293AF44A4013C7B9D4E62C07B_0:
    printf("L_MET_DD0B648293AF44A4013C7B9D4E62C07B_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_DD0B648293AF44A4013C7B9D4E62C07B_1:
    printf("L_MET_DD0B648293AF44A4013C7B9D4E62C07B_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_ad6589f88808f83e12294d79469f8e38(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_AD6589F88808F83E12294D79469F8E38_0:
    printf("L_MET_AD6589F88808F83E12294D79469F8E38_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_AD6589F88808F83E12294D79469F8E38_1:
    printf("L_MET_AD6589F88808F83E12294D79469F8E38_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_c08e9a1dac667ded351f185af6300db6(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_C08E9A1DAC667DED351F185AF6300DB6_0:
    printf("L_MET_C08E9A1DAC667DED351F185AF6300DB6_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_C08E9A1DAC667DED351F185AF6300DB6_1:
    printf("L_MET_C08E9A1DAC667DED351F185AF6300DB6_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_f21ea0e0b0d173ca88ffa97f20559838(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_F21EA0E0B0D173CA88FFA97F20559838_0:
    printf("L_MET_F21EA0E0B0D173CA88FFA97F20559838_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_F21EA0E0B0D173CA88FFA97F20559838_1:
    printf("L_MET_F21EA0E0B0D173CA88FFA97F20559838_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_b93e8bdf062b16ef3905ef33fcc65f45(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_B93E8BDF062B16EF3905EF33FCC65F45_0:
    printf("L_MET_B93E8BDF062B16EF3905EF33FCC65F45_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_B93E8BDF062B16EF3905EF33FCC65F45_1:
    printf("L_MET_B93E8BDF062B16EF3905EF33FCC65F45_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_fd8bc0b037562fcab31a0f19baa69bc4(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_FD8BC0B037562FCAB31A0F19BAA69BC4_0:
    printf("L_MET_FD8BC0B037562FCAB31A0F19BAA69BC4_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_FD8BC0B037562FCAB31A0F19BAA69BC4_1:
    printf("L_MET_FD8BC0B037562FCAB31A0F19BAA69BC4_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_46e2ebdc5ec31c5b1687827c85ca6cda(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_46E2EBDC5EC31C5B1687827C85CA6CDA_0:
    printf("L_MET_46E2EBDC5EC31C5B1687827C85CA6CDA_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_46E2EBDC5EC31C5B1687827C85CA6CDA_1:
    printf("L_MET_46E2EBDC5EC31C5B1687827C85CA6CDA_1\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_31ed664cde450501034e1bee1c98f716(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (6 < 3) ? 3 : 6, 3);
  }
  else {
    stack_extend(mrb, 6, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 6 + 2;
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

  // ["OP_ENTER", 0, 32, 1]
  L_MET_31ED664CDE450501034E1BEE1C98F716_0:
    printf("L_MET_31ED664CDE450501034E1BEE1C98F716_0\n"); fflush(stdout);
{
      /* Ax             arg setup according to flags (24=5:5:1:5:5:1:1) */
      /* number of optional arguments times OP_JMP should follow */
      int ax = 4097;
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
      mrbb_raise(mrb, prev_jmp);
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
   goto L_MET_31ED664CDE450501034E1BEE1C98F716_1;
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
        goto L_MET_31ED664CDE450501034E1BEE1C98F716_1;
      }

    }

  // ["OP_LOADSELF", 3, 0, 0]
  L_MET_31ED664CDE450501034E1BEE1C98F716_1:
    printf("L_MET_31ED664CDE450501034E1BEE1C98F716_1\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[3] = regs[0];
      NEXT;
    }

  // ["OP_ARRAY", 4, 4, 0]
  L_MET_31ED664CDE450501034E1BEE1C98F716_2:
    printf("L_MET_31ED664CDE450501034E1BEE1C98F716_2\n"); fflush(stdout);
{
      /* A B C          R(A) := ary_new(R(B),R(B+1)..R(B+C)) */
      regs[4] = mrb_ary_new_from_values(mrb, 0, &regs[4]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_MOVE", 5, 1, 0]
  L_MET_31ED664CDE450501034E1BEE1C98F716_3:
    printf("L_MET_31ED664CDE450501034E1BEE1C98F716_3\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[5] = regs[1];
      NEXT;
    }

  // ["OP_ARYCAT", 4, 5, 0]
  L_MET_31ED664CDE450501034E1BEE1C98F716_4:
    printf("L_MET_31ED664CDE450501034E1BEE1C98F716_4\n"); fflush(stdout);
{
      /* A B            mrb_ary_concat(R(A),R(B)) */
      mrb_ary_concat(mrb, regs[4],
                     mrb_ary_splat(mrb, regs[5]));
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_MOVE", 5, 2, 0]
  L_MET_31ED664CDE450501034E1BEE1C98F716_5:
    printf("L_MET_31ED664CDE450501034E1BEE1C98F716_5\n"); fflush(stdout);
{
      /* A B    R(A) := R(B) */
      regs[5] = regs[2];
      NEXT;
    }

  // ["OP_SENDB", 3, 0, 127]
  L_MET_31ED664CDE450501034E1BEE1C98F716_6:
    printf("L_MET_31ED664CDE450501034E1BEE1C98F716_6\n"); fflush(stdout);
{
      int a = 3;
      int n = 127;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "new"), n, &regs[a+1], regs[a+n+1]);
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_RETURN", 3, 0, 0]
  L_MET_31ED664CDE450501034E1BEE1C98F716_7:
    printf("L_MET_31ED664CDE450501034E1BEE1C98F716_7\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[3];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value met_21b6e904e67a6d414b30ed56a9f783ae(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (2 < 3) ? 3 : 2, 3);
  }
  else {
    stack_extend(mrb, 2, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 2 + 2;
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

  // ["OP_LOADSELF", 1, 0, 0]
  L_MET_21B6E904E67A6D414B30ED56A9F783AE_0:
    printf("L_MET_21B6E904E67A6D414B30ED56A9F783AE_0\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[1] = regs[0];
      NEXT;
    }

  // ["OP_SCLASS", 1, 1, 0]
  L_MET_21B6E904E67A6D414B30ED56A9F783AE_1:
    printf("L_MET_21B6E904E67A6D414B30ED56A9F783AE_1\n"); fflush(stdout);
{
      /* A B    R(A) := R(B).singleton_class */
      regs[1] = mrb_singleton_class(mrb, regs[1]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_LAMBDA", 2, 0, 5]
  L_MET_21B6E904E67A6D414B30ED56A9F783AE_2:
    printf("L_MET_21B6E904E67A6D414B30ED56A9F783AE_2\n"); fflush(stdout);
{
      /* A b c  R(A) := lambda(SEQ[b],c) (b:c = 14:2) */
      struct RProc *p;
      int c = 1;

      if (c & OP_L_CAPTURE) {
        p = mrbb_closure_new(mrb, met_31ed664cde450501034e1bee1c98f716, (unsigned int)1);
      }
      else {
        p = mrbb_proc_new(mrb, met_31ed664cde450501034e1bee1c98f716);
      }
      p->target_class = (mrb->ci) ? mrb->ci->target_class : 0;
      if (c & OP_L_STRICT) p->flags |= MRB_PROC_STRICT;
      regs[2] = mrb_obj_value(p);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_METHOD", 1, 0, 0]
  L_MET_21B6E904E67A6D414B30ED56A9F783AE_3:
    printf("L_MET_21B6E904E67A6D414B30ED56A9F783AE_3\n"); fflush(stdout);
{
      /* A B            R(A).newmethod(Sym(B),R(A+1)) */
      int a = 1;
      struct RClass *c = mrb_class_ptr(regs[a]);

      mrb_define_method_vm(mrb, c, mrb_intern(mrb, "exception"), regs[a+1]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_LOADNIL", 0, 0, 0]
  L_MET_21B6E904E67A6D414B30ED56A9F783AE_4:
    printf("L_MET_21B6E904E67A6D414B30ED56A9F783AE_4\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 0;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_21B6E904E67A6D414B30ED56A9F783AE_5:
    printf("L_MET_21B6E904E67A6D414B30ED56A9F783AE_5\n"); fflush(stdout);
{
      {
        mrb_callinfo *ci = mrb->ci;
        int acc, eidx = mrb->ci->eidx;
        mrb_value v = regs[0];

        if (mrb->exc) {
          mrbb_raise(mrb, 0);
        }

        switch (0) {
        case OP_R_RETURN:
          if (proc->env || !MRB_PROC_STRICT_P(proc)) {
            struct REnv *e = top_env(mrb, proc);

            if (e->cioff < 0) {
              localjump_error(mrb, "return");
              mrbb_raise(mrb, prev_jmp);
            }
            mrb->ci = mrb->cibase + e->cioff;
            break;
          }
        case OP_R_NORMAL:
          if (ci == mrb->cibase) {
            localjump_error(mrb, "return");
            mrbb_raise(mrb, prev_jmp);
          }
          break;
        case OP_R_BREAK:
          if (proc->env->cioff < 0) {
            localjump_error(mrb, "break");
            mrbb_raise(mrb, prev_jmp);
          }
          mrb->ci = mrb->cibase + proc->env->cioff + 1;
          break;
        default:
          /* cannot happen */
          break;
        }

        if (acc >= 0) {
          //printf("RETURN2RB?\n");
          //exit(0);
        }
        while (eidx > mrb->ci[-1].eidx) {
          mrbb_ecall(mrb, mrb->ensure[--eidx]);
        }
        mrb->jmp = prev_jmp;
        /*
        if (acc < 0) {
          mrb->jmp = prev_jmp;
          return v;
        }
        */
        // TODO optimize (cipop in funcall)
        // important with OP_RETURN break
        return v;
      }
    }

}
mrb_value rb_main(mrb_state *mrb, mrb_value self) {
  mrb_value *regs = NULL;
  int ai = mrb->arena_idx;
  jmp_buf *prev_jmp = (jmp_buf *)mrb->jmp; // TODO remove
  jmp_buf *prev_jmp_onerr = prev_jmp; // TODO OP_ONERR?
  jmp_buf *prev_jmp_ensure = prev_jmp; // TODO OP_EPUSH
  struct RProc *proc = mrb->ci->proc;
  mrb_callinfo *ci = mrb->ci;

  // I have to set up my own stack
  if (ci->argc < 0) {
    stack_extend(mrb, (4 < 3) ? 3 : 4, 3);
  }
  else {
    stack_extend(mrb, 4, ci->argc+2);
  }

  //mrb->ci->proc = proc;
  mrb->ci->nregs = 4 + 2;
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

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_0:
    printf("L_RB_MAIN_0\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_LOADNIL", 2, 0, 0]
  L_RB_MAIN_1:
    printf("L_RB_MAIN_1\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 2;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_CLASS", 1, 0, 0]
  L_RB_MAIN_2:
    printf("L_RB_MAIN_2\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "Exception");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 1]
  L_RB_MAIN_3:
    printf("L_RB_MAIN_3\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_21b6e904e67a6d414b30ed56a9f783ae);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_21b6e904e67a6d414b30ed56a9f783ae]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_4:
    printf("L_RB_MAIN_4\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 1]
  L_RB_MAIN_5:
    printf("L_RB_MAIN_5\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "StandardError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 2, 0]
  L_RB_MAIN_6:
    printf("L_RB_MAIN_6\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "ArgumentError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 3]
  L_RB_MAIN_7:
    printf("L_RB_MAIN_7\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_46e2ebdc5ec31c5b1687827c85ca6cda);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_46e2ebdc5ec31c5b1687827c85ca6cda]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_8:
    printf("L_RB_MAIN_8\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 1]
  L_RB_MAIN_9:
    printf("L_RB_MAIN_9\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "StandardError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 3, 0]
  L_RB_MAIN_10:
    printf("L_RB_MAIN_10\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "LocalJumpError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 4]
  L_RB_MAIN_11:
    printf("L_RB_MAIN_11\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_fd8bc0b037562fcab31a0f19baa69bc4);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_fd8bc0b037562fcab31a0f19baa69bc4]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_12:
    printf("L_RB_MAIN_12\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 1]
  L_RB_MAIN_13:
    printf("L_RB_MAIN_13\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "StandardError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 4, 0]
  L_RB_MAIN_14:
    printf("L_RB_MAIN_14\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "RangeError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 5]
  L_RB_MAIN_15:
    printf("L_RB_MAIN_15\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_b93e8bdf062b16ef3905ef33fcc65f45);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_b93e8bdf062b16ef3905ef33fcc65f45]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_16:
    printf("L_RB_MAIN_16\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 4]
  L_RB_MAIN_17:
    printf("L_RB_MAIN_17\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "RangeError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 5, 0]
  L_RB_MAIN_18:
    printf("L_RB_MAIN_18\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "FloatDomainError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 6]
  L_RB_MAIN_19:
    printf("L_RB_MAIN_19\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_f21ea0e0b0d173ca88ffa97f20559838);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_f21ea0e0b0d173ca88ffa97f20559838]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_20:
    printf("L_RB_MAIN_20\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 1]
  L_RB_MAIN_21:
    printf("L_RB_MAIN_21\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "StandardError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 6, 0]
  L_RB_MAIN_22:
    printf("L_RB_MAIN_22\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "RegexpError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 7]
  L_RB_MAIN_23:
    printf("L_RB_MAIN_23\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_c08e9a1dac667ded351f185af6300db6);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_c08e9a1dac667ded351f185af6300db6]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_24:
    printf("L_RB_MAIN_24\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 1]
  L_RB_MAIN_25:
    printf("L_RB_MAIN_25\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "StandardError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 7, 0]
  L_RB_MAIN_26:
    printf("L_RB_MAIN_26\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "TypeError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 8]
  L_RB_MAIN_27:
    printf("L_RB_MAIN_27\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_ad6589f88808f83e12294d79469f8e38);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_ad6589f88808f83e12294d79469f8e38]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_28:
    printf("L_RB_MAIN_28\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 1]
  L_RB_MAIN_29:
    printf("L_RB_MAIN_29\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "StandardError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 8, 0]
  L_RB_MAIN_30:
    printf("L_RB_MAIN_30\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "NameError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 9]
  L_RB_MAIN_31:
    printf("L_RB_MAIN_31\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_dd0b648293af44a4013c7b9d4e62c07b);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_dd0b648293af44a4013c7b9d4e62c07b]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_32:
    printf("L_RB_MAIN_32\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 8]
  L_RB_MAIN_33:
    printf("L_RB_MAIN_33\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "NameError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 9, 0]
  L_RB_MAIN_34:
    printf("L_RB_MAIN_34\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "NoMethodError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 10]
  L_RB_MAIN_35:
    printf("L_RB_MAIN_35\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_0f22b35e6bed74c3a67e67daee70b7d1);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_0f22b35e6bed74c3a67e67daee70b7d1]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_36:
    printf("L_RB_MAIN_36\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 1]
  L_RB_MAIN_37:
    printf("L_RB_MAIN_37\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "StandardError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 10, 0]
  L_RB_MAIN_38:
    printf("L_RB_MAIN_38\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "IndexError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 11]
  L_RB_MAIN_39:
    printf("L_RB_MAIN_39\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_ae1682ed047769c9346bcb0ac804c2e4);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_ae1682ed047769c9346bcb0ac804c2e4]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_40:
    printf("L_RB_MAIN_40\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 10]
  L_RB_MAIN_41:
    printf("L_RB_MAIN_41\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "IndexError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 11, 0]
  L_RB_MAIN_42:
    printf("L_RB_MAIN_42\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "KeyError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 12]
  L_RB_MAIN_43:
    printf("L_RB_MAIN_43\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_57f280f1d71162b253088e091c13aceb);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_57f280f1d71162b253088e091c13aceb]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADNIL", 1, 0, 0]
  L_RB_MAIN_44:
    printf("L_RB_MAIN_44\n"); fflush(stdout);
{
      /* A B    R(A) := nil */
      int a = 1;

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

  // ["OP_GETCONST", 2, 0, 12]
  L_RB_MAIN_45:
    printf("L_RB_MAIN_45\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[2] = mrb_vm_const_get(mrb, mrb_intern(mrb, "ScriptError"));
      NEXT;
    }

  // ["OP_CLASS", 1, 13, 0]
  L_RB_MAIN_46:
    printf("L_RB_MAIN_46\n"); fflush(stdout);
{
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = 1;
      mrb_value base, super;
      mrb_sym id = mrb_intern(mrb, "NotImplementedError");

      base = regs[a];
      super = regs[a+1];
      if (mrb_nil_p(base)) {
        base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_class(mrb, base, super, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_EXEC", 1, 0, 13]
  L_RB_MAIN_47:
    printf("L_RB_MAIN_47\n"); fflush(stdout);
{
      /* A Bx   R(A) := blockexec(R(A),SEQ[Bx]) */
      int a = 1;
      mrb_callinfo *ci;
      mrb_value recv = regs[a];
      struct RProc *p;

      /* prepare stack */
      ci = cipush(mrb);
      //ci->pc = pc + 1;
      ci->acc = a;
      ci->mid = 0;
      ci->stackidx = mrb->stack - mrb->stbase;
      ci->argc = 0;
      ci->target_class = mrb_class_ptr(recv); // TODO: check if we might need mrb_class() instead

      /* prepare stack */
      mrb->stack += a;

      p = mrbb_proc_new(mrb, met_aea80e2db87abe00360a855d947cdb60);
      // p = mrb_proc_new(mrb, mrb->irep[irep->idx+met_aea80e2db87abe00360a855d947cdb60]);
      p->target_class = ci->target_class;
      ci->proc = p;

      // if (MRB_PROC_CFUNC_P(p)) {
      // else part removed since it is always CFUNC

      mrb->stack[0] = p->body.func(mrb, recv);
      mrb->arena_idx = ai;
      if (mrb->exc) mrbb_raise(mrb, prev_jmp);
      /* pop stackpos */
      regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
      cipop(mrb);
      NEXT;
    }

  // ["OP_LOADI", 1, 255, 127]
  L_RB_MAIN_48:
    printf("L_RB_MAIN_48\n"); fflush(stdout);
{
      /* A Bx   R(A) := sBx */
      SET_INT_VALUE(regs[1], 0);
      NEXT;
    }

  // ["OP_SETGLOBAL", 1, 0, 14]
  L_RB_MAIN_49:
    printf("L_RB_MAIN_49\n"); fflush(stdout);
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, "$ok_test"), regs[1]);
      NEXT;
    }

  // ["OP_LOADI", 1, 255, 127]
  L_RB_MAIN_50:
    printf("L_RB_MAIN_50\n"); fflush(stdout);
{
      /* A Bx   R(A) := sBx */
      SET_INT_VALUE(regs[1], 0);
      NEXT;
    }

  // ["OP_SETGLOBAL", 1, 0, 15]
  L_RB_MAIN_51:
    printf("L_RB_MAIN_51\n"); fflush(stdout);
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, "$ko_test"), regs[1]);
      NEXT;
    }

  // ["OP_LOADI", 1, 255, 127]
  L_RB_MAIN_52:
    printf("L_RB_MAIN_52\n"); fflush(stdout);
{
      /* A Bx   R(A) := sBx */
      SET_INT_VALUE(regs[1], 0);
      NEXT;
    }

  // ["OP_SETGLOBAL", 1, 0, 16]
  L_RB_MAIN_53:
    printf("L_RB_MAIN_53\n"); fflush(stdout);
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, "$kill_test"), regs[1]);
      NEXT;
    }

  // ["OP_ARRAY", 1, 1, 0]
  L_RB_MAIN_54:
    printf("L_RB_MAIN_54\n"); fflush(stdout);
{
      /* A B C          R(A) := ary_new(R(B),R(B+1)..R(B+C)) */
      regs[1] = mrb_ary_new_from_values(mrb, 0, &regs[1]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SETGLOBAL", 1, 0, 17]
  L_RB_MAIN_55:
    printf("L_RB_MAIN_55\n"); fflush(stdout);
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, "$asserts"), regs[1]);
      NEXT;
    }

  // ["OP_GETCONST", 1, 0, 18]
  L_RB_MAIN_56:
    printf("L_RB_MAIN_56\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[1] = mrb_vm_const_get(mrb, mrb_intern(mrb, "Object"));
      NEXT;
    }

  // ["OP_LOADSYM", 2, 0, 20]
  L_RB_MAIN_57:
    printf("L_RB_MAIN_57\n"); fflush(stdout);
{
      /* A B    R(A) := Sym(B) */
      SET_SYM_VALUE(regs[2], mrb_intern(mrb, "Time"));
      NEXT;
    }

  // ["OP_SEND", 1, 19, 1]
  L_RB_MAIN_58:
    printf("L_RB_MAIN_58\n"); fflush(stdout);
{
      int a = 1;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "const_defined?"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_JMPNOT", 1, 256, 3]
  L_RB_MAIN_59:
    printf("L_RB_MAIN_59\n"); fflush(stdout);
{
      /* A sBx  if R(A) pc+=sBx */
      if (!mrb_test(regs[1])) {
        goto L_RB_MAIN_63;
      }
      NEXT;
    }

  // ["OP_GETCONST", 1, 0, 20]
  L_RB_MAIN_60:
    printf("L_RB_MAIN_60\n"); fflush(stdout);
{
      /* A B    R(A) := constget(Sym(B)) */
      regs[1] = mrb_vm_const_get(mrb, mrb_intern(mrb, "Time"));
      NEXT;
    }

  // ["OP_SEND", 1, 21, 0]
  L_RB_MAIN_61:
    printf("L_RB_MAIN_61\n"); fflush(stdout);
{
      int a = 1;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "now"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_SETGLOBAL", 1, 0, 22]
  L_RB_MAIN_62:
    printf("L_RB_MAIN_62\n"); fflush(stdout);
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, "$test_start"), regs[1]);
      NEXT;
    }

  // ["OP_TCLASS", 1, 0, 0]
  L_RB_MAIN_63:
    printf("L_RB_MAIN_63\n"); fflush(stdout);
{
      /* A B    R(A) := target_class */
      if (!mrb->ci->target_class) {
        static const char msg[] = "no target class or module";
        mrb_value exc = mrb_exc_new(mrb, E_TYPE_ERROR, msg, sizeof(msg) - 1);
        mrb->exc = (struct RObject*)mrb_object(exc);
        mrbb_raise(mrb, prev_jmp);
      }
      regs[1] = mrb_obj_value(mrb->ci->target_class);
      NEXT;
    }

  // ["OP_LAMBDA", 2, 0, 57]
  L_RB_MAIN_64:
    printf("L_RB_MAIN_64\n"); fflush(stdout);
{
      /* A b c  R(A) := lambda(SEQ[b],c) (b:c = 14:2) */
      struct RProc *p;
      int c = 1;

      if (c & OP_L_CAPTURE) {
        p = mrbb_closure_new(mrb, met_1718f7e893b5498d22c7a398c86ddcc3, (unsigned int)1);
      }
      else {
        p = mrbb_proc_new(mrb, met_1718f7e893b5498d22c7a398c86ddcc3);
      }
      p->target_class = (mrb->ci) ? mrb->ci->target_class : 0;
      if (c & OP_L_STRICT) p->flags |= MRB_PROC_STRICT;
      regs[2] = mrb_obj_value(p);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_METHOD", 1, 23, 0]
  L_RB_MAIN_65:
    printf("L_RB_MAIN_65\n"); fflush(stdout);
{
      /* A B            R(A).newmethod(Sym(B),R(A+1)) */
      int a = 1;
      struct RClass *c = mrb_class_ptr(regs[a]);

      mrb_define_method_vm(mrb, c, mrb_intern(mrb, "print_assertion_string"), regs[a+1]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_TCLASS", 1, 0, 0]
  L_RB_MAIN_66:
    printf("L_RB_MAIN_66\n"); fflush(stdout);
{
      /* A B    R(A) := target_class */
      if (!mrb->ci->target_class) {
        static const char msg[] = "no target class or module";
        mrb_value exc = mrb_exc_new(mrb, E_TYPE_ERROR, msg, sizeof(msg) - 1);
        mrb->exc = (struct RObject*)mrb_object(exc);
        mrbb_raise(mrb, prev_jmp);
      }
      regs[1] = mrb_obj_value(mrb->ci->target_class);
      NEXT;
    }

  // ["OP_LAMBDA", 2, 0, 61]
  L_RB_MAIN_67:
    printf("L_RB_MAIN_67\n"); fflush(stdout);
{
      /* A b c  R(A) := lambda(SEQ[b],c) (b:c = 14:2) */
      struct RProc *p;
      int c = 1;

      if (c & OP_L_CAPTURE) {
        p = mrbb_closure_new(mrb, met_9305675390ca13ac95791cbd84fa3430, (unsigned int)1);
      }
      else {
        p = mrbb_proc_new(mrb, met_9305675390ca13ac95791cbd84fa3430);
      }
      p->target_class = (mrb->ci) ? mrb->ci->target_class : 0;
      if (c & OP_L_STRICT) p->flags |= MRB_PROC_STRICT;
      regs[2] = mrb_obj_value(p);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_METHOD", 1, 24, 0]
  L_RB_MAIN_68:
    printf("L_RB_MAIN_68\n"); fflush(stdout);
{
      /* A B            R(A).newmethod(Sym(B),R(A+1)) */
      int a = 1;
      struct RClass *c = mrb_class_ptr(regs[a]);

      mrb_define_method_vm(mrb, c, mrb_intern(mrb, "assert"), regs[a+1]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_TCLASS", 1, 0, 0]
  L_RB_MAIN_69:
    printf("L_RB_MAIN_69\n"); fflush(stdout);
{
      /* A B    R(A) := target_class */
      if (!mrb->ci->target_class) {
        static const char msg[] = "no target class or module";
        mrb_value exc = mrb_exc_new(mrb, E_TYPE_ERROR, msg, sizeof(msg) - 1);
        mrb->exc = (struct RObject*)mrb_object(exc);
        mrbb_raise(mrb, prev_jmp);
      }
      regs[1] = mrb_obj_value(mrb->ci->target_class);
      NEXT;
    }

  // ["OP_LAMBDA", 2, 0, 65]
  L_RB_MAIN_70:
    printf("L_RB_MAIN_70\n"); fflush(stdout);
{
      /* A b c  R(A) := lambda(SEQ[b],c) (b:c = 14:2) */
      struct RProc *p;
      int c = 1;

      if (c & OP_L_CAPTURE) {
        p = mrbb_closure_new(mrb, met_d850708a9e8f210f954ee48c12c1486a, (unsigned int)1);
      }
      else {
        p = mrbb_proc_new(mrb, met_d850708a9e8f210f954ee48c12c1486a);
      }
      p->target_class = (mrb->ci) ? mrb->ci->target_class : 0;
      if (c & OP_L_STRICT) p->flags |= MRB_PROC_STRICT;
      regs[2] = mrb_obj_value(p);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_METHOD", 1, 25, 0]
  L_RB_MAIN_71:
    printf("L_RB_MAIN_71\n"); fflush(stdout);
{
      /* A B            R(A).newmethod(Sym(B),R(A+1)) */
      int a = 1;
      struct RClass *c = mrb_class_ptr(regs[a]);

      mrb_define_method_vm(mrb, c, mrb_intern(mrb, "report"), regs[a+1]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_TCLASS", 1, 0, 0]
  L_RB_MAIN_72:
    printf("L_RB_MAIN_72\n"); fflush(stdout);
{
      /* A B    R(A) := target_class */
      if (!mrb->ci->target_class) {
        static const char msg[] = "no target class or module";
        mrb_value exc = mrb_exc_new(mrb, E_TYPE_ERROR, msg, sizeof(msg) - 1);
        mrb->exc = (struct RObject*)mrb_object(exc);
        mrbb_raise(mrb, prev_jmp);
      }
      regs[1] = mrb_obj_value(mrb->ci->target_class);
      NEXT;
    }

  // ["OP_LAMBDA", 2, 0, 73]
  L_RB_MAIN_73:
    printf("L_RB_MAIN_73\n"); fflush(stdout);
{
      /* A b c  R(A) := lambda(SEQ[b],c) (b:c = 14:2) */
      struct RProc *p;
      int c = 1;

      if (c & OP_L_CAPTURE) {
        p = mrbb_closure_new(mrb, met_af96e0a4b0ea390745b073e911bb8867, (unsigned int)1);
      }
      else {
        p = mrbb_proc_new(mrb, met_af96e0a4b0ea390745b073e911bb8867);
      }
      p->target_class = (mrb->ci) ? mrb->ci->target_class : 0;
      if (c & OP_L_STRICT) p->flags |= MRB_PROC_STRICT;
      regs[2] = mrb_obj_value(p);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_METHOD", 1, 26, 0]
  L_RB_MAIN_74:
    printf("L_RB_MAIN_74\n"); fflush(stdout);
{
      /* A B            R(A).newmethod(Sym(B),R(A+1)) */
      int a = 1;
      struct RClass *c = mrb_class_ptr(regs[a]);

      mrb_define_method_vm(mrb, c, mrb_intern(mrb, "check_float"), regs[a+1]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_TCLASS", 1, 0, 0]
  L_RB_MAIN_75:
    printf("L_RB_MAIN_75\n"); fflush(stdout);
{
      /* A B    R(A) := target_class */
      if (!mrb->ci->target_class) {
        static const char msg[] = "no target class or module";
        mrb_value exc = mrb_exc_new(mrb, E_TYPE_ERROR, msg, sizeof(msg) - 1);
        mrb->exc = (struct RObject*)mrb_object(exc);
        mrbb_raise(mrb, prev_jmp);
      }
      regs[1] = mrb_obj_value(mrb->ci->target_class);
      NEXT;
    }

  // ["OP_LAMBDA", 2, 0, 77]
  L_RB_MAIN_76:
    printf("L_RB_MAIN_76\n"); fflush(stdout);
{
      /* A b c  R(A) := lambda(SEQ[b],c) (b:c = 14:2) */
      struct RProc *p;
      int c = 1;

      if (c & OP_L_CAPTURE) {
        p = mrbb_closure_new(mrb, met_e88725a55dac71cfe4a45fc2b3bdea2c, (unsigned int)1);
      }
      else {
        p = mrbb_proc_new(mrb, met_e88725a55dac71cfe4a45fc2b3bdea2c);
      }
      p->target_class = (mrb->ci) ? mrb->ci->target_class : 0;
      if (c & OP_L_STRICT) p->flags |= MRB_PROC_STRICT;
      regs[2] = mrb_obj_value(p);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_METHOD", 1, 27, 0]
  L_RB_MAIN_77:
    printf("L_RB_MAIN_77\n"); fflush(stdout);
{
      /* A B            R(A).newmethod(Sym(B),R(A+1)) */
      int a = 1;
      struct RClass *c = mrb_class_ptr(regs[a]);

      mrb_define_method_vm(mrb, c, mrb_intern(mrb, "exception_test14"), regs[a+1]);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_LOADSELF", 1, 0, 0]
  L_RB_MAIN_78:
    printf("L_RB_MAIN_78\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[1] = regs[0];
      NEXT;
    }

  // ["OP_STRING", 2, 0, 0]
  L_RB_MAIN_79:
    printf("L_RB_MAIN_79\n"); fflush(stdout);
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[2] = mrb_str_new_cstr(mrb, "Exception 14");
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_LAMBDA", 3, 0, 82]
  L_RB_MAIN_80:
    printf("L_RB_MAIN_80\n"); fflush(stdout);
{
      /* A b c  R(A) := lambda(SEQ[b],c) (b:c = 14:2) */
      struct RProc *p;
      int c = 2;

      if (c & OP_L_CAPTURE) {
        p = mrbb_closure_new(mrb, met_9c41e26864a307612a65c0efc525d451, (unsigned int)1);
      }
      else {
        p = mrbb_proc_new(mrb, met_9c41e26864a307612a65c0efc525d451);
      }
      p->target_class = (mrb->ci) ? mrb->ci->target_class : 0;
      if (c & OP_L_STRICT) p->flags |= MRB_PROC_STRICT;
      regs[3] = mrb_obj_value(p);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SENDB", 1, 24, 1]
  L_RB_MAIN_81:
    printf("L_RB_MAIN_81\n"); fflush(stdout);
{
      int a = 1;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "assert"), n, &regs[a+1], regs[a+n+1]);
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_LOADSELF", 1, 0, 0]
  L_RB_MAIN_82:
    printf("L_RB_MAIN_82\n"); fflush(stdout);
{
      /* A      R(A) := self */
      regs[1] = regs[0];
      NEXT;
    }

  // ["OP_SEND", 1, 25, 0]
  L_RB_MAIN_83:
    printf("L_RB_MAIN_83\n"); fflush(stdout);
{
      int a = 1;
      int n = 0;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "report"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_STOP", 0, 0, 0]
  L_RB_MAIN_84:
    printf("L_RB_MAIN_84\n"); fflush(stdout);
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
