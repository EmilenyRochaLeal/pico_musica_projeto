#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "notes.h"


// Definição dos LEDs (para um LED RGB)
#define LEDR 12
#define LEDG 11
#define LEDB 13

// Definição do pino do buzzer
const uint BUZZER = 21;

// Alterna a cor do LED RGB a cada nota
void set_rgb_color(int step) {
    switch (step % 3) {
        case 0:
            gpio_put(LEDR, 1);
            gpio_put(LEDG, 0);
            gpio_put(LEDB, 0);
            break;
        case 1:
            gpio_put(LEDR, 0);
            gpio_put(LEDG, 1);
            gpio_put(LEDB, 0);
            break;
        case 2:
            gpio_put(LEDR, 0);
            gpio_put(LEDG, 0);
            gpio_put(LEDB, 1);
            break;
    }
}


// Configuração do PWM para tocar uma nota
void play_note(uint pin, uint16_t frequency) {
    uint slice = pwm_gpio_to_slice_num(pin);
    
    if (frequency == 0) {
        pwm_set_enabled(slice, false); // Silencia o buzzer
        gpio_put(LEDR, 0);   // Desliga LED Vermelho
        gpio_put(LEDG, 0); // Desliga LED Verde
        gpio_put(LEDB, 0);  // Desliga LED Azul
        return;
    }
    
    uint wrap = (125000000 / 16) / frequency;  
    
    pwm_set_wrap(slice, wrap);
    pwm_set_gpio_level(pin, wrap / 2);
    pwm_set_enabled(slice, true);
    
}

// Função para tocar a melodia
void play_melody(uint pin) {
    for (int i = 0; i < SONG_LENGTH; i++) {  
        set_rgb_color(i);

        // Certifique-se de que SONG_LENGTH está definida
        int note_duration = 1000 / durations[i]; // Ajusta a duração da nota
        play_note(pin, melody[i]);  
        sleep_ms(note_duration); 
        
        // Silencia a nota e desliga os LEDs
        pwm_set_enabled(pwm_gpio_to_slice_num(pin), false);
        sleep_ms(50); // Pequena pausa entre as notas
    }
}


void stop_music() {
    // Para parar o buzzer, desativar o PWM no pino do buzzer
    uint slice = pwm_gpio_to_slice_num(BUZZER);
    pwm_set_enabled(slice, false); // Desliga o PWM do buzzer

    // Desliga os LEDs
    gpio_put(LEDR, 0);
    gpio_put(LEDG, 0);
    gpio_put(LEDB, 0);
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
    gpio_init(LEDR);
    gpio_init(LEDG);
    gpio_init(LEDB);
    gpio_set_dir(LEDR, GPIO_OUT);
    gpio_set_dir(LEDG, GPIO_OUT);
    gpio_set_dir(LEDB, GPIO_OUT);
    gpio_put(LEDR, 0);
    gpio_put(LEDG, 0);
    gpio_put(LEDB, 0);
}

// Executa a música
void main_audio() {
    play_melody(BUZZER);
}
