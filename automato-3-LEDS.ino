//INICIAL --> TRANSICAO --> ACEITACAO
//   ^                          |
//   |--------------------------|

//Constantes que definem: a porta do LED, o botão de entrada do usuário, 1 segundo e meio segundo, respectivamente.
#define LED_VERMELHO_1 3
#define LED_VERDE 5
#define LED_VERMELHO_2 7

#define BOTAO_PISCA 10
#define DOIS_SEGUNDOS 2000
#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

// Definindo os estados do autômato
enum Estado { INICIAL, TRANSICAO, ACEITACAO };
Estado estadoAtual = INICIAL;
unsigned long ultimoTempo = 0;  // Armazena o tempo da última atualização
boolean estadoLed = LOW;        // Estado atual dos LEDs

//Método inicial que roda uma vez
void setup() {
  Serial.begin(9600);
  configurarPortas();
}

//Método que configura as portas de entrada e saída do arduino
void configurarPortas() {
  pinMode(LED_VERMELHO_1, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO_2, OUTPUT);
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
        Serial.println("Transição para o estado TRANSICAO");
       // delay(DOIS_SEGUNDOS);
        acendeLed(LED_VERMELHO_1);
        estadoAtual = TRANSICAO;
      }
      break;

    case TRANSICAO:
      if (botaoPressionado) {
        delay(DOIS_SEGUNDOS);
        Serial.println("Transição para o estado ACEITACAO");
        acendeLed(LED_VERDE);
        estadoAtual = ACEITACAO;
      }else{
       estadoAtual = INICIAL;
       apagarLed(LED_VERDE);
      }
      break;

    case ACEITACAO:
      if (botaoPressionado) {
        delay(DOIS_SEGUNDOS);
        Serial.println("Transição para o estado INICIAL");
        acendeLed(LED_VERMELHO_2);

        while(digitalRead(BOTAO_PISCA) == LOW){
          piscaTodosLeds();
        }
        estadoAtual = INICIAL;
      }else{
       estadoAtual = INICIAL;
       apagarLed(LED_VERMELHO_1);
       apagarLed(LED_VERDE);
       apagarLed(LED_VERMELHO_2);
      }
      break;
  }

  // Representação visual no Serial Monitor
  Serial.print("Estado atual: ");
  if (estadoAtual == INICIAL || !botaoPressionado) {
    Serial.println("INICIAL");
    apagarLed(LED_VERDE);
    apagarLed(LED_VERMELHO_2);
    piscaLed(LED_VERMELHO_1);
  }
  else if (estadoAtual == TRANSICAO){
    Serial.println("TRANSICAO");
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
    digitalWrite(LED_VERDE, estadoLed);
    digitalWrite(LED_VERMELHO_2, estadoLed);
  }
}

//Método que faz todos o led apagarem
void apagarTodosLeds(){
  Serial.println("Apagar todos os leds");
  apagarLed(LED_VERMELHO_1);
  apagarLed(LED_VERDE);
  apagarLed(LED_VERMELHO_2);
}