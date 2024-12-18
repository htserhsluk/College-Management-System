run: main.o
	gcc main.c admin.c faculty.c notice_board.c SQL.c student.c -o main -lmysqlclient

clean:
	rm -f *.o run