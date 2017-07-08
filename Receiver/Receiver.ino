/* Скетч для приемника (Arduino Micro) */

#include <VirtualWire.h>

const int RECEIVE_PIN = 12;

void setup()
{
  // Задержка а 1000 мс
  delay(1000);
  // Настраиваем последовательный порт
  Serial.begin(9600);
  // Устанавливаем пин для приема данных
  vw_set_rx_pin(RECEIVE_PIN);
  // Устанавливаем режим Push to Talk
  vw_set_ptt_inverted(true);
  // Устанавливаем скорость передачи 4000 бит/сек
  vw_setup(4000);
  // Запускаем прием данных
  vw_rx_start();
}

void loop()
{
  // Готовимся к приему сообщения
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  // Если сообщение пришло с верной контрольной сумой
  if (vw_get_message(buf, &buflen))
  {
    // Включаем светодиод при получении данных
    digitalWrite(LED_BUILTIN, HIGH);

    // Выводим сообщение в порт (Смотреть в мониторе порта - Ctrl+Shift+M)
    Serial.print("Receive: ");

    // Выводим полученное сообщение
    for (int i = 0; i < buflen; i++)
    {
      Serial.print((char)buf[i]);
    }

    // Новая строка
    Serial.println();

    // Отключаем светодиод
    digitalWrite(LED_BUILTIN, LOW);
  }
}
