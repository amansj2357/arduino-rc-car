//This one is the one

#include <ArduinoBLE.h>

// --- MOTOR PINS ---
int motorLeftPin1 = 2;
int motorLeftPin2 = 3;
int motorRightPin1 = 4;
int motorRightPin2 = 5;

int leftWheel = 9;
int rightWheel = 10;

  // Create a BLE Service
  BLEService carService("19B10000-E8F2-537E-4F6C-D104768A1214");

// Mailbox that accepts Dabble's full 8-byte packet
BLECharacteristic commandChar("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLEWriteWithoutResponse, 20);

// --- ANTI-SPAM MEMORY ---
bool isStopped = true;

void setup() {
  Serial.begin(9600);

  pinMode(motorLeftPin1, OUTPUT);
  pinMode(motorLeftPin2, OUTPUT);
  pinMode(motorRightPin1, OUTPUT);
  pinMode(motorRightPin2, OUTPUT);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // Set speed (0 to 255)
  analogWrite(9, 200);
  analogWrite(10, 200);

  if (!BLE.begin()) {
    Serial.println("Starting Bluetooth failed!");
    while (1)
      ;
  }

  BLE.setLocalName("RobotCar");
  BLE.setAdvertisedService(carService);
  carService.addCharacteristic(commandChar);
  BLE.addService(carService);
  stopCar();

  BLE.advertise();
  Serial.println("Bluetooth active! Waiting for Dabble connection...");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to phone: ");
    Serial.println(central.address());

    while (central.connected()) {
      if (commandChar.written()) {

        int length = commandChar.valueLength();
        const uint8_t* rawData = commandChar.value();

        // Check if it's a Dabble Packet (Starts with FF and is at least 8 bytes long)
        if (length >= 8 && rawData[0] == 0xFF) {

          // Isolate all 3 possible Gamepad bytes
          uint8_t extraState = rawData[5];   // Dabble might hide Action Buttons here!
          uint8_t buttonState = rawData[6];  // D-Pad Left Side
          uint8_t actionState = rawData[7];  // Right Gamepad

          // --- D-PAD CONTROLS (Left Side) ---
          if (buttonState == 1) {
            if (isStopped) {
              Serial.println("Driving FORWARD");
              isStopped = false;
            }
            moveForward();
          } else if (buttonState == 2) {
            if (isStopped) {
              Serial.println("Driving BACKWARD");
              isStopped = false;
            }
            moveBackward();
          } else if (buttonState == 8) {
            if (isStopped) {
              Serial.println("Turning LEFT");
              isStopped = false;
            }
            turnLeft();
          } else if (buttonState == 4) {
            if (isStopped) {
              Serial.println("Turning RIGHT");
              isStopped = false;
            }
            turnRight();
          }

          // --- ACTION BUTTON CONTROLS (Right Side) ---
          // We check both actionState AND extraState to catch the button press
          else if (actionState == 1 || extraState == 1) {
            if (isStopped) {
              Serial.println("Start Button");
              isStopped = false;
            }
          } else if (actionState == 2 || extraState == 2) {
            if (isStopped) {
              Serial.println("Select Button");
              isStopped = false;
            }
          } else if (actionState == 4 || extraState == 4) {
            if (isStopped) {
              Serial.println("Triangle Pressed");
              isStopped = false;
              triangle();
            }
          } else if (actionState == 8 || extraState == 8) {
            if (isStopped) {
              Serial.println("Circle Pressed");
              isStopped = false;
              circle();
            }
          } else if (actionState == 16 || extraState == 16) {
            if (isStopped) {
              Serial.println("X Pressed");
              isStopped = false;
              x();
            }
          } else if (actionState == 32 || extraState == 32) {
            if (isStopped) {
              Serial.println("Square Pressed");
              isStopped = false;
              square();
            }
          }

          // --- STOPPING LOGIC ---
          // Only stop if ALL bytes read 0
          else if (buttonState == 0 && actionState == 0 && extraState == 0) {
            if (!isStopped) {  // Only print if it isn't ALREADY stopped
              Serial.println("Stopped");
              stopCar();
              isStopped = true;
            }
          }

          // --- UNKNOWN BUTTON TRAP ---
          else {
            Serial.print("Unknown Button Data - Byte 5: ");
            Serial.print(extraState);
            Serial.print(" | Byte 6: ");
            Serial.print(buttonState);
            Serial.print(" | Byte 7: ");
            Serial.println(actionState);
          }
        }
      }
    }
    Serial.println("Phone disconnected. Stopping car.");
    stopCar();
  }
}

// --- MOTOR CONTROL FUNCTIONS ---

void moveForward() {
  analogWrite(9, 200);
  analogWrite(10, 210);
  digitalWrite(motorLeftPin1, LOW);
  digitalWrite(motorLeftPin2, HIGH);
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, HIGH);
}

void moveBackward() {
  analogWrite(9, 200);
  analogWrite(10, 210);
  digitalWrite(motorLeftPin1, HIGH);
  digitalWrite(motorLeftPin2, LOW);
  digitalWrite(motorRightPin1, HIGH);
  digitalWrite(motorRightPin2, LOW);
}

void turnLeft() {
  analogWrite(9, 150);
  analogWrite(10, 150);
  digitalWrite(motorLeftPin1, LOW);
  digitalWrite(motorLeftPin2, HIGH);
  digitalWrite(motorRightPin1, HIGH);
  digitalWrite(motorRightPin2, LOW);
}

void turnRight() {
  analogWrite(9, 150);
  analogWrite(10, 150);
  digitalWrite(motorLeftPin1, HIGH);
  digitalWrite(motorLeftPin2, LOW);
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, HIGH);
}

void stopCar() {
  digitalWrite(motorLeftPin1, LOW);
  digitalWrite(motorLeftPin2, LOW);
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, LOW);
}

void circle() {
  analogWrite(9, 255);
  analogWrite(10, 255);
  digitalWrite(motorLeftPin1, LOW);
  digitalWrite(motorLeftPin2, HIGH);
  digitalWrite(motorRightPin1, HIGH);
  digitalWrite(motorRightPin2, LOW);
}

void square() {
  analogWrite(9, 255);
  analogWrite(10, 255);
  digitalWrite(motorLeftPin1, HIGH);
  digitalWrite(motorLeftPin2, LOW);
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, HIGH);
}

void triangle() {
  analogWrite(9, 255);
  analogWrite(10, 255);
  digitalWrite(motorLeftPin1, LOW);
  digitalWrite(motorLeftPin2, HIGH);
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, HIGH);
}

void x() {
  analogWrite(9, 255);
  analogWrite(10, 255);
  digitalWrite(motorLeftPin1, HIGH);
  digitalWrite(motorLeftPin2, LOW);
  digitalWrite(motorRightPin1, HIGH);
  digitalWrite(motorRightPin2, LOW);
}
