
// Codigo da placa Ardiuno UNO
// Esse codigo tem o intuito de ser simples
// Ele apenas recebe o sinal do NodeMCU no pino 6 
// E ativa a lampada utilizando o pino 7

// Codigo da placa Ardiuno UNO
int lamp = 7; // Porta onde o rele esta conectado
int activation = 6; // Porta onde recebe o sinal do NodeMCU
void setup() {
  Serial.begin(9600);
  pinMode(lamp, OUTPUT);
  pinMode(activation, INPUT);
}

void loop() {
  // Caso receba sinal
  // Ativa o rele
  int shouldActive = getActivation();
  if(shouldActive) {
    digitalWrite(lamp, HIGH);
  } else {
    digitalWrite(lamp, LOW);
  }
  
}

int getActivation() {
  int readMotion = digitalRead(activation);
  if (readMotion) {
    Serial.println("recebeu");
  } else {
    Serial.println("nao recebeu");
  }
  
  return readMotion;
}