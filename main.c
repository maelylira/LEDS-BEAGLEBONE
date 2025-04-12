#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define LED_PATH "/sys/class/leds/beaglebone:green:usr"

// Função para verificar se um arquivo existe
int file_exists(const char *path) {
    return access(path, F_OK) == 0;
}

// Função para controlar o LED
void set_led_state(int led_num, const char *state) {
    char path[50];
    FILE *led_file;

    snprintf(path, sizeof(path), "%s%d/brightness", LED_PATH, led_num);

    if (!file_exists(path)) {
        fprintf(stderr, "Erro: O arquivo do LED %d não existe (%s).\n", led_num, path);
        exit(EXIT_FAILURE);
    }

    led_file = fopen(path, "w");
    if (led_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo do LED %d (%s): %s\n", led_num, path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    fprintf(led_file, "%s", state);
    fclose(led_file);
}

int main() {
    int led_num;
    const int delay = 500000; // 500 ms

    printf("Iniciando o piscar dos LEDs...\n");

    while (1) {
        for (led_num = 0; led_num < 4; led_num++) {
            set_led_state(led_num, "1"); // Acende o LED
            usleep(delay);
            set_led_state(led_num, "0"); // Apaga o LED
        }
    }

    return 0;
}


