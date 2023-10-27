#include <GL/glut.h>
#include <stdio.h> //ayuda a llevar a cabo el manejo de los archivos
//textura es un archivo de grafico

GLfloat offsetX = 0.0f;  // desplazamiento horizontal actual de nube1
GLfloat speed = 0.03f;    // Velocidad de desplazamiento horizontal

GLfloat offsetX1 = 0.0f;  // desplazamiento horizontal actual de nube2
GLfloat speed1 = 0.03f;    // Velocidad de desplazamiento horizontal

GLfloat rotationAngle = 0.0f;

typedef struct{
 GLubyte *dibujo;
 GLuint bpp; //bit por punto
 GLuint largo; //largo de la imagen en pixeles
 GLuint ancho; //ancho de la imagen en pixeles
 GLuint ID; //Un identificador que podr�a estar asociado con la imagen
 
} textura;

//		nombre de la textura
textura Mitextura_fondo_shera;
textura Mitextura_shera;
textura Mitextura_nube1;
textura Mitextura_nube2;

int cargaTGA(char *nombre, textura * imagen){
	//Los 12 caracteres primeros me sirven para identificar
	//como archivo tga
	//en base a esos valores le digo q se cargue la textura
	GLubyte cabeceraTGA[12]={0,0,2,0,0,0,0,0,0,0,0,0}; //valores de la imagen que nos da el hexed.it
	GLubyte compararTGA[12]; //almacene los binarios de la imagen analizados
	GLubyte cabecera[6]; //caracteristicas del archivo TGA, (largo/ancho) de la imagen y sistema de colores
	GLuint bytesporpunto; // bytes de la imagen
	GLuint tamanoimagen; //tener el tama�o de la imagen
	GLuint temp,i; ////creacion y regeneracion de la imagen y para crear un ciclo repetitivo
	GLuint tipo=GL_RGBA; // el sistema de imagen
	
	//interaccion del archivo de forma binaria
	FILE *archivo= fopen(nombre,"rb"); //read binary
	
	//condicional para validar si el archivo existe o no
	
	//fread leer, permite asignar en la memoria de acuerdo a las caracteristicas q yo te indique
	//que lea de 1 en 1, que lea la cantidad de bit del tama�o de compararTGA del archivo
	//que sea diferente al tama�o de comparar tga
	//memcp  
	if(archivo==NULL ||
	   fread(compararTGA,1,sizeof(compararTGA),archivo)!=sizeof(compararTGA) ||
	   memcmp(cabeceraTGA,compararTGA,sizeof(compararTGA))!=0 ||
	   fread(cabecera,1,sizeof(cabecera),archivo)!=sizeof(cabecera)){
	   	
	   if(archivo==NULL){
	   	printf("NO SE ENCONTRO ARCHIVO %s\n", nombre);
	   	return 0;
		}
		else{
	   	fclose(archivo);
	   	return 0;
		}	
	}
	
	imagen->largo= 256*cabecera[1] + cabecera[0];
	          // 256 * 1 + 244=256+244=500
	imagen->ancho=256 * cabecera[3]+cabecera[2];
	    //256 * 1 + 244=256+244=500
    if(
	imagen->largo <=0  ||
	imagen->ancho <=0  ||
	(cabecera[4]!=24  && cabecera[4]!=32)// 24 = RGB , 32=RGBA
	) {
		printf("Datos invalidos\n");
	
		fclose(archivo);
		return 0;
	}
	imagen->bpp=cabecera[4];
	bytesporpunto=cabecera[4]/8;// 4 bytes
	
    tamanoimagen=imagen->largo * imagen->ancho * bytesporpunto; 
    //500 * 500 + 4 = 1000000
    //1000000 /1024= 976,56 =977 
    
    //malloc reserva el tama�o de la imagen
    imagen->dibujo =(GLubyte *)malloc(tamanoimagen);
    if(
	imagen->dibujo==NULL ||
	fread(imagen->dibujo,1,tamanoimagen,archivo)!=tamanoimagen
	){
		
		if(imagen->dibujo != NULL){
			printf("Error leyendo imagen\n");
			free(imagen->dibujo);
			
		}else{
			printf("Error asignando memoria\n");
		}
		fclose(archivo);
		return 0;
	}
    // TGA : BGRA                RGBA
    
    for(i=0; i<(int)tamanoimagen;i+=bytesporpunto){
    	temp=imagen->dibujo[i];
    	imagen->dibujo[i]=imagen->dibujo[i+2];
    	imagen->dibujo[i+2]=temp;
    	
	}
	fclose(archivo);
	glGenTextures(1,&imagen[0].ID);
	glBindTexture(GL_TEXTURE_2D,imagen[0].ID);
	if(imagen->bpp==24) tipo=GL_RGB;	
	glTexImage2D(GL_TEXTURE_2D,0,tipo,imagen[0].ancho,imagen[0].largo,0,tipo,GL_UNSIGNED_BYTE,imagen[0].dibujo);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    return 1;
}

