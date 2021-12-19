//*********************************************************************
//
//  PLIK ŹRÓDŁOWY:		main.cpp
//
//  OPIS:				Program do Laboratorium nr 4 rysujący na
//						ekranie obiekt 3-D, wspierający obsługę
//		                myszki.
//
//  AUTOR:				Karol Pastewski, 252798@student.edu.pl
//
//  DATA
//	MODYFIKACJI:        15.11.2021r.
//
//  PLATFORMA:			System operacyjny:  Microsoft Windows 11
//						Środowisko:         CLion
//
//  MATERIAŁY			Dokumentacja OpenGL
//	ŹRÓDŁOWE:			Dokumentacja GLUT
//						www.zsk.ict.pwr.wroc.pl
//
//  UŻYTE BIBLIOTEKI	cmath — obsługuje matematyczne wzory i stałe
//  NIESTANDARDOWE
//
//*********************************************************************

#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

typedef float point3[3];

struct VERTEXES {
    float point3[3];
    float color3[3];
};

VERTEXES **ARRAY;           // niezainicjalizowana tablica dwuwymiarowa; patrz funkcję 'setArray()'
int N;                      // wielkość tablicy zainicjowana w funkcji 'setArray()'
static int model = 1;               // 1 - model chmury punków;
// 2 - model siatki;
// 3 - model wypełnionych trójkątów
static int showAxes = 1;        // 0 - brak osi współrzędnych;
// 1 - rysowanie osi współrzędnych
static int objectMode = 1;          // 1 - wyświetlenie jajka;
// 2 - wyświetlenie czajnika
static int status = 0;      // stan klawiszy myszy
// 0 - nie naciśnięto żadnego klawisza
// 1 - naciśnięty zostać lewy klawisz
// 2 - naciśnięty prawy klawisz

static float theta = 0.0;
static float phi = 0.0;

static float teapotRotation[] = {0.0, 0.0};

static float radius = 10.0;     // promień

static float pix2angle;     // przelicznik pikseli na stopnie

static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
static float delta_x = 0;        // różnica pomiędzy pozycją bieżącą i poprzednią kursora myszy

static int y_pos_old = 0;       // poprzednia pozycja kursora myszy
static float delta_y = 0;        // różnica pomiędzy pozycją bieżącą i poprzednią kursora myszy

static float viewer[] = {0.0, 0.0, 10.0};   // inicjalizacja położenia obserwatora

static float viewerTeapotZ = 10.0;

static float centerX = 0.0;
static float centerY = 0.0;
static float centerZ = 0.0;


// Funkcja rysująca osie układu współrzędnych
void drawAxes() {
    point3 x_min = {-5.0, 0.0, 0.0};
    point3 x_max = {5.0, 0.0, 0.0};
    // początek i koniec obrazu osi x

    point3 y_min = {0.0, -5.0, 0.0};
    point3 y_max = {0.0, 5.0, 0.0};
    // początek i koniec obrazu osi y

    point3 z_min = {0.0, 0.0, -5.0};
    point3 z_max = {0.0, 0.0, 5.0};
    //  początek i koniec obrazu osi y

    glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
    glBegin(GL_LINES); // rysowanie osi x

    glVertex3fv(x_min);
    glVertex3fv(x_max);

    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
    glBegin(GL_LINES);  // rysowanie osi y

    glVertex3fv(y_min);
    glVertex3fv(y_max);

    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
    glBegin(GL_LINES); // rysowanie osi z

    glVertex3fv(z_min);
    glVertex3fv(z_max);

    glEnd();

}

// Funkcja rysująca każdy punkt w tabeli 'ARRAY'
void drawPoints() {
    glBegin(GL_POINTS);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            glVertex3fv(ARRAY[i][j].point3);
        }
    }

    glEnd();
}

