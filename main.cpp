/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "lvgl/lvgl.h"
#include "lvgl/src/extra/libs/freetype/lv_freetype.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/sdl/sdl.h"
#include "generic_widgets.h"
#include "icons.h"
#include "fonts.h"
#include "components/components.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static void add_mask_event_cb(lv_event_t * e)
{
    static lv_draw_mask_radius_param_t m;
    static int16_t mask_id;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    lv_area_t * area = (lv_area_t *)lv_event_get_user_data(e);
    if(code == LV_EVENT_COVER_CHECK) {
        lv_event_set_cover_res(e, LV_COVER_RES_MASKED);
    }
    else if(code == LV_EVENT_DRAW_MAIN_BEGIN) {
        lv_draw_mask_radius_init(&m, area, 32, false);
        mask_id = lv_draw_mask_add(&m, NULL);

    }
    else if(code == LV_EVENT_DRAW_MAIN_END) {
        lv_draw_mask_free_param(&m);
        lv_draw_mask_remove_id(mask_id);
    }
}

static lv_obj_t * screen1;
static lv_obj_t * screen2;

const char *arr[] = {
	"A:/home/rv/lv_86/lvgl_gui/wallpaper1.png",
	"A:/home/rv/lv_86/lvgl_gui/wallpaper2.png",
	"A:/home/rv/lv_86/lvgl_gui/wallpaper3.png",
	"A:/home/rv/lv_86/lvgl_gui/wallpaper4.png"
};

enum {
    SCREENSAVER_BOX_CORNER_TOP_LEFT = 0,
    SCREENSAVER_BOX_CORNER_TOP_RIGHT,
	SCREENSAVER_BOX_CORNER_BOTTOM_RIGHT,
	SCREENSAVER_BOX_CORNER_BOTTOM_LEFT
};
typedef uint8_t screensaver_box_corner_t;

static bool screensaver = true;
static screensaver_box_corner_t screen_saver_corner = SCREENSAVER_BOX_CORNER_TOP_LEFT;
static void img_snapshot_del_event_cb(lv_event_t * e){
	lv_obj_t * obj = lv_event_get_target(e);
	lv_img_dsc_t* snapshot = (lv_img_dsc_t*)lv_img_get_src(obj);
    if(snapshot) {
        lv_snapshot_free(snapshot);
    }
}

static void tile_clicked_event_cb(lv_event_t * e){
    Component * component = (Component *)lv_event_get_user_data(e);
    lv_obj_t * screen = component->createDetailedScreen();
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false);
}

static void screensaver_clicked_event_cb(lv_event_t * e){
	const lv_coord_t padding = LV_DPI_DEF/10;
	screensaver = false;
 
   
	lv_obj_t * screen = lv_obj_create(NULL);
	lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);

	lv_obj_t * background = lv_img_create(screen);
    lv_img_set_src(background, "A:/home/rv/lv_86/lvgl_gui/wallpaper5.png");
	lv_obj_add_flag(background, LV_OBJ_FLAG_IGNORE_LAYOUT);

struct timeval tv_now;
   gettimeofday(&tv_now, NULL);
   struct tm * tm = localtime(&tv_now.tv_sec);

   lv_obj_t * label1 = lv_label_create(screen);
   lv_obj_set_style_text_color(label1, lv_color_white(), 0);
   lv_obj_set_style_text_font(label1, tiny_font.font, 0);
   char buf[16];
   strftime(buf, 16,"%H:%M", tm);
   lv_label_set_text(label1, buf);
   
   lv_obj_t * page_screen = lv_obj_create(screen);
   lv_obj_set_style_bg_opa(page_screen, LV_OPA_TRANSP, LV_PART_MAIN);
   lv_obj_set_width(page_screen, LV_HOR_RES);
   lv_obj_set_flex_grow(page_screen, 1);
   lv_obj_set_flex_flow(page_screen, LV_FLEX_FLOW_ROW_WRAP);

   lv_obj_update_layout(screen);
   
   LightComponent * lightComponent = new LightComponent();
   
   lv_obj_t * tile = lightComponent->createTiledView(page_screen); 
   lv_obj_add_event_cb(tile, tile_clicked_event_cb, LV_EVENT_CLICKED, lightComponent);
 
  ThermostatComponent thermostatComponent = ThermostatComponent();
   
   thermostatComponent.createTiledView(page_screen); 
	
   lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true);

   //screen2 = hello();
   //lv_scr_load_anim(screen2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 5000, false);
}

