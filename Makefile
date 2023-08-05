# MultiKey
# See LICENSE file for copyright and license details.

CC=gcc
SRC=main.c widgets.c
OBJS=${SRC:.c=.o}
OPTS=`pkg-config --cflags --libs gtk+-3.0 appindicator3-0.1`
PREFIX=/usr/local
MANPREFIX=${PREFIX}/share/man
CFLAGS=-g -std=c11

all: multiKey

.c.o:
	${CC} -c ${CFLAGS} $< ${OPTS}

multiKey: ${OBJS}
	${CC} -o $@ ${OBJS} ${OPTS}

clean:
	rm -f multiKey *.o

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f multiKey ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/multiKey
	# copy logo.png and keyboard.txt to $HOME/.local/share/

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/multiKey