// Funkcja rysująca linie pomiędzy punktami w tabeli 'ARRAY'
void drawLines() {

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            // linia pionowa
            glBegin(GL_LINES);
            glVertex3fv(ARRAY[i][j].point3);
            glVertex3fv(ARRAY[i + 1][j].point3);
            glEnd();
            // linia pozioma
            glBegin(GL_LINES);
            glVertex3fv(ARRAY[i][j].point3);
            glVertex3fv(ARRAY[i][j + 1].point3);
            glEnd();

            // linie ukośne
            glBegin(GL_LINES);
            glVertex3fv(ARRAY[i][j].point3);
            glVertex3fv(ARRAY[i + 1][j + 1].point3);
            glEnd();
            glBegin(GL_LINES);
            glVertex3fv(ARRAY[i][j + 1].point3);
            glVertex3fv(ARRAY[i + 1][j].point3);
            glEnd();
        }
    }
}

// Funkcja rysująca trójkąty połączone z punktów z tabeli 'ARRAY'
//
// GL_TRIANGLE_FAN - pierwszy wierzchołek jest stały, jest on później
// łączony z grupami dwóch kolejnych wierzchołków w trójkąt, czyli np.
// dla 5 wierzchołków wyjdą trójkąty (0, 1, 2) i (0, 3, 4)
void drawTriangles() {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            glBegin(GL_TRIANGLE_FAN);

            glColor3fv(ARRAY[i][j].color3);
            glVertex3fv(ARRAY[i][j].point3);

            glColor3fv(ARRAY[i][j + 1].color3);
            glVertex3fv(ARRAY[i][j + 1].point3);

            glColor3fv(ARRAY[i + 1][j + 1].color3);
            glVertex3fv(ARRAY[i + 1][j + 1].point3);

            glColor3fv(ARRAY[i + 1][j].color3);
            glVertex3fv(ARRAY[i + 1][j].point3);

            glColor3fv(ARRAY[i + 1][j + 1].color3);
            glVertex3fv(ARRAY[i + 1][j + 1].point3);

            glEnd();
        }
    }

}

// Funkcja obsługująca rysowanie jajka
void Egg() {

    if (status == 1) {                  // jeśli lewy klawisz myszy wciśnięty
        theta += (delta_x * pix2angle) / 100;    // modyfikacja kąta obrotu o kąt proporcjonalny
        phi += (delta_y * pix2angle) / 100;

        if (theta > 360.0) theta -= 360.0;
        else if(theta < -360.0) theta += 360.0;
        if (phi > 360) phi -= 360.0;
        else if(phi < -360.0) phi += 360.0;

    } else if (status == 2) {        // jeśli prawy klawisz myszy wciśnięty
        radius += delta_y / 10;
        if (radius > 20) {
            radius = 20;
        } else if (radius < 2) {
            radius = 2;
        }
    }
    viewer[0] = radius * cos(theta) * cos(phi);
    viewer[1] = radius * sin(phi);
    viewer[2] = radius * sin(theta) * cos(phi);

    gluLookAt(viewer[0], viewer[1], viewer[2], centerX, centerY, centerZ, 0.0, 1.0, 0.0);
    // Zdefiniowanie położenia obserwatora

    if (showAxes == 1) drawAxes();

    glColor3f(1.0, 1.0, 1.0);    // ustawienie koloru na biały
    glTranslated(0.0, -(ARRAY[(N - 1) / 2][0].point3[1] / 2), 0.0);    // wyśrodkowanie obiektu

    if (model == 1) drawPoints();
    else if (model == 2) drawLines();
    else drawTriangles();

}

// Funkcja obsługująca rysowanie czajnika
void Teapot() {
    if (status == 1) {      // jeśli lewy klawisz myszy wciśnięty
        teapotRotation[0] +=delta_x * pix2angle;
        teapotRotation[1] +=delta_y * pix2angle;

        if (teapotRotation[0] > 360.0) teapotRotation[0] -= 360.0;
        else if(teapotRotation[0] < -360.0) teapotRotation[0] += 360.0;
        if (teapotRotation[1] > 360) teapotRotation[1] -= 360.0;
        else if(teapotRotation[1] < -360.0) teapotRotation[1] += 360.0;

    } else if (status == 2) {       // jeśli prawy klawisz myszy wciśnięty
        viewerTeapotZ += delta_y / 10;
        if (viewerTeapotZ > 20) {
            viewerTeapotZ = 20;
        } else if (viewerTeapotZ < 2) {
            viewerTeapotZ = 2;
        }
    }

    gluLookAt(0.0, 0.0, viewerTeapotZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
    // Zdefiniowanie położenia obserwatora

    glRotatef(teapotRotation[0], 0.0, 1.0, 0.0);
    glRotatef(teapotRotation[1], 1.0, 0.0, 0.0);

    if (showAxes == 1) drawAxes();

    glColor3f(1.0, 1.0, 1.0);    // ustawienie koloru na biały
    glutWireTeapot(4.0);
}

void renderScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // czyszczenie okna aktualnym kolorem czyszczącym

    glLoadIdentity();    // czyszczenie macierzy bieżącej

    if (objectMode == 1) Egg();
    else Teapot();

    glutSwapBuffers();
}

