#include "objeto_revolucion.h"
#include "robot.h"

Robot::Robot(){
  cubo = new Cubo;
  prisma_hex = new ObjetoRevolucion(perfil_cilindro, 6);
  cilindro = new ObjetoRevolucion(perfil_cilindro, 15);
  generarPerfilEsfera();
  esfera = new ObjetoRevolucion(perfil_esfera, 20);
  generarPerfilToroide();
  toroide = new ObjetoRevolucion(perfil_toroide, 20);
  prisma_tri = new ObjetoRevolucion(perfil_cilindro, 3);
}

//este método controla el color con el que dibujamos cada parte del robot
void Robot::dibujar(unsigned char modo, float grados_hombro, float grados_cabeza, float mov_ojos, float grados_pierna){
  dibujarCuerpo(modo, grados_hombro, grados_cabeza, mov_ojos, grados_pierna);
}

void Robot::dibujarCuerpo(unsigned char modo, float grados_hombro, float grados_cabeza, float mov_ojos, float grados_pierna){
  //el tronco constará de un hexágono del que sale un pequeño cilindro a modo de
  // cuello
  glPushMatrix();
    glScalef(100.0,100.0,50.0);
    prisma_hex->dibujar(modo);
  glPopMatrix();
  glPushMatrix();
    glScalef(15.0,15.0,15.0);
    glTranslatef(0.0,3.80,0.0);
    cilindro->dibujar(modo);
  glPopMatrix();
  dibujarCabeza(modo, grados_cabeza, mov_ojos);
  dibujarBrazos(modo, grados_hombro);
  dibujarPiernas(modo, grados_pierna);
}

void Robot::dibujarPiernas(unsigned char modo, float grados_pierna){
  //cada pierna es un cilindro con una esfera al principio y un prisma triangular
  // "tumbado" al final
  glPushMatrix();//pierna izda
    glTranslatef(-20,-50,0);
    glRotatef(grados_pierna,1,0,0);
    glPushMatrix();
      glScalef(12,12,12);
      esfera->dibujar(modo);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0,-12,0);
      glPushMatrix();
        glScalef(12,60,12);
        cilindro->dibujar(modo);
      glPopMatrix();
      glPushMatrix();
        glTranslatef(0,-32,0);
        glRotatef(90,0,0,1);
        glScalef(15,28,24);
        prisma_tri->dibujar(modo);
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  glPushMatrix();//pierna izda
    glTranslatef(20,-50,0);
    glRotatef(grados_pierna,1,0,0);
    glPushMatrix();
      glScalef(12,12,12);
      esfera->dibujar(modo);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0,-12,0);
      glPushMatrix();
        glScalef(12,60,12);
        cilindro->dibujar(modo);
      glPopMatrix();
      glPushMatrix();
        glTranslatef(0,-32,0);
        glRotatef(90,0,0,1);
        glScalef(15,28,24);
        prisma_tri->dibujar(modo);
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();
}

void Robot::dibujarBrazos(unsigned char modo, float grados){

  glPushMatrix();//cilindro del hombro izquierdo (fijo)
    glTranslatef(-56,38,0);
    glRotatef(90,0,0,1);
    glScalef(12,24,12);
    cilindro->dibujar(modo);
  glPopMatrix();
  //brazo izquierdo
  glPushMatrix();//esfera del hombro (rota con el brazo)
    glPushMatrix();
      glTranslatef(-65,38,0);
      glRotatef(grados,1,0,0);
      glScalef(12,12,12);
      esfera->dibujar(modo);
    glPopMatrix();
    glPushMatrix();//brazo
      glTranslatef(-65,38,0);
      glRotatef(grados,1,0,0);
      glTranslatef(0,-38.5,0);
      glPushMatrix();
        glScalef(12,76,12);
        cilindro->dibujar(modo);
      glPopMatrix();
      glPushMatrix();//mano izquierda(rota en el extremo del brazo)
        glTranslatef(0,-38,0);
        glScalef(12,12,12);
        esfera->dibujar(modo);
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  glPushMatrix();//cilindro del hombro derecho (fijo)
    glTranslatef(56,38,0);
    glRotatef(90,0,0,1);
    glScalef(12,24,12);
    cilindro->dibujar(modo);
  glPopMatrix();
  //brazo derecho
  glPushMatrix();//esfera del hombro (rota con el brazo)
    glPushMatrix();
      glTranslatef(65,38,0);
      glRotatef(grados,1,0,0);
      glScalef(12,12,12);
      esfera->dibujar(modo);
    glPopMatrix();
    glPushMatrix();//brazo
      glTranslatef(65,38,0);
      glRotatef(grados,1,0,0);
      glTranslatef(0,-38.5,0);
      glPushMatrix();
        glScalef(12,76,12);
        cilindro->dibujar(modo);
      glPopMatrix();
      glPushMatrix();//mano derecha(rota en el extremo del brazo)
        glTranslatef(0,-38,0);
        glScalef(12,12,12);
        esfera->dibujar(modo);
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();
}

void Robot::dibujarCabeza(unsigned char modo, float grados_cuello, float mov_ojos){
  //la cabeza será un simple cubo, con un toroide encima algo separado a modo de
  // aureola
  glPushMatrix();
    glTranslatef(0,95,0);
    glRotatef(grados_cuello,0,1,0);
    glPushMatrix();
      glScalef(75,60,75);
      cubo->trasladar();
      cubo->dibujar(modo);
    glPopMatrix();
    glPushMatrix();//ojo izdo
      glTranslatef(-15,10,37.5+mov_ojos);
      glRotatef(90,1,0,0);
      glRotatef(30,0,1,0);
      glScalef(18,1,18);
      prisma_tri->dibujar('s');
    glPopMatrix();
    glPushMatrix();//ojo dcho
      glTranslatef(15,10,37.5+mov_ojos);
      glRotatef(90,1,0,0);
      glRotatef(30,0,1,0);
      glScalef(18,1,18);
      prisma_tri->dibujar('s');
    glPopMatrix();

  glPopMatrix();

    // glPushMatrix();
    //   glScalef(40,40,40);
    //   toroide->dibujar(modo);
    // glPopMatrix();

}
void Robot::dibujarAureola(unsigned char modo){

}

void Robot::generarPerfilEsfera(){
  int n = 60;
  float alpha = M_PI/2, suma = 2*M_PI/n, radio = 1.0;
  for(int i=0; i<=n/2; i++){
    perfil_esfera.push_back(-radio*cos(alpha));
    perfil_esfera.push_back(-radio*sin(alpha));
    perfil_esfera.push_back(0.0);
    alpha += suma;
  }
}

void Robot::generarPerfilToroide(){
  int n = 60;
  float alpha = M_PI/2, suma = 2*M_PI/n, radio = 1.0;
  for(int i=0; i<=n; i++){
    perfil_toroide.push_back(-radio*cos(alpha)+2.5);
    perfil_toroide.push_back(-radio*sin(alpha));
    perfil_toroide.push_back(0.0);
    alpha += suma;
  }
}
