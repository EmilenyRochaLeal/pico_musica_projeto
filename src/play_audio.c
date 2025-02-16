#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "notes.h"

// Definição dos LEDs (para um LED RGB)
#define LED_RED 12
#define LED_GREEN 13  // LED Verde no pino 13
#define LED_BLUE 14

// Definição do pino do buzzer
const uint BUZZER = 21;

// Configuração do PWM para tocar uma nota
void play_note(uint pin, uint16_t frequency) {
    uint slice = pwm_gpio_to_slice_num(pin);

    if (frequency == 0) {
        pwm_set_enabled(slice, false); // Silencia o buzzer
        gpio_put(LED_RED, 0);   // Desliga LED Vermelho
        gpio_put(LED_GREEN, 0); // Desliga LED Verde
        gpio_put(LED_BLUE, 0);  // Desliga LED Azul
        return;
    }

    uint wrap = (125000000 / 16) / frequency;  

    pwm_set_wrap(slice, wrap);
    pwm_set_gpio_level(pin, wrap / 2);
    pwm_set_enabled(slice, true);

    // Acender apenas o LED Verde
    gpio_put(LED_RED, 0);   // Desliga Vermelho
    gpio_put(LED_GREEN, 1); // Acende Verde
    gpio_put(LED_BLUE, 0);  // Desliga Azul
}

// Função para tocar a melodia
void play_melody(uint pin) {
    for (int i = 0; i < SONG_LENGTH; i++) {  // Certifique-se de que SONG_LENGTH está definida
        int note_duration = 1000 / durations[i]; // Ajusta a duração da nota
        play_note(pin, melody[i]);  
        sleep_ms(note_duration); 
        
        // Silencia a nota e desliga os LEDs
        pwm_set_enabled(pwm_gpio_to_slice_num(pin), false);
        gpio_put(LED_RED, 0);
        gpio_put(LED_GREEN, 0); // Desliga o LED Verde
        gpio_put(LED_BLUE, 0);

        sleep_ms(50); // Pequena pausa entre as notas
    }
}

// Configuração inicial
void setup_audio() {
    stdio_init_all();
    
    // Configuração do buzzer como saída PWM
    gpio_set_function(BUZZER, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(BUZZER);
    pwm_set_clkdiv(slice, 16.0);
    pwm_set_enabled(slice, false);

    // Inicializa LEDs
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    // Garante que os LEDs comecem desligados
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
}

// Executa a música
void main_audio() {
    play_melody(BUZZER);
}
