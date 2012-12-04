
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
