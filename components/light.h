#include "component.h"

class LightComponent : public Component {
    private:
        bool _on;
        uint8_t _brightness; /* 0 - 255 */
        uint8_t _temperature; /* 0 - 255 */
        lv_color_hsv_t _hsv;
        
        lv_obj_t * brightness_slider_1;
        lv_obj_t * brightness_slider_2;
        
        
        static void brightness_slider_event_cb(lv_event_t * e){
            lv_obj_t * slider = lv_event_get_target(e);
            LightComponent * component = (LightComponent *)lv_event_get_user_data(e);

            component->_brightness = lv_slider_get_value(slider);
            lv_slider_set_value(component->brightness_slider_1, component->_brightness, LV_ANIM_OFF);
            lv_slider_set_value(component->brightness_slider_2, component->_brightness, LV_ANIM_OFF);
        };

        static void temperature_slider_event_cb(lv_event_t * e){
            lv_obj_t * slider = lv_event_get_target(e);
            LightComponent * component = (LightComponent *)lv_event_get_user_data(e);

            component->_temperature = lv_slider_get_value(slider);
        };

    public:
       LightComponent(){
        _on = false;
        _brightness = false;
        _temperature = 0;
        _hsv = lv_color_to_hsv(lv_color_make(0, 0, 255));
       };
   
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
            lv_label_set_text(icon, MATERIAL_ICON_LIGHTBULB);