int cargaTGA2(char *nombre, textura * imagen){
	//Los 12 caracteres primeros me sirven para identificar
	//como archivo tga
	//en base a esos valores le digo q se cargue la textura
	GLubyte cabeceraTGA[12]={0,0,2,0,0,0,0,0,0,0,0,0}; //valores de la imagen que nos da el hexed.it
	GLubyte compararTGA[12]; //almacene los binarios de la imagen analizados
	GLubyte cabecera[6]; //caracteristicas del archivo TGA, (largo/ancho) de la imagen y sistema de colores
	GLuint bytesporpunto; // bytes de la imagen
	GLuint tamanoimagen; //tener el tama�o de la imagen
	GLuint temp,i; ////creacion y regeneracion de la imagen y para crear un ciclo repetitivo
	GLuint tipo=GL_RGBA; // el sistema de imagen
	
	//interaccion del archivo de forma binaria
	FILE *archivo= fopen(nombre,"rb"); //read binary
	
	//condicional para validar si el archivo existe o no
	
	//fread leer, permite asignar en la memoria de acuerdo a las caracteristicas q yo te indique
	//que lea de 1 en 1, que lea la cantidad de bit del tama�o de compararTGA del archivo
	//que sea diferente al tama�o de comparar tga
	//memcp  
	if(archivo==NULL ||
	   fread(compararTGA,1,sizeof(compararTGA),archivo)!=sizeof(compararTGA) ||
	   memcmp(cabeceraTGA,compararTGA,sizeof(compararTGA))!=0 ||
	   fread(cabecera,1,sizeof(cabecera),archivo)!=sizeof(cabecera)){
	   	
	   if(archivo==NULL){
	   	printf("NO SE ENCONTRO ARCHIVO %s\n", nombre);
	   	return 0;
		}
		else{
	   	fclose(archivo);
	   	return 0;
		}	
	}
	
	imagen->largo= 256*cabecera[1] + cabecera[0];
	          // 256 * 1 + 244=256+244=500
	imagen->ancho=256 * cabecera[3]+cabecera[2];
	    //256 * 1 + 244=256+244=500
    if(
	imagen->largo <=0  ||
	imagen->ancho <=0  ||
	(cabecera[4]!=24  && cabecera[4]!=32)// 24 = RGB , 32=RGBA
	) {
		printf("Datos invalidos\n");
	
		fclose(archivo);
		return 0;
	}
	imagen->bpp=cabecera[4];
	bytesporpunto=cabecera[4]/8;// 4 bytes
	
    tamanoimagen=imagen->largo * imagen->ancho * bytesporpunto; 
    //500 * 500 + 4 = 1000000
    //1000000 /1024= 976,56 =977 
    imagen->dibujo =(GLubyte *)malloc(tamanoimagen);
    if(
	imagen->dibujo==NULL ||
	fread(imagen->dibujo,1,tamanoimagen,archivo)!=tamanoimagen
	){
		
		if(imagen->dibujo != NULL){
			printf("Error leyendo imagen\n");
			free(imagen->dibujo);
			
		}else{
			printf("Error asignando memoria\n");
		}
		fclose(archivo);
		return 0;
	}
    // TGA : BGRA                RGBA
    
    for(i=0; i<(int)tamanoimagen;i+=bytesporpunto){
    	temp=imagen->dibujo[i];
    	imagen->dibujo[i]=imagen->dibujo[i+2];
    	imagen->dibujo[i+2]=temp;
    	
	}
	fclose(archivo);
	glGenTextures(1,&imagen[0].ID);
	glBindTexture(GL_TEXTURE_2D,imagen[0].ID);
	if(imagen->bpp==24) tipo=GL_RGB;	
	glTexImage2D(GL_TEXTURE_2D,0,tipo,imagen[0].ancho,imagen[0].largo,0,tipo,GL_UNSIGNED_BYTE,imagen[0].dibujo);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    return 1;
}

