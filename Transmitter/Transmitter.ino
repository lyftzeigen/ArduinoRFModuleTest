/* Скетч для передатчика (Arduino UNO) */

// https://ru.aliexpress.com/item/1set-RF-module-433-Mhz-superheterodyne-receiver-and-transmitter-Support-ASK-OOK-small-size-low-power/32571703475.html?spm=2114.13010608.0.0.4dzcM0

#include <VirtualWire.h>

const int TRANSMIT_PIN = 12;
const int RANDOM_STRING_LENGTH = 25;

// Алфавит для генерации случайных чисел
const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz0123456789";

// Здесь будут храниться символы случайной строки без \0
char* message = new char[RANDOM_STRING_LENGTH];

void setup()
{   
  // Устанавливаем пин для передачи данных
  vw_set_tx_pin(TRANSMIT_PIN);
  // Устанавливаем режим Push to Talk
  vw_set_ptt_inverted(true);
  // Устанавливаем скорость передачи 4000 бит/сек
  vw_setup(4000);
}

void loop()
{ 
  for (int i = 0; i < RANDOM_STRING_LENGTH; i++)
  {
    message[i] = ALPHABET[random(0, strlen(ALPHABET))];
  }

  // Включаем светодиод во время передачи данных
  digitalWrite(LED_BUILTIN, HIGH);
  // Отправляем данные
  vw_send((uint8_t*)message, RANDOM_STRING_LENGTH);
  // Ждем окончания отправки данных
  vw_wait_tx();
  // Отключаем светодиод
  digitalWrite(LED_BUILTIN, LOW);
  // Задержка в 500 мс
  delay(500);
}

