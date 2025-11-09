#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#ifndef LV_ATTRIBUTE_IMAGE_NAGINATA
#define LV_ATTRIBUTE_IMAGE_NAGINATA
#endif

#ifndef LV_ATTRIBUTE_IMAGE_ABC
#define LV_ATTRIBUTE_IMAGE_ABC
#endif

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

extern const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMAGE_NAGINATA uint8_t naginata_map[];
extern const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMAGE_ABC uint8_t abc_map[];

extern const lv_img_dsc_t naginata;
extern const lv_img_dsc_t abc;