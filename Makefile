LK = -lcryptopp -lpthread -L./lib/uttu -L./lib/core/ -L../core/proto/hclc/bin
CR = -I./lib/core/inc -I../core/proto/hclc/inc

LC = ~/code/concord/core/src/
LU = ~/code/concord/uttu/

default: c 

c:
	g++ -std=c++20 $(CR) main.cpp -o c.out $(LK) -lcore -lhclc -luttu
	
rebuild: reset c

# might make sense to mark the chain files as write protected
# -- or at least a toggle
clean:
	rm -r client/chains/*

# rebuild only the protocols
rbp:
	cd $(LC) && $(MAKE) protocols

# go into local version of core & uttu, build, and then cp to ./lib/
# -- core needs uttu
reset:
	rm -rf lib/*
	cd $(LU) && $(MAKE) clean && $(MAKE) linux
	cp -r $(LU)build/exe/. ./lib/uttu/
	cp -r lib/uttu $(LC)../lib/
	cd $(LC) && $(MAKE) clean && $(MAKE)
	cp -r $(LC)../build/exe/. ./lib/core 