void render_screensaver(lv_obj_t * img_snapshot, const void * src_img, screensaver_box_corner_t corner){
	const lv_coord_t box_margin = 30; 
	const lv_coord_t box_w = 300;
    const lv_coord_t box_h = 300;

	lv_coord_t x;
    lv_coord_t y;

	switch (corner)
	{
	case SCREENSAVER_BOX_CORNER_TOP_LEFT:
	    x = box_margin;
		y = box_margin;
		break;
	case SCREENSAVER_BOX_CORNER_TOP_RIGHT:
	    x = LV_HOR_RES - box_w - box_margin;
		y = box_margin;
		break;
	case SCREENSAVER_BOX_CORNER_BOTTOM_RIGHT:
	    x = LV_HOR_RES - box_w - box_margin;
		y = LV_VER_RES - box_h - box_margin;
		break; 
	case SCREENSAVER_BOX_CORNER_BOTTOM_LEFT:
	    x = box_margin;
		y = LV_VER_RES - box_h - box_margin;
	default:
		break;
	}

    lv_obj_t * screen = lv_obj_create(NULL);
   
   lv_obj_t * background = lv_img_create(screen);
   lv_img_set_src(background, src_img);

   lv_obj_t * canvas = lv_canvas_create(screen);
   lv_color_t * canvas_buf = (lv_color_t *)lv_mem_alloc(LV_IMG_BUF_SIZE_TRUE_COLOR_ALPHA(LV_HOR_RES, LV_VER_RES));
   lv_canvas_set_buffer(canvas, canvas_buf, LV_HOR_RES, LV_VER_RES, LV_IMG_CF_TRUE_COLOR_ALPHA);
   lv_draw_img_dsc_t img_dsc;
   lv_draw_img_dsc_init(&img_dsc);
   lv_canvas_draw_img(canvas, 0, 0, src_img, &img_dsc);
   lv_area_t final_blurred_area = {x, y, x + box_w, y + box_h};
   lv_obj_add_event_cb(canvas, add_mask_event_cb, LV_EVENT_ALL, &final_blurred_area);

   lv_area_t area = {0, 0, LV_HOR_RES, LV_VER_RES};
   lv_canvas_blur_hor(canvas, &area, 60);
   lv_canvas_blur_ver(canvas, &area, 60);
   
    lv_obj_t * box = lv_obj_create(screen);
	lv_obj_set_flex_flow(box, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_size(box, box_w, box_h);
	lv_obj_set_style_border_opa(box, LV_OPA_TRANSP, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(box, LV_OPA_TRANSP, LV_PART_MAIN);
	lv_obj_set_style_pad_row(box, 0, LV_PART_MAIN);

    lv_obj_align(box, LV_ALIGN_TOP_LEFT, x, y);
   
   struct timeval tv_now;
   gettimeofday(&tv_now, NULL);
   struct tm * tm = localtime(&tv_now.tv_sec);

   lv_obj_t * label1 = lv_label_create(box);
   lv_obj_set_style_text_color(label1, lv_color_white(), 0);
   lv_obj_set_style_text_font(label1, large_font.font, 0);
   
   char buf[16];
   strftime(buf, 16,"%H:%M", tm);
   lv_label_set_text(label1, buf);

   lv_obj_t * label2 = lv_label_create(box);
   lv_obj_set_style_text_color(label2, lv_color_white(), 0);
   lv_obj_set_style_text_font(label2, medium_font.font, 0);
   strftime(buf, 16,"%a", tm);
   lv_label_set_text(label2, buf);

   lv_obj_t * label3 = lv_label_create(box);
   lv_obj_set_style_text_color(label3, lv_color_white(), 0);
   lv_obj_set_style_text_font(label3, medium_font.font, 0);
   strftime(buf, 16,"%d %b", tm);
   lv_label_set_text(label3, buf);

   lv_img_dsc_t* snapshot = (lv_img_dsc_t*)lv_img_get_src(img_snapshot);
    if(snapshot) {
        lv_snapshot_free(snapshot);
    }
    snapshot = lv_snapshot_take(screen, LV_IMG_CF_TRUE_COLOR_ALPHA);
    lv_img_set_src(img_snapshot, snapshot);

   lv_obj_del(screen);

   lv_mem_free(canvas_buf);
}


void my_timer(lv_timer_t * timer)
{
	if(screensaver){
		lv_obj_t * screen = lv_obj_create(NULL);
		lv_obj_add_event_cb(screen, screensaver_clicked_event_cb, LV_EVENT_CLICKED, NULL);
		lv_obj_t * img = lv_img_create(screen);
		lv_obj_add_event_cb(img, img_snapshot_del_event_cb, LV_EVENT_DELETE, NULL);
		render_screensaver(img, arr[screen_saver_corner], screen_saver_corner);

		lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_FADE_ON, 750, 0, true);


		if(screen_saver_corner < 3){
			screen_saver_corner++;
		}else{
			screen_saver_corner = 0;
		}

	}
}

int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init();

    /*FreeType uses C standard file system, so no driver letter is required.*/
    large_font.name = "/home/rv/lv_86/lvgl_gui/Lato-Regular.ttf";
    large_font.weight = 100;
    large_font.style = FT_FONT_STYLE_NORMAL;
    large_font.mem = NULL;
    if(!lv_ft_font_init(&large_font)) {
        LV_LOG_ERROR("create failed.");
    }

    medium_font.name = "/home/rv/lv_86/lvgl_gui/Lato-Light.ttf";
    medium_font.weight = 56;
    medium_font.style = FT_FONT_STYLE_NORMAL;
    medium_font.mem = NULL;
    if(!lv_ft_font_init(&medium_font)) {
        LV_LOG_ERROR("create failed.");
    }

	small_font.name = "/home/rv/lv_86/lvgl_gui/Lato-Regular.ttf";
    small_font.weight = 36;
    small_font.style = FT_FONT_STYLE_NORMAL;
    small_font.mem = NULL;
    if(!lv_ft_font_init(&small_font)) {
        LV_LOG_ERROR("create failed.");
    }
 
	tiny_font.name = "/home/rv/lv_86/lvgl_gui/Lato-Regular.ttf";
    tiny_font.weight = 24;
    tiny_font.style = FT_FONT_STYLE_NORMAL;
    tiny_font.mem = NULL;
    if(!lv_ft_font_init(&tiny_font)) {
        LV_LOG_ERROR("create failed.");
    }

	material_icons_large_font.name = "/home/rv/lv_86/lvgl_gui/MaterialIconsOutlined-200.ttf";
    material_icons_large_font.weight = 64;
    material_icons_large_font.style = FT_FONT_STYLE_NORMAL;
    material_icons_large_font.mem = NULL;
    if(!lv_ft_font_init(&material_icons_large_font)) {
        LV_LOG_ERROR("create failed.");
    }

	material_icons_medium_font.name = "/home/rv/lv_86/lvgl_gui/MaterialIconsOutlined-200.ttf";
    material_icons_medium_font.weight = 48;
    material_icons_medium_font.style = FT_FONT_STYLE_NORMAL;
    material_icons_medium_font.mem = NULL;
    if(!lv_ft_font_init(&material_icons_medium_font)) {
        LV_LOG_ERROR("create failed.");
    }

  //lv_demo_widgets();
	lv_timer_t * timer = lv_timer_create(my_timer, 5000,  NULL);
	my_timer(timer);

  while(1) {
      /* Periodically call the lv_task handler.
       * It could be done in a timer interrupt or an OS task too.*/
      lv_timer_handler();
      usleep(5 * 1000);
  }

  return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static void hal_init(void)
{
  /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 480;
    disp_drv.ver_res    = 480;
    lv_disp_drv_register(&disp_drv);

    evdev_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv_1.read_cb = evdev_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

  /*Set a cursor for the mouse*/
  LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
  lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/
}

uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
