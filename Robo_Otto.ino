/**
 * @file Meu_Robo_Otto.ino
 * Modificado por: Saulo Aislan
 * Baseado no código exemplo - Otto avoid obstacles with ultrasonic sensor
 * Otto DIY - https://www.ottodiy.com/
 * @brief Firmware para detectar obstáculos e fazer o robô desviar.
 * @version 0.1
 * 
 * @copyright Copyright (c) 2022
 * 
*/

#include <Otto.h> // Disponível em: https://github.com/OttoDIY/OttoDIYLib
Otto Otto;

#define PernaEsq 2 
#define PernaDir 3
#define PeEsq 4 
#define PeDir 5 
#define Buzzer  13 
#define Trigger 8 // Pino trigger do sensor utrassonico
#define Echo 9 // Pino echo do sensor utrassonico

/**
 * @brief Emite um onda ultrassônico para medir a distância
 * @return long distância
 */
long ultrasound()
{
   long duration, distance;
   digitalWrite(Trigger,LOW);
   delayMicroseconds(2);
   digitalWrite(Trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(Trigger, LOW);
   duration = pulseIn(Echo, HIGH); // Duração do pulso(ms) do pino Echo.
   distance = duration/58; // Tempo em microssegundos dividido pelo dobro da distância que o som percorre por microssegundo(cm)
   return distance;
}

/**
 * @brief setup
 */
void setup() {
  Otto.init(PernaEsq, PernaDir, PeEsq, PeDir, true, Buzzer); // Inicializa os pinos dos servos e Buzzer
  pinMode(Trigger, OUTPUT); 
  pinMode(Echo, INPUT); 
  Otto.swing(2, 1000, 20); // Balançando de um lado para o outro
  Otto.shakeLeg (1,2000,-1); // Chacoalhar a perna direita
}

/**
 * @brief setup
 */
void loop()
{
    if (ultrasound() <= 15) // Se a distância for menor ou igual a 15cm
    {
      Otto.sing(S_surprise); // Emite um som de surpresa
      Otto.walk(2,1000,-1); // Volta dois passo
      Otto.turn(4,1000,1); // Faz uma curva pela esqueda em 3 passos
    }
    Otto.walk(1,1000,1); // Anda um passo para frente
}
