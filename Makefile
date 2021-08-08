shk:
	gcc main.c -o a
	chown root:root a
	chmod u+s a
clean: shk
	rm a
test:
	gcc test.c -o test
