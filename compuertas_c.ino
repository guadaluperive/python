// Definición de pines para los LEDs de los semáforos
const int verde1 = 15;  // LED verde del semáforo 1
const int amarillo1 = 14;  // LED amarillo del semáforo 1
const int rojo1 = 13;  // LED rojo del semáforo 1

const int verde2 = 12;  // LED verde del semáforo 2
const int amarillo2 = 11;  // LED amarillo del semáforo 2
const int rojo2 = 10;  // LED rojo del semáforo 2

// Definición de pines para los botones
const int botonIniciar = 19;  // Botón que inicia el ciclo del semáforo (A5)
const int botonDetener = 20;  // Botón que detiene el ciclo del semáforo (A4)

// Variables para controlar el estado de los botones
int estadoBotonIniciar = 0;
int estadoBotonDetener = 0;
bool semaforoActivo = false; // Variable para saber si el semáforo está activo
bool detenido = false;       // Variable para saber si está detenido

// Temporización para los semáforos
unsigned long tiempoCambio = 0;
unsigned long intervalo = 2000; // 2 segundos para cada color

int estadoSemaforo = 0;

void setup() {
  // Configuración de los pines de los LEDs como salida
  pinMode(verde1, OUTPUT);
  pinMode(amarillo1, OUTPUT);
  pinMode(rojo1, OUTPUT);

  pinMode(verde2, OUTPUT);
  pinMode(amarillo2, OUTPUT);
  pinMode(rojo2, OUTPUT);

  // Configuración de los pines de los botones como entrada
  pinMode(botonIniciar, INPUT);
  pinMode(botonDetener, INPUT);

  // Inicializar el semáforo apagado
  apagarSemaforos();
}

void loop() {
  // Lectura de los botones
  estadoBotonIniciar = digitalRead(botonIniciar);
  estadoBotonDetener = digitalRead(botonDetener);

  // Si se presiona el botón de iniciar, activar el ciclo del semáforo
  if (estadoBotonIniciar == HIGH && !semaforoActivo) {
    semaforoActivo = true;
    detenido = false;
    tiempoCambio = millis();  // Guardar el tiempo actual
  }

  // Si se presiona el botón de detener, desactivar el ciclo del semáforo
  if (estadoBotonDetener == HIGH && semaforoActivo) {
    detenido = true;
    semaforoActivo = false;
  }

  // Si el semáforo está activo y no está detenido, cambiar los estados
  if (semaforoActivo && !detenido) {
    // Cambiar el estado del semáforo según el tiempo transcurrido
    if (millis() - tiempoCambio >= intervalo) {
      estadoSemaforo++;
      if (estadoSemaforo > 2) {
        estadoSemaforo = 0; // Reiniciar ciclo
      }
      actualizarSemaforos();
      tiempoCambio = millis();  // Reiniciar el tiempo para el siguiente cambio
    }
  }
}

void actualizarSemaforos() {
  switch (estadoSemaforo) {
    case 0: // Verde
      digitalWrite(verde1, HIGH);
      digitalWrite(amarillo1, LOW);
      digitalWrite(rojo1, LOW);

      digitalWrite(verde2, HIGH);
      digitalWrite(amarillo2, LOW);
      digitalWrite(rojo2, LOW);
      break;
    case 1: // Amarillo
      digitalWrite(verde1, LOW);
      digitalWrite(amarillo1, HIGH);
      digitalWrite(rojo1, LOW);

      digitalWrite(verde2, LOW);
      digitalWrite(amarillo2, HIGH);
      digitalWrite(rojo2, LOW);
      break;
    case 2: // Rojo
      digitalWrite(verde1, LOW);
      digitalWrite(amarillo1, LOW);
      digitalWrite(rojo1, HIGH);

      digitalWrite(verde2, LOW);
      digitalWrite(amarillo2, LOW);
      digitalWrite(rojo2, HIGH);
      break;
  }
}

void apagarSemaforos() {
  // Apagar ambos semáforos
  digitalWrite(verde1, LOW);
  digitalWrite(amarillo1, LOW);
  digitalWrite(rojo1, LOW);

  digitalWrite(verde2, LOW);
  digitalWrite(amarillo2, LOW);
  digitalWrite(rojo2, LOW);
}