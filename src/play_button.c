// #include "pico/stdlib.h"



// #define BUTTON_A 5 // Defina o pino correto onde o botão está conectado

// // Função para configurar o botão
// void setup_button() {
//     gpio_init(BUTTON_A);
//     gpio_set_dir(BUTTON_A, GPIO_IN);
//     gpio_pull_up(BUTTON_A);  // Configura o pino com resistor pull-up
 
    
// }

// void check_button_and_stop_music() {
//     static bool last_button_state = true;  // Começa com o botão não pressionado
//     bool button_state = gpio_get(BUTTON_A);  // Lê o estado atual do botão

//     // Verifica se o botão foi pressionado (estado de transição de HIGH para LOW)
//     if (!button_state && last_button_state) {
//         // Para a música quando o botão é pressionado
//         // printf("Botão pressionado!\n");
//         // stop_music(); // Chama a função para parar a música
//         sleep_ms(50);  // Delay para evitar múltiplos acionamentos do botão
//     }

//     last_button_state = button_state;  // Atualiza o estado anterior do botão
// }

#include "pico/stdlib.h"
#include "play_audio.h"

#define BUTTON_A 5   // Pino do botão
#define LED_PIN 12   // Pino do LED (onboard do Raspberry Pi Pico / BitDogLab)

void setup_button() {
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
}

void setup_led() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void check_button_and_stop_music() {
    static bool last_button_state = true;
    bool button_state = gpio_get(BUTTON_A);

    if (!button_state && last_button_state) {
        // Botão foi pressionado -> Acende o LED
        gpio_put(LED_PIN, 1);
        sleep_ms(500); // Mantém o LED aceso por meio segundo
        stop_music(); 
        // gpio_put(LED_PIN, 0); // Apaga
    }

    last_button_state = button_state;
}