int cargaTGA3(char *nombre, textura * imagen){
	//Los 12 caracteres primeros me sirven para identificar
	//como archivo tga
	//en base a esos valores le digo q se cargue la textura
	GLubyte cabeceraTGA[12]={0,0,2,0,0,0,0,0,0,0,0,0}; //valores de la imagen que nos da el hexed.it
	GLubyte compararTGA[12]; //almacene los binarios de la imagen analizados
	GLubyte cabecera[6]; //caracteristicas del archivo TGA, (largo/ancho) de la imagen y sistema de colores
	GLuint bytesporpunto; // bytes de la imagen
	GLuint tamanoimagen; //tener el tama�o de la imagen
	GLuint temp,i; ////creacion y regeneracion de la imagen y para crear un ciclo repetitivo
	GLuint tipo=GL_RGBA; // el sistema de imagen
	
	//interaccion del archivo de forma binaria
	FILE *archivo= fopen(nombre,"rb"); //read binary
	
	//condicional para validar si el archivo existe o no
	
	//fread leer, permite asignar en la memoria de acuerdo a las caracteristicas q yo te indique
	//que lea de 1 en 1, que lea la cantidad de bit del tama�o de compararTGA del archivo
	//que sea diferente al tama�o de comparar tga
	//memcp  
	if(archivo==NULL ||
	   fread(compararTGA,1,sizeof(compararTGA),archivo)!=sizeof(compararTGA) ||
	   memcmp(cabeceraTGA,compararTGA,sizeof(compararTGA))!=0 ||
	   fread(cabecera,1,sizeof(cabecera),archivo)!=sizeof(cabecera)){
	   	
	   if(archivo==NULL){
	   	printf("NO SE ENCONTRO ARCHIVO %s\n", nombre);
	   	return 0;
		}
		else{
	   	fclose(archivo);
	   	return 0;
		}	
	}
	
	imagen->largo= 256*cabecera[1] + cabecera[0];
	          // 256 * 1 + 244=256+244=500
	imagen->ancho=256 * cabecera[3]+cabecera[2];
	    //256 * 1 + 244=256+244=500
    if(
	imagen->largo <=0  ||
	imagen->ancho <=0  ||
	(cabecera[4]!=24  && cabecera[4]!=32)// 24 = RGB , 32=RGBA
	) {
		printf("Datos invalidos\n");
	
		fclose(archivo);
		return 0;
	}
	imagen->bpp=cabecera[4];
	bytesporpunto=cabecera[4]/8;// 4 bytes
	
    tamanoimagen=imagen->largo * imagen->ancho * bytesporpunto; 
    //500 * 500 + 4 = 1000000
    //1000000 /1024= 976,56 =977 
    imagen->dibujo =(GLubyte *)malloc(tamanoimagen);
    if(
	imagen->dibujo==NULL ||
	fread(imagen->dibujo,1,tamanoimagen,archivo)!=tamanoimagen
	){
		
		if(imagen->dibujo != NULL){
			printf("Error leyendo imagen\n");
			free(imagen->dibujo);
			
		}else{
			printf("Error asignando memoria\n");
		}
		fclose(archivo);
		return 0;
	}
    // TGA : BGRA                RGBA
    
    for(i=0; i<(int)tamanoimagen;i+=bytesporpunto){
    	temp=imagen->dibujo[i];
    	imagen->dibujo[i]=imagen->dibujo[i+2];
    	imagen->dibujo[i+2]=temp;
    	
	}
	fclose(archivo);
	glGenTextures(1,&imagen[0].ID);
	glBindTexture(GL_TEXTURE_2D,imagen[0].ID);
	if(imagen->bpp==24) tipo=GL_RGB;	
	glTexImage2D(GL_TEXTURE_2D,0,tipo,imagen[0].ancho,imagen[0].largo,0,tipo,GL_UNSIGNED_BYTE,imagen[0].dibujo);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    return 1;
}

