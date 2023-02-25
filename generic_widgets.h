#ifndef GENERIC_WIDGETS_H
#define GENERIC_WIDGETS_H

#include "lvgl/lvgl.h"
#include "icons.h"
#include "fonts.h"

lv_obj_t * tile_create(lv_obj_t * parent){
   const lv_coord_t padding = lv_obj_get_style_pad_left(parent, LV_PART_MAIN);
   const lv_coord_t box_w = (LV_HOR_RES - padding*3)/2;
   const lv_coord_t box_h = (lv_obj_get_height(parent) - padding*4)/3;

   lv_obj_t * tile = lv_btn_create(parent);
   
   lv_obj_set_size(tile, box_w, box_h);
   lv_obj_set_flex_flow(tile, LV_FLEX_FLOW_COLUMN);
   lv_obj_set_style_pad_all(tile, 0, LV_PART_MAIN);
   lv_obj_set_style_pad_row(tile, 0, LV_PART_MAIN);
   lv_obj_set_style_bg_color(tile, lv_color_black(), LV_PART_MAIN);
   lv_obj_set_style_bg_opa(tile, LV_OPA_20, LV_PART_MAIN);
   lv_obj_set_style_border_width(tile, 0, LV_PART_MAIN);
   lv_obj_set_style_radius(tile, 16, LV_PART_MAIN);

   return tile;
};


lv_obj_t * create_tile_preset(lv_obj_t * parent, const char * text, const char * icon_src){ 
   lv_obj_t * tile = tile_create(parent);

   lv_obj_t * box_box = lv_obj_create(tile);
   lv_obj_set_width(box_box, lv_pct(100));
   lv_obj_set_flex_flow(box_box, LV_FLEX_FLOW_ROW);
   lv_obj_set_style_pad_all(box_box, 0, LV_PART_MAIN);
   lv_obj_set_style_border_width(box_box, 0, LV_PART_MAIN);
   lv_obj_set_style_bg_opa(box_box, LV_OPA_TRANSP, LV_PART_MAIN);
   lv_obj_set_flex_align(box_box, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
   lv_obj_set_flex_grow(box_box, 1);
 
   lv_obj_t * icon = lv_label_create(box_box);
   lv_obj_set_style_text_color(icon, lv_color_white(), 0);
   lv_obj_set_style_text_font(icon, material_icons_large_font.font, 0);
   lv_label_set_text(icon, icon_src);

   lv_obj_t * label = lv_label_create(tile);
   lv_obj_set_style_pad_all(label, LV_DPI_DEF/20, LV_PART_MAIN);
   lv_obj_set_size(label, lv_pct(100), LV_SIZE_CONTENT);
   lv_obj_set_style_text_color(label, lv_color_white(), 0);
   lv_obj_set_style_text_font(label, tiny_font.font, 0);
   lv_label_set_text(label, text);
   lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);

   return tile;
}


lv_obj_t * large_slider_create(lv_obj_t * parent, const char * icon_src){
	lv_obj_t * slider = lv_slider_create(parent);
    lv_slider_set_range(slider, 0, 255);
	lv_obj_set_flex_flow(slider, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(slider, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_bg_opa(slider, LV_OPA_TRANSP, LV_PART_KNOB);
	lv_obj_set_style_bg_color(slider, lv_color_black(), LV_PART_MAIN);
	lv_obj_set_style_radius(slider, LV_DPI_DEF/8, LV_PART_MAIN);
	lv_obj_set_style_radius(slider, LV_DPI_DEF/8, LV_PART_INDICATOR); 
	lv_obj_set_style_bg_color(slider, lv_color_white(), LV_PART_INDICATOR);
	lv_obj_set_style_bg_opa(slider, LV_OPA_80, LV_PART_INDICATOR);
	lv_obj_set_size(slider, lv_pct(100), LV_DPI_DEF/2);


	lv_obj_t * icon = lv_label_create(slider);
	lv_obj_set_style_pad_left(icon, LV_DPI_DEF/12, LV_PART_MAIN);
	lv_obj_set_style_text_color(icon, lv_color_make(100, 100, 100), 0);
	lv_obj_set_style_text_font(icon, material_icons_medium_font.font, 0);
	lv_label_set_text(icon, icon_src);

	return slider;
};	

#endif