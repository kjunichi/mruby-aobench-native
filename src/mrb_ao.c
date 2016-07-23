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
#include <stdlib.h>
#include <string.h>

#define WIDTH        256
#define HEIGHT       256

typedef struct _vec
{
    double x;
    double y;
    double z;
} vec;

typedef struct _Sphere
{
    vec    center;
    double radius;

} Sphere;

extern void aobench_saveppm(const char *fname);
extern void aobench();


extern Sphere spheres[3];

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
  char *fname;
  int argc;

  /* check args */
  argc = mrb_get_args(mrb,"|z", &fname);
  if(argc>0) {
    fprintf(stderr,"fname = %s\n", fname);
    aobench_saveppm(fname);
    return mrb_nil_value();
  }
  img = (unsigned char *)malloc(WIDTH * HEIGHT * 3);
  aobench(img);
  v1 = mrb_str_new_cstr(mrb, "P6\n256 256\n255\n");
  v2 = mrb_str_new(mrb, (const char*)img, 256*256*3);
  free(img);
  mrb_funcall(mrb, v1, "concat", 1, v2);
  return v1;
}

static mrb_value
mrb_ao_sphere_pos(mrb_state *mrb, mrb_value self)
{
  mrb_value sx[3],sy[3],sz[3];
  int i;

  mrb_get_args(mrb,"fffffffff", &sx[0],&sy[0],&sz[0], &sx[1],&sy[1],&sz[1], &sx[2],&sy[2],&sz[2]);
  for(i =0; i<3;i++) {
    spheres[i].center.x = mrb_float(sx[i]);
    spheres[i].center.y = mrb_float(sy[i]);
    spheres[i].center.z = mrb_float(sz[i]);
    spheres[i].radius = 0.5;
  }
}

static void setSpheres()
{
  spheres[0].center.x = -2.0;
  spheres[0].center.y =  0.0;
  spheres[0].center.z = -3.5;
  spheres[0].radius = 0.5;

  spheres[1].center.x = -0.5;
  spheres[1].center.y =  0.0;
  spheres[1].center.z = -3.0;
  spheres[1].radius = 0.5;

  spheres[2].center.x =  1.0;
  spheres[2].center.y =  0.0;
  spheres[2].center.z = -2.2;
  spheres[2].radius = 0.5;
}
void mrb_mruby_aobench_native_gem_init(mrb_state *mrb)
{
    struct RClass *ao;
    ao = mrb_define_class(mrb, "Ao", mrb->object_class);
    setSpheres();
    mrb_define_class_method(mrb, ao, "render", mrb_ao_render, MRB_ARGS_OPT(1));
    mrb_define_class_method(mrb, ao, "setSpherePosition", mrb_ao_sphere_pos, MRB_ARGS_REQ(9));
    DONE;
}

void mrb_mruby_aobench_native_gem_final(mrb_state *mrb)
{
}
