#include "mruby.h"
#include "mruby/proc.h"
#include "mruby/dump.h"
#include "mruby/cdump.h"
#include "mruby/compile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// defines from vm.c
#define SET_TRUE_VALUE(r) MRB_SET_VALUE(r, MRB_TT_TRUE, value.i, 1)
#define SET_FALSE_VALUE(r) MRB_SET_VALUE(r, MRB_TT_FALSE, value.i, 1)
#define SET_NIL_VALUE(r) MRB_SET_VALUE(r, MRB_TT_FALSE, value.i, 0)
#define SET_INT_VALUE(r,n) MRB_SET_VALUE(r, MRB_TT_FIXNUM, value.i, (n))
#define SET_SYM_VALUE(r,v) MRB_SET_VALUE(r, MRB_TT_SYMBOL, value.sym, (v))
#define SET_OBJ_VALUE(r,v) MRB_SET_VALUE(r, (((struct RObject*)(v))->tt), value.p, (v))
#ifdef MRB_NAN_BOXING
#define SET_FLT_VALUE(r,v) r.f = (v)
#else
#define SET_FLT_VALUE(r,v) MRB_SET_VALUE(r, MRB_TT_FLOAT, value.f, (v))
#endif

// my defines
#define NEXT

// copied defines

#define attr_i value.i
#ifdef MRB_NAN_BOXING
#define attr_f f
#else
#define attr_f value.f
#endif

#define TYPES2(a,b) (((((int)(a))<<8)|((int)(b)))&0xffff)
#define OP_MATH_BODY(op,v1,v2) do {\
  regs[a].v1 = regs[a].v1 op regs[a+1].v2;\
} while(0)

#define OP_CMP_BODY(op,v1,v2) do {\
  if (regs[a].v1 op regs[a+1].v2) {\
    SET_TRUE_VALUE(regs[a]);\
  }\
  else {\
    SET_FALSE_VALUE(regs[a]);\
  }\
} while(0)

// removed first line from OP_CMP
#define OP_CMP(op) do {\
  /* need to check if - is overridden */\
  switch (TYPES2(mrb_type(regs[a]),mrb_type(regs[a+1]))) {\
  case TYPES2(MRB_TT_FIXNUM,MRB_TT_FIXNUM):\
    OP_CMP_BODY(op,attr_i,attr_i);\
    break;\
  case TYPES2(MRB_TT_FIXNUM,MRB_TT_FLOAT):\
    OP_CMP_BODY(op,attr_i,attr_f);\
    break;\
  case TYPES2(MRB_TT_FLOAT,MRB_TT_FIXNUM):\
    OP_CMP_BODY(op,attr_f,attr_i);\
    break;\
  case TYPES2(MRB_TT_FLOAT,MRB_TT_FLOAT):\
    OP_CMP_BODY(op,attr_f,attr_f);\
    break;\
  default:\
    break;\
  }\
} while (0)


void testfunc(mrb_state *mrb) {
  mrb_value *regs = NULL;
  regs = mrb->stack;
  regs[0] = mrb_top_self(mrb);

#include "codegen_rb/out.c"

}

int
main(int argc, char **argv)
{
  mrb_state *mrb = mrb_open();

  if (mrb == NULL) {
    fprintf(stderr, "Invalid mrb_state, exiting driver");
    return EXIT_FAILURE;
  }
  testfunc(mrb);
  mrb_close(mrb);
  return EXIT_SUCCESS;
}
