//INICIAL --> TRANSICAO --> ACEITACAO
//   ^                          |
//   |--------------------------|

#include <LiquidCrystal.h>
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Constantes que definem: a porta do LED, o botão de entrada do usuário, 1 segundo e meio segundo, respectivamente.
#define LED_VERMELHO_1 13
#define LED_VERDE_1 12
#define LED_VERMELHO_2 11
#define LED_VERDE_2 10
#define LED_VERMELHO_3 9

#define BOTAO_PISCA 8
#define DOIS_SEGUNDOS 2000
#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

// Definindo os estados do autômato
enum Estado { INICIAL, TRANSICAO_1, TRANSICAO_2, TRANSICAO_3, ACEITACAO };
Estado estadoAtual = INICIAL;
unsigned long ultimoTempo = 0;  // Armazena o tempo da última atualização
boolean estadoLed = LOW;        // Estado atual dos LEDs

//Método inicial que roda uma vez
void setup() {
  Serial.begin(9600);
  configurarPortas();
  configurarDisplay();
}

//Método que configura o display do arduino
void configurarDisplay() {
 lcd.begin(16, 2); // Aqui informo que são 16 caracteres e 2 linhas
 lcd.setCursor(0, 0); // To colocando para exibir a frase na coluna 0 e linha 0 (opcional)
 lcd.print("Arduino"); // Escrevo "Arduino"
 lcd.setCursor(0, 1); // E agora to colocando para exibir a frase na coluna 0 e linha 1
 lcd.print("Display LCD"); // E escrevo "Display LCD"
}

//Método que configura as portas de entrada e saída do arduino
void configurarPortas() {
  pinMode(LED_VERMELHO_1, OUTPUT);
  pinMode(LED_VERDE_1, OUTPUT);
  pinMode(LED_VERMELHO_2, OUTPUT);
  pinMode(LED_VERDE_2, OUTPUT);
  pinMode(LED_VERMELHO_3, OUTPUT);

  pinMode(BOTAO_PISCA, INPUT_PULLUP);
}

//Método que roda sempre em loop
void loop() {
  //Leitura do botão, se está pressionado
  boolean botaoPressionado = !digitalRead(BOTAO_PISCA);

  // Transições do autômato
  switch (estadoAtual) {
    case INICIAL:
      if (botaoPressionado) {
       // apagarLed(LED_VERMELHO_1);
        Serial.println("Transição para o estado TRANSICAO_1");
        delay(MEIO_SEGUNDO);
        acendeLed(LED_VERMELHO_1);
        estadoAtual = TRANSICAO_1;
      }
      break;

    case TRANSICAO_1:
      if (botaoPressionado) {
        delay(MEIO_SEGUNDO);
        Serial.println("Transição para o estado TRANSICAO_2");
        lcd.clear();
        lcd.print("TRANSICAO_1");
        acendeLed(LED_VERDE_1);
        estadoAtual = TRANSICAO_2;
      }else{
       estadoAtual = INICIAL;
       apagarTodosLeds();
      }
      break;

    case TRANSICAO_2:
      if (botaoPressionado) {
        delay(MEIO_SEGUNDO);
        Serial.println("Transição para o estado TRANSICAO_3");
        acendeLed(LED_VERMELHO_2);
        lcd.clear();
        lcd.print("TRANSICAO_2");
        estadoAtual = TRANSICAO_3;
      }else{
       estadoAtual = INICIAL;
       apagarTodosLeds();
      }
      break;

    case TRANSICAO_3:
      if (botaoPressionado) {
        delay(MEIO_SEGUNDO);
        Serial.println("Transição para o estado ACEITACAO");
        acendeLed(LED_VERDE_2);
        lcd.clear();
        lcd.print("TRANSICAO_3");
        estadoAtual = ACEITACAO;
      }else{
       estadoAtual = INICIAL;
       apagarTodosLeds();
      }
      break;

    case ACEITACAO:
      if (botaoPressionado) {
        delay(MEIO_SEGUNDO);
        acendeLed(LED_VERMELHO_3);
        lcd.clear();
        lcd.print("ACEITACAO");
        while(digitalRead(BOTAO_PISCA) == LOW){
          piscaTodosLeds();
        }

        Serial.println("Transição para o estado INICIAL");
        estadoAtual = INICIAL;
      }else{
       estadoAtual = INICIAL;
       apagarTodosLeds();
      }
      break;
  }

  // Representação visual no Serial Monitor
  Serial.print("Estado atual: ");
  if (estadoAtual == INICIAL || !botaoPressionado) {
    Serial.println("INICIAL");
    apagarTodosLeds();
    piscaLed(LED_VERMELHO_1);
    lcd.clear();
    lcd.print("INICIAL");
  }
  else if (estadoAtual == TRANSICAO_1){
    Serial.println("TRANSICAO_1");
  } 
  else if (estadoAtual == TRANSICAO_2){
    Serial.println("TRANSICAO_2");
  } 
  else if (estadoAtual == TRANSICAO_3){
    Serial.println("TRANSICAO_3");
  } 
  else if (estadoAtual == ACEITACAO) {
    Serial.println("ACEITACAO");
  }

  delay(100); // Pequeno delay para evitar leitura múltipla do botão
}

//Método que faz o led acender
void acendeLed(int led){
  digitalWrite(led, HIGH);
}

//Método que faz o led apagar
void apagarLed(int led){
  digitalWrite(led, LOW);
}

//Método que faz o led piscar
void piscaLed(int led){
  digitalWrite(led, HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(led, LOW);
  delay(MEIO_SEGUNDO);
}

//Método que faz todos o led piscarem
void piscaTodosLeds(){
  Serial.println("Piscar todos os leds");

  unsigned long tempoAtual = millis();

  // Verifica se passou o tempo suficiente para alternar o estado dos LEDs
 if ((millis() - ultimoTempo) >= UM_SEGUNDO) {

    ultimoTempo = tempoAtual;  // Atualiza o tempo
    estadoLed = !estadoLed;    // Alterna o estado

    // Define o estado de todos os LEDs
    digitalWrite(LED_VERMELHO_1, estadoLed);
    digitalWrite(LED_VERDE_1, estadoLed);
    digitalWrite(LED_VERMELHO_2, estadoLed);
    digitalWrite(LED_VERDE_2, estadoLed);
    digitalWrite(LED_VERMELHO_3, estadoLed);
  }
}

//Método que faz todos o led apagarem
void apagarTodosLeds(){
  Serial.println("Apagar todos os leds");
  apagarLed(LED_VERMELHO_1);
  apagarLed(LED_VERDE_1);
  apagarLed(LED_VERMELHO_2);
  apagarLed(LED_VERDE_2);
  apagarLed(LED_VERMELHO_3);
}