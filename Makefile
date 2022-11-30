all:	
	g++ 4a-tickets.cpp -o ticket
	
run:
	./ticket flights.csv bookings.csv
