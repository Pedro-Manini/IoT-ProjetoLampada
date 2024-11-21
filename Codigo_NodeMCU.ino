#include <elapsedMillis.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// #define topic_sub "MQTTDetectSend"
#define topic_pub   "MQTTDetectReceive"
#define ID_MQTT  "ProjIOTPIR"

elapsedMillis timer;
int lightInterval = 4000;

int lamp = D7; //Porta digital de comunicacao com o Arduino
int pir = D5; //Porta digital para receber sinal do Sensor
bool on = false;
int motion;
bool didSetup = false;

// WIFI
const char* SSID = "MotoEdge"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "thiago1234"; // Senha da rede WI-FI que deseja se conectar
  
// MQTT
const char* BROKER_MQTT = "192.168.213.230"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT

//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
char lampState = '0';  //variável que armazena o estado atual da saída
  

void setup() {
  Serial.begin(115200);
  pinMode(lamp, OUTPUT);
  pinMode(pir, INPUT);

  initWiFi();
  initMQTT();
  
  // WiFi.setOutputPower(19.25);
}

void initWiFi() 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
     
    reconectWiFi();
}

void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}

void loop() {
  VerificaConexoesWiFIEMQTT();
  EnviaEstadoOutputMQTT();
  MQTT.loop();
}

int getMotion() {
  int readMotion = digitalRead(pir);
  if(readMotion) {
    // Serial.println("Detectou");
    timer = 0;
  } else {
    // Serial.println("Nada detectado");
  }

  return readMotion;
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
   
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }

    Serial.println("Recebeu Mensagem - " + msg);
    Serial.println(msg);
   
    if (msg.equals("L"))
    {
       digitalWrite(lamp, HIGH);
        lampState = '1';
    }
 
    if (msg.equals("D"))
    {
        digitalWrite(lamp, LOW);
        lampState = '0';
    }
     
}

void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(topic_pub); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}

void reconectWiFi() 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED) {
      // Serial.println("Ja esta conectado");
      return;
    }
         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.println(".");
        Serial.println("Nao conectado ao WiFi");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

void VerificaConexoesWiFIEMQTT(void)
{

     reconectWiFi();
     
     if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o WiFI, a conexão é refeita
}

void EnviaEstadoOutputMQTT(void)
{

  motion = getMotion();

  // Mantem a luz ligada por 4 segundos antes de desligar
  if(on) {
    if(timer <= lightInterval) {
      return;
    } else {
      on = false;
    }
  }

  if(motion) {
    on = true;
    Serial.println("Detectou");
    //LIGA
    MQTT.publish(topic_pub, "L");
    Serial.println("Envia estado Ligado");
    return;
  } else {
    //DESLIGA
    Serial.println("Parou de detectar");
    MQTT.publish(topic_pub, "D");
    Serial.println("Envia estado Desligado");
  }
  Serial.println("- Estado da saida enviado ao broker!");
}

