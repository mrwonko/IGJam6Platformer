# Jump & Run - Formate #

1 Level = 1 Ordner. Inhalt beschreibt alles.

x_y.png, x_y.collision.png, x_y.game.png und x_y.images.png beschreiben das Level
player.png und player.png.animations.txt beschreiben den Spieler und seine Animationen
exit.png (und ggf. exit.png.animations.txt) beschreibt den Ausgang

## *.png.animations.txt ##

Definition der Animationen eines Bilds. Wenn diese Datei existiert, wird *.png als Spritesheet interpretiert.

Format:

{Framebreite} {Frameh�he}
{Animation 1 Name} {Animation 1 Start} {Animation 1 L�nge} {Animation 1 FPS}
...
{Animation N Name} {Animation N Start} {Animation N L�nge} {Animation N FPS}

Standardm��ig wird die Animation "idle" abgespielt.

## x_y.png ##

Aussehen des Levels, in St�cke gleicher Gr��e (!!!) geteilt. Es muss ein St�ck 0_0 geben!!!

Beispiel: 1_2.png ist Horizontal an Position 1 (rechts), Vertikal an Position 2 (unten)

Alle Kacheln m�ssen die gleiche H�he und Breite haben!


## x_y.collision.png ##

Kollisionsbeschreibung, f�r jeden Pixel. Farbe bestimmt Zustand:

Wei� (255, 255, 255) = Luft, kann man durchlaufen
Schwarz (0, 0, 0) = Boden, Fest
Rot (255, 0, 0) = T�dlich

F�r jedes x_y.png muss es ein x_y.collision.png geben.


## x_y.game.png ##

Spielrelevante Informationen, wie zu sammelnde Objekte und der Spielerstartpunkt, Bedeutung der Farben in game.txt definiert. Obere linke Ecke entsprechend anmalen.

### game.txt ###

Format:

{Rot} {Gr�n} {Blau} {Typ} {Parameter1} {Parameter2} ... {ParameterN}

Es gibt folgende Typen:

*	Player: Spielerstart (Oben Links)
*	Exit {Abstand Links} {Abstand Oben} {Breite} {H�he}: Ausgang
*	Enemy {Abstand Links} {Abstand Oben} {Breite} {H�he} {Dateiname (relativ zum Levelverzeichnis)} {Lauf-Verhalten} {Angriffs-Typ}: Gegner.
	Dabei gibt es folgende Lauf-Verhalten:
	*	0 Vorw�rts laufen und umdrehen, wenn man gegen eine Wand st��t
	*	1 Wie 0, aber dreht auch um, wenn er sonst st�rzen w�rde
	Und folgende Angriffstypen:
	*	0 Nahkampf: Ber�hrung = Tod
*	Collectible {Abstand Links} {Abstand Oben} {Breite} {H�he}: Gegenstand, von dem alle eingesammelt werden m�ssen, um das Level beenden zu k�nnen.

Die Abstand/Gr��e-Definition bezieht sich dabei auf die Kollisionserkennung, Abstand ist relativ zum oberen linken Pixel. Angaben in Pixeln.

## x_y.images.png ##

Position von (m�glicherweise animierten) Bildern an festen Positionen. Oberen linken Pixel in Farbe gem�� images.txt anmalen.

### images.txt ###

Definition der statischen Bilder im Level:

Eine Zeile je Definition, Format:

{Rot} {Gr�n} {Blau} {Dateiname (relativ zum Levelverzeichnis)}

z.B.

0 255 0 test.png

= An gr�nen Pixeln wird das Bild test.png dargestellt. Wenn dieses animiert ist, so ist das in test.png.animations.txt beschrieben. Es wird die Animation "idle" abgespielt.


## gameplay.txt ##

Enth�lt Gameplay Informationen, im Format "Name Wert", Werte sind positive Zahlen. Es gibt folgende Namen (Gro�-/Kleinschreibung egal):

* ScreenWidth: Breite des sichtbaren Ausschnitts in Pixeln
* PlayerHeight: Kollisions-H�he des Spielers in Pixeln
* PlayerWidth: Kollisions-Breite des Spielers in Pixeln
* PlayerOffsetX: Abstand des Kollisionsrechtecks vom linken Rand des Bilds
* PlayerOffsetY: Abstand des Kollisionsrechtecks vom rechten Rand des Bilds
* JumpHeight: Sprungh�he in Pixeln (???)
* StepHeight: Stufen dieser H�he k�nnen ohne Sprung erklommen werden.
* Gravity: Erdanziehungskraft in Pixeln pro Quadratsekunde