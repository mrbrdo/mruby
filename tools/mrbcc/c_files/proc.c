#define MRB_PROC_MRBCFUNC 512
#define MRB_PROC_MRBCFUNC_P(p) ((p)->flags & MRB_PROC_MRBCFUNC)

struct RProc *mrbb_proc_new(mrb_state* mrb, mrb_func_t cfunc)
{
  struct RProc *p = mrb_proc_new_cfunc(mrb, cfunc);

  p->flags |= MRB_PROC_MRBCFUNC;
  p->env = 0;

  return p;
}

struct RProc *mrbb_closure_new(mrb_state* mrb, mrb_func_t cfunc, unsigned int nlocals)
{
  struct RProc *p = mrbb_proc_new(mrb, cfunc);

  // stolen from mrb_closure_new()
  struct REnv *e;

  if (!mrb->ci->env) {
    e = (struct REnv*)mrb_obj_alloc(mrb, MRB_TT_ENV, (struct RClass*)mrb->ci->proc->env);
    e->flags= nlocals;
    e->mid = mrb->ci->mid;
    e->cioff = mrb->ci - mrb->cibase;
    e->stack = mrb->stack;
    mrb->ci->env = e;
  }
  else {
    e = mrb->ci->env;
  }
  p->env = e;

  return p;
}
