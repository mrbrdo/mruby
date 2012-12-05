#include "mruby.h"
#include "mruby/proc.h"
#include "mruby/class.h"
#include "mruby/array.h"
#include "mruby/dump.h"
#include "mruby/range.h"
#include "../src/opcode.h"
#include "mruby/cdump.h"
#include "mruby/compile.h"
#include "mruby/variable.h"
#include "mruby/string.h"
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
#define CALL_MAXARGS 127

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

mrb_value testfun(mrb_state *mrb, mrb_value args) {
  printf("ok!");
  mrb_p(mrb, args);
  return mrb_nil_value();
}

void testfunc(mrb_state *mrb) {
  mrb_value *regs = NULL;
  regs = mrb->stack;
  regs[0] = mrb_top_self(mrb);

  mrb_define_method_vm(mrb, mrb_class(mrb, regs[0]),
    mrb_intern(mrb, "testfun"),
    mrb_obj_value(mrb_proc_new_cfunc(mrb, testfun)));

  mrb_funcall(mrb, regs[0], "testfun", 1, mrb_nil_value());
}


#define STACK_INIT_SIZE 128
#define CALLINFO_INIT_SIZE 32
static inline void
stack_copy(mrb_value *dst, const mrb_value *src, size_t size)
{
  int i;

  for (i = 0; i < size; i++) {
    dst[i] = src[i];
  }
}
static void
stack_init(mrb_state *mrb)
{
  /* assert(mrb->stack == NULL); */
  mrb->stbase = (mrb_value *)mrb_calloc(mrb, STACK_INIT_SIZE, sizeof(mrb_value));
  mrb->stend = mrb->stbase + STACK_INIT_SIZE;
  mrb->stack = mrb->stbase;

  /* assert(mrb->ci == NULL); */
  mrb->cibase = (mrb_callinfo *)mrb_calloc(mrb, CALLINFO_INIT_SIZE, sizeof(mrb_callinfo));
  mrb->ciend = mrb->cibase + CALLINFO_INIT_SIZE;
  mrb->ci = mrb->cibase;
  mrb->ci->target_class = mrb->object_class;
}
static void
argnum_error(mrb_state *mrb, int num)
{
  char buf[256];
  int len;
  mrb_value exc;

  if (mrb->ci->mid) {
    len = snprintf(buf, sizeof(buf), "'%s': wrong number of arguments (%d for %d)",
       mrb_sym2name(mrb, mrb->ci->mid),
       mrb->ci->argc, num);
  }
  else {
    len = snprintf(buf, sizeof(buf), "wrong number of arguments (%d for %d)",
       mrb->ci->argc, num);
  }
  exc = mrb_exc_new(mrb, E_ARGUMENT_ERROR, buf, len);
  mrb->exc = (struct RObject*)mrb_object(exc);
}
static mrb_callinfo*
cipush(mrb_state *mrb)
{
  int eidx = mrb->ci->eidx;
  int ridx = mrb->ci->ridx;

  if (mrb->ci + 1 == mrb->ciend) {
    size_t size = mrb->ci - mrb->cibase;

    mrb->cibase = (mrb_callinfo *)mrb_realloc(mrb, mrb->cibase, sizeof(mrb_callinfo)*size*2);
    mrb->ci = mrb->cibase + size;
    mrb->ciend = mrb->cibase + size * 2;
  }
  mrb->ci++;
  mrb->ci->nregs = 2;
  mrb->ci->eidx = eidx;
  mrb->ci->ridx = ridx;
  mrb->ci->env = 0;
  return mrb->ci;
}

static void
cipop(mrb_state *mrb)
{
  if (mrb->ci->env) {
    struct REnv *e = mrb->ci->env;
    int len = (int)e->flags;
    mrb_value *p = (mrb_value *)mrb_malloc(mrb, sizeof(mrb_value)*len);

    e->cioff = -1;
    stack_copy(p, e->stack, len);
    e->stack = p;
  }

  mrb->ci--;
}

static void
envadjust(mrb_state *mrb, mrb_value *oldbase, mrb_value *newbase)
{
  mrb_callinfo *ci = mrb->cibase;

  while (ci <= mrb->ci) {
    struct REnv *e = ci->env;
    if (e && e->cioff >= 0) {
      int off = e->stack - oldbase;

      e->stack = newbase + off;
    }
    ci++;
  }
}

static void
stack_extend(mrb_state *mrb, int room, int keep)
{
  int size, off;

  if (mrb->stack + room >= mrb->stend) {
    mrb_value *oldbase = mrb->stbase;

    size = mrb->stend - mrb->stbase;
    off = mrb->stack - mrb->stbase;

    if (room <= size)  /* double size is enough? */
      size *= 2;
    else
      size += room;
    mrb->stbase = (mrb_value *)mrb_realloc(mrb, mrb->stbase, sizeof(mrb_value) * size);
    mrb->stack = mrb->stbase + off;
    mrb->stend = mrb->stbase + size;
    envadjust(mrb, oldbase, mrb->stbase);
  }
  if (room > keep) {
    int i;

    for (i=keep; i<room; i++) {
#ifndef MRB_NAN_BOXING
      static const mrb_value mrb_value_zero = { { 0 } };
      mrb->stack[i] = mrb_value_zero;
#else
      SET_NIL_VALUE(mrb->stack[i]);
#endif
    }
  }
}

