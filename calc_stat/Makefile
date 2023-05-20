.PHONY: all

Folders = ../obj/ ../build/

OPT_FLAGS = -O1 -mavx -mavx2 -lm

DEBUG_FLAGS = -march=native -D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -fsanitize=address,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

FLAGS = $(OPT_FLAGS)

CC = gcc

all: hashmap

clean:
	find .. -name "*.o" -delete

folders:
	mkdir -p $(Folders)

hashstat: ../obj/hashmap.o ../obj/input.o ../obj/list.o ../obj/hash.o ../obj/hashstat.o ../obj/hashstat_main.o 
	$(CC) ../obj/hashmap.o ../obj/input.o ../obj/list.o ../obj/hash.o ../obj/hashstat.o ../obj/hashstat_main.o ../obj/list_find.o -o ../build/hashstat $(FLAGS)

searchstat: ../obj/hashmap.o ../obj/input.o ../obj/list.o ../obj/hash.o ../obj/searchstat.o ../obj/searchstat_main.o 
	$(CC) ../obj/hashmap.o ../obj/input.o ../obj/list.o ../obj/hash.o ../obj/searchstat.o ../obj/searchstat_main.o ../obj/list_find.o -o ../build/searchstat $(FLAGS)

../obj/hashmap.o: ../src/hashmap.cpp ../src/hashmap.h ../src/hash.h ../src/list.h ../src/input.h
	$(CC) -c ../src/hashmap.cpp -o ../obj/hashmap.o  $(FLAGS)

../obj/hash.o: ../src/hash.cpp ../src/hash.h
	$(CC) -c ../src/hash.cpp -o ../obj/hash.o  $(FLAGS)

../obj/input.o: ../src/input.cpp ../src/input.h ../src/hashmap.h
	$(CC) -c ../src/input.cpp -o ../obj/input.o $(FLAGS)

../obj/list.o: ../src/list.cpp ../src/list.h
	$(CC) -c ../src/list.cpp -o ../obj/list.o $(FLAGS)

../obj/list_find.o: ../src/list_find.asm
	nasm -f elf64 ../src/list_find.asm -o ../obj/list_find.o

../obj/hashstat.o: hash/hash.cpp hash/hash.h ../src/hashmap.h ../src/hash.h ../src/input.h
	$(CC) -c hash/hash.cpp -o ../obj/hashstat.o $(FLAGS)

../obj/hashstat_main.o: hash/main.cpp hash/hash.h ../src/hashmap.h ../src/hash.h ../src/input.h
	$(CC) -c hash/main.cpp -o ../obj/hashstat_main.o  $(FLAGS)

../obj/searchstat.o: search/bench.cpp search/bench.h ../src/hashmap.h ../src/hash.h ../src/input.h
	$(CC) -c search/bench.cpp -o ../obj/searchstat.o $(FLAGS)

../obj/searchstat_main.o: search/main.cpp search/bench.h ../src/hashmap.h ../src/hash.h ../src/input.h
	$(CC) -c search/main.cpp -o ../obj/searchstat_main.o  $(FLAGS)