int cargaTGA4(char *nombre, textura * imagen){
	//Los 12 caracteres primeros me sirven para identificar
	//como archivo tga
	//en base a esos valores le digo q se cargue la textura
	GLubyte cabeceraTGA[12]={0,0,2,0,0,0,0,0,0,0,0,0}; //valores de la imagen que nos da el hexed.it
	GLubyte compararTGA[12]; //almacene los binarios de la imagen analizados
	GLubyte cabecera[6]; //caracteristicas del archivo TGA, (largo/ancho) de la imagen y sistema de colores
	GLuint bytesporpunto; // bytes de la imagen
	GLuint tamanoimagen; //tener el tama�o de la imagen
	GLuint temp,i; ////creacion y regeneracion de la imagen y para crear un ciclo repetitivo
	GLuint tipo=GL_RGBA; // el sistema de imagen
	
	//interaccion del archivo de forma binaria
	FILE *archivo= fopen(nombre,"rb"); //read binary
	
	//condicional para validar si el archivo existe o no
	
	//fread leer, permite asignar en la memoria de acuerdo a las caracteristicas q yo te indique
	//que lea de 1 en 1, que lea la cantidad de bit del tama�o de compararTGA del archivo
	//que sea diferente al tama�o de comparar tga
	//memcp  
	if(archivo==NULL ||
	   fread(compararTGA,1,sizeof(compararTGA),archivo)!=sizeof(compararTGA) ||
	   memcmp(cabeceraTGA,compararTGA,sizeof(compararTGA))!=0 ||
	   fread(cabecera,1,sizeof(cabecera),archivo)!=sizeof(cabecera)){
	   	
	   if(archivo==NULL){
	   	printf("NO SE ENCONTRO ARCHIVO %s\n", nombre);
	   	return 0;
		}
		else{
	   	fclose(archivo);
	   	return 0;
		}	
	}
	
	//calcular largo
	imagen->largo= 256*cabecera[1] + cabecera[0];
	          // 256 * 1 + 244=256+244=500
	//calcular ancho
	imagen->ancho=256 * cabecera[3]+cabecera[2];
	    //256 * 1 + 244=256+244=500
    if(
	imagen->largo <=0  ||
	imagen->ancho <=0  ||
	(cabecera[4]!=24  && cabecera[4]!=32)// 24 = RGB , 32=RGBA
	) {
		printf("Datos invalidos\n");
	
		fclose(archivo);
		return 0;
	}
	imagen->bpp=cabecera[4];
	bytesporpunto=cabecera[4]/8;// 4 bytes
	
    tamanoimagen=imagen->largo * imagen->ancho * bytesporpunto; 
    //500 * 500 + 4 = 1000000
    //1000000 /1024= 976,56 =977 
    imagen->dibujo =(GLubyte *)malloc(tamanoimagen);
    if(
	imagen->dibujo==NULL ||
	fread(imagen->dibujo,1,tamanoimagen,archivo)!=tamanoimagen
	){
		
		if(imagen->dibujo != NULL){
			printf("Error leyendo imagen\n");
			free(imagen->dibujo);
			
		}else{
			printf("Error asignando memoria\n");
		}
		fclose(archivo);
		return 0;
	}
    // TGA : BGRA                RGBA
    
    for(i=0; i<(int)tamanoimagen;i+=bytesporpunto){
    	temp=imagen->dibujo[i];
    	imagen->dibujo[i]=imagen->dibujo[i+2];
    	imagen->dibujo[i+2]=temp;
    	
	}
	fclose(archivo);
	glGenTextures(1,&imagen[0].ID);
	glBindTexture(GL_TEXTURE_2D,imagen[0].ID);
	if(imagen->bpp==24) tipo=GL_RGB;	
	glTexImage2D(GL_TEXTURE_2D,0,tipo,imagen[0].ancho,imagen[0].largo,0,tipo,GL_UNSIGNED_BYTE,imagen[0].dibujo);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    return 1;
}

