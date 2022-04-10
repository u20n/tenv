LK = -lcryptopp -lpthread -L./lib/core/
CR = -I./lib/core/inc
UT = -I./lib/uttu/inc

LC = ~/code/concord/core/src/
LU = ~/code/concord/uttu/

default: both

c:
	g++ -std=c++20 $(CR) client/client.cpp -o c.out $(LK) -lcore
	
h:
	g++ -std=c++20 $(CR) host/host.cpp -o h.out $(LK) -lcore

both: c h

rebuild: reset both

# might make sense to mark the chain files as write protected
# -- or at least a toggle
clean:
	rm -r client/chains/*
	rm -r host/chains/*

# go into local version of core & uttu, build, and then cp to ./lib/
# -- core needs uttu
reset:
	cd $(LU) && $(MAKE) clean && $(MAKE) linux_obj
	cp -r $(LU)build/exe/. ./lib/uttu/
	cp -r lib/uttu $(LC)../lib/
	cd $(LC) && $(MAKE) clean && $(MAKE)
	cp -r $(LC)../exe/. ./lib/core 
