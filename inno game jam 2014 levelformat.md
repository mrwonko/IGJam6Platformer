# Jump & Run - Formate #

1 Level = 1 Ordner. Inhalt beschreibt alles.

x_y.png, x_y.collision.png, x_y.game.png und x_y.images.png beschreiben das Level
player.png und player.png.animations.txt beschreiben den Spieler und seine Animationen
exit.png (und ggf. exit.png.animations.txt) beschreibt den Ausgang

## *.png.animations.txt ##

Definition der Animationen eines Bilds. Wenn diese Datei existiert, wird *.png als Spritesheet interpretiert.

Format:

{Framebreite} {Framehöhe}
{Animation 1 Name} {Animation 1 Start} {Animation 1 Länge} {Animation 1 FPS}
...
{Animation N Name} {Animation N Start} {Animation N Länge} {Animation N FPS}

Standardmäßig wird die Animation "idle" abgespielt.

## x_y.png ##

Aussehen des Levels, in Stücke gleicher Größe (!!!) geteilt. Es muss ein Stück 0_0 geben!!!

Beispiel: 1_2.png ist Horizontal an Position 1 (rechts), Vertikal an Position 2 (unten)

Alle Kacheln müssen die gleiche Höhe und Breite haben!


## x_y.collision.png ##

Kollisionsbeschreibung, für jeden Pixel. Farbe bestimmt Zustand:

Weiß (255, 255, 255) = Luft, kann man durchlaufen
Schwarz (0, 0, 0) = Boden, Fest
Rot (255, 0, 0) = Tödlich

Für jedes x_y.png muss es ein x_y.collision.png geben.


## x_y.game.png ##

Spielrelevante Informationen, wie zu sammelnde Objekte und der Spielerstartpunkt, Bedeutung der Farben in game.txt definiert. Obere linke Ecke entsprechend anmalen.

### game.txt ###

Format:

{Rot} {Grün} {Blau} {Typ} {Parameter1} {Parameter2} ... {ParameterN}

Es gibt folgende Typen:

*	Player: Spielerstart (Oben Links)
*	Exit {Abstand Links} {Abstand Oben} {Breite} {Höhe}: Ausgang
*	Enemy {Abstand Links} {Abstand Oben} {Breite} {Höhe} {Dateiname (relativ zum Levelverzeichnis)} {Lauf-Verhalten} {Angriffs-Typ}: Gegner.
	Dabei gibt es folgende Lauf-Verhalten:
	*	0 Vorwärts laufen und umdrehen, wenn man gegen eine Wand stößt
	*	1 Wie 0, aber dreht auch um, wenn er sonst stürzen würde
	Und folgende Angriffstypen:
	*	0 Nahkampf: Berührung = Tod
*	Collectible {Abstand Links} {Abstand Oben} {Breite} {Höhe}: Gegenstand, von dem alle eingesammelt werden müssen, um das Level beenden zu können.

Die Abstand/Größe-Definition bezieht sich dabei auf die Kollisionserkennung, Abstand ist relativ zum oberen linken Pixel. Angaben in Pixeln.

## x_y.images.png ##

Position von (möglicherweise animierten) Bildern an festen Positionen. Oberen linken Pixel in Farbe gemäß images.txt anmalen.

### images.txt ###

Definition der statischen Bilder im Level:

Eine Zeile je Definition, Format:

{Rot} {Grün} {Blau} {Dateiname (relativ zum Levelverzeichnis)}

z.B.

0 255 0 test.png

= An grünen Pixeln wird das Bild test.png dargestellt. Wenn dieses animiert ist, so ist das in test.png.animations.txt beschrieben. Es wird die Animation "idle" abgespielt.


## gameplay.txt ##

Enthält Gameplay Informationen, im Format "Name Wert", Werte sind positive Zahlen. Es gibt folgende Namen (Groß-/Kleinschreibung egal):

* ScreenWidth: Breite des sichtbaren Ausschnitts in Pixeln
* PlayerHeight: Kollisions-Höhe des Spielers in Pixeln
* PlayerWidth: Kollisions-Breite des Spielers in Pixeln
* PlayerOffsetX: Abstand des Kollisionsrechtecks vom linken Rand des Bilds
* PlayerOffsetY: Abstand des Kollisionsrechtecks vom rechten Rand des Bilds
* JumpHeight: Sprunghöhe in Pixeln (???)
* StepHeight: Stufen dieser Höhe können ohne Sprung erklommen werden.
* Gravity: Erdanziehungskraft in Pixeln pro Quadratsekunde