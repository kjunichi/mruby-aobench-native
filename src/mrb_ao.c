/*
** mrb_ao.c - Ao class
**
** Copyright (c) Junichi Kajiwara 2016
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_ao.h"

extern unsigned char *aobench(const char *fname);

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_ao_data;

static const struct mrb_data_type mrb_ao_data_type = {
  "mrb_ao_data", mrb_free,
};

static mrb_value mrb_ao_init(mrb_state *mrb, mrb_value self)
{
  mrb_ao_data *data;
  char *str;
  int len;

  data = (mrb_ao_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_ao_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_ao_data *)mrb_malloc(mrb, sizeof(mrb_ao_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}
static mrb_value mrb_ao_render(mrb_state *mrb, mrb_value self)
{
  unsigned char *img;
  mrb_value v1,v2;

  img = aobench("ao_mruby.ppm");
  v1 = mrb_str_new_cstr(mrb, "P6\n256 256\n255\n");
  v2 = mrb_str_new(mrb, (const char*)img, 256*256*3);
  mrb_funcall(mrb, v1, "concat", 1, v2);
  return v1;
}

void mrb_mruby_aobench_native_gem_init(mrb_state *mrb)
{
    struct RClass *ao;
    ao = mrb_define_class(mrb, "Ao", mrb->object_class);
    mrb_define_class_method(mrb, ao, "render", mrb_ao_render, MRB_ARGS_NONE());
    DONE;
}

void mrb_mruby_aobench_native_gem_final(mrb_state *mrb)
{
}