mrb_value
mrb_funcall_fast(mrb_state *mrb, mrb_value self, mrb_sym mid, int argc, mrb_value *argv, mrb_value blk, mrb_value *regs, int a)
{
  struct RProc *p;
  struct RClass *c;
  mrb_sym undef = 0;
  mrb_callinfo *ci;
  int n;
  mrb_value val;
  int tmp_ci = mrb->ci - mrb->cibase;

  n = mrb->ci->nregs;
  if (argc < 0) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "negative argc for funcall (%d)", argc);
  }
  // check OP_SENDB
  if (mrb_nil_p(blk)) {
    if (n == CALL_MAXARGS) {
      SET_NIL_VALUE(regs[a+2]);
    }
    else {
      SET_NIL_VALUE(regs[a+argc+1]);
    }
  }
  c = mrb_class(mrb, self);
  p = mrb_method_search_vm(mrb, &c, mid);
  if (!p) {
    undef = mid;
    mid = mrb_intern(mrb, "method_missing");
    p = mrb_method_search_vm(mrb, &c, mid);
    n++; argc++;
    // TODO
  }
  ci = cipush(mrb);
  ci->mid = mid;
  ci->proc = p;
  ci->stackidx = mrb->stack - mrb->stbase;
  ci->argc = argc;

  ci->target_class = p->target_class;
  if (ci->argc == CALL_MAXARGS) ci->argc = -1;
  ci->acc = a;

  /* prepare stack */
  mrb->stack += a;

  if (MRB_PROC_CFUNC_P(p)) {
    int ai = mrb->arena_idx;
    void *prev_jmp = mrb->jmp;
    if (argc == CALL_MAXARGS) {
      ci->nregs = 3;
    }
    else {
      ci->nregs = argc + 2;
    }

    ci->acc = -1;

    val = p->body.func(mrb, self);
    mrb->arena_idx = ai;
    // TODO: cheap error handling
    if (mrb->exc) {
      printf("EXC!!!\n");
      mrb_p(mrb, mrb_obj_value(mrb->exc));
      return mrb_nil_value();
    }
    mrb_gc_protect(mrb, val);
    ci = mrb->ci;
    cipop(mrb);
    mrb->stack = mrb->stbase + ci->stackidx;
    mrb->jmp = prev_jmp;
  }
  else {
    int ai = mrb->arena_idx;
    ci->acc = -1;
    /* setup environment for calling method */
    val = mrb_run(mrb, p, self);
    mrb->arena_idx = ai;
    /*irep = p->body.irep;
    pool = irep->pool;
    syms = irep->syms;
    ci->nregs = irep->nregs;
    if (ci->argc < 0) {
      stack_extend(mrb, (irep->nregs < 3) ? 3 : irep->nregs, 3);
    }
    else {
      stack_extend(mrb, irep->nregs,  ci->argc+2);
    }
    regs = mrb->stack;
    pc = irep->iseq;*/
  }
  return val;
  /*ci->target_class = p->target_class;
  if (MRB_PROC_CFUNC_P(p)) {
    ci->nregs = argc + 2;
  }
  else {
    ci->nregs = p->body.irep->nregs + 2;
  }
  ci->acc = -1;
  mrb->stack = mrb->stack + n;

  stack_extend(mrb, ci->nregs, 0);
  mrb->stack[0] = self;
  if (undef) {
    mrb->stack[1] = mrb_symbol_value(undef);
    stack_copy(mrb->stack+2, argv, argc-1);
  }
  else if (argc > 0) {
    stack_copy(mrb->stack+1, argv, argc);
  }
  mrb->stack[argc+1] = blk;

  if (MRB_PROC_CFUNC_P(p)) {
    int ai = mrb->arena_idx;
    val = p->body.func(mrb, self);
    mrb->arena_idx = ai;
    mrb_gc_protect(mrb, val);
    mrb->stack = mrb->stbase + mrb->ci->stackidx;
    cipop(mrb);
  }
  else {
    val = mrb_run(mrb, p, self);
  }
  return val;*/
}

mrb_value
mrb_funcall_fast2(mrb_state *mrb, mrb_value recv, mrb_sym mid, int argc, mrb_value *argv, mrb_value blk, mrb_value *regs, int a)
{
  struct RClass *c;
  struct RProc *m;
  mrb_sym undef = 0;
  mrb_callinfo *ci;
  int n = argc;
  mrb_value result;

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

  /* push callinfo */
  ci = cipush(mrb);
  ci->mid = mid;
  ci->proc = m;
  ci->stackidx = mrb->stack - mrb->stbase;
  ci->argc = n;
  if (ci->argc == CALL_MAXARGS) ci->argc = -1;
  ci->target_class = c;
  ci->acc = a;

  /* prepare stack */
  mrb->stack += a;

  if (MRB_PROC_CFUNC_P(m)) {
    if (n == CALL_MAXARGS) {
      ci->nregs = 3;
    }
    else {
      ci->nregs = n + 2;
    }
    result = m->body.func(mrb, recv);
    mrb->stack[0] = result;
    //mrb->arena_idx = ai;
    // TODO: cheap error handling
    if (mrb->exc) {
      mrb_p(mrb, mrb_obj_value(mrb->exc));
      return mrb_nil_value();
    }
    /* pop stackpos */
    //regs = mrb->stack = mrb->stbase + mrb->ci->stackidx;
    cipop(mrb);
    return result;
  }
  else {
    return mrb_run(mrb, m, recv);
  }
}
#include "codegen_rb/out.c"

int
main(int argc, char **argv)
{
  mrb_state *mrb = mrb_open();

  if (mrb == NULL) {
    fprintf(stderr, "Invalid mrb_state, exiting driver");
    return EXIT_FAILURE;
  }
  //testfunc(mrb);
  rb_main(mrb, mrb_top_self(mrb));
  mrb_close(mrb);
  return EXIT_SUCCESS;
}