// Inicjalizacja losowych kolorów dla każdego punktu w tabeli 'ARRAY'
void setColors() {
    srand(time(nullptr));        // inicjalizacja generatora losowych liczb
    float red, green, blue;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            red = (float) (rand() / (float) RAND_MAX);        // losowanie liczb
            green = (float) (rand() / (float) RAND_MAX);        // zakres liczb: <0.0; 1.0>
            blue = (float) (rand() / (float) RAND_MAX);        //
            ARRAY[i][j].color3[0] = red;
            ARRAY[i][j].color3[1] = green;
            ARRAY[i][j].color3[2] = blue;
        }
    }

    // Pętla, dzięki której nie widać pasków na powierzchni jajka
    for (int i = 0; i < N / 2; i++) {
        ARRAY[i][0].color3[0] = ARRAY[N - i - 1][N - 1].color3[0];
        ARRAY[i][0].color3[1] = ARRAY[N - i - 1][N - 1].color3[1];
        ARRAY[i][0].color3[2] = ARRAY[N - i - 1][N - 1].color3[2];
        ARRAY[i][N - 1].color3[0] = ARRAY[N - i - 1][0].color3[0];
        ARRAY[i][N - 1].color3[1] = ARRAY[N - i - 1][0].color3[1];
        ARRAY[i][N - 1].color3[2] = ARRAY[N - i - 1][0].color3[2];
    }
}

// Inicjalizacja współrzędnych punktów potrzebnych do wyświetlenia jajka
void setVertices() {
    for (int i = 0; i < N; i++) {
        float u = (float) i / (N - 1);
        float uPow5 = pow(u, 5);
        float uPow4 = pow(u, 4);
        float uPow3 = pow(u, 3);
        float uPow2 = pow(u, 2);
        float x, y, z;

        y = 160 * uPow4 - 320 * uPow3 + 160 * uPow2;

        for (int j = 0; j < N; j++) {
            float v = (float) j / (N - 1);

            x = (-90 * uPow5 + 225 * uPow4 - 270 * uPow3 + 180 * uPow2 - 45 * u) * cos(M_PI * v);
            z = (-90 * uPow5 + 225 * uPow4 - 270 * uPow3 + 180 * uPow2 - 45 * u) * sin(M_PI * v);

            ARRAY[i][j].point3[0] = x;
            ARRAY[i][j].point3[1] = y;
            ARRAY[i][j].point3[2] = z;
        }
    }
}

// Funkcja inicjalizuje tablicę 'ARRAY' oraz wywołuje funkcje inicjalizujące
// kolory i współrzędne punktów
void setArray() {
    cout << "Podaj liczbe N = ";
    cin >> N;
    VERTEXES **newArray = new VERTEXES *[N];
    for (int i = 0; i < N; i++) {
        newArray[i] = new VERTEXES[N];
    }
    ARRAY = newArray;
    setColors();
    setVertices();
}

