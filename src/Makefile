.PHONY: all

Folders = ../obj/ ../build/

OPT_FLAGS = -O3 -mavx -mavx2 -lm

DEBUG_FLAGS = -march=native -D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -fsanitize=address,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

FLAGS = $(DEBUG_FLAGS)

CC=gcc

all: hashmap

clean:
	find .. -name "*.o" -delete

folders:
	mkdir -p $(Folders)

hashmap: ../obj/hashmap.o ../obj/input.o ../obj/main.o ../obj/list.o ../obj/hash.o
	$(CC) ../obj/hashmap.o ../obj/input.o ../obj/list.o ../obj/main.o ../obj/hash.o -o ../build/hashmap $(FLAGS)

tests: ../obj/hashmap.o ../obj/input.o ../obj/list.o ../obj/hash.o ../obj/tests.o ../obj/tests_main.o
	$(CC) ../obj/hashmap.o ../obj/input.o ../obj/list.o ../obj/hash.o ../obj/tests.o ../obj/tests_main.o -o ../build/test $(FLAGS)

../obj/hashmap.o: hashmap.cpp hashmap.h hash.h list.h input.h
	$(CC) -c hashmap.cpp -o ../obj/hashmap.o  $(FLAGS)

../obj/hash.o: hash.cpp hash.h
	$(CC) -c hash.cpp -o ../obj/hash.o  $(FLAGS)

../obj/main.o: main.cpp hashmap.h hash.h input.h
	$(CC) -c main.cpp -o ../obj/main.o  $(FLAGS)

../obj/input.o: input.cpp input.h hashmap.h
	$(CC) -c input.cpp -o ../obj/input.o $(FLAGS)

../obj/list.o: list.cpp list.h
	$(CC) -c list.cpp -o ../obj/list.o $(FLAGS)

../obj/tests.o: ../test/test.cpp ../test/test.h
	$(CC) -c ../test/test.cpp -o ../obj/tests.o $(FLAGS)

../obj/tests_main.o: ../test/main.cpp ../test/test.h hashmap.h hash.h input.h
	$(CC) -c ../test/main.cpp -o ../obj/tests_main.o  $(FLAGS)