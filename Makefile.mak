run: main.o login.o
  gcc -o run main.o login.o

main.o: main.c
  gcc -c main.c

login.o: login.c
  gcc -c login.c

clean:
  rm -f *.o run