// Funkcja wyświetlająca w konsoli informacje o opcjach programu
void initProgram() {
    cout << "Program z laboratorium 3 - modelowanie obiektow 3-D\n";
    setArray();
    cout << "Odpowiednie klawisze zmieniaja widok modelu:\n";
    cout << "   Wyswietlany obiekt:\n";
    cout << "      'f' - jajko (domyslne)\n";
    cout << "      'g' - czajnik\n";
    cout << "   Model wyswietlania jajka (nie dziala dla obiektu czajnika):\n";
    cout << "      '1' - model chmury punktow (domyslne)\n";
    cout << "      '2' - model siatki\n";
    cout << "      '3' - model wypelnionych trojkatow\n";
    cout << "   Wyswietlanie osi wspolrzednych:\n";
    cout << "      'a' - nie\n";
    cout << "      's' - tak (domyslne)\n";
    cout << "   Sterowanie myszka:\n";
    cout << "      'Przytrzymaj LPM' - obrot obiektu\n";
    cout << "      'Przytrzymaj PPM' - zoom obiektu\n";
    cout << "   Operowanie programem:\n";
    cout << "      'esc' - wyjscie z programu\n";
}

// Funkcja obsługująca działanie programu za pomocą klawiszy klawiatury
void keys(unsigned char key, int x, int y) {
    if (objectMode == 1) {
        if (key == '1') model = 1;
        if (key == '2') model = 2;
        if (key == '3') model = 3;
    }
    if (key == 'a') showAxes = 0;
    if (key == 's') showAxes = 1;
    if (key == 'f') objectMode = 1;
    if (key == 'g') objectMode = 2;
    if (key == (char) 27) exit(0);

    renderScene(); // przerysowanie obrazu sceny
}

// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) sś
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna.
void changeSize(GLsizei horizontal, GLsizei vertical) {

    pix2angle = 360.0 / (float) horizontal;  // przeliczenie pikseli na stopnie

    glMatrixMode(GL_PROJECTION);
    // Przełączenie macierzy bieżącej na macierz projekcji

    glLoadIdentity();
    // Czyszczenie macierzy bieżącej

    gluPerspective(70, 1.0, 1.0, 30.0);
    // Ustawienie parametrów dla rzutu perspektywicznego

    if (horizontal <= vertical)
        glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);
    else
        glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
    // Ustawienie wielkości okna widoku (viewport) w zależności
    // relacji pomiędzy wysokością i szerokością okna

    glMatrixMode(GL_MODELVIEW);
    // Przełączenie macierzy bieżącej na macierz widoku modelu

    glLoadIdentity();
    // Czyszczenie macierzy bieżącej

}

// Funkcja obsługuje wciśnięcie przycisku na myszcze
void Mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora jako pozycji poprzedniej
        y_pos_old = y;
        status = 1;          // wciśnięty został lewy klawisz myszy
    } else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        y_pos_old = y;
        status = 2;
    } else {
        status = 0;          // nie został wciśnięty żaden klawisz
    }
}

// Funkcja "monitoruje" położenie kursora myszy i ustawia wartości odpowiednich
// zmiennych globalnych
void Motion(GLsizei x, GLsizei y) {

    delta_x = x - x_pos_old;     // obliczenie różnicy położenia kursora myszy
    delta_y = y - y_pos_old;

    x_pos_old = x;            // podstawienie bieżącego położenia jako poprzednie
    y_pos_old = y;

    glutPostRedisplay();     // przerysowanie obrazu sceny
}

// Funkcja ustalająca stan renderowania
void myInit() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Kolor czyszczący (wypełnienia okna) ustawiono na czarny
    glEnable(GL_DEPTH_TEST);
    // Włączenie mechanizmu usuwania powierzchni niewidocznych

}

// Główny punkt wejścia programu. Program działa w trybie konsoli
int main() {

    initProgram();

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(600, 600);

    glutCreateWindow("Rzutowanie perspektywiczne");

    glutDisplayFunc(renderScene);
    // Określenie, że funkcja renderScene będzie funkcją zwrotną
    // (callback function).  Biedzie ona wywoływana za każdym razem,
    // gdy zajdzie potrzeba przerysowania okna

    glutReshapeFunc(changeSize);
    // Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
    // za zmiany rozmiaru okna

    glutKeyboardFunc(keys);

    glutMouseFunc(Mouse);
    // Ustala funkcję zwrotną odpowiedzialną za badanie stanu myszy

    glutMotionFunc(Motion);
    // Ustala funkcję zwrotną odpowiedzialną za badanie ruchu myszy

    myInit();
    // Funkcja myInit() (zdefiniowana powyżej) wykonuje wszelkie
    // inicjalizacje konieczne  przed przystąpieniem do renderowania

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

}
