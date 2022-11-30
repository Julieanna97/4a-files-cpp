all:	
	g++ 4a-tickets.cpp -o ticket
	
run:
	./ticket flights.csv bookings.csv
	cat ticket-2011.txt
  	cat Cancelled-flights.csv
