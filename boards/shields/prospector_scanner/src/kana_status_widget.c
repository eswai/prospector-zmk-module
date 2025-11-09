/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

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

#include <zephyr/logging/log.h>
#include <zmk/status_advertisement.h>
#include <zmk/status_scanner.h>
#include "kana_status_widget.h"
#include "img.h"

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

// Stylish pastel colors for 0-9 layers (10 total) - full support
static lv_color_t get_layer_color(int layer) {
    switch (layer) {
        case 0: return lv_color_make(0xFF, 0x9B, 0x9B);  // Layer 0: Soft Coral Pink
        case 1: return lv_color_make(0xFF, 0xD9, 0x3D);  // Layer 1: Sunny Yellow  
        case 2: return lv_color_make(0x6B, 0xCF, 0x7F);  // Layer 2: Mint Green
        case 3: return lv_color_make(0x4D, 0x96, 0xFF);  // Layer 3: Sky Blue
        case 4: return lv_color_make(0xB1, 0x9C, 0xD9);  // Layer 4: Lavender Purple
        case 5: return lv_color_make(0xFF, 0x6B, 0x9D);  // Layer 5: Rose Pink
        case 6: return lv_color_make(0xFF, 0x9F, 0x43);  // Layer 6: Peach Orange
        case 7: return lv_color_make(0x87, 0xCE, 0xEB);  // Layer 7: Light Sky Blue
        case 8: return lv_color_make(0xF0, 0xE6, 0x8C);  // Layer 8: Light Khaki
        case 9: return lv_color_make(0xDD, 0xA0, 0xDD);  // Layer 9: Plum
        default: return lv_color_white(); // Fallback for undefined layers
    }
}

static void update_layer_display(struct zmk_widget_layer_status *widget, struct zmk_keyboard_status *kbd) {
    if (!widget || !kbd) {
        return;
    }
    
    uint8_t active_layer = kbd->data.active_layer;
    
    // Update image based on active layer
    if (active_layer == 1) {
        // Add background to make image visible
        lv_obj_set_style_bg_opa(widget->layer_image, LV_OPA_50, 0);
        lv_obj_set_style_bg_color(widget->layer_image, lv_color_black(), 0);
        
        // Recolor the image to ensure visibility
        lv_obj_align(widget->layer_image, LV_ALIGN_TOP_RIGHT, 0, 0); // Center the image
        lv_obj_set_style_img_recolor_opa(widget->layer_image, LV_OPA_100, 0);
        lv_obj_set_style_img_recolor(widget->layer_image, lv_color_make(45, 196, 3), 0);
        lv_img_set_src(widget->layer_image, &naginata);
        LOG_INF("🔵 Setting naginata image (layer 1) - size: %dx%d", naginata.header.w, naginata.header.h);
    } else {

        // Add background to make image visible
        lv_obj_set_style_bg_opa(widget->layer_image, LV_OPA_50, 0);
        lv_obj_set_style_bg_color(widget->layer_image, lv_color_black(), 0);

        // Recolor the image to ensure visibility
        lv_obj_align(widget->layer_image, LV_ALIGN_TOP_LEFT, 0, 0); // Center the image
        lv_obj_set_style_img_recolor_opa(widget->layer_image, LV_OPA_100, 0);
        lv_obj_set_style_img_recolor(widget->layer_image, lv_color_white(), 0);
        lv_img_set_src(widget->layer_image, &abc);
        LOG_INF("🔴 Setting abc image (layer %d) - size: %dx%d", active_layer, abc.header.w, abc.header.h);
    }
    
    LOG_DBG("Layer display updated: active layer %d, image set to %s", active_layer, (active_layer == 1) ? "naginata" : "abc");
}

int zmk_widget_layer_status_init(struct zmk_widget_layer_status *widget, lv_obj_t *parent) {
    if (!widget || !parent) {
        return -1;
    }
    
    // Create container widget for layer display
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 260, 90); // Slightly taller for "Layer" label
    // lv_obj_set_style_bg_opa(widget->obj, LV_OPA_50, 0);
    // lv_obj_set_style_bg_color(widget->obj, lv_color_make(50, 50, 50), 0); // Dark gray for visibility
    // lv_obj_set_style_border_opa(widget->obj, LV_OPA_100, 0);
    // lv_obj_set_style_border_color(widget->obj, lv_color_white(), 0);
    // lv_obj_set_style_border_width(widget->obj, 1, 0);
    // lv_obj_set_style_pad_all(widget->obj, 2, 0);
    
    // Create stylish "Layer" title label (smaller font)
    widget->layer_title = lv_label_create(widget->obj);
    lv_label_set_text(widget->layer_title, "Layer");
    lv_obj_set_style_text_font(widget->layer_title, &lv_font_montserrat_16, 0); // Smaller title font
    lv_obj_set_style_text_color(widget->layer_title, lv_color_make(160, 160, 160), 0); // Soft gray
    lv_obj_set_style_text_opa(widget->layer_title, LV_OPA_70, 0);
    lv_obj_align(widget->layer_title, LV_ALIGN_TOP_MID, 0, -5); // Above the image
    
    // Create image object for layer display
    widget->layer_image = lv_img_create(widget->obj);
    lv_obj_set_size(widget->layer_image, 106, 90); // Smaller size to fit container
    lv_obj_align(widget->layer_image, LV_ALIGN_TOP_LEFT, 0, 0); // Center the image
    
    // Add background to make image visible
    lv_obj_set_style_bg_opa(widget->layer_image, LV_OPA_100, 0);
    lv_obj_set_style_bg_color(widget->layer_image, lv_color_black(), 0);
    
    // Recolor the image to ensure visibility
    lv_obj_set_style_img_recolor_opa(widget->layer_image, LV_OPA_100, 0);
    lv_obj_set_style_img_recolor(widget->layer_image, lv_color_white(), 0);
    
    // Set initial image to abc (for layer 0)
    lv_img_set_src(widget->layer_image, &abc);
    
    LOG_INF("✨ Layer widget initialized with image display (64x64)");
    return 0;
}

void zmk_widget_layer_status_update(struct zmk_widget_layer_status *widget, struct zmk_keyboard_status *kbd) {
    update_layer_display(widget, kbd);
}

void zmk_widget_layer_status_reset(struct zmk_widget_layer_status *widget) {
    if (!widget || !widget->layer_image) {
        return;
    }
    
    LOG_INF("Layer widget reset - resetting to layer 0");
    
    // Reset image to abc (default state)
    lv_img_set_src(widget->layer_image, &abc);
}

lv_obj_t *zmk_widget_layer_status_obj(struct zmk_widget_layer_status *widget) {
    return widget ? widget->obj : NULL;
}