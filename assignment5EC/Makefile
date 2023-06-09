assignment5: assignment5.o CovidDB.o DataEntry.o
	g++ -o assignment5 assignment5.o CovidDB.o DataEntry.o

assignment5.o: CovidDB.h DataEntry.h assignment5.cpp
	g++ -c -Wall -Werror -pedantic assignment5.cpp

CovidDB.o: CovidDB.h CovidDB.cpp
	g++ -c -Wall -Werror -pedantic CovidDB.cpp

DataEntry.o: DataEntry.h DataEntry.cpp
	g++ -c -Wall -Werror -pedantic DataEntry.cpp