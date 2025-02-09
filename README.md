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


## Display oled i2c


## Matriz de Led


## UART


## Entrada dos botões


## Vídeo
