#include <N64Controller.h>

N64Controller controller (12); // this controller for player one is on PIN 12

void setup() {
    Serial.begin(9600);
    controller.begin(); // Initialisation
}

void loop() {
    delay(100);
    controller.update();
    // player1.print_N64_status();

    Serial.print("Stick: ");
    Serial.print(controller.axis_x(), DEC);
    Serial.print(" , ");
    Serial.println(controller.axis_y(), DEC);

    if (controller.A())
      Serial.println("A");

     if (controller.B())
      Serial.println("B");
}
