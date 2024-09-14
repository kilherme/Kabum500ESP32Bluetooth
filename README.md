# Kabum500ESP32Bluetooth V0.9
Projeto para Controlar Robo Aspirador Kabum Smart 500 / Liectroux-C30B / Liectroux-XR500 e talvez Ropo Glass 3 e ABIR X6 usando ESP32, transmissor Infravermelho e controle Bluetooth

Usa as bibliotecas pra Arduino BluePad32 e ESP32  
  
O Tutorial para conectar e configurar com controle pode ser encontrado em:  
https://github.com/ricardoquesada/bluepad32  
O Tutorial para Receber e Enviar via Infravermelho pode ser encontrado em:  
https://github.com/Arduino-IRremote/Arduino-IRremote

Material necessário:  
-ESP32, de preferência com suporte a bateria de lithium  
-Bateria de Lithium ou PowerBank  
-LED com resistor ou Placa já pronta pra arduino  
-Controle Bluetooth  
  
ESP32 não salva o controle, toda vez é necessário colocar no modo de pareamento.  
Receptor interno do aparelho fica na frente do aparelho, portando o led precisa ficar no para-choque e apontar pra baixo se possivel.  
Pode-se prender o ESP32+bateria+LED no Controle Bluetooth porém o módulo LED IR para Arduino é fraco.
