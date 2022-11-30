/**
 * @file 4a-tickets.cpp
 * @author Julie Anne(julie.cantillep@studerande.movant.se)
 * @brief Program that demonstrate a ticket generator system in C++
 * @version 1.0
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>  
#include <cstdlib>
#include <cstring>
#include <fstream>   
#include <sstream>   
#include <string>
#include <algorithm>
#include <list>
#include <unistd.h>
#include <getopt.h>

using namespace std;

/**
 * @brief Defines Booking Information and its properties
 * 
 */
/* -- Class implenting a real Booking Data -- */
class Booking
{
    private:
        int booknum;        /* Booking no. */
        string bdatestr;    /* Departure date */
        string btimestr;    /* Departure time */
        string bdepart;     /* Departure airport code */
        string bdest;       /* Destination airport code */
        string clas;        /* Class Category Definition */
        string fname;       /* Passenger's First Name */
        string lname;       /* Passenger's Last Name */
        
    public:
        Booking(){}  // empty constructor 
        /* -- Access Functions -- */
        /* Setters */
        void setBookNo(int bookNo) {booknum = bookNo;}
        void setBDate(string bDate) {bdatestr = bDate;}
        void setBTime(string bTime) {btimestr = bTime;}
        void setBDep(string bDep) {bdepart = bDep;}
        void setBDest(string bDest) {bdest = bDest;}
        // Prints Invalid Class if user enters Invalid Input out of these 3 categories
        void setBkClass(string bkClass) 
        {
            if(bkClass == "first" || bkClass == "business" || bkClass == "economy")
            {
                clas = bkClass;
            }
            else
            {
                clas = "Invalid Class";
            }
        }
        void setFName(string fName) {fname = fName;}
        void setLName(string lName) {lname = lName;}

        /* Getters */
        int getBookNum() {return booknum;}
        string getBDate() const {return bdatestr;}
        string getBTime() const {return btimestr;}
        string getBDep() const {return bdepart;}
        string getBDest() const {return bdest;}
        string getSeatClass() const {return clas;}
        string getFirstName() const {return fname;}
        string getLastName() const {return lname;}
};
/**
 * @brief Defines Flight Information and its properties
 * 
 */
/* -- Class implenting a real Flight Data -- */ 
class Flight
{
    private:
        int flightnum;        /* Flight no. */
        string fdepart;       /* Departure airport code */
        string fdestination;  /* Destination airport code */
        string fdatestr;      /* Date Departure */
        string ftimestr;      /* Time Departure */
        int fclass;           /* No. of First Class seats */
        int *farr;            /* Pointer for first class array */
        int bclass;           /* No. of Business Class seats */
        int *barr;            /* Pointer to business class array */
        int eclass;           /* No. of Economy Class seats */
        int *earr;            /* Pointer to economy class array */

    public:
        Flight(){}  // empty constructor 
        // Implement plane seat array using malloc()
        void allocateMem()
        {
            /* Allocate memory for class categories */
            // 7 is the number of seats in a row
            // replaces values of seats using memset() with 0 <- not occupied
            farr = (int*)malloc(fclass * sizeof(int) * 7); memset(farr, 0, fclass * sizeof(int) * 7);
            barr = (int*)malloc(bclass * sizeof(int) * 7); memset(barr, 0, bclass * sizeof(int) * 7);
            earr = (int*)malloc(eclass * sizeof(int) * 7); memset(earr, 0, eclass * sizeof(int) * 7);
        }
        /* -- Access Functions -- */
        /* Setters */
        void setFlightNo(int flightNo) {flightnum = flightNo;}
        void setFDepart(string fdep) {fdepart = fdep;}
        void setFDestination(string fdest) {fdestination = fdest;}
        void setFDate(string fdate) {fdatestr = fdate;}
        void setFTime(string ftime) {ftimestr = ftime;}
        void setFClass(int fClass) {fclass = fClass; }
        void setBClass(int bClass) {bclass = bClass; }
        void setEClass(int eClass) {eclass = eClass; }

