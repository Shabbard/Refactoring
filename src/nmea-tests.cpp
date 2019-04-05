#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ParseNMEATests
#include <boost/test/unit_test.hpp>

#include <stdexcept>

#include "logs.h"
#include "parseNMEA.h"

using namespace GPS;

/////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( IsValidSentence )

BOOST_AUTO_TEST_CASE( WellFormedSentences )
{
    BOOST_CHECK( isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*69") );
    BOOST_CHECK( isValidSentence("$GPGGA,113922.000,3722.5993,N,00559.2458,W,1,0,,4.0,M,,M,,*40") );
    BOOST_CHECK( isValidSentence("$GPRMC,113922.000,A,3722.5993,N,00559.2458,W,0.000,0.00,150914,,A*62") );
}

BOOST_AUTO_TEST_CASE( IncorrectChecksum )
{
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*24") );
    BOOST_CHECK( ! isValidSentence("$GPGGA,113922.000,3722.5993,N,00559.2458,W,1,0,,4.0,M,,M,,*41") );
    BOOST_CHECK( ! isValidSentence("$GPRMC,113922.000,A,3722.5993,N,00559.2458,W,0.000,0.00,150914,,A*97") );
}

BOOST_AUTO_TEST_CASE( CorrectChecksumsWithUppercaseHexDigits )
{
    BOOST_CHECK( isValidSentence("$GPGLL,5430.49,N,106.74,W,163958*5E") );
    BOOST_CHECK( isValidSentence("$GPGGA,114530.000,3722.6279,N,00559.1566,W,1,0,,1.0,M,,M,,*4E") );
    BOOST_CHECK( isValidSentence("$GPRMC,115856.000,A,3722.6710,N,00559.3014,W,0.000,0.00,150914,,A*6D") );
}

BOOST_AUTO_TEST_CASE( IncorrectChecksumsWithUppercaseHexDigits )
{
    BOOST_CHECK( ! isValidSentence("$GPGLL,5430.46,N,106.94,W,164623*4B") );
    BOOST_CHECK( ! isValidSentence("$GPGGA,114530.000,3722.6279,N,00559.1566,W,1,0,,1.0,M,,M,,*8F") );
    BOOST_CHECK( ! isValidSentence("$GPRMC,115856.000,A,3722.6710,N,00559.3014,W,0.000,0.00,150914,,A*6F") );
}

BOOST_AUTO_TEST_CASE( CorrectChecksumsWithLowercaseHexDigits )
{
    BOOST_CHECK( isValidSentence("$GPGLL,5430.49,N,106.74,W,163958*5e") );
    BOOST_CHECK( isValidSentence("$GPGGA,114530.000,3722.6279,N,00559.1566,W,1,0,,1.0,M,,M,,*4e") );
    BOOST_CHECK( isValidSentence("$GPRMC,115856.000,A,3722.6710,N,00559.3014,W,0.000,0.00,150914,,A*6d") );
}

BOOST_AUTO_TEST_CASE( IncorrectChecksumsWithLowercaseHexDigits )
{
    BOOST_CHECK( ! isValidSentence("$GPGLL,5430.46,N,106.94,W,164623*7b") );
    BOOST_CHECK( ! isValidSentence("$GPGGA,114530.000,3722.6279,N,00559.1566,W,1,0,,1.0,M,,M,,*2a") );
    BOOST_CHECK( ! isValidSentence("$GPRMC,115856.000,A,3722.6710,N,00559.3014,W,0.000,0.00,150914,,A*1d") );
}

BOOST_AUTO_TEST_CASE( IllFormedSentences )
{
    BOOST_CHECK( ! isValidSentence("") );
    BOOST_CHECK( ! isValidSentence("$") );
    BOOST_CHECK( ! isValidSentence("$G") );
    BOOST_CHECK( ! isValidSentence("$GP") );
    BOOST_CHECK( ! isValidSentence("$GPG") );
    BOOST_CHECK( ! isValidSentence("$GPGL") );
    BOOST_CHECK( ! isValidSentence("$GPGLL") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,*") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,*1") );
    BOOST_CHECK( ! isValidSentence("Hello World") );
    BOOST_CHECK( ! isValidSentence("GPGLL,5425.31,N,107.03,W,82610*69") );
    BOOST_CHECK( ! isValidSentence("$GPGLL5425.31,N,107.03,W,82610*69") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*6") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*693") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*he") );
}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////////////////////////

