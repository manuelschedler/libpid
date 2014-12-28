LIBS=libpid.so

all: ${LIBS}

clean:
	rm ${LIBS}

libpid.so: pid.cpp
	g++ -fPIC -Wall -shared -Wl,-soname,$@.1 -o $@ $<
	ln -fs $@ $@.1
