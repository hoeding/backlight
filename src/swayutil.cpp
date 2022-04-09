#include "backlight.hpp"
#include "logging.hpp"
#include "utility.hpp"
#include <chrono>
#include <ctime>
#include <memory>
#include <mutex>
#include <project_version.hpp>
#include <shared_mutex>
#include <thread>
#include <time.h>

using std::endl;
using std::flush;
using std::mutex;
using std::shared_mutex;
using std::string;
using std::thread;
using std::to_string;
using std::this_thread::sleep_for;
using namespace utility;

class data_pack {
private:
  string battery{"BATTERY_PLACEHOLDER"};
  shared_mutex battery_mtx;

  string my_time{"my_time_PLACEHOLDER"};
  shared_mutex my_time_mtx;

  string brightness{"BRIGHTNESS_PLACEHOLDER"};
  shared_mutex brightness_mtx;

  bool if_true_we_quit = false;
  shared_mutex if_true_we_quit_mtx;

  bool if_true_we_have_updated_data = false;
  shared_mutex if_true_we_have_updated_data_mtx;

public:
  void swap_battery(string fresh_string) {
    battery_mtx.lock();
    battery.swap(fresh_string);
    update();
    battery_mtx.unlock();
  }

  string read_battery() {
    string returner;
    battery_mtx.lock_shared();
    returner = battery;
    battery_mtx.unlock();
    return returner;
  }

  string read_my_time() {
    string returner;
    my_time_mtx.lock_shared();
    returner = my_time;
    my_time_mtx.unlock();
    return returner;
  };
  void write_my_time(string param) {
    my_time_mtx.lock();
    my_time = param;
    update();
    my_time_mtx.unlock();
  };

  void swap_brightness(string fresh_string) {
    brightness_mtx.lock();
    brightness.swap(fresh_string);
    update();
    brightness_mtx.unlock();
  }

  string read_brightness() {

    string returner;
    brightness_mtx.lock_shared();
    returner = brightness;
    brightness_mtx.unlock();
    return returner;
  };

  void write_brightness(string param) {
    brightness_mtx.lock();
    brightness = param;
    update();
    brightness_mtx.unlock();
  };
  void update() {
    if_true_we_have_updated_data_mtx.lock();
    if_true_we_have_updated_data = true;
    if_true_we_have_updated_data_mtx.unlock();
  };
  void reset() {
    if_true_we_have_updated_data_mtx.lock();
    if_true_we_have_updated_data = false;
    if_true_we_have_updated_data_mtx.unlock();
  };
  void stop() {
    if_true_we_quit_mtx.lock();
    if_true_we_quit = true;
    if_true_we_quit_mtx.unlock();
  }
  bool are_we_still_going() {
    bool returner;
    if_true_we_quit_mtx.lock_shared();
    returner = !if_true_we_quit;
    if_true_we_quit_mtx.unlock();
    return returner;
  };
  bool are_we_stale() {
    bool returner;
    if_true_we_have_updated_data_mtx.lock_shared();
    returner = if_true_we_have_updated_data;
    if_true_we_have_updated_data_mtx.unlock();
    return returner;

    return if_true_we_have_updated_data;
  };
};

void battery_fn(data_pack *shared_state) {
  try {
    cerr << "battery_fn called\n" << flush;
    string old_str{""};
    string new_str{""};
    for (; shared_state->are_we_still_going(); sleep_for(4000ms)) {

      new_str = to_string(ez_pct(
          get_int_from_file("/sys/class/power_supply/BAT0/charge_now"),
          get_int_from_file("/sys/class/power_supply/BAT0/charge_full")));
      if (old_str.compare(new_str) != 0) {
        old_str = new_str;
        shared_state->swap_battery(new_str);
      }
      new_str.clear();
    };
  } catch (...) {
    dbg(true, 0, "Battery thread caught unknown exception, terminating");
    shared_state->stop();
  }
};

void my_time_fn(data_pack *shared_state) {
  try {
    for (; shared_state->are_we_still_going(); sleep_for(1s)) {
      time_t now = time(0);
      struct tm tstruct;
      char buf[80];
      tstruct = *localtime(&now);
      strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
      shared_state->write_my_time(buf);
    }

  } catch (...) {
    dbg(true, 0, "my_time thread caught unknown exception, terminating");
    shared_state->stop();
  }
};
void brightness_fn(data_pack *shared_state) {
  using namespace backlight;
  try {
    cerr << "brightness_fn called\n" << flush;
    string old_str{""};
    string new_str{""};
    vector<path> paths_to_config_files = backlight::default_paths;
    for (; shared_state->are_we_still_going(); sleep_for(500ms)) {
      for (auto config_file : paths_to_config_files) {
        vector<path> devices = get_backlights_from_config_file(config_file);
        for (auto device : devices) {
          float how_bright =
              backlight::get_current_brightness_percentage(device);
          new_str = new_str + " " + to_string(how_bright);
        }
        //;
      }

      if (old_str.compare(new_str) != 0) {
        old_str = new_str;
        shared_state->swap_brightness(new_str);
      }
      new_str.clear();
    }

  } catch (...) {
    dbg(true, 0, "brightness thread caught unknown exception, terminating");
    shared_state->stop();
  }
};

void writer_fn(data_pack *shared_state) {
  cout << "Swayutil version PROJECT_VERSION\n" << flush;
  for (; shared_state->are_we_still_going(); this_thread::sleep_for(200ms)) {
    if (shared_state->are_we_stale()) {
      cout << shared_state->read_battery() << " "
           << shared_state->read_my_time() << " "
           << shared_state->read_brightness() << endl;
      shared_state->reset();
      ;
    }
  }
}

int main([[maybe_unused]] const int argc, [[maybe_unused]] const char *argv[]) {

  data_pack shared_state;
  thread battery(battery_fn, &shared_state);
  thread my_time(my_time_fn, &shared_state);
  thread brightness(brightness_fn, &shared_state);
  thread writer(writer_fn, &shared_state);

  cerr << "Joining battery\n" << flush;
  battery.join();
  cerr << "Joining my_time\n" << flush;
  my_time.join();
  cerr << "Joining brightness\n" << flush;
  brightness.join();
  cerr << "Joining writer\n" << flush;
  writer.join();
}