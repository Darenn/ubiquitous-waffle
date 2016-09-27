# Numéro du TDM
TDM_NUMERO := 3

## Compilation automatique de source C
# Compilteur
CC := gcc
#options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb -Wno-unused-but-set-parameter -Wno-unused-variable -Wno-unused-parameter -Wno-abi
# Règle de compilation

all : test_arbres_int test_arbres_sigle

test_arbres_int : test_arbres_int.o arbres.o
	$(CC) $(CFLAGS) -o $@ $^	


test_arbres_sigle : test_arbres_sigle.o arbres.o
	$(CC) $(CFLAGS) -o $@ $^	

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

test_arbres : test_arbres_int
	./test_arbres_int; diff -s -Z test_arbres_int_out.txt test_arbres_int_out_acomparer.txt


memoire_int : test_arbres_int
	valgrind --leak-check=full ./test_arbres_int

test_sigle : test_arbres_sigle
	./test_arbres_sigle; diff -s -Z test_arbres_sigle_out.txt test_arbres_sigle_out_acomparer.txt


memoire_sigle : test_arbres_sigle
	valgrind --leak-check=full ./test_arbres_sigle


clean:
	rm *.o test_arbres_int test_arbres_sigle test_arbres_sigle_out.txt test_arbres_int_out.txt

#
# Pour faire l'archive de remise
#
TGZ_FILES :=  *.c *.h ?akefile cr.pdf
TDM_DIR := TDM$(TDM_NUMERO)

rendu :
	[ -e cr.pdf ] || echo > cr.pdf
	cd .. ; tar czf $(TDM_DIR)/rendu.tgz $(TGZ_FILES:%=$(TDM_DIR)/%)