/* It is bad practice to add things to the standard namespace,
 * but it is the only easy work-around here.
 * TODO: find a better solution.
 */
namespace std
{
    // Define stream insertion to allow use of BOOST_CHECK_EQUAL().
    std::ostream & operator<<(std::ostream & os, const std::vector<string> v)
    {
        os << '{';
        for (auto it = v.begin(); it != v.end(); ++it)
        {
            if (it != v.begin()) os << ',';
            os << *it;
        }
        os << '}';
        return os;
    }
}

BOOST_AUTO_TEST_SUITE( DecomposeSentence )

BOOST_AUTO_TEST_CASE( GLL )
{
    NMEAPair decomposedSentence = decomposeSentence("$GPGLL,5425.31,N,107.03,W,82610*69");

    BOOST_CHECK_EQUAL( decomposedSentence.first , std::string("GPGLL") );

    BOOST_CHECK_EQUAL( decomposedSentence.second , std::vector<std::string>({"5425.31","N","107.03","W","82610"}) );
}

BOOST_AUTO_TEST_CASE( GGA )
{
    NMEAPair decomposedSentence = decomposeSentence("$GPGGA,114530.000,3722.6279,N,00559.1566,W,1,0,,1.0,M,,M,,*4E");

    BOOST_CHECK_EQUAL( decomposedSentence.first , std::string("GPGGA") );

    BOOST_CHECK_EQUAL( decomposedSentence.second , std::vector<std::string>({"114530.000","3722.6279","N","00559.1566","W","1","0","","1.0","M","","M","",""}) );
}

BOOST_AUTO_TEST_CASE( RMC )
{
    NMEAPair decomposedSentence = decomposeSentence("$GPRMC,115856.000,A,3722.6710,N,00559.3014,W,0.000,0.00,150914,,A*6d");

    BOOST_CHECK_EQUAL( decomposedSentence.first , std::string("GPRMC") );

    BOOST_CHECK_EQUAL( decomposedSentence.second , std::vector<std::string>({"115856.000","A","3722.6710","N","00559.3014","W","0.000","0.00","150914","","A"}) );
}

// Unsupported formats should decompose okay, but they will be rejected by extractPosition().
BOOST_AUTO_TEST_CASE( UnsupportedFormat )
{
    NMEAPair decomposedSentence = decomposeSentence("$GPMSS,55,27,318.0,100,*66");

    BOOST_CHECK_EQUAL( decomposedSentence.first , std::string("GPMSS") );

    BOOST_CHECK_EQUAL( decomposedSentence.second , std::vector<std::string>({"55","27","318.0","100",""}) );
}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( ExtractPosition )

const double epsilon = 0.0001;
const double percentageAccuracy = 0.0001;

