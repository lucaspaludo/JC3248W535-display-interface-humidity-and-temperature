#include <ui.h>
#include <Arduino.h>
#include <lvgl.h>
#include "display.h"
#include "esp_bsp.h"
#include "lv_port.h"

#define LVGL_PORT_ROTATION_DEGREE (90)

/* Configurações de tela */
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

void setup()
{
    Serial.begin(115200);

    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = EXAMPLE_LCD_QSPI_H_RES * EXAMPLE_LCD_QSPI_V_RES,
#if LVGL_PORT_ROTATION_DEGREE == 90
        .rotate = LV_DISP_ROT_90,
#elif LVGL_PORT_ROTATION_DEGREE == 270
        .rotate = LV_DISP_ROT_270,
#elif LVGL_PORT_ROTATION_DEGREE == 180
        .rotate = LV_DISP_ROT_180,
#elif LVGL_PORT_ROTATION_DEGREE == 0
        .rotate = LV_DISP_ROT_NONE,
#endif
    };

    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();

    Serial.println("Create UI");
    bsp_display_lock(0); // Trava o mutex
    ui_init();           // Inicializa a interface
    bsp_display_unlock(); // Destrava o mutex
}

void loop()
{
    lv_timer_handler(); /* Atualiza a GUI */
    ui_Screen1_update_analog_read(); /* Atualiza a leitura do pino 5 */
    delay(100); /* Delay para evitar atualizações muito rápidas */
}
