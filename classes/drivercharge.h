#ifndef DRIVERCHARGE_H
#define DRIVERCHARGE_H

#include "QVariantList"
#include "QString"
#include "QDateTime"

using namespace std;

class DriverCharge
{
private:
    QString name;

    int id;
    int carId;
    int driverId;
    int locationId;
    float kwh;
    float duration;
    QDateTime date;

public:
    DriverCharge();
    DriverCharge(QVariantList drivercharge);
    QString getName();

    int getId();
    int getCarId();
    int getDriverId();
    int getLocationId();
    float getKwh();
    float getDuration();
    QDateTime getDate();

    void setCarId(int newCarId);
    void setDriverId(int newDriverId);
    void setLocationId(int newLocationId);
    void setKwh(float newKwh);
    void setDuration(float newDuration);
    void setDate(QDateTime newDate);
};

#endif // DRIVERCHARGE_H
