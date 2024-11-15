# Arduino-projects

Projetos criados em C++ na IDE do arduino.
Projeto pisca-led -> Ao conectar um arduino com led corretamente configurado na porta 2, o mesmo pisca num intervalo de 0,5 segundos;

Projeto pisca0-led-btn -> Ao conectar um arduino com led corretamente configurado na porta 2, o mesmo pisca num intervalo de 0,5 segundos quando se aperta um botão(configurado na porta 10);

Projeto pisca0-led-btn -> Ao conectar um arduino com led corretamente configurado na porta 2, e ao apertar um botão(configurado na porta 10), o programa percorre um automato que lê 3 estados, o estado inicial, de aceitação e final, caso chegue no estado final, o led pisca.

INICIAL --> TRANSICAO --> ACEITACAO
   ^                          |
   |--------------------------|
