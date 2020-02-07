default:
	@echo creating all available utilities...
	g++ -o mymv FileManager.cpp mymv.cpp
	g++ -o mycp FileManager.cpp mycp.cpp
	g++ -o myls FileManager.cpp myls.cpp
	g++ -o mycat FileManager.cpp mycat.cpp
	g++ -o myrm FileManager.cpp myrm.cpp
	g++ -o mydiff FileManager.cpp mydiff.cpp
	g++ -o mystat FileManager.cpp mystat.cpp

mymv: FileManager.cpp mymv.cpp
	@echo creating mymv...
	g++ -o mymv FileManager.cpp mymv.cpp

mycp: FileManager.cpp mycp.cpp
	@echo creating mycp...
	g++ -o mycp FileManager.cpp mycp.cpp


myls: FileManager.cpp myls.cpp
	@echo creating myls...
	g++ -o myls FileManager.cpp myls.cpp

mycat: FileManager.cpp mycat.cpp
	@echo creating mycat...
	g++ -o mycat FileManager.cpp mycat.cpp

myrm: FileManager.cpp myrm.cpp
	@echo creating myrm...
	g++ -o mymv FileManager.cpp myrm.cpp

mydiff: FileManager.cpp mydiff.cpp
	@echo creating mydiff...
	g++ -o mymv FileManager.cpp mydiff.cpp

mystat: FileManager.cpp mystat.cpp
	@echo creating mystat...
	g++ -o mymv FileManager.cpp mystat.cpp

clean:
	@echo deleting all executable files...
	rm mycat mycp mydiff myls mymv myrm mystat
