#include "component.h"

class ThermostatComponent : public Component {
    public:
       lv_obj_t * createTiledView(lv_obj_t * parent){
            lv_obj_t * tile = tile_create(parent);
            lv_obj_t * box_box = lv_obj_create(tile);
            lv_obj_clear_flag(box_box, LV_OBJ_FLAG_CLICKABLE);
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
            lv_label_set_text(icon, MATERIAL_ICON_THERMOSTAT);

            lv_obj_t * box_box_box = lv_obj_create(box_box);
            lv_obj_set_flex_flow(box_box_box, LV_FLEX_FLOW_ROW);
            lv_obj_set_flex_align(box_box_box, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
            lv_obj_set_flex_grow(box_box_box, 1);
            lv_obj_set_height(box_box_box, LV_SIZE_CONTENT);
            lv_obj_set_style_border_width(box_box_box, 0, LV_PART_MAIN);
            lv_obj_set_style_bg_opa(box_box_box, LV_OPA_TRANSP, LV_PART_MAIN); 

            lv_obj_t * sw = lv_switch_create(box_box_box);
            lv_obj_set_size(sw, LV_DPI_DEF/1.8, LV_DPI_DEF/3.2);

            lv_obj_t * label2 = lv_label_create(tile);
            lv_obj_set_style_pad_all(label2, LV_DPI_DEF/20, LV_PART_MAIN);
            lv_obj_set_size(label2, lv_pct(100), LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(label2, lv_color_white(), 0);
            lv_obj_set_style_text_font(label2, tiny_font.font, 0);
            lv_label_set_text(label2, "Living Room AC");
            lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);

            return tile;
       };

       lv_obj_t * createDetailedScreen(){
            return NULL;
       }; 
};