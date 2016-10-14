/*
 * Código por: Felipe Proença Arantes Vieira 
 *           lipe4601w@gmailcom
 *     Instituto Federal de São Paulo (IFSP)
 *           Campus Itapetininga - 2016
 *          Trabalho de conclusão de curso
 *    MSI (Manutenção e Suporte em Informática)
 *        Código do Controle para Kinect
 */
#include <RCSwitch.h> //inclusão da biblioteca
RCSwitch trans = RCSwitch(); //criação de objeto da classe
int pTrans = 2; //pino do transmissor de rádio
int azul = 4, verde = 7, amarelo = 8, vermelho = 12; //pinos nos leds
String valor = "";  //variavel que guardara a leitura da porta serial

void setup() {
  pinMode(azul, OUTPUT); //leds como saida
  pinMode(verde, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(vermelho, OUTPUT);
  
  digitalWrite(azul, LOW); //apaga todos os leds
  digitalWrite(verde, LOW);
  digitalWrite(amarelo, LOW);
  digitalWrite(vermelho, LOW);

  trans.enableTransmit(pTrans); //habilita a transmissão no pino da variavel pTrans
  Serial.begin(9600); //inicia a porta serial
  delay(100); //espera 100 milisegundos
}

void loop() {
  valor = Serial.read(); //le a porta serial
  if(valor == "103"){ //Utiliza-se a tabela ASCII para a comparação
    //se o valor lido for igual a 103, o robô irá para frente
    digitalWrite(azul, HIGH);//acende apenas o led azul e apaga os demais
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, LOW);
    Enviar(1); //envia o número 1 por rádio
    delay(100); // esperá-se 100 milisegundos
    //o restante do código funciona da mesma maneira
  }else if(valor == "104"){ //Voltar
    digitalWrite(azul, LOW);
    digitalWrite(verde, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, LOW);
    Enviar(2);
    delay(100);
  }else if(valor == "105"){ //Esquerda
    digitalWrite(azul, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, HIGH);
    digitalWrite(vermelho, LOW);
    Enviar(3);
    delay(100);
  }else if(valor == "106"){ //Direita
    digitalWrite(azul, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, HIGH);
    Enviar(4);
    delay(100);
  }else{
    digitalWrite(azul, LOW);
    digitalWrite(verde, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, LOW);
  }
}

void Enviar(int h){ //método para enviar o sinal
 trans.send(h, 24); //transmite um número inteiro codificado em Decimal
}
