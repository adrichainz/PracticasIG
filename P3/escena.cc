#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <string>
#include "escena.h"


Escena::Escena(){
  Front_plane=50;
  Back_plane=2000;
  Observer_distance = 4*Front_plane;
  Observer_angle_x = Observer_angle_y=0;
  ejes.changeAxisSize(5000);
}

void Escena::inicializar(int UI_window_width,int UI_window_height) {
	glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer
	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);
  /* Creación de objetos */
  char* nombre_ply = "modelos_ply/big_porsche.ply";
  vector<float> vertices = {5.0,6.0,0.0, 4.5,5.0,0.0, 4.0,4.0,0.0,
                            3.0,3.0,0.0, 2.0,2.0,0.0, 1.0,1.0,0.0,
                            1.0,0.0,0.0, 1.0,-1.0,0.0, 1.0,-2.0,0.0,
                            2.0,-3.0,0.0, 5.0,-4.0,0.0};
  revolucion = new ObjetoRevolucion(vertices, 40);
  ply = new ObjetoPLY(nombre_ply);
  robot = new Robot;
}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects(unsigned char figura_a_dibujar) {
  switch(figura_a_dibujar){
    case '1':
      ply->escalar(); //para visualizarlo a una escala razonable
      ply->dibujar(forma_dibujado);
      break;
    case '2':
      revolucion->escalar();
      revolucion->dibujar(forma_dibujado);
      break;
    case '3':
      robot->dibujar(forma_dibujado, grados_hombro, grados_cabeza, mov_ojos, grados_pierna);
      break;
    case 'Z':
      grados_hombro += 2;
      break;
    case 'z':
      grados_hombro -= 2;
      break;
    case 'X':
      if(grados_cabeza < 90)
        grados_cabeza += 2;
      break;
    case 'x':
      if(grados_cabeza > -90)
        grados_cabeza -= 2;
      break;
    case 'C':
      if(mov_ojos < 5)
        mov_ojos += 0.5;
      break;
    case 'c':
      if(mov_ojos > 0)
        mov_ojos -= 0.5;
      break;
    case 'V':
      if(grados_pierna < 60)
        grados_pierna += 5;
      break;
    case 'v':
      if(grados_pierna > -60)
        grados_pierna -= 5;
      break;
  }
}


void Escena::dibujar(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	draw_axis();
	draw_objects(figura_dibujada);
}

int Escena::teclaPulsada(unsigned char tecla,int x,int y) {

  std::cout << "Tecla " << tecla << std::endl;
	if (toupper(tecla)=='Q') return 1;

  else if(tolower(tecla)=='p' || tolower(tecla)=='l' || tolower(tecla)=='s' || tolower(tecla)=='a'){
    //con estas 4 teclas cambiamos la forma de dibujado: alambres, sólido, puntos y ajedrez
    forma_dibujado = tolower(tecla);
    return 0;
  }

  else if(tecla=='z' || tecla=='Z' || tecla=='x' || tecla=='X' || tecla=='c' || tecla=='C'
          || tecla=='v' || tecla=='V'){
    // z/Z -> modificar grado de libertad: rotación de los brazos con respecto a los hombros
    // x/X -> modificar grado de libertad: rotación de la cabeza sobre el cuello (eje Y)
    // c/C -> modificar grado de libertad: traslación de los ojos (eje Z)
    // v/V -> modificar grado de libertad: rotación de las piernas sobre la ingle (eje X)
    draw_objects(tecla);
    return 0;
  }

  else if(tecla=='1' || tecla=='2' || tecla=='3'){
    figura_dibujada = tecla;
    draw_objects(figura_dibujada);
    return 0;
  }

  //si pulsamos cualquier otra, no cambia nada
  else return 0;
}

void Escena::teclaEspecial(int Tecla1,int x,int y) {
switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}

	std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformación de proyección
//***************************************************************************

void Escena::change_projection()  {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Width,Width,-Height,Height,Front_plane,Back_plane);
}


void Escena::redimensionar(int newWidth,int newHeight) {
change_projection();
Width=newWidth/10;
Height=newHeight/10;
glViewport(0,0,newWidth,newHeight);
}


//**************************************************************************
// Funcion para definir la transformaci�n de vista (posicionar la camara)
//***************************************************************************



void Escena::change_observer() {

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis()
{
ejes.draw();
}
