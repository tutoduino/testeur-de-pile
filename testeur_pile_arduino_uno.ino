// Mesure de la tension d'une pile à vide et en charge
// La mesure de la tension est faite sur l'entrée analogique A0
// Le contrôle de la mise en charge est faite via la sortie D7
//
// Lors de la lecture d'une valeur analogique, le convertisseur de l'Arduino
// retourne une valeur codée sur 10 bits, la  valeur maximale est donc
// de 1023 et elle correspond à la tension de référence (5V)

void setup() {
  // Initialisation de la communication série pour afficher les valeurs de la
  // tension mesurée sur le moniteur série
  Serial.begin(9600);
  Serial.println("Initialisation");

  // La référence par défaut est utilisée pour la mesure analogique.
  // Cette référence a une valeur de 5V sur la carte Arduino Uno
  analogReference(DEFAULT);

  // La PIN D7 est une sortie tout ou rien qui contrôle l'état du transistor
  // (bloqué ou saturé) afin de mesurer la tension de la pile à vide ou
  // lorsque elle génère un courant
  pinMode(7, OUTPUT);
}

void loop() {
  float tensionVide;
  float tensionCharge;

  // Lecture de la tension à vide de la pile
  // Bloque le transistor en positionnant la sortie D7 à LOW
  digitalWrite(7, LOW);
  delay(500);
  tensionVide = analogRead(A0)*5.0/1023;

  // Lecture de la tension en charge de la pile
  // Sature le transistor en positionnant la sortie D7 à HIGH
  digitalWrite(7, HIGH);
  delay(500);
  tensionCharge = analogRead(A0)*5.0/1023;

  Serial.print("Tension à vide = ");
  Serial.print(tensionVide);
  Serial.println("V");
  Serial.print("Tension en charge = ");
  Serial.print(tensionCharge);
  Serial.println("V");
  if (tensionCharge > 1.2) {
    Serial.println("Pile bonne");
  } else if (tensionCharge > 1.0) {
    Serial.println("Pile faible");
  } else {
    Serial.println("Pile à remplacer");
  }
}
