LNK = -lcryptopp -lpthread -L./lib/
CR = -I./lib/core_inc
UT = -I./lib/uttu_inc
c:
	g++ -std=c++20 $(CR) client/run.cpp -o c.out $(LNK) -lcore

h:
	g++ -std=c++20 $(CR) host/run.cpp -o h.out $(LNK) -lcore

n:
	g++ -std=c++20 $(UT) net/run.cpp -o n.out $(LNK) -luttu
	
clean:
	rm client/chains/GbJYVuHBUMqDTP/ItZsjrb0O/*
	rm host/chains/GbJYVuHBUMqDTP/ItZsjrb0O/*

build:
	$(MAKE) -C lib/builds/uttu linux_obj && \
	cp -r lib/builds/uttu/exe/inc/ lib/builds/core/lib/. && \
	cp lib/builds/uttu/exe/libuttu.o lib/builds/core/lib/. && \
	$(MAKE) -C lib/builds/core/src static_unix

update: build
	cp -r lib/builds/core/exe/inc lib/core_inc
	cp lib/builds/core/exe/libcore.a lib/. 