        /* Getters */
        int getFlightno() {return flightnum;}
        string getFDeparture() const {return fdepart;}
        string getFDestination() const {return fdestination;}
        string getFDate() const {return fdatestr;}
        string getFTime() const {return ftimestr;}
        int getFSeats() {return fclass;}
        int *getFArr() {return farr;}
        int getBSeats() {return bclass;}
        int *getBArr() {return barr;}
        int getESeats() {return eclass;}
        int *getEArr() {return earr;}

};

class FlightManager
{
    private:
        /* Flight list definition */
        list<Flight*> getFlightsList;
    public:
        FlightManager() {}
        /* Method to store gathered flight list information */
        list<Flight*> getFlights();
        FlightManager(const char *filename);
};

/**
 * @brief Very important function that reads flight information from a file.
 * 
 * @param[in] filename Takes filename as a parameter
 * @param[out] FlightManager Reads from a file and store its information.
 */
FlightManager :: FlightManager(const char *filename)
{
    string line;
    int num_lines = 0;  // keeps track of lines in ifstream operation
    ifstream flightfile;
    flightfile.open(filename, ios::in);

    if(flightfile.is_open())
    {
        /* Read each line */
        while(getline(flightfile, line))
        {
            string fill;
            num_lines++;
            /* converts string into object using stringstream */
            stringstream ss(line);
            
            // allocate memory space for Flight class
            Flight *f = new Flight;
            /* Reads until seperated comma & stores in class variables */
            /* atoi = converts string value to integer value */
            getline(ss, fill, ',');
            f->setFlightNo(atoi(fill.c_str()));

            getline(ss, fill, ',');
            f->setFDepart(fill);

            getline(ss, fill, ',');
            f->setFDestination(fill);

            getline(ss, fill, ',');
            f->setFDate(fill);

            getline(ss, fill, ',');
            f->setFTime(fill);

            getline(ss, fill, ',');
            f->setFClass(atoi(fill.c_str()));

            getline(ss, fill, ',');
            f->setBClass(atoi(fill.c_str()));

            getline(ss, fill, ',');
            f->setEClass(atoi(fill.c_str()));

            // allocate seat function call 
            f->allocateMem();

            /* push_back() - appends values to Flight List */
            getFlightsList.push_back(f);
        }
        flightfile.close();
    }
    else
    {
        // if file fails to open
        cerr << "Error: " << strerror(errno);
        cerr << "Failed to open file: " << filename << endl;
    }
}
/**
 * @brief Iterate through the class list of Flight
 * 
 * @return list<Flight*> 
 */
list<Flight*> FlightManager :: getFlights()
{
    return getFlightsList;
}

class BookingManager 
{
    private:
        /* Booking list definition */
        list<Booking*>BookingList;
    public:
        BookingManager(){}   // Empty constructor 
        BookingManager(const char *filename);   // Function/Method definition
        /* Method to store gathered booking list information */
        list<Booking*>getBookings();
};

/**
 * @brief Very important function that reads booking information from a file.
 * 
 * @param[in] filename Takes file name as a parameter
 * @param[out] BookingManager Reads from a file and store its information.
 */
BookingManager :: BookingManager(const char *filename)
{
    string line;
    int num_lines = 0;   // keeps track of lines in ifstream operation
    ifstream bookfile;
    bookfile.open(filename, ios::in);
    if(bookfile.is_open())
    {
        /* Read each line */
        while(getline(bookfile, line))
        {
            num_lines++;
            /* converts string into object using stringstream */
            stringstream ss(line);
            string fill;
            // allocate memory space for Booking class
            Booking *b = new Booking;

            /* Reads until seperated comma & stores in class variables */
            /* atoi = converts string value to integer value */
            getline(ss, fill, ',');
            b->setBookNo(atoi(fill.c_str()));

            getline(ss, fill, ',');
            b->setBDate(fill);

            getline(ss, fill, ',');
            b->setBTime(fill);

            getline(ss, fill, ',');
            b->setBDep(fill);

            getline(ss, fill, ',');
            b->setBDest(fill);

            getline(ss, fill, ',');
            b->setBkClass(fill);

            getline(ss, fill, ',');
            b->setFName(fill);

            getline(ss, fill, ',');
            b->setLName(fill);

            /* push_back() - appends values to Flight List */
            BookingList.push_back(b);
        }
            bookfile.close();
    }
    else 
    {
        // if file fails to open
        cerr << "Failed to open file" << endl;
    }
    
}

