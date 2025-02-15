#include "drivercharge.h"
#include "iostream"
using namespace std;

DriverCharge::DriverCharge() {}

DriverCharge::DriverCharge(QVariantList drivercharge)
{
    this->id = drivercharge[0].toInt();
    this->carId = drivercharge[1].toInt();
    this->driverId = drivercharge[2].toInt();
    this->locationId = drivercharge[3].toInt();
    this->kwh = drivercharge[4].toFloat();
    this->duration = drivercharge[5].toFloat();
    this->date = drivercharge[6].toDateTime();

    this->name = drivercharge[7].toString();
}

QString DriverCharge::getName()
{
    return name;
}

int DriverCharge::getId()
{
    return id;
}

int DriverCharge::getCarId()
{
    return carId;
}

int DriverCharge::getDriverId()
{
    return driverId;
}

int DriverCharge::getLocationId()
{
    return locationId;
}

float DriverCharge::getKwh()
{
    return kwh;
}

float DriverCharge::getDuration()
{
    return duration;
}

QDateTime DriverCharge::getDate() {
    return date;
}

void DriverCharge::setCarId(int newCarId)
{
    carId = newCarId;
}

void DriverCharge::setDriverId(int newDriverId)
{
    driverId = newDriverId;
}

void DriverCharge::setLocationId(int newLocationId)
{
    locationId = newLocationId;
}

void DriverCharge::setKwh(float newKwh)
{
    kwh = newKwh;
}

void DriverCharge::setDuration(float newDuration)
{
    duration = newDuration;
}

void DriverCharge::setDate(QDateTime newDate) {
    date = newDate;
};
