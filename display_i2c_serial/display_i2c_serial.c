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
