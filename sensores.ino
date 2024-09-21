
//Nivel 3:
#define TRIG_PIN1 23
#define ECHO_PIN1 25
#define TRIG_PIN2 27
#define ECHO_PIN2 29
#define TRIG_PIN3 31
#define ECHO_PIN3 33
#define TRIG_PIN4 35
#define ECHO_PIN4 37
#define TRIG_PIN5 39
#define ECHO_PIN5 41

//Nivel 2:
#define TRIG_PIN6 43
#define ECHO_PIN6 45
#define TRIG_PIN7 47
#define ECHO_PIN7 49
#define TRIG_PIN8 51
#define ECHO_PIN8 53
#define TRIG_PIN9 22
#define ECHO_PIN9 24

//Nivel 1:
#define TRIG_PIN10 26
#define ECHO_PIN10 28
#define TRIG_PIN11 30
#define ECHO_PIN11 32
#define TRIG_PIN12 34
#define ECHO_PIN12 36

// Pines de salida para los contadores de cada nivel
#define SALIDA_NIVEL_3 38  // Pin para el nivel 3
#define SALIDA_NIVEL_2 40  // Pin para el nivel 2
#define SALIDA_NIVEL_1 42  // Pin para el nivel 1
#define SALIDA_TOTAL 12    // Pin para el total de espacios ocupados

#define RESET 13

// Variables para guardar los estados de ocupación anteriores
bool estado_espacio[12] = {false, false, false, false, false, false, false, false, false, false, false, false};


void setup() {
  Serial.begin(9600);

  // Configurar los pines de los sensores como salida y entrada
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(TRIG_PIN3, OUTPUT);
  pinMode(ECHO_PIN3, INPUT);
  pinMode(TRIG_PIN4, OUTPUT);
  pinMode(ECHO_PIN4, INPUT);
  pinMode(TRIG_PIN5, OUTPUT);
  pinMode(ECHO_PIN5, INPUT);
  pinMode(TRIG_PIN6, OUTPUT);
  pinMode(ECHO_PIN6, INPUT);
  pinMode(TRIG_PIN7, OUTPUT);
  pinMode(ECHO_PIN7, INPUT);
  pinMode(TRIG_PIN8, OUTPUT);
  pinMode(ECHO_PIN8, INPUT);
  pinMode(TRIG_PIN9, OUTPUT);
  pinMode(ECHO_PIN9, INPUT);
  pinMode(TRIG_PIN10, OUTPUT);
  pinMode(ECHO_PIN10, INPUT);
  pinMode(TRIG_PIN11, OUTPUT);
  pinMode(ECHO_PIN11, INPUT);
  pinMode(TRIG_PIN12, OUTPUT);
  pinMode(ECHO_PIN12, INPUT);
  // Configurar los pines de salida para los contadores como salida
  pinMode(SALIDA_NIVEL_3, OUTPUT);
  pinMode(SALIDA_NIVEL_2, OUTPUT);
  pinMode(SALIDA_NIVEL_1, OUTPUT);
  pinMode(SALIDA_TOTAL, OUTPUT);
  pinMode(RESET, OUTPUT);
}


void loop() {
  digitalWrite(RESET, LOW);
  delay(500);
  digitalWrite(RESET, HIGH);


  // Leer cada sensor y verificar si el espacio está ocupado
  verificarEspacio(1, TRIG_PIN1, ECHO_PIN1);
  verificarEspacio(2, TRIG_PIN2, ECHO_PIN2);
  verificarEspacio(3, TRIG_PIN3, ECHO_PIN3);
  verificarEspacio(4, TRIG_PIN4, ECHO_PIN4);
  verificarEspacio(5, TRIG_PIN5, ECHO_PIN5);
  //Nivel 2:
  verificarEspacio(6, TRIG_PIN6, ECHO_PIN6);
  verificarEspacio(7, TRIG_PIN7, ECHO_PIN7);
  verificarEspacio(8, TRIG_PIN8, ECHO_PIN8);
  verificarEspacio(9, TRIG_PIN9, ECHO_PIN9);
  //Nivel 1:
  verificarEspacio(10, TRIG_PIN10, ECHO_PIN10);
  verificarEspacio(11, TRIG_PIN11, ECHO_PIN11);
  verificarEspacio(12, TRIG_PIN12, ECHO_PIN12);
  
  // Mostrar el estado de cada estacionamiento
  Serial.println("Estado de los estacionamientos:");
  for (int i = 0; i < 5; i++) {
    Serial.print("Estacionamiento ");
    Serial.print(i + 1);
    if (estado_espacio[i]) {
      Serial.println(": Ocupado");
      digitalWrite(SALIDA_TOTAL, HIGH);
      digitalWrite(SALIDA_NIVEL_3, HIGH);
      delay(500);
      digitalWrite(SALIDA_TOTAL, LOW);
      digitalWrite(SALIDA_NIVEL_3, LOW);
    } else {
      Serial.println(": Vacío");
    }
  }

  for (int i = 5; i < 9; i++) {
    Serial.print("Estacionamiento ");
    Serial.print(i + 1);
    if (estado_espacio[i]) {
      Serial.println(": Ocupado");
      digitalWrite(SALIDA_TOTAL, HIGH);
      digitalWrite(SALIDA_NIVEL_2, HIGH);
      delay(500);
      digitalWrite(SALIDA_TOTAL, LOW);
      digitalWrite(SALIDA_NIVEL_2, LOW);
    } else {
      Serial.println(": Vacío");
    }
  }

  for (int i = 9; i < 12; i++) {
    Serial.print("Estacionamiento ");
    Serial.print(i + 1);
    if (estado_espacio[i]) {
      Serial.println(": Ocupado");
      digitalWrite(SALIDA_TOTAL, HIGH);
      digitalWrite(SALIDA_NIVEL_1, HIGH);
      delay(500);
      digitalWrite(SALIDA_TOTAL, LOW);
      digitalWrite(SALIDA_NIVEL_1, LOW);
    } else {
      Serial.println(": Vacío");
    }
  }
  
  Serial.println("-------------------------------");
  delay(5000); // Esperar 15 segundo antes de la siguiente lectura
}

void verificarEspacio(int numero_espacio, int trigPin, int echoPin) {
  long duracion, distancia;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duracion = pulseIn(echoPin, HIGH);
  distancia = (duracion / 2) / 29.1;  // Convertir duración a distancia en cm

  // Verificar si el espacio está ocupado (por ejemplo, si la distancia es menor a 20 cm)
  bool ocupado = (distancia < 3);

  // Actualizar el estado del espacio
  estado_espacio[numero_espacio - 1] = ocupado;
}