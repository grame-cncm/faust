// Sensor mapping queries must describe the mapping that receives sensor updates.
#include <cstdio>

#include "faust/gui/APIUI.h"

static int errors = 0;
static int checks = 0;

static void check(bool condition, const char* message)
{
    ++checks;
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", message);
        ++errors;
    }
}

static void testSensor(bool accelerometer)
{
    APIUI ui;
    FAUSTFLOAT zone = 0;
    ui.openVerticalBox("test");
    ui.declare(&zone, accelerometer ? "acc" : "gyr", "0 0 -10 0 10");
    ui.addHorizontalSlider("gain", &zone, 0.5, 0, 1, 0.01);
    ui.closeBox();

    auto set = [&](int axis, int curve) {
        if (accelerometer) {
            ui.setAccConverter(0, axis, curve, -20, 0, 20);
        } else {
            ui.setGyrConverter(0, axis, curve, -20, 0, 20);
        }
    };
    auto get = [&](int expected_axis, int expected_curve, double expected_max) {
        int axis, curve;
        double min, mid, max;
        if (accelerometer) {
            ui.getAccConverter(0, axis, curve, min, mid, max);
        } else {
            ui.getGyrConverter(0, axis, curve, min, mid, max);
        }
        check(axis == expected_axis, "getter returns the active axis");
        check(curve == expected_curve, "getter returns the active curve");
        check(min == -expected_max && mid == 0 && max == expected_max,
              "getter returns the active mapping bounds");
    };
    auto propagate = [&](int axis, double value) {
        if (accelerometer) {
            ui.propagateAcc(axis, value);
        } else {
            ui.propagateGyr(axis, value);
        }
    };
    APIUI::Type type = accelerometer ? APIUI::kAcc : APIUI::kGyr;
    get(0, 0, 10);
    check(ui.getParamType(0) == type, "metadata activates the sensor");

    // Keep inactive records on earlier axes while moving to Y and then Z.
    for (int axis = 1; axis <= 2; ++axis) {
        set(axis, axis);
        get(axis, axis, 20);
        zone = 0.25;
        propagate(axis - 1, 20);
        check(zone == FAUSTFLOAT(0.25), "the previous axis no longer updates the zone");
        propagate(axis, -20);
        check(zone == FAUSTFLOAT(axis == 1 ? 1 : 0), "the active axis updates the zone");
    }

    set(-1, 0);
    get(-1, 0, 100);
    check(ui.getParamType(0) == APIUI::kNoType, "disabled sensor has no type");
    zone = 0.25;
    for (int axis = 0; axis < 3; ++axis) propagate(axis, 20);
    check(zone == FAUSTFLOAT(0.25), "disabled mappings do not update the zone");

    // Existing records must still be reusable by the setter after disabling.
    for (int curve = 0; curve < 4; ++curve) {
        set(0, curve);
        get(0, curve, 20);
        check(ui.getParamType(0) == type, "reactivation restores the sensor type");
        zone = 0.25;
        propagate(0, -20);
        check(zone == FAUSTFLOAT(curve == 1 || curve == 3 ? 1 : 0),
              "reactivated curves update the zone");
    }
}

int main()
{
    testSensor(true);
    testSensor(false);

    // A disabled accelerometer must not hide an active gyroscope.
    APIUI ui;
    FAUSTFLOAT zone = 0;
    ui.addHorizontalSlider("gain", &zone, 0.5, 0, 1, 0.01);
    check(ui.getParamType(0) == APIUI::kNoType, "unmapped parameter has no sensor type");
    ui.setAccConverter(0, 0, 0, -10, 0, 10);
    ui.setAccConverter(0, -1, 0, -10, 0, 10);
    ui.setGyrConverter(0, 2, 0, -10, 0, 10);
    check(ui.getParamType(0) == APIUI::kGyr, "inactive accelerometer does not hide gyroscope");

    std::printf("Sensor mapping tests: %d checks, %d errors\n", checks, errors);
    return errors == 0 ? 0 : 1;
}
