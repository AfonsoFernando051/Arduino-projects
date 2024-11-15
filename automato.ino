//INICIAL --> TRANSICAO --> ACEITACAO
//   ^                          |
//   |--------------------------|

//Constantes que definem: a porta do LED, o botão de entrada do usuário, 1 segundo e meio segundo, respectivamente.
#define LED_VERMELHO 2
#define BOTAO_PISCA 10
#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

// Definindo os estados do autômato
enum Estado { INICIAL, TRANSICAO, ACEITACAO };
Estado estadoAtual = INICIAL;

//Método inicial que roda uma vez
void setup() {
  Serial.begin(9600);
  configurarPortas();
}

//Método que configura as portas de entrada e saída do arduino
void configurarPortas() {
  pinMode(LED_VERMELHO, OUTPUT);
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
        estadoAtual = TRANSICAO;
        Serial.println("Transição para o estado TRANSICAO");
      }
      break;

    case TRANSICAO:
      if (botaoPressionado) {
        estadoAtual = ACEITACAO;
        Serial.println("Transição para o estado ACEITACAO");
      }
      break;

    case ACEITACAO:
      if (botaoPressionado) {
        estadoAtual = INICIAL;
        Serial.println("Transição para o estado INICIAL");
      }
      piscaLed(LED_VERMELHO);
      break;
  }

  // Representação visual no Serial Monitor
  Serial.print("Estado atual: ");
  if (estadoAtual == INICIAL) Serial.println("INICIAL");
  else if (estadoAtual == TRANSICAO) Serial.println("TRANSICAO");
  else if (estadoAtual == ACEITACAO) Serial.println("ACEITACAO");

  delay(100); // Pequeno delay para evitar leitura múltipla do botão
}

//Método que faz o led piscar
void piscaLed(int led){
  digitalWrite(led, HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(led, LOW);
  delay(MEIO_SEGUNDO);
}