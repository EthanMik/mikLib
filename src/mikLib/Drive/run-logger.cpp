#include "vex.h"
#include "mikLib/Drive/run-logger.h"

#include <cstdio>
#include <vector>

namespace mik::run_log {

namespace {
    struct row {
        uint32_t t_ms;
        float x, y, theta;
    };

    // Rows accumulate here for the whole run and reach the card once, in stop(). An SD write is
    // slow enough that doing one per sample would disturb the very loop timing being measured.
    std::vector<row> buffer;
    std::string destination = "run.csv";
    vex::task sampler;

    bool running = false;

    int sample_task() {
        // Timestamps are relative to the moment logging began, not to brain uptime, so a log always
        // starts at zero no matter how long the robot has been powered.
        const uint32_t started = Brain.Timer.system();

        while (running) {
            buffer.push_back(row{
                Brain.Timer.system() - started,
                chassis.get_X_position(),
                chassis.get_Y_position(),
                chassis.get_absolute_heading(),
            });

            // A plain sleep, so the true rate drifts slightly under load. That is why every row
            // carries its own timestamp rather than the reader assuming a fixed interval.
            vex::this_thread::sleep_for(1000 / SAMPLE_HZ);
        }
        return 0;
    }

    /**
     * Writes the whole buffer in one transaction.
     *
     * savefile replaces the file rather than appending, so each run overwrites the last. Pass a
     * different name to start() when several runs need keeping.
     *
     * @return True if every byte reached the card. savefile reports how many bytes it saved, which
     *         falls short when the card is pulled mid-run or the write otherwise fails.
     */
    bool flush() {
        std::string out = "# mikGen run log v1\n";
        out += "t_ms,x,y,theta\n";

        char line[128];
        for (const row& r : buffer) {
            snprintf(line, sizeof(line), "%lu,%.3f,%.3f,%.2f\n",
                (unsigned long)r.t_ms, r.x, r.y, r.theta);
            out += line;
        }

        std::vector<uint8_t> bytes(out.begin(), out.end());
        const int32_t saved = Brain.SDcard.savefile(destination.c_str(), bytes.data(), bytes.size());
        return saved == (int32_t)bytes.size();
    }
}

bool start(const std::string& file_name) {
    if (running) { return true; }

    if (!Brain.SDcard.isInserted()) {
        print("run_log: no SD card, nothing will be recorded", mik::bright_red);
        return false;
    }

    destination = file_name;
    buffer.clear();
    // Enough for a 70 second run, which covers a 60 second skills routine with margin. Reserving
    // up front keeps a vector reallocation, and the copy that comes with it, out of the sample
    // loop. At 16 bytes a row this is about 56 kB, which the brain will not miss.
    buffer.reserve(SAMPLE_HZ * 70);

    running = true;

    sampler = vex::task(sample_task);
    return true;
}

void stop() {
    if (!running) { return; }
    running = false;

    // Give the sampling loop one full period plus a margin to notice the cleared flag and return
    // on its own. Reading the buffer while it is still being appended to would be a data race.
    vex::this_thread::sleep_for(1000 / SAMPLE_HZ + 10);
    sampler.stop();

    if (flush()) {
        print(("run_log: wrote " + to_string(buffer.size()) + " rows to " + destination).c_str(), mik::green);
    } else {
        print(("run_log: failed to write " + destination + " to the SD card").c_str(), mik::bright_red);
    }
}

bool is_running() { return running; }

int sample_count() { return (int)buffer.size(); }

}
