main:
	gcc main.c -o a
	chown root:root a
	chmod u+s a
clean:
	rm a
