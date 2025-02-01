#include <stdio.h> // Biblioteca padrão do C.
#include "pico/stdlib.h" // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.

const uint LED_PIN_GREEN = 11;
const uint LED_PIN_BLUE = 12; 
const uint LED_PIN_RED = 13;     
const uint BUTTON_PIN = 5;  // Define o pino GPIO 5 para ler o estado do botão.

bool led_sequence_active = false;  // Indica se a sequência de LEDs está em execução.

// Função de callback para desligar o LED vermelho
int64_t turn_off_callback_red(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_RED, false);
    led_sequence_active = false;  // Libera o botão para nova ativação
    return 0;
}

// Função de callback para desligar o LED verde
int64_t turn_off_callback_green(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_GREEN, false);
    return 0;
}

// Função de callback para desligar o LED azul
int64_t turn_off_callback_blue(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_BLUE, false);
    return 0;
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    while (true) {
        if (gpio_get(BUTTON_PIN) == 0 && !led_sequence_active) {
            sleep_ms(50); // Debounce

            if (gpio_get(BUTTON_PIN) == 0) { // Verificação extra após debounce
                led_sequence_active = true;  // Bloqueia novas ativações até o fim da sequência

                gpio_put(LED_PIN_RED, true);
                gpio_put(LED_PIN_GREEN, true);
                gpio_put(LED_PIN_BLUE, true);

                add_alarm_in_ms(3000, turn_off_callback_green, NULL, false);
                add_alarm_in_ms(6000, turn_off_callback_blue, NULL, false);
                add_alarm_in_ms(9000, turn_off_callback_red, NULL, false);
            }
        }

        sleep_ms(10);
    }
    return 0;
}