BOOST_AUTO_TEST_CASE( GLL_NW )
{
    NMEAPair decomposedSentence = { "GPGLL", {"5425.31","N","107.03","W","82610"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , ddmTodd("5425.31") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , -ddmTodd("107.03") , percentageAccuracy );
    BOOST_CHECK_SMALL( pos.elevation() , epsilon );
}

BOOST_AUTO_TEST_CASE( GLL_NE )
{
    NMEAPair decomposedSentence = { "GPGLL", {"5425.31","N","107.03","E","82610"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , ddmTodd("5425.31") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , ddmTodd("107.03") , percentageAccuracy );
    BOOST_CHECK_SMALL( pos.elevation() , epsilon );
}

BOOST_AUTO_TEST_CASE( GLL_SE )
{
    NMEAPair decomposedSentence = { "GPGLL", {"5425.31","S","107.03","E","82610"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -ddmTodd("5425.31") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , ddmTodd("107.03") , percentageAccuracy );
    BOOST_CHECK_SMALL( pos.elevation() , epsilon );
}

BOOST_AUTO_TEST_CASE( GLL_SW )
{
    NMEAPair decomposedSentence = { "GPGLL", {"5425.31","S","107.03","W","82610"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -ddmTodd("5425.31") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , -ddmTodd("107.03") , percentageAccuracy );
    BOOST_CHECK_SMALL( pos.elevation() , epsilon );
}

BOOST_AUTO_TEST_CASE( RMC_NW )
{
    NMEAPair decomposedSentence = { "GPRMC", {"115856.000","A","3722.6710","N","00559.3014","W","0.000","0.00","150914","","A"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , ddmTodd("3722.6710") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , -ddmTodd("00559.3014") , percentageAccuracy );
    BOOST_CHECK_SMALL( pos.elevation() , epsilon );
}

BOOST_AUTO_TEST_CASE( RMC_NE )
{
    NMEAPair decomposedSentence = { "GPRMC", {"115856.000","A","3722.6710","N","00559.3014","E","0.000","0.00","150914","","A"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , ddmTodd("3722.6710") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , ddmTodd("00559.3014") , percentageAccuracy );
    BOOST_CHECK_SMALL( pos.elevation() , epsilon );
}

BOOST_AUTO_TEST_CASE( RMC_SE )
{
    NMEAPair decomposedSentence = { "GPRMC", {"115856.000","A","3722.6710","S","00559.3014","E","0.000","0.00","150914","","A"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -ddmTodd("3722.6710") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , ddmTodd("00559.3014") , percentageAccuracy );
    BOOST_CHECK_SMALL( pos.elevation() , epsilon );
}

BOOST_AUTO_TEST_CASE( RMC_SW )
{
    NMEAPair decomposedSentence = { "GPRMC", {"115856.000","A","3722.6710","S","00559.3014","W","0.000","0.00","150914","","A"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -ddmTodd("3722.6710") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , -ddmTodd("00559.3014") , percentageAccuracy );
    BOOST_CHECK_SMALL( pos.elevation() , epsilon );
}

BOOST_AUTO_TEST_CASE( GGA_NW )
{
    NMEAPair decomposedSentence = { "GPGGA", {"170834","4124.8963","N","08151.6838","W","1","05","1.5","280.2","M","-34.0","M","",""} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , ddmTodd("4124.8963") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , -ddmTodd("08151.6838") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.elevation() , 280.2 , percentageAccuracy );
}

BOOST_AUTO_TEST_CASE( GGA_NE )
{
    NMEAPair decomposedSentence = { "GPGGA", {"170834","4124.8963","N","08151.6838","E","1","05","1.5","280.2","M","-34.0","M","",""} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , ddmTodd("4124.8963") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , ddmTodd("08151.6838") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.elevation() , 280.2 , percentageAccuracy );
}

BOOST_AUTO_TEST_CASE( GGA_SE )
{
    NMEAPair decomposedSentence = { "GPGGA", {"170834","4124.8963","S","08151.6838","E","1","05","1.5","280.2","M","-34.0","M","",""} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -ddmTodd("4124.8963") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , ddmTodd("08151.6838") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.elevation() , 280.2 , percentageAccuracy );
}

BOOST_AUTO_TEST_CASE( GGA_SW )
{
    NMEAPair decomposedSentence = { "GPGGA", {"170834","4124.8963","S","08151.6838","W","1","05","1.5","280.2","M","-34.0","M","",""} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -ddmTodd("4124.8963") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , -ddmTodd("08151.6838") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.elevation() , 280.2 , percentageAccuracy );
}

BOOST_AUTO_TEST_CASE( GGA_NegativeElevation )
{
    NMEAPair decomposedSentence = { "GPGGA", {"170834","4124.8963","S","08151.6838","W","1","05","1.5","-280.2","M","-34.0","M","",""} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -ddmTodd("4124.8963") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.longitude() , -ddmTodd("08151.6838") , percentageAccuracy );
    BOOST_CHECK_CLOSE( pos.elevation() , -280.2 , percentageAccuracy );
}

BOOST_AUTO_TEST_CASE( UnsupportedFormat )
{
    NMEAPair decomposedSentence = { "GPMSS", {"55","27","318.0","100",""} };
    BOOST_CHECK_THROW( extractPosition(decomposedSentence) , std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( EmptyFieldVector )
{
    NMEAPair decomposedSentenceGLL = { "GPGLL", {} };
    BOOST_CHECK_THROW( extractPosition(decomposedSentenceGLL) , std::invalid_argument );

    NMEAPair decomposedSentenceRMC = { "GPRMC", {} };
    BOOST_CHECK_THROW( extractPosition(decomposedSentenceRMC) , std::invalid_argument );

    NMEAPair decomposedSentenceGGA = { "GPGGA", {} };
    BOOST_CHECK_THROW( extractPosition(decomposedSentenceGGA) , std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( MissingFieldsGLL )
{
    NMEAPair missingN = { "GPGLL", {"5425.31","107.03","E","82610"} };
    BOOST_CHECK_THROW( extractPosition(missingN) , std::invalid_argument );

    NMEAPair missingE = { "GPGLL", {"5425.31","N","107.03","82610"} };
    BOOST_CHECK_THROW( extractPosition(missingE) , std::invalid_argument );

    NMEAPair missingLat = { "GPGLL", {"N","107.03","E","82610"} };
    BOOST_CHECK_THROW( extractPosition(missingLat) , std::invalid_argument );

    NMEAPair missingLon = { "GPGLL", {"5425.31","N","E","82610"} };
    BOOST_CHECK_THROW( extractPosition(missingLon) , std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( MissingFieldsRMC )
{
    NMEAPair missingN = { "GPRMC", {"115856.000","A","3722.6710","00559.3014","E","0.000","0.00","150914","","A"} };
    BOOST_CHECK_THROW( extractPosition(missingN) , std::invalid_argument );

    NMEAPair missingE = { "GPRMC", {"115856.000","A","3722.6710","S","00559.3014","0.000","0.00","150914","","A"} };
    BOOST_CHECK_THROW( extractPosition(missingE) , std::invalid_argument );

    NMEAPair missingLat = { "GPRMC", {"115856.000","A","S","00559.3014","E","0.000","0.00","150914","","A"} };
    BOOST_CHECK_THROW( extractPosition(missingLat) , std::invalid_argument );

    NMEAPair missingLon = { "GPRMC", {"115856.000","A","3722.6710","S","E","0.000","0.00","150914","","A"} };
    BOOST_CHECK_THROW( extractPosition(missingLon) , std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( MissingFieldsGGA )
{
    NMEAPair missingN = { "GPGGA", {"170834","4124.8963","08151.6838","W","1","05","1.5","280.2","M","-34.0","M","",""} };
    BOOST_CHECK_THROW( extractPosition(missingN) , std::invalid_argument );

    NMEAPair missingW = { "GPGGA", {"170834","4124.8963","N","08151.6838","1","05","1.5","280.2","M","-34.0","M","",""} };
    BOOST_CHECK_THROW( extractPosition(missingN) , std::invalid_argument );

    NMEAPair missingM = { "GPGGA", {"170834","4124.8963","N","08151.6838","W","1","05","1.5","",""} };
    BOOST_CHECK_THROW( extractPosition(missingN) , std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( InvalidFieldData )
{
    NMEAPair invalidGLL_N = { "GPGLL", {"three","N","107.03","W","82610"} };
    BOOST_CHECK_THROW( extractPosition(invalidGLL_N) , std::invalid_argument );

    NMEAPair invalidRMC_W = { "GPRMC", {"115856.000","A","3722.6710","N","?&*","W","0.000","0.00","150914","","A"} };
    BOOST_CHECK_THROW( extractPosition(invalidRMC_W) , std::invalid_argument );

    NMEAPair invalidGGA_M = { "GPGGA", {"170834","4124.8963","N","08151.6838","W","1","05","1.5","zero","M","-34.0","M","",""} };
    BOOST_CHECK_THROW( extractPosition(invalidGGA_M) , std::invalid_argument );
}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( RouteFromNMEALog )

const double epsilon = 0.0001;
const double percentageAccuracy = 0.0001;

BOOST_AUTO_TEST_CASE( Log_GLL )
{
    std::vector<Position> route = routeFromNMEALog(LogFiles::NMEALogsDir + "gll.log");

    BOOST_CHECK_EQUAL( route.size() , 1091 );

    // $GPGLL,5425.32,N,107.11,W,82319*65
    BOOST_CHECK_CLOSE( route[0].latitude() , ddmTodd("5425.32") , percentageAccuracy );
    BOOST_CHECK_CLOSE( route[0].longitude() , -ddmTodd("107.11") , percentageAccuracy );

    // $GPGLL,5430.32,N,106.39,W,154912*51
    BOOST_CHECK_CLOSE( route[1000].latitude() , ddmTodd("5430.32") , percentageAccuracy );
    BOOST_CHECK_CLOSE( route[1000].longitude() , -ddmTodd("106.39") , percentageAccuracy );
}

BOOST_AUTO_TEST_CASE( Log_GGA_RMC )
{
    std::vector<Position> route = routeFromNMEALog(LogFiles::NMEALogsDir + "gga_rmc.log");

    BOOST_CHECK_EQUAL( route.size() , 632 );

    // $GPGGA,094627.000,3723.1622,N,00559.5788,W,1,0,,30.0,M,,M,,*7A
    BOOST_CHECK_CLOSE( route[0].latitude() , ddmTodd("3723.1622") , percentageAccuracy );
    BOOST_CHECK_CLOSE( route[0].longitude() , -ddmTodd("00559.5788") , percentageAccuracy );
    BOOST_CHECK_CLOSE( route[0].elevation() , 30 , percentageAccuracy );

    // $GPRMC,113720.000,A,3722.5563,N,00559.2403,W,0.000,0.00,150914,,A*63
    BOOST_CHECK_CLOSE( route[501].latitude() , ddmTodd("3722.5563") , percentageAccuracy );
    BOOST_CHECK_CLOSE( route[501].longitude() , -ddmTodd("00559.2403") , percentageAccuracy );
}

BOOST_AUTO_TEST_CASE( AnnotatedLog_GGA_RMC )
{
    std::vector<Position> route = routeFromNMEALog(LogFiles::NMEALogsDir + "gga_rmc-annotated.log");

    BOOST_CHECK_EQUAL( route.size() , 1826 ); // The header and blank line should be discarded

    // $GPGGA,091138.000,5320.4819,N,00136.3714,W,1,0,,395.0,M,,M,,*46
    BOOST_CHECK_CLOSE( route[0].latitude() , ddmTodd("5320.4819") , percentageAccuracy );
    BOOST_CHECK_CLOSE( route[0].longitude() , -ddmTodd("00136.3714") , percentageAccuracy );
    BOOST_CHECK_CLOSE( route[0].elevation() , 395 , percentageAccuracy );

    // $GPRMC,133549.000,A,5320.9122,N,00138.1426,W,0.000,0.00,120812,,A*66
    BOOST_CHECK_CLOSE( route[1517].latitude() , ddmTodd("5320.9122") , percentageAccuracy );
    BOOST_CHECK_CLOSE( route[1517].longitude() , -ddmTodd("00138.1426") , percentageAccuracy );

}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////////////////////////
