# MultiKey
# See LICENSE file for copyright and license details.

CC=gcc
SRC=main.c widgets.c
OBJS=${SRC:.c=.o}
CFLAGS=-Wall -g -std=c11
OPTS=`pkg-config --cflags --libs gtk+-3.0 appindicator3-0.1`

SRCDIR=src
PREFIX=/usr/local
MANPREFIX=${PREFIX}/share/man
INFODIR=/usr/share/multikey

all: multikey

.c.o:
	${CC} -c ${CFLAGS} $< ${OPTS}

multikey: ${OBJS}
	${CC} -o $@ ${OBJS} ${OPTS}

clean:
	rm -f multikey *.o

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	mkdir -p ${INFODIR}
	cp -f multikey ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/multikey
	cp -f multikey_logo.png multikey_default.txt ${INFODIR}

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/multikey
	rm -f ${INFODIR}/multikey_logo.png
	rm -f ${INFODIR}/multikey_default.txt
