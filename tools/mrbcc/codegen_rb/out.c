
// 000 OP_STRING R1  "lol"


L_MAIN_0:
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[1] = mrb_str_literal(mrb, pool["lol"]);
      mrb->arena_idx = ai;
      NEXT;
    }
// 001 OP_SETGLOBAL  :$hello R1


L_MAIN_1:
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, 1), regs["$hello"]);
      NEXT;
    }
// 002 OP_GETGLOBAL  R1  :$hello


L_MAIN_2:
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[1] = mrb_gv_get(mrb, mrb_intern(mrb, "$hello"));
      NEXT;
    }
// 003 OP_STRING R2  "hej"


L_MAIN_3:
{
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[2] = mrb_str_literal(mrb, pool["hej"]);
      mrb->arena_idx = ai;
      NEXT;
    }
// 004 OP_ADD  R1  :+  1


L_MAIN_4:
{
      /* A B C  R(A) := R(A)+R(A+1) (Syms[B]=:+,C=1)*/
      int a = 1;

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
  goto L_SEND;
      }
      mrb->arena_idx = ai;
      NEXT;
    }
// 005 OP_SETGLOBAL  :$hello R1


L_MAIN_5:
{
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, mrb_intern(mrb, 1), regs["$hello"]);
      NEXT;
    }
// 006 OP_LOADSELF R1


L_MAIN_6:
{
      /* A      R(A) := self */
      regs[1] = regs[0];
      NEXT;
    }
// 007 OP_GETGLOBAL  R2  :$hello


L_MAIN_7:
{
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[2] = mrb_gv_get(mrb, mrb_intern(mrb, "$hello"));
      NEXT;
    }
// 008 OP_SEND R1  :puts 1


L_MAIN_8:
{
      int a = 1;

      regs[a] = mrb_funcall(mrb, regs[a], "puts", 1, regs[a+1]);
  }
// 009 OP_STOP

L_MAIN_9:
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