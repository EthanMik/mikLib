#pragma once

#include <string>

/**
 * @brief Records an autonomous run to the SD card so it can be replayed over the planned path in
 * mikGen.
 *
 * Every row holds a timestamp and the robot's odometry pose: t_ms, x, y and theta, in the same
 * field inches and compass degrees mikLib uses everywhere else. mikGen compares those poses
 * against the planned path itself, so nothing else needs recording.
 *
 * A caveat worth knowing before reading too much into a run. This logs what the robot believed,
 * taken from its own odometry. It cannot see odometry drift itself: if the wheels slip, the log is
 * wrong along with the robot and the run still looks clean. To catch that, measure where the robot
 * physically stopped and compare it against the final row.
 *
 * Rows are buffered in RAM and written once, on stop(). Writing inside the sample loop would put an
 * SD transaction on a 20 ms cadence and disturb the very timing being measured. A 15 second run is
 * roughly 750 rows and about 20 kB, so the buffer is not a concern.
 *
 * auton() in main.cpp already wraps every autonomous run in start() and stop(), so a match is
 * recorded with nothing added. Call them yourself only to record a run started some other way,
 * such as the brain screen's test button. Calling stop() from inside an auton ends the recording
 * at that point, and the stop() in auton() then has nothing left to write.
 * @code
 * mik::run_log::start("run.csv");
 * // run the routine
 * mik::run_log::stop();
 * @endcode
 */
namespace mik::run_log {

    /** @brief Hz the logger samples at. Odometry updates at 200 Hz; 50 is plenty to draw the path and keeps files small. */
    constexpr int SAMPLE_HZ = 50;

    /**
     * @brief Clears the buffer and starts sampling in the background.
     * @param file_name Destination on the SD card. The contents are CSV, so .csv is the honest
     *                  extension; savefile() is called directly and imposes no naming rule, and
     *                  mikGen's importer accepts .csv and .txt alike.
     * @return False if no SD card is inserted, in which case nothing is recorded.
     */
    bool start(const std::string& file_name = "run.csv");

    /** @brief Stops sampling and writes the buffer to the SD card. Safe to call when not running. */
    void stop();

    /** @return True while a run is being recorded. */
    bool is_running();

    /** @return Rows captured so far, for a readout on the brain screen. */
    int sample_count();
}
