// ON/OFF Servo Motor
//   http://docs.spark.io/firmware/#libraries-servo

#include <stdarg.h>

Servo servo;
int led = D0;

#define PRINTF_BUFFER_SIZE 128
void Serial_printf(const char* fmt, ...) {
   char buff[PRINTF_BUFFER_SIZE];
   va_list args;
   va_start(args, fmt);
   vsnprintf(buff, PRINTF_BUFFER_SIZE, fmt, args);
   va_end(args);
   Serial.println(buff);
}

bool isComingHome = false;

int coming_home(String command)
{
  isComingHome = true;
  return 0;
}

void setup()
{
  // Use serial port for debug print
  Serial.begin(9600);

  // Expose coming_home api
  Spark.function("coming_home", coming_home);

  // Setup Servo
  servo.attach(A0);
  resetPosition();

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void resetPosition()
{
  int pos = servo.read();
  for (int i = pos; i > 3; i--) {
    servo.write(i);
    delay(50);
  }
}

void loop()
{
  if (isComingHome) {
    for (int i = 0; i < 50; i++) {
      digitalWrite(led, HIGH);
      delay(50);
      digitalWrite(led, LOW);
      delay(50);
      servo.write(i * (90.0 / 50.0));
    }
    isComingHome = false;
    for (int i = 0; i < 50; i++) {
      digitalWrite(led, HIGH);
      delay(50);
      digitalWrite(led, LOW);
      delay(50);
    }
    resetPosition();
  }
}
