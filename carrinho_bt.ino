#include <Servo.h>
#include <Dabble.h>

// Definição dos pinos
#define MOTOR_PWM 5   // Pino PWM para controlar a velocidade do motor DC
#define MOTOR_IN1 6   // Entrada 1 da ponte H
#define MOTOR_IN2 7   // Entrada 2 da ponte H
#define SERVO_PIN 9   // Pino do servo motor

Servo direcao; // Objeto do servo motor

void setup() {
    Serial.begin(9600);  // Inicializa a comunicação serial
    pinMode(MOTOR_PWM, OUTPUT);
    pinMode(MOTOR_IN1, OUTPUT);
    pinMode(MOTOR_IN2, OUTPUT);
    direcao.attach(SERVO_PIN);
    direcao.write(90); // Inicia o servo na posição central
    Dabble.begin(9600); // Inicializa a comunicação com o app Dabble
}

void loop() {
    Dabble.processInput(); // Processa os comandos recebidos

    if (GamePad.isTrianglePressed()) { // Frente (Botão Triângulo)
        digitalWrite(MOTOR_IN1, HIGH);
        digitalWrite(MOTOR_IN2, LOW);
        analogWrite(MOTOR_PWM, 150);
    } else if (GamePad.isCrossPressed()) { // Ré (Botão X)
        digitalWrite(MOTOR_IN1, LOW);
        digitalWrite(MOTOR_IN2, HIGH);
        analogWrite(MOTOR_PWM, 150);
    } else { // Parar
        digitalWrite(MOTOR_IN1, LOW);
        digitalWrite(MOTOR_IN2, LOW);
        analogWrite(MOTOR_PWM, 0);
    }

    if (GamePad.isLeftPressed()) { // Esquerda
        direcao.write(45);
    } else if (GamePad.isRightPressed()) { // Direita
        direcao.write(135);
    } else {
        direcao.write(90); // Retorna ao centro
    }
}