//dibujo estrella
void estrellas() {
	glDisable(GL_LIGHTING);
	
	//Dibuja el primer pol�gono que forma la estrella
    glPushMatrix();
     glColor3f(0.0f, 0.0f, 0.0f / 0.0f); // Establece el color a rojo (R, G, B)
     glBegin(GL_POLYGON);
    glVertex2d(255.3962013077444, 76.9400935719892); 
    glVertex2d(322.5976131946271, 0); 
    glVertex2d(320.2112549969244, 35.0976076243205); 
    glVertex2d(353.2722796, 50.34684); 
    glEnd();

    // Dibuja el segundo pol�gono que forma la estrella
    glBegin(GL_POLYGON);
    glVertex2d(313.1103550458907, 98.286424406646); 
    glVertex2d(260.7227956049141, 13.6156639549835); 
    glVertex2d(298.2848645083196, 27.5342402006447); 
    glVertex2d(322.5976131946271, 0);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);  // Restaura el color a blanco (R, G, B)
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void init(){	
	//direccion de luz DERECHO,ARRIBA,ADELANTE,ATRAS	
	GLfloat light_position[] = {0.0,0.0,1.0,0.0};
	glEnable(GL_LIGHTING);//Prende o activa el sistema de iluminaci�n
	glEnable(GL_LIGHT0); //Se hace uso del tipo de luz: 0 a 7
	glLightfv(GL_LIGHT0,GL_POSITION, light_position);
	glEnable(GL_COLOR_MATERIAL);
	
	glShadeModel(GL_SMOOTH);//mejora las sombras en el modelado
	glClearColor(0.0,0.0,0.0,0.0);
	glClearDepth(1.0);//borra cualquier tipo de profundidad
	//habilitar la profundidad, para verificar la profundidad de cada grafico
	glEnable(GL_DEPTH_TEST);
	//mejora perspectiva del grafico
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
	//texturizo
	glEnable(GL_TEXTURE_2D);
	//carga de textura
	if(!cargaTGA("Shera.tga",&Mitextura_fondo_shera)){
		printf("Error cargando textura\n");
	}
	if(!cargaTGA2("Shera_fijo.tga",&Mitextura_shera)){
		printf("Error cargando textura\n");
	}
	if(!cargaTGA3("nube_fija.tga",&Mitextura_nube1)){
		printf("Error cargando textura\n");
	}
	if(!cargaTGA4("nube_fija.tga",&Mitextura_nube2)){
		printf("Error cargando textura\n");
	}
}

