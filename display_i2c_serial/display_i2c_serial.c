#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "pico/time.h"
#include "hardware/pio.h"
#include "inc/ssd1306.h"
#include "ws2812.h"
#include "hardware/i2c.h"
#include "inc/font.h"

// definições para uso do display oled integrado
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Pinos dos perifericos
const uint8_t LED_R=13, LED_B=12, LED_G=11;
const uint8_t BOTAO_A=5,BOTAO_B=6,BOTAO_JYK=22;

// Variavél para registro de tempo e controle de bounce da interrupção
static volatile uint32_t tempo_anterior = 0;
// Variável de controle das leds
static volatile bool led_g_on=false,led_b_on=false;
// protótipos de funções
void inicializar_leds();
void inicializar_botoes();
void set_rgb(char cor,bool ativa);
static void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    // incializa PIO para utilizar matriz de leds
    PIO pio = pio0;
    uint sm = configurar_matriz(pio);
    configurar_numero();

    // variável para leitura serial
    char msg= '\0';

    // Configura GPIO para os leds e botões
    inicializar_leds();
    inicializar_botoes();
    //cria gatilhos de interrupções para os os botões
    gpio_set_irq_enabled_with_callback(BOTAO_A,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_B,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_JYK,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handler);

    while (true) {
        // se a conexão usb está garantida
        if(stdio_usb_connected){
            // leitura do caractere dafila
            if (scanf("%c\n",&msg)==1){
                printf("Caractere recebido:%c\n",msg);
            }
        }
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
    //botão B
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B,GPIO_IN);
    gpio_pull_up(BOTAO_B);
    //botão C
    gpio_init(BOTAO_JYK);
    gpio_set_dir(BOTAO_JYK,GPIO_IN);
    gpio_pull_up(BOTAO_JYK);
}


/*
|   Função set_rgb
|   Ativa ou desativa a cor rgb de acordo ao parâmetro cor e o paramêtro on
|   char cor: 'R'= vermelho 'G' = verde 'B' = azul 'W' = branco '-' apagar  
*/
void set_rgb(char cor,bool ativa){
    switch (cor)
    {
    case 'R':
        gpio_put(LED_R,ativa);
        break;
    case 'G':
        gpio_put(LED_G,ativa);
        break;
    case 'B':
        gpio_put(LED_B,ativa);
        break;
    case 'W':
        gpio_put(LED_R,ativa);
        gpio_put(LED_G,ativa);
        gpio_put(LED_B,ativa);
        break;
    case '-':
        gpio_put(LED_R,0);
        gpio_put(LED_G,0);
        gpio_put(LED_B,0);
        break;
    default:
        printf("Caractere invalido!!\n informe R,G,B,W ou -\n");
        break;
    }
}

static void gpio_irq_handler(uint gpio, uint32_t events){
    // obtém tempo atual da execução do programa
    uint32_t tempo_atual = to_us_since_boot(get_absolute_time());
    // com o botão pressionado por pelo menos 200ms
    if(tempo_atual-tempo_anterior > 200000){
        tempo_anterior= tempo_atual;
        // executa tratamento da interrupção
        if(gpio == BOTAO_A){
            //atualiza variável da led
            led_g_on = !led_g_on;
            // configura a led verde
            set_rgb('G',led_g_on);
            // Informe pelo monitor serial
            printf("A led verde está com valor:%d\n",led_g_on);
        }
        else if(gpio == BOTAO_B){
            led_b_on = !led_b_on;
            // configura a led azul
            set_rgb('B',led_b_on);
            // Informe pelo monitor serial
            printf("A led azul está com valor:%d\n",led_b_on);
        }
        else if(gpio == BOTAO_JYK){
            reset_usb_boot(0,0);
        }
    }
}