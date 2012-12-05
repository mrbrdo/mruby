
    CASE(OP_ADDI) {
      /* A B C  R(A) := R(A)+C (Syms[B]=:+)*/
      int a = GETARG_A(i);

      /* need to check if + is overridden */
      switch (mrb_type(regs[a])) {
      case MRB_TT_FIXNUM:
  {
    mrb_int x = regs[a].attr_i;
    mrb_int y = GETARG_C(i);
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
        regs[a].attr_f += GETARG_C(i);
        break;
      default:
        regs[a] = mrb_funcall(mrb, regs[a], GETARG_B(i), 1, mrb_fixnum_value(GETARG_C(i)));
      }
      NEXT;
    }

    CASE(OP_ADD) {
      /* A B C  R(A) := R(A)+R(A+1) (Syms[B]=:+,C=1)*/
      int a = GETARG_A(i);

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
  // change
  //    default:
  // goto L_SEND;
      }
      // change
      //mrb->arena_idx = ai;
      NEXT;
    }