void display(){
	//Limpia la memoria de color y de profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Matriz de transformaci�n general
    glLoadIdentity();
     
    //FONDO_SHERA
    //Llama a las texturas o sea las im�genes
	glBindTexture(GL_TEXTURE_2D,Mitextura_fondo_shera.ID);
	glBegin(GL_QUADS);
	  glTexCoord2f(0,0);
	  glVertex3d(-500,500,0);
	  glTexCoord2f(1,0);
	  glVertex3d(500,500,0);
	  glTexCoord2f(1,1);
	  glVertex3d(500,-500,0);
	  glTexCoord2f(0,1);
	  glVertex3d(-500,-500,0);
	glEnd();
	
	//IMAGEN SHERA FIJO
	//Llama a las texturas o sea las im�genes
	glBindTexture(GL_TEXTURE_2D,Mitextura_shera.ID);
    glTranslatef(-10,60,0);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0);
      glVertex3d(-80, 120, 0);     
      glTexCoord2f(1, 0);
      glVertex3d(215, 120, 0);    
      glTexCoord2f(1, 1);
      glVertex3d(215, -170, 0);  
      glTexCoord2f(0, 1);
      glVertex3d(-80, -170, 0);  
    glEnd();
    
    //glPushMatrix() -> duplica la matriz
    //glPopMatrix() -> volvemos a la matriz original
    
    //ESTRELLA 1
    glPushMatrix();
    glScalef(0.2, 0.2, 1.0);
    glTranslated(50, -400, 300);
    estrellas(); // Dibuja la estrella
    glPopMatrix();
    
    //ESTRELLA 2.1
    glPushMatrix();
    glScalef(0.3, 0.3, 1.0);
    glTranslated(-700, 30, 300);
    estrellas(); // Dibuja la estrella
    glPopMatrix();
    
    //ESTRELLA 3.1
    glPushMatrix();
    glScalef(0.4, 0.4, 1.0);
    glTranslated(-1000, 300, 300);
    estrellas(); // Dibuja la estrella
    glPopMatrix();
    
    //ESTRELLA 2.2
    glPushMatrix();
    glScalef(0.3, 0.3, 1.0);
    glTranslated(650, 30, 300);
    estrellas(); // Dibuja la estrella
    glPopMatrix();
    
    //ESTRELLA 3.2
    glPushMatrix();
    glScalef(0.4, 0.4, 1.0);
    glTranslated(850, 300, 300);
    estrellas(); // Dibuja la estrella
    glPopMatrix();
    
    //ILUMINACI�N PARA LA ESFERA GRANDE
    GLfloat mat_ambient[] = {208.0f / 255.0f, 206.0f / 255.0f,207.0f/ 255.0f, 1.0f};//sombras
    GLfloat mat_diffuse[] = {208.0f / 255.0f, 206.0f / 255.0f,207.0f/ 255.0f, 0.8f};//relleno
    GLfloat mat_specular[] = {249.0f / 255.0f,144.0f / 255.0f, 15.0f / 255.0f, 1.0f};//color brillo
    GLfloat mat_shininess[] = {100.0f};//Tama�o de brillo desde 1 a 128

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);//sombras
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);//relleno
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);//color brillo
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    
    //ESFERA GRANDE
    glPushMatrix();
    glTranslatef(280, 310, 100);  // Translada al centro de la esfera grande
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);  // Rotaci�n alrededor del eje Z
    glutSolidSphere(80, 50, 50); // Dibuja la esfera con radio 
    glPopMatrix();
    
    //NUBE PEQUE�A
    glScalef(0.7f,0.7f,0.7f);
	glTranslatef(offsetX, 0.0f, 0.0f);
	//Llama a las texturas o sea las im�genes
	glBindTexture(GL_TEXTURE_2D,Mitextura_nube1.ID);
    glTranslatef(-200,270,0);
	glBegin(GL_QUADS);
	  glTexCoord2f(0,0);
	  glVertex3d(-120,120,0);
	  glTexCoord2f(1,0);
	  glVertex3d(120,120,0);
	  glTexCoord2f(1,1);
	  glVertex3d(120,-120,0);
	  glTexCoord2f(0,1);
	  glVertex3d(-120,-120,0);
	glEnd();
	
	//NUBE GRANDE
	glTranslatef(offsetX1, 0.0f, 0.0f);
	//Llama a las texturas o sea las im�genes
	glBindTexture(GL_TEXTURE_2D,Mitextura_nube2.ID);
    glTranslatef(-150,290,0);

	glBegin(GL_QUADS);
	  glTexCoord2f(0,0);
	  glVertex3d(-120,120,0);
	  glTexCoord2f(1,0);
	  glVertex3d(120,120,0);
	  glTexCoord2f(1,1);
	  glVertex3d(120,-120,0);
	  glTexCoord2f(0,1);
	  glVertex3d(-120,-120,0);
	glEnd();
	
  	glutSwapBuffers(); //Renderizacion para el uso de texturas	
}