list<Booking*> BookingManager :: getBookings()
{
    return BookingList;
}

/**
 * @brief Function that allocates seats for Flights
 * 
 * @param fp Read from flight class
 * @param bp Read from booking class
 * @param row initialize row 
 * @param seat initialize seat 
 * @return int 
 */
// Function for allocating seat in a flight
int allocate_seat(Flight *fp, Booking *bp, int *row, int *seat)
{
    // First Class Definition
    // seat and row pointer as referral
    int rn = 0, sn = 0; 
    // Assign class to array: first, business, economy
    if(bp->getSeatClass() == "first")
    {
        // define each row of 7 seats
        int *tmpfarr = fp->getFArr();
        for(int p = 0; p < fp->getFSeats() * 7; p++)
        {
            if(tmpfarr[p] == 0)
            {
                tmpfarr[p] = 1;
                sn = p + 1;
                rn = (int) p / 7 + 1;
                break;
            }
        }
    }

    // Business Class Definition
    if(bp->getSeatClass() == "business")
    {
        // define each row of 7 seats
        for(int p = 0; p < fp->getBSeats() * 7; p++)
        {
            int *tmpbarr = fp->getBArr();
            if(tmpbarr[p] == 0)
            {
                tmpbarr[p] = 1;
                // save previous class row & no. of seats to prevent overwrite
                sn = p + fp->getFSeats() * 7 + 1;
                rn = fp->getFSeats() + (int) p / 7 + 1;
                break;
            }
        }
    }
    
    // Economy Class Definition
    if(bp->getSeatClass() == "economy")
    {
        // define each row of 7 seats
        for(int p = 0; p < fp->getESeats() * 7; p++)
        {
            int *tmpearr = fp->getEArr();
            if(tmpearr[p] == 0)
            {
                tmpearr[p] = 1;
                // save previous class row & no. of seats to prevent overwrite
                sn = p + fp->getFSeats() * 7 + fp->getBSeats() * 7 + 1;
                rn = fp->getFSeats() + fp->getBSeats() + (int) p / 7 + 1; 
                break;
            }
        }
    }

    if(rn == 0 || sn == 0)
    {
        cerr << "Could not find class " << bp->getSeatClass() << " on this plane." << endl;
    }
    // refer rn & sn to pointer parameter
    *row = rn; 
    *seat = sn;
    return(1);
};

class TicketPrinter
{
    private:
        list<Flight *> :: iterator flight;
        list<Booking *> :: iterator book;
    public:
        TicketPrinter(list<Flight*> f, list<Booking*>b);
};

/**
 * @brief A class called Ticketprinter that prints out tickets
 * 
 * @param f List of flight as a parameter
 * @param b List of Booking as a parameter
 * @return TicketPrinter 
 */
