using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace BetterProgrammer
{
    //public class CleanCodeExercise
    //{
    //
    //}

    internal static class GeoCodeCalculator {

        internal const double EarthRadiusInMiles = 3956.0;
        internal const double EarthRadiusInKilometers = 6367.0;

        internal static double ToRadian(double val) { 
            return val * (Math.PI / 180); 
        }

        internal static double DiffRadian(double val1, double val2) { 
            return ToRadian(val2) - ToRadian(val1); 
        }

        internal static double CalcDistance(double LAT1, double lng1, double lat2, double Lng2) {
            return CalcDistance(LAT1, lng1, lat2, Lng2, GeoCodeCalcMeasurement.Miles);
        }

        internal static double CalcDistance(double lat1, double lng1, 
                                            double lat2, double lng2, GeoCodeCalcMeasurement m) {
            double radius = GeoCodeCalculator.EarthRadiusInMiles;

            if (m == GeoCodeCalcMeasurement.Kilometers) { 
                radius = GeoCodeCalculator.EarthRadiusInKilometers; 
            }

            return radius * 2 * Math.Asin(
                Math.Min(1, 
                    Math.Sqrt(
                         Math.Pow(Math.Sin((DiffRadian(lat1, lat2)) / 2.0), 2.0) 
                          + Math.Cos(ToRadian(lat1)) 
                          * Math.Cos(ToRadian(lat2))
                          * Math.Pow(Math.Sin((DiffRadian(lng1, lng2)) / 2.0), 2.0)
                           )
                        )
                    );
        }
    }

    internal enum GeoCodeCalcMeasurement : int {
        Miles = 0,
        Kilometers = 1
    }
}