void idlenube1() {
    // Actualiza la posici�n horizontal de nube1
    offsetX += speed;
    // Si offsetX llega al punto 0 o 100, cambia la direcci�n de movimiento
    if (offsetX <= 0.0f  ||  offsetX >= 115.0f) {
        speed = -speed;  // Cambia la direcci�n invirtiendo la velocidad
    }
    glutPostRedisplay(); // Marca la ventana para ser repintada en el pr�ximo ciclo de renderizado
}

void idlenube2() {
    // Actualiza la posici�n horizontal de nube2
    offsetX1 += speed1;
    // Si offsetX llega al punto 0 o 100, cambia la direcci�n de movimiento
    if (offsetX1 <= 0.0f  ||  offsetX1 >= 115.0f) {
        speed1 = -speed1;  // Cambia la direcci�n invirtiendo la velocidad
    }
    glutPostRedisplay(); // Marca la ventana para ser repintada en el pr�ximo ciclo de renderizado
}

// Funci�n de temporizador para la rotaci�n de la esfera grande
void rotateSphere(int value) {
    rotationAngle += 1.0f;  // Incrementa el �ngulo de rotaci�n
    glutPostRedisplay();  // Marca la ventana para ser repintada
    glutTimerFunc(16, rotateSphere, 0);  // Llama a la funci�n nuevamente despu�s de 16 ms (aproximadamente 60 FPS)
}

void reshape(int largo, int ancho){
	//Se aplica un casteo, que es una conversi�n forzada de un tipo de variable
	glViewport(0,0,(GLsizei)largo,(GLsizei)ancho);
	glMatrixMode(GL_PROJECTION); //Proyecta los gr�ficos
	glLoadIdentity();
	int t=500; //tama�o de los l�mites de la proyecci�n ortogr�fica
	glOrtho(-t,t,-t,t,-t,t); //par�metros de la caja de proyecci�n
	glMatrixMode(GL_MODELVIEW); //Matriz de transformaci�n general
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc,argv); //Conecta el m�todo main con la inicializaci�n de la libreria glut
	//El primer par�metro sirve para la memoria de color con el tema de transparencia
	//El segundo par�metro sirve para la memoria de gr�fico 3D con uso de texturas
	//El tercer par�metro sirve para la memoria de profundidad 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //Representaci�n de los gr�ficos en la ventana
	glutInitWindowSize(600,600); //Ancho y altura de la ventana de visualizacion
	glutInitWindowPosition(100,100); //Posici�n de la ventana
	glutCreateWindow("T3"); //T�tulo de la ventana
	init(); //Llama a la funcion init
	glutDisplayFunc(display); // llama a la funci�n display
	glutReshapeFunc(reshape); //Redimensionado, permite identificar los cambios o adaptaci�n
	//de la figura de acuerdo al tama�o de la ventana(aumenta o disminuye la proporci�n)
	glutIdleFunc(idlenube1); //Llamamos a la funci�n idlenube1
	
	glutTimerFunc(0, rotateSphere, 0);
	glutMainLoop(); //Permite mostrar cualquier cambio que se ha realizado en el modelado
	return 0;
}