            lv_obj_t * box_box_box = lv_obj_create(box_box);
            lv_obj_clear_flag(box_box_box, LV_OBJ_FLAG_CLICKABLE);
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
            lv_label_set_text(label2, "Living Room Light");
            lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);

            return tile;
       };

       lv_obj_t * createDetailedScreen(){
        lv_obj_t * screen = lv_obj_create(NULL);
            lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_style_pad_row(screen, 0, LV_PART_MAIN);

            lv_obj_t * background = lv_img_create(screen);
            lv_img_set_src(background, "A:/home/hx2003/Desktop/lv_86/lvgl_gui/wallpaper5.png");
            lv_obj_add_flag(background, LV_OBJ_FLAG_IGNORE_LAYOUT);
            
            lv_obj_t * header = lv_obj_create(screen);
            lv_obj_set_size(header, LV_HOR_RES, LV_DPI_DEF/2);
            lv_obj_set_flex_flow(header, LV_FLEX_FLOW_ROW);
            lv_obj_set_flex_align(header, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
            lv_obj_set_style_pad_hor(header, LV_DPI_DEF/20, LV_PART_MAIN);
            lv_obj_set_style_pad_ver(header, 0, LV_PART_MAIN);
            lv_obj_set_style_bg_opa(header, LV_OPA_TRANSP, LV_PART_MAIN);
            lv_obj_set_style_border_width(header, 0, LV_PART_MAIN);

            lv_obj_t * back_btn = lv_btn_create(header);
            lv_obj_set_size(back_btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_pad_hor(back_btn, LV_DPI_DEF/20, LV_PART_MAIN);
            lv_obj_set_style_pad_ver(back_btn, 0, LV_PART_MAIN);
            lv_obj_t * back_icon = lv_label_create(back_btn);
            lv_obj_set_style_bg_opa(back_btn, LV_OPA_TRANSP, LV_PART_MAIN);
        lv_obj_set_style_text_font(back_icon, material_icons_medium_font.font, 0);
        lv_label_set_text(back_icon, MATERIAL_ICON_ARROW_BACK_IOS);

            lv_obj_t * title = lv_label_create(header);
        lv_obj_set_style_text_font(title, small_font.font, 0);
        lv_label_set_text(title, "Living Room Light");

            lv_obj_t * tabview = lv_tabview_create(screen, LV_DIR_TOP, LV_DPI_DEF/4);
            lv_obj_set_flex_grow(tabview, 1);
            
            lv_obj_set_style_bg_opa(tabview, LV_OPA_TRANSP, LV_PART_MAIN);
            lv_obj_t * color_tab = lv_tabview_add_tab(tabview, "Color");
            lv_obj_t * white_tab = lv_tabview_add_tab(tabview, "White");
            lv_obj_t * presets_tab = lv_tabview_add_tab(tabview, "Presets");
            
            lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
            lv_obj_set_style_text_font(tab_btns, tiny_font.font, LV_PART_MAIN);
            lv_obj_set_style_text_color(tab_btns, lv_color_make(100, 100, 100), LV_PART_MAIN);
            lv_obj_set_style_text_color(tab_btns, lv_color_white(), LV_PART_ITEMS | LV_STATE_CHECKED);
            lv_obj_set_style_bg_opa(tab_btns, LV_OPA_TRANSP, LV_PART_MAIN);
            lv_obj_set_style_bg_opa(tab_btns, LV_OPA_TRANSP, LV_PART_ITEMS | LV_STATE_CHECKED);
            lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_NONE, LV_PART_ITEMS | LV_STATE_CHECKED);
            
            
            lv_obj_set_flex_flow(color_tab, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_flex_align(color_tab, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
            lv_obj_set_style_pad_all(color_tab, 0, LV_PART_MAIN);

            lv_obj_t * box = lv_obj_create(color_tab);
            lv_obj_set_width(box, LV_HOR_RES);
            lv_obj_set_flex_grow(box, 1);
            lv_obj_set_flex_align(box, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
            lv_obj_set_style_bg_opa(box, LV_OPA_TRANSP, LV_PART_MAIN);
            lv_obj_set_style_border_width(box, 0, LV_PART_MAIN);

            lv_obj_t * cw = lv_colorwheel_create(box, true);
            lv_obj_set_size(cw, LV_DPI_DEF*2, LV_DPI_DEF*2);
            lv_obj_set_style_arc_width(cw, LV_DPI_DEF/4, LV_PART_MAIN); 
        
            
            lv_obj_t * box2 = lv_obj_create(color_tab);
            lv_obj_set_size(box2, LV_HOR_RES, LV_SIZE_CONTENT);
            lv_obj_set_style_bg_opa(box2, LV_OPA_TRANSP, LV_PART_MAIN);
            lv_obj_set_style_border_width(box2, 0, LV_PART_MAIN);
            lv_obj_set_style_pad_ver(box2, 0, LV_PART_MAIN);
            brightness_slider_1 = large_slider_create(box2, MATERIAL_ICON_LIGHT_MODE);
            lv_obj_add_event_cb(brightness_slider_1, brightness_slider_event_cb, LV_EVENT_VALUE_CHANGED, this);

            lv_obj_set_flex_flow(white_tab, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_flex_align(white_tab, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
            lv_obj_set_style_pad_all(white_tab, 0, LV_PART_MAIN);

            lv_obj_t * box3 = lv_obj_create(white_tab);
            lv_obj_set_size(box3, LV_HOR_RES, LV_SIZE_CONTENT);
            lv_obj_set_style_bg_opa(box3, LV_OPA_TRANSP, LV_PART_MAIN);
            lv_obj_set_style_border_width(box3, 0, LV_PART_MAIN);
            lv_obj_set_style_pad_ver(box3, 0, LV_PART_MAIN);
            lv_obj_t * slider2 = large_slider_create(box3, MATERIAL_ICON_THERMOMETER);
            lv_obj_set_style_bg_color(slider2, lv_palette_lighten(LV_PALETTE_BLUE, 4), LV_PART_INDICATOR);
            lv_obj_set_style_bg_grad_color(slider2, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_INDICATOR);
            lv_obj_set_style_bg_grad_dir(slider2, LV_GRAD_DIR_HOR, LV_PART_INDICATOR);
            lv_obj_add_event_cb(slider2, temperature_slider_event_cb, LV_EVENT_VALUE_CHANGED, this);

            lv_obj_t * box4 = lv_obj_create(white_tab);
            lv_obj_set_size(box4, LV_HOR_RES, LV_SIZE_CONTENT);
            lv_obj_set_style_bg_opa(box4, LV_OPA_TRANSP, LV_PART_MAIN);
            lv_obj_set_style_border_width(box4, 0, LV_PART_MAIN);
            lv_obj_set_style_pad_ver(box4, 0, LV_PART_MAIN);
            brightness_slider_2 = large_slider_create(box4, MATERIAL_ICON_LIGHT_MODE);
            lv_obj_add_event_cb(brightness_slider_2, brightness_slider_event_cb, LV_EVENT_VALUE_CHANGED, this);

        lv_obj_set_flex_flow(presets_tab, LV_FLEX_FLOW_ROW_WRAP);
        lv_obj_update_layout(presets_tab);
        
        create_tile_preset(presets_tab, "Work", MATERIAL_ICON_LIGHTBULB);
        create_tile_preset(presets_tab, "Theatre", MATERIAL_ICON_LIGHTBULB);
        create_tile_preset(presets_tab, "Relax", MATERIAL_ICON_LIGHTBULB);

        return screen;
       }; 
};