/* -- Create Ticket for each line -- */
TicketPrinter :: TicketPrinter(list<Flight*> f, list<Booking*> b)
{
    int num_tickets = 0;  // count no. of tickets
    cout << "Writing tickets: " << endl;
    /* Iterate throgh booking list */
    for(book = b.begin(); book != b.end(); book++)
    {
        /* Iterate through flight list */
        for(flight = f.begin(); flight != f.end(); flight++)
        {
            /* data comparison */
            if((*flight)->getFDeparture() == (*book)->getBDep() && (*flight)->getFDestination() == (*book)->getBDest() && (*flight)->getFDate() == (*book)->getBDate() && (*flight)->getFTime() == (*book)->getBTime())
            {
                int row = 0, seat = 0;
                Flight *fp = *flight;
                Booking *bp = *book;
                /* allocate seat */
                if(allocate_seat(fp, bp, &row, &seat))
                {
                    fprintf(stdout, "[ticket-%d.txt]", bp->getBookNum());
                    cout << endl;
                    char filename[20];
                    // store ticket name for every .txt file
                    snprintf(filename, sizeof(filename), "ticket-%d.txt", bp->getBookNum());
                    ofstream file;
                    file.open(filename);
                    if(file.is_open())
                    {
                        // Prints to ticket file
                        file << "BOOKING: " << bp->getBookNum() << endl;
                        file << "FLIGHT: " << fp->getFlightno() << " DEPARTURE: " << bp->getBDep() << " DESTINATION: " << bp->getBDest() << " " << bp->getBDate() << " " << bp->getBTime() << endl;
                        file << "PASSENGER: " << bp->getFirstName() << " " << bp->getLastName() << endl;
                        file << "ROW: " << row << " SEAT: " << seat << endl;
                        num_tickets++; 
                    }
                    file.close();
                }
            }
        }
    }
    // prints total no. of tickets 
    cout << "Created " << num_tickets << " tickets" << endl;
}

class CancelFlight
{
    private:
        /* List of Flight list */
        list<Flight *> :: iterator flightit;
    public:
        CancelFlight(){}   // Constructor
        CancelFlight(list<Flight *> myFlights);  // Function/Method Definition
};

/**
 * @brief A function that cancels flights if the flight isn't full
 * 
 * @param myFlights Address of class members to Flight class
 * @return CancelFlight 
 */
/* prints cancelled flights to .txt file */
CancelFlight :: CancelFlight(list<Flight*> myFlights)
{
    Flight *fp;
    cout << "Cancelled Flights Printed..." << endl;
    ofstream flightfile;
    flightfile.open("Cancelled_flights.txt", ios::app);
    for(flightit = myFlights.begin(); flightit != myFlights.end(); flightit++)
    {
        fp = (*flightit); 
        int *tmpfarr = fp->getFArr(); // get index of first class
        int *tmpbarr = fp->getBArr(); // get index of business class
        int *tmpearr = fp->getEArr(); // get index of economy class
        // check if seats are free, refers to index[0] of flight seats
        if(tmpfarr[0] == 0 && tmpbarr[0] == 0 && tmpearr[0] == 0) 
        {
            // creates file to print cancelled flights
            flightfile << "Flight: " << (*flightit)->getFlightno() << " " << (*flightit)->getFTime() << " is cancelled." << endl;
        }
        else
        {
            flightfile << "Plane is not empty" << endl;
        }
    

    }
    flightfile.close();
}

/**
 * @brief Main entry point of the program.
 * This program prints out single ticket to each passenger through .txt file.
 * 
 * @param[in] argc Number of command line arguments.
 * @param[in] argv An array of character pointers listing all the arguments.
 * @param[out] returns 0 on success.
 */
int main(int argc, char *argv[])
{
    /**
     * @brief Create ticket using getopt() by reading files
     * 
     */
    // Access data information using getopt() function
    try
    {
        int opt;
        FlightManager flights = nullptr;
        BookingManager bookings = nullptr;

        while((opt = getopt(argc, argv, ":f:b:")) != -1)
        {
            switch(opt)
            {
                case 'f':
                    // input for flight file
                    flights = optarg;
                    break;
                case 'b':
                    // input for booking file
                    bookings = optarg;
                    break;
                case '?':
                    // if an option doesn't exist, will print error
                    fprintf(stderr, "Unknown option: %c\n", optopt);
                    break;
                case ':':
                    // prints missing arg for specific option
                    fprintf(stderr, "Missing argc for %c\n", optopt);
                    break;
                default:
                    // if all else fails in the options
                    fprintf(stderr, "Usage:  .\4a-tickets.exe[ -f flight-file ] [ -b booking-file ]\n");
                    break;
            }
        }

        TicketPrinter printer(flights.getFlights(), bookings.getBookings());
        CancelFlight cancel(flights.getFlights()); 
    }
    // if operator fails, this message pops
    catch(exception &e)
    {
        cerr << "Exception occured!" << strerror(errno);
    }


    return 0;
}