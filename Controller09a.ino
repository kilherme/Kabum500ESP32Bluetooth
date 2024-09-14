// Projeto para Controlar Robo Aspirador Kabum Smart 500/ Liectroux-C30B usando ESP32 e controle Bluetooth
// Usa as bibliotecas pra Arduino BluePad32 e ESP32

#include <Bluepad32.h>
#include <uni.h>
#include "PinDefinitionsAndMore.h"
#if !defined(ARDUINO_ESP32C3_DEV) // This is due to a bug in RISC-V compiler, which requires unused function sections :-(.
#define DISABLE_CODE_FOR_RECEIVER // Disables static receiver code like receive timer ISR handler and static IRReceiver and irparams data. Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not required.
#endif
//#define EXCLUDE_EXOTIC_PROTOCOLS  // Saves around 240 bytes program memory if IrSender.write is used
//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition
//#define USE_ACTIVE_HIGH_OUTPUT_FOR_SEND_PIN // Simulate an active high receiver signal instead of an active low signal.
//#define USE_OPEN_DRAIN_OUTPUT_FOR_SEND_PIN  // Use or simulate open drain output mode at send pin. Attention, active state of open drain is LOW, so connect the send LED between positive supply and send pin!
//#define NO_LED_FEEDBACK_CODE      // Saves 566 bytes program memory

//#undef IR_SEND_PIN // enable this, if you need to set send pin programmatically using uint8_t tSendPin below
#include <IRremote.hpp>
#define DELAY_AFTER_SEND 200
#define DELAY_AFTER_LOOP 500

static const char * controller_addr_string = "aa:bb:cc:dd:ee:ff";//MAC Adress Bluetooth do Gamepad


ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
            // Additionally, you can get certain gamepad properties like:
            // Model, VID, PID, BTAddr, flags, etc.
            ControllerProperties properties = ctl->getProperties();
            Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                           properties.product_id);
            myControllers[i] = ctl;
            foundEmptySlot = true;
            break;
        }
    }
    if (!foundEmptySlot) {
        Serial.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            foundController = true;
            break;
        }
    }

    if (!foundController) {
        Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

void dumpGamepad(ControllerPtr ctl) {
    Serial.printf(
        "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
        "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
        ctl->index(),        // Controller Index
        ctl->dpad(),         // D-pad
        ctl->buttons(),      // bitmask of pressed buttons
        ctl->axisX(),        // (-511 - 512) left X Axis
        ctl->axisY(),        // (-511 - 512) left Y axis
        ctl->axisRX(),       // (-511 - 512) right X axis
        ctl->axisRY(),       // (-511 - 512) right Y axis
        ctl->brake(),        // (0 - 1023): brake button
        ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
        ctl->miscButtons(),  // bitmask of pressed "misc" buttons
        ctl->gyroX(),        // Gyro X
        ctl->gyroY(),        // Gyro Y
        ctl->gyroZ(),        // Gyro Z
        ctl->accelX(),       // Accelerometer X
        ctl->accelY(),       // Accelerometer Y
        ctl->accelZ()        // Accelerometer Z
    );
}



void processGamepad(ControllerPtr ctl) {
    // There are different ways to query whether a button is pressed.
    // By query each button individually:
    //  a(), b(), x(), y(), l1(), etc...
    if (ctl->buttons()==0x0008) {//UP
      Serial.printf("UP \n");
      IrSender.sendPulseDistanceWidth(38, 3100, 2950, 600, 1600, 600, 500, 0x7A2D55, 24, PROTOCOL_IS_LSB_FIRST, 20, 25);
    }

    if (ctl->buttons()==0x0004) {//LEFT
      Serial.printf("LEFT \n");
      IrSender.sendPulseDistanceWidth(38, 3100, 2950, 600, 1600, 600, 500, 0xF2A555, 24, PROTOCOL_IS_LSB_FIRST, 20, 7);
    }

    if (ctl->buttons()==0x0001) {//DOWN
      Serial.printf("DOWN \n");
      IrSender.sendPulseDistanceWidth(38, 3050, 2950, 600, 1600, 600, 500, 0x441E55, 24, PROTOCOL_IS_LSB_FIRST, 20, 7);
    }
    if (ctl->buttons()==0x0002) {//RIGHT
      Serial.printf("RIGHT \n");
      IrSender.sendPulseDistanceWidth(38, 3100, 2950, 600, 1600, 600, 500, 0x8CE155, 24, PROTOCOL_IS_LSB_FIRST, 20, 7);
    }    
    if (ctl->buttons()==0x0010) {//Mode //São 3 sinais para cada modo em apenas um botão, falta implementar
      Serial.printf("MODE \n");
    }
    if (ctl->buttons()==0x0020) {//Type
      Serial.printf("Type \n");
      IrSender.sendPulseDistanceWidth(38, 3100, 2900, 600, 1600, 600, 500, 0x673C55, 24, PROTOCOL_IS_LSB_FIRST, 20, 7);
    }
    if (ctl->buttons()==0x0100) {//Home
      Serial.printf("HOME \n");
      IrSender.sendPulseDistanceWidth(38, 3100, 2950, 600, 1600, 600, 500, 0xB6C355, 24, PROTOCOL_IS_LSB_FIRST, 20, 7);
    }
    if (ctl->buttons()==0x0200) {//Play
      Serial.printf("PLAY \n");
      IrSender.sendPulseDistanceWidth(38, 3050, 2950, 600, 1600, 600, 500, 0x26955, 24, PROTOCOL_IS_LSB_FIRST, 20, 7);
    }
    dumpGamepad(ctl);//Mostra código do botão em hexa e qual botão
}




void processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            if (myController->isGamepad()) {
                processGamepad(myController);
            }
            else {
                Serial.println("Unsupported controller");
            }
        }
    }
}

// Arduino setup function. Runs in CPU 1
void setup() {
    Serial.begin(115200);
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Setup the Bluepad32 callbacks
    BP32.setup(&onConnectedController, &onDisconnectedController);

    // "forgetBluetoothKeys()" should be called when the user performs
    // a "device factory reset", or similar.
    // Calling "forgetBluetoothKeys" in setup() just as an example.
    // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
    // But it might also fix some connection / re-connection issues.
    BP32.forgetBluetoothKeys();

    // Enables mouse / touchpad support for gamepads that support them.
    // When enabled, controllers like DualSense and DualShock4 generate two connected devices:
    // - First one: the gamepad
    // - Second one, which is a "virtual device", is a mouse.
    // By default, it is disabled.
    BP32.enableVirtualDevice(false);
}

// Arduino loop function. Runs in CPU 1.
void loop() {
    // This call fetches all the controllers' data.
    // Call this function in your main loop.
    bool dataUpdated = BP32.update();
    //if (dataUpdated)
    processControllers();


    // The main loop must have some kind of "yield to lower priority task" event.
    // Otherwise, the watchdog will get triggered.
    // If your main loop doesn't have one, just add a simple `vTaskDelay(1)`.
    // Detailed info here:
    // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time

    //     vTaskDelay(1);
    delay(50);
}
