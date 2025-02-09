# Tarefa comunicacao serial

Este repósitorio é destiando para implementação da tarefa sobre comunicação serial da unidde 4 de microntoladores do curso de formação básica em software embarcado do Embarcatech

Recursos utilizados no projeto:

* Matriz 5x5 de LEDs (endereçáveis) WS2812, conectada à GPIO 7.
* LED RGB, com os pinos conectados às GPIOs (11, 12 e 13).
* Botão A conectado à GPIO 5
* Botão B conectado à GPIO 6.
* Display SSD1306 conectado via I2C (GPIO 14 e GPIO15).

Funcionalidades do projeto

1. Modificação da Biblioteca font.h
   * Adicionar caracteres minúsculos à biblioteca font.h. Use sua criatividade para criar os novos
     caracteres.
2. Entrada de caracteres via PC
   * Utilize o Serial Monitor do VS Code para digitar os caracteres
   * Cada caractere digitado no Serial Monitor deve ser exibido no display SSD1306.
     Observação: Apenas um caractere será enviado de cada vez, não é necessário suportar o
     envio de strings completas.
   * Quando um número entre 0 e 9 for digitado, um símbolo correspondente ao número deve
     ser exibido, também, na matriz 5x5 WS2812.
3. Interação com o Botão A
   * Pressionar o botão A deve alternar o estado do LED RGB Verde (ligado/desligado)
   * A operação deve ser registrada de duas formas:
     * Uma mensagem informativa sobre o estado do LED deve ser exibida no display
       SSD1306
     * Um texto descritivo sobre a operação deve ser enviado ao Serial Monitor.
4. Interação com o Botão B
   * Pressionar o botão A deve alternar o estado do LED RGB Azul (ligado/desligado)
   * A operação deve ser registrada de duas formas:
     * Uma mensagem informativa sobre o estado do LED deve ser exibida no display
       SSD1306
     * Um texto descritivo sobre a operação deve ser enviado ao Serial Monitor
     * 

## Diagrama do circuito

Na figura abaixo está representado o diagrama do circuito montado no simulador wokwi, nela estão presentes os perifericos utilizados neste projeto junto ao microcontrolador raspberry pi pico w

