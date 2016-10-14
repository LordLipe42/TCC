/*
 * Código por: Felipe Proença Arantes Vieira 
 *           lipe4601w@gmailcom
 *     Instituto Federal de São Paulo (IFSP)
 *           Campus Itapetininga - 2016
 *          Trabalho de conclusão de curso
 *    MSI (Manutenção e Suporte em Informática)
 *              Código do Controle de rádio
 */
#include <RCSwitch.h> //inclusão da biblioteca
int pTrans = 12;  //pino do transmissor
int led = 13; //led indicador (da própria placa)
int frente = 8, re = 7, e = 4, direita = 2; //pinos dos botões

RCSwitch trans = RCSwitch(); //objeto da classe

void setup() {
  Serial.begin(9600); //inicio da comunicação serial
  delay(100); //espera de 100 milisegundos

  pinMode(led,OUTPUT); // led como saida
  digitalWrite(led, LOW); //apaga o led

  pinMode(frente, INPUT); //botões como entrada
  pinMode(re, INPUT);
  pinMode(e, INPUT);
  pinMode(direita, INPUT);

  digitalWrite(frente, HIGH); //botões com valor lógico alto
  digitalWrite(re, HIGH);
  digitalWrite(direita, HIGH);
  digitalWrite(e, HIGH);
  
  trans.enableTransmit(pTrans); // habilita a transmissão
}

void loop() {
  if(digitalRead(frente) == 0 ){ //se o botão for pressionado
    Enviar(1); //envia o número que corresponde a ele por rádio
    Piscar(); //executa o método piscar
  }
  //o restante do código funciona de maneira identica
  else if(digitalRead(re) == 0 ){
    Enviar(2);
    Piscar();
  }
  else if(digitalRead(e) == 0 ){
    Enviar(3);
    Piscar();
  }
  else if(digitalRead(direita) == 0 ){
    Enviar(4);
    Piscar();
  }
  else {
    Enviar(5); //envia um valor 5, que fará o robô parar
  } 
}

void Enviar(int h){ //método enviar
 trans.send(h, 24); //transmite o numero inteiro codificado em Decimal
}

void Piscar(){  //método piscar
  digitalWrite(led, HIGH); //acende o led
  delay(250); //espera 250 milisegundos
  digitalWrite(led, LOW);  //apaga o led
}
