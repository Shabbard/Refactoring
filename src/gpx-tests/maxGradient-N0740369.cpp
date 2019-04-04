#include <boost/test/unit_test.hpp>
#include <fstream>
#include <string>

#include "earth.h"
#include "gridworld.h"
#include "gridworld_route.h"
#include "logs.h"
#include "route.h"

using namespace GPS;

// Constants for tests
const degrees CHECK_TOLERANCE = 0.2;
const degrees GRADIENT = 0.5729386;      // arctan(100 / 10000)
const degrees DIAG_GRADIENT = 0.4051355; // arctan(100 / sqrt(2 * (10000^2))
const metres HORIZONTAL_GRID_UNIT = 10000;
const metres VERTICAL_GRID_UNIT = 100;

/**
 * Saves a log file for route.
 *
 * \param name Name of saved file
 * \param route Route to save to log
 * \return File path of the saves file
 */
static std::string saveLogFile(std::string name, GridWorldRoute &route) {
  std::string filepath = LogFiles::GPXRoutesDir + "N0740369-" + name + ".gpx";

  std::ofstream logFile(filepath);
  logFile << route.toGPX(true, name);
  logFile.close();

  return filepath;
}

BOOST_AUTO_TEST_SUITE(Route_MaxGradient_N0740369)

/**
 * Checks that a route with a singular point returns 0 for maximum gradient
 */
BOOST_AUTO_TEST_CASE(SINGLE_POINT) {
  GridWorld world(Earth::CityCampus, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT);
  GridWorldRoute gridRoute("A", world);
  std::string logPath = saveLogFile("flat-route", gridRoute);

  Route route(logPath, true);
  BOOST_CHECK_CLOSE(route.maxGradient(), 0.0, CHECK_TOLERANCE);
}

/**
 * Checks that a route with no gradient (is flat) returns 0 for maximum gradient
 */
BOOST_AUTO_TEST_CASE(FLAT_ROUTE) {
  GridWorld world(Earth::CityCampus, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT);
  GridWorldRoute gridRoute("ABC", world);
  std::string logPath = saveLogFile("flat-route", gridRoute);

  Route route(logPath, true);
  BOOST_CHECK_CLOSE(route.maxGradient(), 0.0, CHECK_TOLERANCE);
}

/**
 * Checks that an entirely downhill route returns a negative gradient
 */
BOOST_AUTO_TEST_CASE(DOWNHILL_ROUTE) {
  GridWorld world(Earth::CityCampus, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT);
  GridWorldRoute gridRoute("MRW", world);
  std::string logPath = saveLogFile("downhill-route", gridRoute);

  Route route(logPath, true);
  BOOST_CHECK_CLOSE(route.maxGradient(), -GRADIENT, CHECK_TOLERANCE);
}

/**
 * Checks that an entirely uphill route returns a positive gradient
 */
BOOST_AUTO_TEST_CASE(UPHILL_ROUTE) {
  GridWorld world(Earth::CityCampus, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT);
  GridWorldRoute gridRoute("WRM", world);
  std::string logPath = saveLogFile("uphill-route", gridRoute);

  Route route(logPath, true);
  BOOST_CHECK_CLOSE(route.maxGradient(), GRADIENT, CHECK_TOLERANCE);
}

/**
 * Checks that an entirely downhill route with a flat section returns 0 for
 * maximum gradient
 */
BOOST_AUTO_TEST_CASE(DOWNHILL_ROUTE_WITH_FLAT) {
  GridWorld world(Earth::CityCampus, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT);
  GridWorldRoute gridRoute("MRWX", world);
  std::string logPath = saveLogFile("downhill-route-with-flat", gridRoute);

  Route route(logPath, true);
  BOOST_CHECK_CLOSE(route.maxGradient(), 0, CHECK_TOLERANCE);
}

/**
 * Checks that an entirely uphill route with a flat section returns a positive
 * gradient
 */
BOOST_AUTO_TEST_CASE(UPHILL_ROUTE_WITH_FLAT) {
  GridWorld world(Earth::CityCampus, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT);
  GridWorldRoute gridRoute("XWRM", world);
  std::string logPath = saveLogFile("uphill-route-with-flat", gridRoute);

  Route route(logPath, true);
  BOOST_CHECK_CLOSE(route.maxGradient(), GRADIENT, CHECK_TOLERANCE);
}

/**
 * Checks that an enitrely downhill route with a diagonal section returns the
 * greater of the two gradients
 */
BOOST_AUTO_TEST_CASE(DOWNHILL_ROUTE_WITH_DIAG) {
  GridWorld world(Earth::CityCampus, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT);
  GridWorldRoute gridRoute("MLF", world);
  std::string logPath = saveLogFile("downhill-route-with-diag", gridRoute);

  Route route(logPath, true);
  BOOST_CHECK_CLOSE(route.maxGradient(), -DIAG_GRADIENT, CHECK_TOLERANCE);
}

/**
 * Checks that an entirely uphill route with a diagonal section returns the
 * greater of the two gradients
 */
BOOST_AUTO_TEST_CASE(UPHILL_ROUTE_WITH_DIAG) {
  GridWorld world(Earth::CityCampus, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT);
  GridWorldRoute gridRoute("FLM", world);
  std::string logPath = saveLogFile("uphill-route-with-diag", gridRoute);

  Route route(logPath, true);
  BOOST_CHECK_CLOSE(route.maxGradient(), GRADIENT, CHECK_TOLERANCE);
}

/**
 * Checks that a route with both uphill and downhill sections returns a positive
 * gradient
 */
BOOST_AUTO_TEST_CASE(ROUTE_WITH_UPHILL_AND_DOWNHILL) {
  GridWorld world(Earth::CityCampus, HORIZONTAL_GRID_UNIT, VERTICAL_GRID_UNIT);
  GridWorldRoute gridRoute("KLMNO", world);
  std::string logPath =
      saveLogFile("route-with-uphill-and-downhill", gridRoute);

  Route route(logPath, true);
  BOOST_CHECK_CLOSE(route.maxGradient(), GRADIENT, CHECK_TOLERANCE);
}

BOOST_AUTO_TEST_SUITE_END()
