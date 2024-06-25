#include <Servo.h>

Servo servo_0; // Declaración del objeto para controlar el primer servo
Servo servo_1; // Declaración del objeto para controlar el segundo servo
Servo servo_2; // Declaración del objeto para controlar el tercer servo
Servo servo_3; // Declaración del objeto para controlar el cuarto servo
Servo servo_4; // Declaración del objeto para controlar el quinto servo
Servo servo_5; // Declaración del objeto para controlar el sexto servo

void setup() {
  Serial.begin(9600); // Inicializar comunicación serial
  servo_0.attach(2); // Asocia el servo_0 al pin 2
  servo_1.attach(3); // Asocia el servo_1 al pin 3
  servo_2.attach(4); // Asocia el servo_2 al pin 4
  servo_3.attach(5); // Asocia el servo_3 al pin 5
  servo_4.attach(6); // Asocia el servo_4 al pin 6
  servo_5.attach(7); // Asocia el servo_5 al pin 7
}

void loop() {
  if (Serial.available() > 0) { // Si hay datos disponibles para leer
    String input = Serial.readStringUntil('\n'); // Leer la cadena de datos hasta el salto de línea
    input.trim(); // Eliminar espacios en blanco al inicio y final de la cadena

    int angles[6];
    int angleIndex = 0;
    int startIndex = 0;
    for (int i = 0; i < input.length(); i++) {
      if (input[i] == ',' || i == input.length() - 1) {
        String angleStr;
        if (i == input.length() - 1) {
          angleStr = input.substring(startIndex);
        } else {
          angleStr = input.substring(startIndex, i);
        }
        angles[angleIndex] = angleStr.toInt();
        angleIndex++;
        startIndex = i + 1;
      }
    }

    if (angleIndex == 6) {
      servo_0.write(angles[0]);
      servo_1.write(angles[1]);
      servo_2.write(angles[2]);
      servo_3.write(angles[3]);
      servo_4.write(angles[4]);
      servo_5.write(angles[5]);
    }
  }
}
