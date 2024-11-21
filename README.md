# IoT-ProjetoLampada

## Hardwares utilizados e instruções para reprodução:

Hardwares utilzados: 

1. NodeMCU (ESP8266): O NodeMCU ESP8266 foi a plataforma escolhida para este protótipo. Ele será a peça central do projeto. Por ser um microcontrolador com interface Wi-Fi, ele facilita a integração pelo protocolo MQTT.
2. Arduino UNO: Neste projeto, o Arduino terá o papel de acionar o relé, ligando/desligando a lâmpada. Utilizamos o Arduino pois o relé apenas aciona com uma corrente de 5v, e o NodeMCU tem apenas 3.3v.
3. Sensor de Presença PIR (Passive Infrared): O sensor será utilizado para detectar a presença de pessoas no ambiente e acionar o sistema.
4. Módulo Relé: O relé será utilizado para controlar a ligação e desligamento da lâmpada, funcionando como um interruptor eletrônico que será acionado pelo microcontrolador.
5. Fonte de Alimentação (5V/9V): Necessário para alimentar o microcontrolador e o módulo relé.
6. Lâmpada e Soquete: Será necessário uma lâmpada de LED e seu soquete, que será controlado ligado e desligado pelo Relé
7. Protoboard e Jumpers: Utilizados para montar o circuito e interligar os componentes de forma prática e segura.

Instruções e métodos:

- Conexão do Sensor PIR: Conectar o sensor PIR ao NodeMCU, ligando os pinos de alimentação e saída de dados ao microcontrolador.
- Conexão do Módulo Relé: O relé será controlado pelo NodeMCU para ligar e desligar a lâmpada. Isso envolve conectar o relé de forma que ele funcione como um interruptor para a lâmpada.
- Conexões de Alimentação: Garantir que o NodeMCU e o módulo relé estão sendo alimentados adequadamente com uma fonte de alimentação de 5V/9V.
- Servidor MQTT Local: Configurar um servidor MQTT: Mosquitto MQTT Broker em um PC local.
