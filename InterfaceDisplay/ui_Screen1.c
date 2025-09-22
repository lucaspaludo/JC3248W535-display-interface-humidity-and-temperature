#include "ui.h"
#include <Arduino.h> // Para funções como analogRead

#define ANALOG_PIN 5 // Define o pino analógico como 5

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_s1PanelFundo = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_s1PanelFundo, lv_pct(100));
    lv_obj_set_height(ui_s1PanelFundo, lv_pct(100));
    lv_obj_set_align(ui_s1PanelFundo, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_s1PanelFundo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_s1PanelFundo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_s1PanelFundo, lv_color_hex(0xB4CEFD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_s1PanelFundo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_s1PanelTopo = lv_obj_create(ui_s1PanelFundo);
    lv_obj_set_width(ui_s1PanelTopo, lv_pct(40));
    lv_obj_set_height(ui_s1PanelTopo, lv_pct(30));
    lv_obj_clear_flag(ui_s1PanelTopo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_s1PanelTopo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_s1Titulo = lv_label_create(ui_s1PanelTopo);
    lv_obj_set_width(ui_s1Titulo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_s1Titulo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_s1Titulo, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_s1Titulo, "Leitura Umidade");

    ui_s1LeituraUmid = lv_label_create(ui_s1PanelTopo);
    lv_obj_set_width(ui_s1LeituraUmid, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_s1LeituraUmid, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_s1LeituraUmid, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_s1LeituraUmid, "0");

    // Configuração do pino analógico
    pinMode(ANALOG_PIN, INPUT);

        ui_setPointUmidadeAlta = lv_textarea_create(ui_Screen1);
    lv_obj_set_width(ui_setPointUmidadeAlta, 156);
    lv_obj_set_height(ui_setPointUmidadeAlta, 70);
    lv_obj_set_x(ui_setPointUmidadeAlta, 144);
    lv_obj_set_y(ui_setPointUmidadeAlta, -85);
    lv_obj_set_align(ui_setPointUmidadeAlta, LV_ALIGN_CENTER);
    lv_textarea_set_placeholder_text(ui_setPointUmidadeAlta, "Umidade alta");

    ui_labelUmidadeAlta = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_labelUmidadeAlta, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_labelUmidadeAlta, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_labelUmidadeAlta, 141);
    lv_obj_set_y(ui_labelUmidadeAlta, -134);
    lv_obj_set_align(ui_labelUmidadeAlta, LV_ALIGN_CENTER);
    lv_label_set_text(ui_labelUmidadeAlta, "Setpoint umidade alta");

    ui_Keyboard2 = lv_keyboard_create(ui_Screen1);
    lv_keyboard_set_mode(ui_Keyboard2, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_set_width(ui_Keyboard2, 399);
    lv_obj_set_height(ui_Keyboard2, 120);
    lv_obj_set_x(ui_Keyboard2, 6);
    lv_obj_set_y(ui_Keyboard2, 90);
    lv_obj_set_align(ui_Keyboard2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Keyboard2, LV_OBJ_FLAG_HIDDEN);     /// Flags

    lv_obj_add_event_cb(ui_setPointUmidadeAlta, ui_event_setPointUmidadeAlta, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Keyboard2, ui_event_Keyboard2, LV_EVENT_ALL, NULL);

}

void ui_Screen1_update_analog_read(void)
{
    // Leitura do valor analógico
    int analogValue = analogRead(ANALOG_PIN);

    // Conversão do valor para string
    char valueStr[10];
    snprintf(valueStr, sizeof(valueStr), "%d", analogValue);
    //printf("%s\n", valueStr);

    // Atualização do label
    lv_label_set_text(ui_s1LeituraUmid, valueStr);
}
