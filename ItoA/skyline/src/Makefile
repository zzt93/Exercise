CFLAGS=-Wall -lGLU -lglut -g
skyline: Merge.o OpenGL_Draw.o main.c skyline.h
	gcc $(CFLAGS) -o skyline Merge.o OpenGL_Draw.o main.c
Merge.o: Merge.c skyline.h
	gcc $(CFLAGS) -o Merge.o -c Merge.c
OpenGL_Draw.o: OpenGL_Draw.c skyline.h
	gcc $(CFLAGS) -o OpenGL_Draw.o -c OpenGL_Draw.c
clean:
	rm -f *.o *~ skyline