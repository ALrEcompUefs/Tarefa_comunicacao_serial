#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"

// Pinos dos perifericos

const uint8_t LED_R=13, LED_B=12, LED_G=11;
const uint8_t BOTAO_A=5;BOTAO_B=6;

// protótipos de funções
void inicializar_leds();
void inicializar_botoes();
void set_rgb(char cor);
static void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}



/*
|   Função inicializar_leds
|   Configura os pinos da LED RGB
*/
void inicializar_leds(){
    // led vermelha
    gpio_init(LED_R);
    gpio_set_dir(LED_R,GPIO_OUT);
    // led verde
    gpio_init(LED_G);
    gpio_set_dir(LED_G,GPIO_OUT);
    // led azul
    gpio_init(LED_B);
    gpio_set_dir(LED_B,GPIO_OUT);
}


void inicializar_botoes(){
    //botão A
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A,GPIO_IN);
    gpio_pull_up(BOTAO_A);
}
