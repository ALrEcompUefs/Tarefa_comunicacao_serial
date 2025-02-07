# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)

project(display_i2c_serial C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Criar biblioteca 'mtx'
add_library(mtx STATIC 
    mtx/ws2812.c
)

target_include_directories(mtx PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/mtx
)

# Adicionar executável
add_executable(display_i2c_serial 
    display_i2c_serial.c 
    inc/ssd1306.c 
)

# Gera o cabeçalho PIO a partir do arquivo .pio
pico_generate_pio_header(display_i2c_serial ${CMAKE_CURRENT_LIST_DIR}/mtx/pio_matrix.pio)

# Configurar nome e versão do programa
pico_set_program_name(display_i2c_serial "display_i2c_serial")
pico_set_program_version(display_i2c_serial "0.1")

# Habilitar saída UART/USB
pico_enable_stdio_uart(display_i2c_serial 1)
pico_enable_stdio_usb(display_i2c_serial 1)

# Incluir diretórios necessários
target_include_directories(display_i2c_serial PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

# Vincular bibliotecas ao executável
target_link_libraries(display_i2c_serial 
    pico_stdlib
    hardware_pio
    hardware_i2c
    mtx  # Linkando a biblioteca mtx corretamente
)

# Adicionar saídas extras
pico_add_extra_outputs(display_i2c_serial)
