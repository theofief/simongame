#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ledPins[4] = {5, 18, 19, 21};
int boutonPins[4] = {14, 27, 26, 25};  // bouton 4 = index 3 (pin 25)

const int BUZZER_PIN = 17;
const int MAX_NIVEAU = 100;
int seq[MAX_NIVEAU];
int niveau = 1;
int indexBouton = 0;
bool sequenceMontree = false;
bool partieCommencee = false;

int score = 0;
int highScore = 0;

void jouerSonErreur();
void jouerSonSucces();
void jouerSonVictoire();
void afficherMenu();
void startGame();
void montrerSequence();
void verifierRepetition();
void afficherDefaite();
void afficherVictoire();
void afficherVersion();
int boutonAppuye();
void allumerLED(int couleur);
void eteindreLED(int couleur);
void jouerSon(int couleur);

void setup() {
  Serial.begin(9600);
  EEPROM.begin(1);
  highScore = EEPROM.read(0);

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(boutonPins[i], INPUT_PULLDOWN);
  }

  pinMode(BUZZER_PIN, OUTPUT);
  Wire.begin(23, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Erreur d'écran OLED"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  afficherMenu();

  randomSeed(analogRead(0));
}

void loop() {
  if (!partieCommencee) {
    if (digitalRead(boutonPins[0])) {
      startGame();
    } else if (digitalRead(boutonPins[1])) {
      afficherVersion();
    } else if (digitalRead(boutonPins[3])) {
      highScore = 0;
      EEPROM.write(0, highScore);
      EEPROM.commit();
      afficherMenu();
    }
    return;
  }

  if (!sequenceMontree) {
    montrerSequence();
    sequenceMontree = true;
  } else {
    verifierRepetition();
  }
}

void afficherMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Menu Principal :");
  display.println("1: Lancer le jeu");
  display.println("2: Version");
  display.println("4: Reset le best");
  display.display();
}

void startGame() {
  niveau = 1;
  score = 0;
  indexBouton = 0;
  seq[0] = random(0, 4);
  sequenceMontree = false;
  partieCommencee = true;
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("C'est parti !");
  display.display();
  delay(1000);
}

void montrerSequence() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Niveau ");
  display.print(niveau);
  display.print(" | Score ");
  display.println(score);
  display.display();

  for (int i = 0; i < niveau; i++) {
    int couleur = seq[i];
    allumerLED(couleur);
    jouerSon(couleur);
    delay(500);
    eteindreLED(couleur);
    delay(300);
  }

  display.clearDisplay();
  display.setCursor(0, 40);
  display.println("A toi de jouer !");
  display.display();

  indexBouton = 0;
}

void verifierRepetition() {
  int couleur = boutonAppuye();
  if (couleur != -1) {
    allumerLED(couleur);
    jouerSon(couleur);
    delay(300);
    eteindreLED(couleur);

    if (couleur == seq[indexBouton]) {
      indexBouton++;
      if (indexBouton == niveau) {
        score++;
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Bravo !");
        display.display();
        jouerSonSucces();
        delay(1000);

        if (niveau < MAX_NIVEAU) {
          niveau++;
          seq[niveau - 1] = random(0, 4);
          sequenceMontree = false;
        } else {
          afficherVictoire();
        }
      }
    } else {
      jouerSonErreur();
      afficherDefaite();
    }

    delay(300);
  }
}

void afficherDefaite() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Erreur !");
  display.display();
  delay(2000);

  if (score > highScore) {
    highScore = score;
    EEPROM.write(0, highScore);
    EEPROM.commit();
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Score : ");
  display.println(score);
  display.print("High Score : ");
  display.println(highScore);
  display.setCursor(0, 40);
  display.println("1: Rejouer");
  display.println("4: Menu principal");
  display.display();

  while (true) {
    if (digitalRead(boutonPins[0])) {
      delay(20);
      while (digitalRead(boutonPins[0]));
      startGame();
      break;
    }
    if (digitalRead(boutonPins[3])) {
      delay(20);
      while (digitalRead(boutonPins[3]));
      partieCommencee = false;
      afficherMenu();
      break;
    }
  }
}

void afficherVictoire() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Gagne !");
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print("Score final : ");
  display.println(score);
  display.print("High Score : ");
  display.println(highScore);
  display.display();
  jouerSonVictoire();
  while (true);
}

void afficherVersion() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Version : 1.0");
  display.println("Développé par");
  display.println("Theo Fief");
  display.setCursor(0, 56);
  display.println("1: Menu principal");
  display.display();

  while (!digitalRead(boutonPins[0])) delay(10);
  while (digitalRead(boutonPins[0])) delay(10);
  afficherMenu();
}

int boutonAppuye() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(boutonPins[i])) {
      delay(20);
      while (digitalRead(boutonPins[i]));
      return i;
    }
  }
  return -1;
}

void allumerLED(int couleur) {
  digitalWrite(ledPins[couleur], HIGH);
}

void eteindreLED(int couleur) {
  digitalWrite(ledPins[couleur], LOW);
}

void jouerSon(int couleur) {
  int frequence[4] = {261, 329, 392, 523};  // Do, Mi, Sol, Do supérieur
  tone(BUZZER_PIN, frequence[couleur], 200);
}

void jouerSonErreur() {
  tone(BUZZER_PIN, 100, 500);  // Son grave pour l'erreur
  delay(500);
  noTone(BUZZER_PIN);
}

void jouerSonSucces() {
  tone(BUZZER_PIN, 880, 150);
  delay(150);
  tone(BUZZER_PIN, 988, 150);
  delay(150);
  noTone(BUZZER_PIN);
}

void jouerSonVictoire() {
  int melodie[] = {523, 659, 784, 1047};  // petite mélodie de victoire
  for (int i = 0; i < 4; i++) {
    tone(BUZZER_PIN, melodie[i], 200);
    delay(250);
  }
  noTone(BUZZER_PIN);
}