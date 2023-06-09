assignment4: assignment4.o CovidDB.o DataEntry.o
	g++ -o assignment4 assignment4.o CovidDB.o DataEntry.o

assignment4.o: CovidDB.h DataEntry.h assignment4.cpp
	g++ -c -Wall -Werror -pedantic assignment4.cpp

CovidDB.o: CovidDB.h CovidDB.cpp
	g++ -c -Wall -Werror -pedantic CovidDB.cpp

DataEntry.o: DataEntry.h DataEntry.cpp
	g++ -c -Wall -Werror -pedantic DataEntry.cpp