![Diagrama do circuito Implementado no wokwi](https://github.com/ALrEcompUefs/Tarefa_comunicacao_serial/blob/main/img/img1.png?raw=true "Diagrama do circuito")

## Display oled i2c

Utilizando a biblioteca  **ssd1306** disponibilizada para o projeto é possível utilzar o display oled presente na placa bitdoglab para exibir textos com fonte maiúsculas por isso foi solicitado adicionar letras minúsculas ao arquivo **font.h**. 

As letras minusculas foram criadas em um arquivo de edição como na figura abaixo e depois o número de pixel ativos dentro da região de 8x8 pixels foi convertido para um número hexadecimal equivalente a cada coluna.

![img](https://github.com/ALrEcompUefs/Tarefa_comunicacao_serial/blob/main/img/img2.png?raw=true "Criação das fontes")

A partir dos números hexadecimais equivalantes a cada letra o arquivo font.h foi atualizado com as novas letras como segue no exemplo abaixo.

```c
0x00, 0x38, 0x44, 0x44, 0x028, 0x7C,0x00, 0x00, //a
0x00, 0x7F, 0x28, 0x44, 0x44, 0x38, 0x00, 0x00, //b
0x00, 0x38, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00, //c
0x00, 0x38, 0x44, 0x44, 0x28, 0x7F, 0x00, 0x00, //d
0x00, 0x38, 0x54, 0x54, 0x54, 0x58, 0x00, 0x00, //e
0x00, 0x00, 0x04, 0x7F, 0x05, 0x00, 0x00, 0x00, //f
0x00, 0x0E, 0x51, 0x51, 0x4A, 0x3F, 0x00, 0x00, //g
0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, 0x00, //h
```

A bibllioteca ssd1306 teve uma atualização na função **ssd1306_draw_char** para reconhecer as letras minúsculas

```c
else if (c >='a' && c <='z'){
    index = (c - 'a' + 37) * 8; // Para letras minúsculas
  }
```

Este trecho de codígo calcula o indice da letra no vetor de fonte com base no valor ASCII e na primeira posição dentro do vetor.

As operações com o display oled utilizam as funções da biblioteca disponibilizada e da biblioteca **hardware/i2**c que possibilita a comunicação serial i2c no raspberry pi pico w. No código são definidos os pinos de comunicação i2c do pico w que são os pinos 14(SDA) e 15(SCL) além do endereço do display oled que é o **0x3C.**

## Matriz de Led

A Matriz de leds RGB WS2812 é utilizada para exibir números de 0 a 9 quando são lidos na entrada serial.

Para utilizar a matriz foi utilizada a biblioteca definifa pelo usúario ws2812, nela as funçãos básicas para inicialização e desenho da matriz são implementadas bastando realizar a chamada destas funções.

Para inicializar a matriz e a exibição de núemros deve ser feita a seguinte rotina

```
// Variavéis globais para desenho da matriz
PIO pio;
uint sm;
// incializa PIO para utilizar matriz de leds
    pio = pio0;
    sm = configurar_matriz(pio);
    configurar_numero();

```

Para desenhar números na matriz e apaga-la usa-se as funções ` imprimir_numero(valor,pio,sm);` e `  apagar_matriz(pio,sm);.`

## UART

Para a entrada de dados pelo computador foi utilizada a UART e o monitor serial para leitura dos caracteres enviados

```c
// se a conexão usb está garantida
        if(stdio_usb_connected){
            // leitura do caractere da fila
            if (scanf("%c\n",&msg)==1){
                atualizar_matriz(msg);
                printf("Caractere recebido:%c\n",msg);
            }
        }
```

Os dados recebidos via monitor serial são exibidos no monitor e tamém no display oled

## Entrada dos botões

Os três botões presentes na placa bitdoglab foram utilizados no projeto, todos foram configurados como pinos de entrada em modo pull-up no pico w e a leitura do botão é feita com uma rotina de interrupção para borda de descida.

Um debouncer foi implementado dentro da rotina de interrupção para minimizar os efeitos de ruído no projeto.

Foram declaradas duas variáveis globais com modificador **static volatile** para o controle das leds: **led_g_on** e **led_b_on** cada vez que um botão é apertado o estado da led que ele está controlando é trocado pelo operador de negação **!** e a função **set_rgb(**) atualiza o estado da led.

Para facilitar o desenvolvimento na placa bitdoglab o botão do módulo joystick no pio 22 é utilizado para ativar o modo bootsel.

## Estrutura do programa

Descrevendo a estrutura geral do programa

1. Importação das bibliotecas
2. Definição das portas e endereços para o display oled
3. Declaração dos pinos da GPIO dos périfericos
4. Declaração de variáveis globais
5. Declaração do protótipo de funções
6. Função main
7. Declaração de funções

Descrevendo a função main temos:

* Inicialização da entrada e saída padrão `stdio_init_all();`
* Inicialização da matriz de leds
* Inicialização dos périfericos leds e botões com a chaamada da funções de inicialização
* Definição das rotinas de interupção para os botões `gpio_set_irq_enabled_with_callback(BOTAO_A,GPIO_IRQ_EDGE_FALL,true,&gpio_irq_handler);`
* Super laço

Dentro do laço tem-se:

```c
// atualiza display de leds
        atualizar_display(msg);
        // se a conexão usb está garantida
        if(stdio_usb_connected){
            // leitura do caractere da fila
            if (scanf("%c\n",&msg)==1){
                atualizar_matriz(msg);
                printf("Caractere recebido:%c\n",msg);
            }
        }
        sleep_ms(500);
```

Primeiro o display de leds é atualizado para exibir novas informações, em seguida é verificado se a porta serial está disponivél e caso esteja éf eita a leitura da porta serial e o caractere lido vai ser exibido na proxíma atualização do display oled. A função atualizar matriz é chamada passando como parâmetro o caractere lido, se for um número ele é exibido na matriz de leds e caso seja uma letra a matriz é apagada.

Sempre que um botão for apertado ou um caractere for lido na porta serial a informação é impressa no monitor serial.

Para entrar em modo bootsel basta apertar o botão do joystick.

## Vídeo
