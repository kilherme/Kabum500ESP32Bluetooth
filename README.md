# Kabum Smart500 ESP32 Bluetooth->IR Gamepad V0.9
Projeto para Controlar Robo Aspirador Kabum Smart 500 / Liectroux-C30B / Liectroux-XR500 e talvez Ropo Glass 3 e ABIR X6 usando ESP32, transmissor Infravermelho e controle Bluetooth

Usa as bibliotecas pra Arduino BluePad32 e ESP32  
  
O Tutorial para conectar e configurar com controle pode ser encontrado em:  
https://github.com/ricardoquesada/bluepad32  
O Tutorial para Receber e Enviar via Infravermelho pode ser encontrado em:  
https://github.com/Arduino-IRremote/Arduino-IRremote

Material necessário:  
-ESP32, de preferência com suporte a bateria de lithium  
-Bateria de Lithium ou PowerBank  
-LED Infravermelho 38kHz com resistor ou Placa já pronta pra arduino  
-Controle Bluetooth  
-Cabos  
  
LED Infravermelho conectado ao pino 4 do ESP32 mas isso pode ser mudado alterando o PinDefinitionsAndMore.h  

ESP32 não salva o controle, toda vez é necessário colocar no modo de pareamento.  

Receptor interno do aparelho fica na frente do aparelho, portando o led precisa ficar no para-choque e apontar pra baixo se possivel.  
  
Pode-se prender o ESP32+bateria+LED no Controle Bluetooth porém o módulo LED IR para Arduino é fraco, o módulo HX-53 possui resistor de 220 ohms em série com o led quando deveria ser 90ohms.
  
Precisa apertar o botão várias vezes para continuar o movimento, preciso alterar isso quando tiver tempo...  
  
Testado somente no Kabum Smart500
