/*
 * Código por: Felipe Proença Arantes Vieira 
 *           lipe4601w@gmailcom
 *     Instituto Federal de São Paulo (IFSP)
 *           Campus Itapetininga - 2016
 *          Trabalho de conclusão de curso
 *    MSI (Manutenção e Suporte em Informática)
 *              Código do Robô
 */
#include <RCSwitch.h>
//Inclusão da biblioteca para recepção de sinal de rádio
#include <Ultrasonic.h>
//Inclusão da biblioteca para o sensor ultra sonico

RCSwitch rec = RCSwitch();
//criação de um objeto da classe RCSwitch com o nome rec

int echo = 43, trigger = 42;
//variaveis para  os pinos do sensor ultrasonico

Ultrasonic ultrasonic(trigger, echo);
//cria um objeto do sensor e usa as variaveis como argumento

int pot = 0, valor = 0, verde = 5, amarelo = 3, azul = 4, LEDcolisao = 7;
//Potenciometro, valor de leitura do potenciometro, leds

int buz = 53, recebido = 0;
//buzzer, valor recebido do receptor 

int in1 = 28, in2 = 29, in3 = 26, in4 = 27;
//variaveis dos motores

int frente = 32, re = 33, esquerda = 34, direita = 35, go = 36, esquecer = 37;
//Botões de direção

String cmd = "";
//String para armazenar os comandos vindo dos botões

void setup() {
  rec.enableReceive(0);
  //habilita a recepção de sinal pelo RF receptor
  
  pinMode(pot, INPUT); // Potenciometro como entrada
  pinMode(verde, OUTPUT); // Led verde como saida
  pinMode(amarelo, OUTPUT); // Led Amarelo como saida
  pinMode(azul, OUTPUT); // Led azul como saida
  pinMode(buz, OUTPUT); // buzzer como saida
  pinMode(LEDcolisao, OUTPUT); //Led que mostra se o sensor detectou algo
  
  pinMode(frente, INPUT); // botão frente como entrada
  pinMode(re, INPUT);    // botão re(voltar) como entrada
  pinMode(esquerda, INPUT); // botão esquerda como entrada
  pinMode(direita, INPUT); // botão direita como entrada
  pinMode(go, INPUT);      // botão go(ir) como entrada
  pinMode(esquecer, INPUT); // botão esquecer como entrada
  
  pinMode(in1, OUTPUT); // motor 1-A como saida
  pinMode(in2, OUTPUT); // motor 1-B como saida
  pinMode(in3, OUTPUT); // motor 2-A como saida
  pinMode(in4, OUTPUT); // motor 2-B como saida
  
  digitalWrite(verde, LOW); //Escreve no led verde valor lógico baixo
  digitalWrite(amarelo, LOW); //Escreve no led amarelo valor lógico baixo
  digitalWrite(azul, LOW); //Escreve no led azul valor lógico baixo
  digitalWrite(buz, LOW); //Escreve no buzzer o valor lógico baixo
  digitalWrite(LEDcolisao, LOW); //Led do sensor ultrassonico desligado

  digitalWrite(in1, LOW); //Inicia o motor como desligado
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  digitalWrite(frente, HIGH); //Escreve valor alto no botão frente
  digitalWrite(re, HIGH);     //Escreve valor alto no botão re
  digitalWrite(esquerda, HIGH); //Escreve valor alto no botão esquerda
  digitalWrite(direita, HIGH); //Escreve valor alto no botão direita
  digitalWrite(go, HIGH);     //Escreve valor alto no botão ir(go)
  digitalWrite(esquecer, HIGH); //Escreve valor alto no botão esquecer
  
  Serial.begin(9600); //Inicia a comunicação serial
  delay(100); //espera 1/10 de segundo (100 millisigundos)
}

