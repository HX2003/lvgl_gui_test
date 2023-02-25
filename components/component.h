#ifndef COMPONENT_H
#define COMPONENT_H

#include "lvgl/lvgl.h"
#include "../generic_widgets.h"
#include "../icons.h"
#include "../fonts.h"

class Component
{
   public:
      virtual lv_obj_t * createTiledView(lv_obj_t * parent){return NULL;};
      virtual lv_obj_t * createDetailedScreen(){return NULL;};
};

#endif