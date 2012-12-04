    CASE(OP_NOP) {
      /* do nothing */
      NEXT;
    }

    CASE(OP_MOVE) {
      /* A B    R(A) := R(B) */
      regs[GETARG_A(i)] = regs[GETARG_B(i)];
      NEXT;
    }

    CASE(OP_LOADL) {
      /* A Bx   R(A) := Pool(Bx) */
      regs[GETARG_A(i)] = pool[GETARG_Bx(i)];
      NEXT;
    }

    CASE(OP_LOADI) {
      /* A Bx   R(A) := sBx */
      SET_INT_VALUE(regs[GETARG_A(i)], GETARG_sBx(i));
      NEXT;
    }

    CASE(OP_LOADSYM) {
      /* A B    R(A) := Sym(B) */
      SET_SYM_VALUE(regs[GETARG_A(i)], syms[GETARG_Bx(i)]);
      NEXT;
    }

    CASE(OP_LOADSELF) {
      /* A      R(A) := self */
      regs[GETARG_A(i)] = regs[0];
      NEXT;
    }

    CASE(OP_LOADT) {
      /* A      R(A) := true */
      SET_TRUE_VALUE(regs[GETARG_A(i)]);
      NEXT;
    }

    CASE(OP_LOADF) {
      /* A      R(A) := false */
      SET_FALSE_VALUE(regs[GETARG_A(i)]);
      NEXT;
    }

    CASE(OP_GETGLOBAL) {
      /* A B    R(A) := getglobal(Sym(B)) */
      regs[GETARG_A(i)] = mrb_gv_get(mrb, syms[GETARG_Bx(i)]);
      NEXT;
    }

    CASE(OP_SETGLOBAL) {
      /* setglobal(Sym(b), R(A)) */
      mrb_gv_set(mrb, syms[GETARG_Bx(i)], regs[GETARG_A(i)]);
      NEXT;
    }

    CASE(OP_GETSPECIAL) {
      /* A Bx   R(A) := Special[Bx] */
      regs[GETARG_A(i)] = mrb_vm_special_get(mrb, GETARG_Bx(i));
      NEXT;
    }

    CASE(OP_SETSPECIAL) {
      /* A Bx   Special[Bx] := R(A) */
      mrb_vm_special_set(mrb, GETARG_Bx(i), regs[GETARG_A(i)]);
      NEXT;
    }

    CASE(OP_GETIV) {
      /* A Bx   R(A) := ivget(Bx) */
      regs[GETARG_A(i)] = mrb_vm_iv_get(mrb, syms[GETARG_Bx(i)]);
      NEXT;
    }

    CASE(OP_SETIV) {
      /* ivset(Sym(B),R(A)) */
      mrb_vm_iv_set(mrb, syms[GETARG_Bx(i)], regs[GETARG_A(i)]);
      NEXT;
    }

    CASE(OP_GETCV) {
      /* A B    R(A) := ivget(Sym(B)) */
      regs[GETARG_A(i)] = mrb_vm_cv_get(mrb, syms[GETARG_Bx(i)]);
      NEXT;
    }

    CASE(OP_SETCV) {
      /* ivset(Sym(B),R(A)) */
      mrb_vm_cv_set(mrb, syms[GETARG_Bx(i)], regs[GETARG_A(i)]);
      NEXT;
    }

    CASE(OP_GETCONST) {
      /* A B    R(A) := constget(Sym(B)) */
      regs[GETARG_A(i)] = mrb_vm_const_get(mrb, syms[GETARG_Bx(i)]);
      NEXT;
    }

    CASE(OP_SETCONST) {
      /* A B    constset(Sym(B),R(A)) */
      mrb_vm_const_set(mrb, syms[GETARG_Bx(i)], regs[GETARG_A(i)]);
      NEXT;
    }

    CASE(OP_GETMCNST) {
      /* A B C  R(A) := R(C)::Sym(B) */
      int a = GETARG_A(i);

      regs[a] = mrb_const_get(mrb, regs[a], syms[GETARG_Bx(i)]);
      NEXT;
    }

    CASE(OP_SETMCNST) {
      /* A B C  R(A+1)::Sym(B) := R(A) */
      int a = GETARG_A(i);

      mrb_const_set(mrb, regs[a+1], syms[GETARG_Bx(i)], regs[a]);
      NEXT;
    }

    CASE(OP_GETUPVAR) {
      /* A B C  R(A) := uvget(B,C) */

      regs[GETARG_A(i)] = uvget(mrb, GETARG_C(i), GETARG_B(i));
      NEXT;
    }

    CASE(OP_SETUPVAR) {
      /* A B C  uvset(B,C,R(A)) */
      uvset(mrb, GETARG_C(i), GETARG_B(i), regs[GETARG_A(i)]);
      NEXT;
    }

    CASE(OP_LOADNIL) {
      /* A B    R(A) := nil */
      int a = GETARG_A(i);

      SET_NIL_VALUE(regs[a]);
      NEXT;
    }

    CASE(OP_SENDB) {
      /* fall through */
    };

    CASE(OP_FSEND) {
      /* A B C  R(A) := fcall(R(A),Sym(B),R(A+1),... ,R(A+C)) */
      NEXT;
    }


    CASE(OP_KARG) {
      /* A B C          R(A) := kdict[Sym(B)]; if C kdict.rm(Sym(B)) */
      /* if C == 2; raise unless kdict.empty? */
      /* OP_JMP should follow to skip init code */
      NEXT;
    }

    CASE(OP_KDICT) {
      /* A C            R(A) := kdict */
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
      default:
  goto L_SEND;
      }
      mrb->arena_idx = ai;
      NEXT;
    }

    CASE(OP_SUB) {
      /* A B C  R(A) := R(A)-R(A+1) (Syms[B]=:-,C=1)*/
      int a = GETARG_A(i);

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
  goto L_SEND;
      }
      NEXT;
    }

    CASE(OP_MUL) {
      /* A B C  R(A) := R(A)*R(A+1) (Syms[B]=:*,C=1)*/
      int a = GETARG_A(i);

      /* need to check if op is overridden */
      switch (TYPES2(mrb_type(regs[a]),mrb_type(regs[a+1]))) {
      case TYPES2(MRB_TT_FIXNUM,MRB_TT_FIXNUM):
  {
    mrb_int x, y, z;

    x = mrb_fixnum(regs[a]);
    y = mrb_fixnum(regs[a+1]);
    z = x * y;
    if (x != 0 && z/x != y) {
      SET_FLT_VALUE(regs[a], (mrb_float)x * (mrb_float)y);
    }
    else {
      SET_INT_VALUE(regs[a], z);
    }
  }
  break;
      case TYPES2(MRB_TT_FIXNUM,MRB_TT_FLOAT):
  {
    mrb_int x = mrb_fixnum(regs[a]);
    mrb_float y = mrb_float(regs[a+1]);
    SET_FLT_VALUE(regs[a], (mrb_float)x * y);
  }
  break;
      case TYPES2(MRB_TT_FLOAT,MRB_TT_FIXNUM):
  OP_MATH_BODY(*,attr_f,attr_i);
  break;
      case TYPES2(MRB_TT_FLOAT,MRB_TT_FLOAT):
  OP_MATH_BODY(*,attr_f,attr_f);
  break;
      default:
  goto L_SEND;
      }
      NEXT;
    }

    CASE(OP_DIV) {
      /* A B C  R(A) := R(A)/R(A+1) (Syms[B]=:/,C=1)*/
      int a = GETARG_A(i);

      /* need to check if op is overridden */
      switch (TYPES2(mrb_type(regs[a]),mrb_type(regs[a+1]))) {
      case TYPES2(MRB_TT_FIXNUM,MRB_TT_FIXNUM):
  {
    mrb_int x = mrb_fixnum(regs[a]);
    mrb_int y = mrb_fixnum(regs[a+1]);
    SET_FLT_VALUE(regs[a], (mrb_float)x / (mrb_float)y);
  }
  break;
      case TYPES2(MRB_TT_FIXNUM,MRB_TT_FLOAT):
  {
    mrb_int x = mrb_fixnum(regs[a]);
    mrb_float y = mrb_float(regs[a+1]);
    SET_FLT_VALUE(regs[a], (mrb_float)x / y);
  }
  break;
      case TYPES2(MRB_TT_FLOAT,MRB_TT_FIXNUM):
  OP_MATH_BODY(/,attr_f,attr_i);
  break;
      case TYPES2(MRB_TT_FLOAT,MRB_TT_FLOAT):
  OP_MATH_BODY(/,attr_f,attr_f);
  break;
      default:
  goto L_SEND;
      }
      NEXT;
    }

    CASE(OP_SUBI) {
      /* A B C  R(A) := R(A)-C (Syms[B]=:+)*/
      int a = GETARG_A(i);

      /* need to check if + is overridden */
      switch (mrb_type(regs[a])) {
      case MRB_TT_FIXNUM:
  {
    mrb_int x = regs[a].attr_i;
    mrb_int y = GETARG_C(i);
    mrb_int z = x - y;

    if (((x < 0) ^ (y < 0)) == 0 && (x < 0) != (z < 0)) {
      /* integer overflow */
      SET_FLT_VALUE(regs[a], (mrb_float)x - (mrb_float)y);
      break;
    }
    regs[a].attr_i = z;
  }
        break;
      case MRB_TT_FLOAT:
        regs[a].attr_f -= GETARG_C(i);
        break;
      default:
        SET_INT_VALUE(regs[a+1], GETARG_C(i));
        i = MKOP_ABC(OP_SEND, a, GETARG_B(i), 1);
        goto L_SEND;
      }
      NEXT;
    }

    CASE(OP_EQ) {
      /* A B C  R(A) := R(A)<R(A+1) (Syms[B]=:<,C=1)*/
      int a = GETARG_A(i);
      if (mrb_obj_eq(mrb, regs[a], regs[a+1])) {
  SET_TRUE_VALUE(regs[a]);
      }
      else {
  OP_CMP(==);
      }
      NEXT;
    }

    CASE(OP_LT) {
      /* A B C  R(A) := R(A)<R(A+1) (Syms[B]=:<,C=1)*/
      OP_CMP(<);
      NEXT;
    }

    CASE(OP_LE) {
      /* A B C  R(A) := R(A)<R(A+1) (Syms[B]=:<,C=1)*/
      OP_CMP(<=);
      NEXT;
    }

    CASE(OP_GT) {
      /* A B C  R(A) := R(A)<R(A+1) (Syms[B]=:<,C=1)*/
      OP_CMP(>);
      NEXT;
    }

    CASE(OP_GE) {
      /* A B C  R(A) := R(A)<R(A+1) (Syms[B]=:<,C=1)*/
      OP_CMP(>=);
      NEXT;
    }

    CASE(OP_ARRAY) {
      /* A B C          R(A) := ary_new(R(B),R(B+1)..R(B+C)) */
      regs[GETARG_A(i)] = mrb_ary_new_from_values(mrb, GETARG_C(i), &regs[GETARG_B(i)]);
      mrb->arena_idx = ai;
      NEXT;
    }

    CASE(OP_ARYCAT) {
      /* A B            mrb_ary_concat(R(A),R(B)) */
      mrb_ary_concat(mrb, regs[GETARG_A(i)],
                     mrb_ary_splat(mrb, regs[GETARG_B(i)]));
      mrb->arena_idx = ai;
      NEXT;
    }

    CASE(OP_ARYPUSH) {
      /* A B            R(A).push(R(B)) */
      mrb_ary_push(mrb, regs[GETARG_A(i)], regs[GETARG_B(i)]);
      NEXT;
    }

    CASE(OP_AREF) {
      /* A B C          R(A) := R(B)[C] */
      int a = GETARG_A(i);
      int c = GETARG_C(i);
      mrb_value v = regs[GETARG_B(i)];

      if (!mrb_array_p(v)) {
        if (c == 0) {
          regs[GETARG_A(i)] = v;
        }
        else {
          SET_NIL_VALUE(regs[a]);
        }
      }
      else {
  regs[GETARG_A(i)] = mrb_ary_ref(mrb, v, c);
      }
      NEXT;
    }

    CASE(OP_ASET) {
      /* A B C          R(B)[C] := R(A) */
      mrb_ary_set(mrb, regs[GETARG_B(i)], GETARG_C(i), regs[GETARG_A(i)]);
      NEXT;
    }

    CASE(OP_APOST) {
      /* A B C  *R(A),R(A+1)..R(A+C) := R(A) */
      int a = GETARG_A(i);
      mrb_value v = regs[a];
      int pre  = GETARG_B(i);
      int post = GETARG_C(i);

      if (!mrb_array_p(v)) {
        regs[a++] = mrb_ary_new_capa(mrb, 0);
        while (post--) {
          SET_NIL_VALUE(regs[a]);
          a++;
        }
      }
      else {
        struct RArray *ary = mrb_ary_ptr(v);
        int len = ary->len;
        int i;

        if (len > pre + post) {
          regs[a++] = mrb_ary_new_elts(mrb, len - pre - post, ary->ptr+pre);
          while (post--) {
      regs[a++] = ary->ptr[len-post-1];
          }
        }
        else {
    regs[a++] = mrb_ary_new_capa(mrb, 0);
          for (i=0; i+pre<len; i++) {
      regs[a+i] = ary->ptr[pre+i];
          }
          while (i < post) {
            SET_NIL_VALUE(regs[a+i]);
            i++;
          }
        }
      }
      mrb->arena_idx = ai;
      NEXT;
    }

    CASE(OP_STRING) {
      /* A Bx           R(A) := str_new(Lit(Bx)) */
      regs[GETARG_A(i)] = mrb_str_literal(mrb, pool[GETARG_Bx(i)]);
      mrb->arena_idx = ai;
      NEXT;
    }

    CASE(OP_STRCAT) {
      /* A B    R(A).concat(R(B)) */
      mrb_str_concat(mrb, regs[GETARG_A(i)], regs[GETARG_B(i)]);
      NEXT;
    }

    CASE(OP_HASH) {
      /* A B C   R(A) := hash_new(R(B),R(B+1)..R(B+C)) */
      int b = GETARG_B(i);
      int c = GETARG_C(i);
      int lim = b+c*2;
      mrb_value hash = mrb_hash_new_capa(mrb, c);

      while (b < lim) {
        mrb_hash_set(mrb, hash, regs[b], regs[b+1]);
        b+=2;
      }
      regs[GETARG_A(i)] = hash;
      mrb->arena_idx = ai;
      NEXT;
    }

    CASE(OP_OCLASS) {
      /* A      R(A) := ::Object */
      regs[GETARG_A(i)] = mrb_obj_value(mrb->object_class);
      NEXT;
    }

    CASE(OP_CLASS) {
      /* A B    R(A) := newclass(R(A),Sym(B),R(A+1)) */
      struct RClass *c = 0;
      int a = GETARG_A(i);
      mrb_value base, super;
      mrb_sym id = syms[GETARG_B(i)];

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

    CASE(OP_MODULE) {
      /* A B            R(A) := newmodule(R(A),Sym(B)) */
      struct RClass *c = 0;
      int a = GETARG_A(i);
      mrb_value base;
      mrb_sym id = syms[GETARG_B(i)];

      base = regs[a];
      if (mrb_nil_p(base)) {
  base = mrb_obj_value(mrb->ci->target_class);
      }
      c = mrb_vm_define_module(mrb, base, id);
      regs[a] = mrb_obj_value(c);
      mrb->arena_idx = ai;
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

    CASE(OP_SCLASS) {
      /* A B    R(A) := R(B).singleton_class */
      regs[GETARG_A(i)] = mrb_singleton_class(mrb, regs[GETARG_B(i)]);
      mrb->arena_idx = ai;
      NEXT;
    }

    CASE(OP_TCLASS) {
      /* A B    R(A) := target_class */
      if (!mrb->ci->target_class) {
        static const char msg[] = "no target class or module";
        mrb_value exc = mrb_exc_new(mrb, E_TYPE_ERROR, msg, sizeof(msg) - 1);
        mrb->exc = (struct RObject*)mrb_object(exc);
        goto L_RAISE;
      }
      regs[GETARG_A(i)] = mrb_obj_value(mrb->ci->target_class);
      NEXT;
    }

    CASE(OP_RANGE) {
      /* A B C  R(A) := range_new(R(B),R(B+1),C) */
      int b = GETARG_B(i);
      regs[GETARG_A(i)] = mrb_range_new(mrb, regs[b], regs[b+1], GETARG_C(i));
      mrb->arena_idx = ai;
      NEXT;
    }

    CASE(OP_DEBUG) {
      /* A      debug print R(A),R(B),R(C) */
#ifdef ENABLE_STDIO
      printf("OP_DEBUG %d %d %d\n", GETARG_A(i), GETARG_B(i), GETARG_C(i));
#else
      abort();
#endif
      NEXT;
    }
