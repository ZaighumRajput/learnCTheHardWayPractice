
CFLAGS=-g -02 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
HEADERS=$(wildcard src/**/*.h src/*.h)
OBJECTS=$(patsubt %.c, %.o, $(SOURCES))

TEST_SRC=$(wildcard test/*_tests.c)
TESTS = $(patsubt %.c,%, $(TEST_SRC))

TARGET = build/libYOUR_LIBRARY.a

SO_TARGET=$(patsubt %.a, %.so, $(TARGET))

#The Target Build

all : $(TARGET) $(SO_TARGET) tests

dev = CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)

dev: all

$(TESTS): $(TARGET) $(SO_TARGET)

$(TARGET): CLAGS += -fPIC
	#$@ means the current target
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build: 
	@mkdir -p build
	@mkdir -p bin

#The Unit Tests
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

#The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dYSM" -print`

#The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

#The Checker
check:
	@echo Files with potentially dangerous functions
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
		stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true

