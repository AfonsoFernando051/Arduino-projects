#define LED_VERMELHO 2
#define BOTAO_PISCA 10
#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

void setup() {
  Serial.begin(9600);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BOTAO_PISCA, INPUT_PULLUP);
}

void loop() {
  boolean estadoBotao = !digitalRead(BOTAO_PISCA);
  if(estadoBotao){
    piscaLed(LED_VERMELHO);
  }
  Serial.println(estadoBotao);
}

void piscaLed(int led){
  digitalWrite(led, HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(led, LOW);
  delay(MEIO_SEGUNDO);
}