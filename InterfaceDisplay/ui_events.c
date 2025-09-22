#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

char umidadeAlta[10];
// Função para capturar o valor digitado no teclado
void defineSPUmidadeAlta(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e); // Obtém o objeto que disparou o evento
    lv_obj_t *ta = lv_keyboard_get_textarea(obj); // Obtém a área de texto associada ao teclado

    if (ta) { // Verifica se a área de texto é válida
        const char *text = lv_textarea_get_text(ta); // Obtém o texto digitado na área de texto

        // Copia o texto para umidadeAlta, limitando o tamanho para evitar estouro de buffer
        snprintf(umidadeAlta, sizeof(umidadeAlta), "%s", text);

        // Exibe o valor no monitor serial
        printf("Umidade alta definida como: %s\n", umidadeAlta);
        int valorUmidadeAltaInt = atoi(umidadeAlta);
        int spUmidadeAlta = 4095 - (valorUmidadeAltaInt*4095)/100;
        printf("SP Umidade alta convertida: %i\n", spUmidadeAlta);
  
    } else {
        printf("Erro: Nenhuma área de texto associada.\n");
    }

    lv_obj_add_flag(ui_Keyboard2, LV_OBJ_FLAG_HIDDEN);     /// Flags
}
