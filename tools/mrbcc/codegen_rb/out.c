mrb_value met_f93c435ce5da72760ae3f13c9773e8e8(mrb_state *mrb, mrb_value self) {
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

/*
        mrb->jmp = prev_jmp_ensure; // TODO: what about retry?
        mrbb_ecall(mrb, mrbb_proc_new(mrb, GETARG_Bx(i)));
        longjmp(*(jmp_buf*)mrb->jmp, 1);
*/

  // ["OP_LOADT", 0, 0, 0]
  L_MET_F93C435CE5DA72760AE3F13C9773E8E8_0:
  {
      /* A      R(A) := true */
      SET_TRUE_VALUE(regs[0]);
      NEXT;
    }

  // ["OP_RETURN", 0, 0, 0]
  L_MET_F93C435CE5DA72760AE3F13C9773E8E8_1:
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

/*
        mrb->jmp = prev_jmp_ensure; // TODO: what about retry?
        mrbb_ecall(mrb, mrbb_proc_new(mrb, GETARG_Bx(i)));
        longjmp(*(jmp_buf*)mrb->jmp, 1);
*/

  // ["OP_LOADSELF", 2, 0, 0]
  L_RB_MAIN_0:
  {
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_LOADSYM", 3, 0, 1]
  L_RB_MAIN_1:
  {
      /* A B    R(A) := Sym(B) */
      SET_SYM_VALUE(regs[3], mrb_intern(mrb, "lambda"));
      NEXT;
    }

  // ["OP_LAMBDA", 4, 0, 6]
  L_RB_MAIN_2:
  {
      /* A b c  R(A) := lambda(SEQ[b],c) (b:c = 14:2) */
      struct RProc *p;
      int c = 2;

      if (c & OP_L_CAPTURE) {
        p = mrbb_closure_new(mrb, met_f93c435ce5da72760ae3f13c9773e8e8, (unsigned int)2);
      }
      else {
        p = mrbb_proc_new(mrb, met_f93c435ce5da72760ae3f13c9773e8e8);
      }
      p->target_class = (mrb->ci) ? mrb->ci->target_class : 0;
      if (c & OP_L_STRICT) p->flags |= MRB_PROC_STRICT;
      regs[4] = mrb_obj_value(p);
      mrb->arena_idx = ai;
      NEXT;
    }

  // ["OP_SENDB", 2, 0, 1]
  L_RB_MAIN_3:
  {
      int a = 2;
      int n = 1;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "__send__"), n, &regs[a+1], regs[a+n+1]);
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_MOVE", 1, 2, 0]
  L_RB_MAIN_4:
  {
      /* A B    R(A) := R(B) */
      regs[1] = regs[2];
      NEXT;
    }

  // ["OP_LOADSELF", 2, 0, 0]
  L_RB_MAIN_5:
  {
      /* A      R(A) := self */
      regs[2] = regs[0];
      NEXT;
    }

  // ["OP_LOADSYM", 3, 0, 2]
  L_RB_MAIN_6:
  {
      /* A B    R(A) := Sym(B) */
      SET_SYM_VALUE(regs[3], mrb_intern(mrb, "respond_to?"));
      NEXT;
    }

  // ["OP_LOADSYM", 4, 0, 3]
  L_RB_MAIN_7:
  {
      /* A B    R(A) := Sym(B) */
      SET_SYM_VALUE(regs[4], mrb_intern(mrb, "nil?"));
      NEXT;
    }

  // ["OP_SEND", 2, 0, 2]
  L_RB_MAIN_8:
  {
      int a = 2;
      int n = 2;
      mrb_callinfo *prev_ci = mrb->ci;

      mrb_p(mrb, regs[a]);
      mrb_p(mrb, regs[a+1]);
      mrb_p(mrb, regs[a+2]);
      printf("MAIN8\n");
      mrb_funcall_fast(mrb, regs[a], mrb_intern(mrb, "__send__"), n, &regs[a+1], mrb_nil_value());
      mrb->arena_idx = ai; // TODO probably can remove
      if (mrb->ci != prev_ci) { // special OP_RETURN (e.g. break)
        cipush(mrb);
        return regs[a];
      }
      NEXT;
  }

  // ["OP_STOP", 0, 0, 0]
  L_RB_MAIN_9:
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