void loop() {
  valor = analogRead(pot); //inicia a leitura do potenciometro
  if(valor <= 250){ //Se o valor lido pelo potenciometro for menor que 250...
    digitalWrite(verde, HIGH); //ligue o led verde
    digitalWrite(amarelo, LOW); //Desligue o led amarelo
    if(rec.available()){//se tiver algum sinal de rádio disponivel
      digitalWrite(azul, HIGH); //acende o led azul
      recebido = rec.getReceivedValue(); //pega o valor recebido do sinal
      if(recebido == 1){//se o valor que foi recebido é igual a 1
        ir(); //Inicia o método de andar para frente
        BuscarSinal(); //atualiza a disponibilidade do sinal
      }else if (recebido == 2){//se o valor recebido for igual a 2
        voltar();   //Iniciar o método para andar para tras
        delay(500); //espera meio segundo
        BuscarSinal();//atualiza a disponibilidade do sinal
      }else if (recebido == 3){//se o valor recebido for igual a 3
        giro();  //girar o robô para esquerda
        delay(250); //espera 1/4 de segundo
        parar(); //Parar o robô
        recebido = 84; //número falso para impedir o robô de andar
        BuscarSinal(); //atualiza a disponibilidade do sinal
      }else if (recebido == 4){//se o valor recebido for igual a 4
        giro2();  //girar o robô para a direita
        delay(250); //espera 1/4 desegundo
        parar(); //Parar o robô
        recebido = 84; //número falso para impedir o robô de andar
        BuscarSinal(); //atualiza a disponibilidade do sinal
      }else{//Se não...
        parar(); //Parar o robô
        delay(250); //espera 1/4 desegundo
        BuscarSinal(); //atualiza a disponibilidade do sinal
      }
    }else{// se não tiver nenhum sinal disponível
      digitalWrite(azul, LOW); //apaga o led azul
      recebido = 5;  //o valor recebido recebe o valor 5, o que fará o robô parar
      parar(); //Parar o robô
    }
  }else{                          //Se o valor do potênciometro não for menor ou igual a 250
    digitalWrite(verde, LOW);     //Apaga o led verde
    digitalWrite(amarelo, HIGH);  //Acende o Led amarelo
    
    if(digitalRead(frente) == 0){ //Se o notão para ir para frente for pressionado
      cmd += "A";                 //a letra A será adicionada à string
      delay(500);                 //Espera meio segundo
      Sinal();                    //Executa o método de sinal
      Serial.println(cmd);        //Escreve na porta serial o valor da string para acompanhamento do funcionamento
    }
    if(digitalRead(re) == 0){     //se o botão re for precionado
      cmd += "B";                 //a letra B é adicionada à String de comandos
      delay(500);                 //Esperar meio segundo
      Sinal();                    //Executar o sinal
      Serial.println(cmd);        //Escreve a string na porta serial
    }
    if(digitalRead(esquerda) == 0){ //se o botão da esquerda for pressionado
      cmd += "C";                  //a letra C é adicionada à String
      delay(500);                  //esperar meio segundo
      Sinal();                     //executar o sinal
      Serial.println(cmd);         //escrever a string na porta serial
    }
    if(digitalRead(direita) == 0){ //Se o botão da direita for presionado
      cmd += "D";                 // a letra D é adicionado à String
      delay(500);                 //espera meio segundo
      Sinal();                    //Executa o sinal
      Serial.println(cmd);        //escreve na porta serial
    }
    if(digitalRead(esquecer) == 0){ //se o botão esquecer for pressionado
      cmd = "";                     //A string de comandos é igual a vazia, não armazena comandos
      delay(500);                   //espera meio segundo
      Sinal();                      //executa um sinal duplo
      Sinal();
      Serial.println(cmd);          //escreve na porta serial o valor da string
    }
    if(digitalRead(go) == 0){ //se o botão ir for pressionado
      delay(500);             //espera meio segundo
      Sinal();                //executa um sinal
      int tam = cmd.length(), g; //tamanho = a quantidade de comandos na string, g = variavel para auxiliar o FOR
      Serial.println(tam);       //escreve o tamanho da string na porta serial para acompanhamento
      for(g =0; g < tam; g++){   //Começa um laço for do 0 até a quantidade de comandos pressionados
        if(cmd[g] == 'A'){       //se o comando atual for igual a A
          ir();                  //o robô deve anda
		  ir();					 //cada vez que o método é chamado o robô anda meio segundo
        }else if(cmd[g] == 'B'){ //se o comando na string for igual a B
          voltar();              //o robô volta para tras
          delay(1000);           //espera um segundo
          parar();               //para o robô
          delay(500);            //espera meio segundo
        }else if(cmd[g] == 'C'){ //se o comando na string for igual a C
          giro();             //gira o robo para a esquerda
          delay(250);         //espera 250 millisegundos
          parar();            //para o robô
          delay(500);         //espera meio segundo
        }else{                //se não...
         giro2();             //girar para a direita
         delay(250);          //espera 250 millisegundos
         parar();             //para o robô
         delay(500);  
        }
      }
      Sinal(); //sinal duplo
      Sinal();
      delay(500); //espera meio segundo
    }
  }//Aqui vai o código do próximo modo de funcionamento do robô
}

void Sinal(){ //método sinal
  digitalWrite(azul, HIGH); //acende o led azul
  delay(100); //espera 100 milisegundos
  tone(buz, 300, 200);    //o buzzer libera um som de na frequencia de 300mhz por 200 milisegundos
  digitalWrite(azul, LOW); //apaga o led azul
}

void ir(){ 								//Método ir
    int u = 0; 					 		//variavel para medir os ciclos do laço
    while(u < 20){ 				 		//enquanto o laço não der 20 voltas
      if(medir() <= 30){		 		//se a medida do sensor for menor ou igual a 30 centimetros
        digitalWrite(LEDcolisao, HIGH); //acende o led de colisão
        parar(); 						//para o robô
        delay(100); 					//espera 100 millisegundos
        digitalWrite(LEDcolisao, LOW);  //apaga o led de colisão
        break; 							//quebra o laço de repetição
      }
      digitalWrite(in1, HIGH); 			//Faz o robô ir para frente
      digitalWrite(in4, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      delay(25); 						//espra 25 millisegundos
      parar(); 							//para o robô
      u++; 								//incrementa 1 no laço
    }
}

void parar(){ //método parar
  digitalWrite(in1, LOW); //Faz o robô parar
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void voltar(){ //método voltar
  digitalWrite(in1, LOW); //faz o robô ir para tras
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void giro(){ //método de giro 1
  digitalWrite(in1, LOW); //gira o robô para a esquerda
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void giro2(){ //método de giro 2
  digitalWrite(in1, HIGH);  //gira o robô para a direita
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

float medir (){ // método de medida do sensor
 float dis; // distancia
 long micro = ultrasonic.timing(); //microsegundos
 dis = ultrasonic.convert(micro, Ultrasonic::CM); //distância = a conversão de microsegundos para CM
 return dis; //devolve o valor da medida
}
void BuscarSinal(){
  rec.resetAvailable(); //fará que o robô procure novamente um sinal disponível
}
