#include <chrono>
#include <iostream>
#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

struct ProgramMetrics {
  string name;
  int fileSize;
  double excTime;
  int memAccess;
};

// TODO: IF I have time, translate this to run on Linux

ProgramMetrics measureProgramMac(const string &program,
                                 const string &args = "") {
  ProgramMetrics metrics = {program, 0, 0, 0};

  // Measure the file size of the executable program
  struct stat st;
  if (stat(program.c_str(), &st) != 0) {
    cerr << "Error: cannot stat file " << program << endl;
    return metrics;
  }
  metrics.fileSize = st.st_size;

  // Start the clock
  steady_clock::time_point start = steady_clock::now();

  // Execute the program
  string cmd = "./" + program + " " + args + " > /dev/null";
  int ret = system(cmd.c_str());
  if (ret != 0) {
    cerr << "Error: cannot execute " << program << endl;
    return metrics;
  }

  // Stop the clock
  steady_clock::time_point stop = steady_clock::now();

  // Calculate the execution time of the program
  duration<double> elapsed = duration_cast<duration<double>>(stop - start);
  metrics.excTime = elapsed.count();

  // Measure the memory access of the program
  // ! This runs on MAC ONLY!
  mach_vm_size_t vmsize;
  mach_vm_size_t vm_page_size;
  mach_port_t task;

  // Get the task port of the current process
  task_for_pid(mach_task_self(), getpid(), &task);

  // Get the virtual memory size of the task
  vm_region_basic_info_data_64_t info;
  mach_vm_address_t address = mach_vm_trunc_page(0);
  while (true) {
    mach_msg_type_number_t count = VM_REGION_BASIC_INFO_COUNT_64;
    if (mach_vm_region(task, &address, &vmsize, VM_REGION_BASIC_INFO_64,
                       (vm_region_info_64_t)&info, &count,
                       &task) != KERN_SUCCESS)
      break;

    // Calculate the total number of memory accesses
    vm_page_size = vmsize;
    address += vmsize;
  }

  metrics.memAccess = vm_page_size;

  return metrics;
}

// run program metric test battery (k = 30) and return the average
ProgramMetrics runTestBattery(const string &program, int k = 30,
                              const string &args = "") {
  ProgramMetrics avgMetrics = {program, 0, 0, 0};

  for (int i = 0; i < k; i++) {
    ProgramMetrics metrics = measureProgramMac(program, args);
    avgMetrics.fileSize += metrics.fileSize;
    avgMetrics.excTime += metrics.excTime;
    avgMetrics.memAccess += metrics.memAccess;
  }

  avgMetrics.fileSize /= k;
  avgMetrics.excTime /= k;
  avgMetrics.memAccess /= k;

  return avgMetrics;
}

std::string comparePrograms(const string &program1, const string &program2,
                            int k = 30, const string &args = "") {

  // Run the test battery for program 1
  ProgramMetrics metrics1 = runTestBattery(program1, k, args);

  // Run the test battery for program 2
  ProgramMetrics metrics2 = runTestBattery(program2, k, args);

  // Compare the two programs and calculate the weighted ratio
  int fileSizeDiff = -(metrics1.fileSize - metrics2.fileSize);
  double excTimeDiff = -(metrics1.excTime - metrics2.excTime);
  int memAccessDiff = -(metrics1.memAccess - metrics2.memAccess);

  double fileSizeRatio =
      fileSizeDiff / max(metrics1.fileSize, metrics2.fileSize);
  double excTimeRatio = excTimeDiff / max(metrics1.excTime, metrics2.excTime);
  double memAccessRatio =
      memAccessDiff / max(metrics1.memAccess, metrics2.memAccess);

  double score =
      0.5 * excTimeRatio + 0.3 * memAccessRatio + 0.2 * fileSizeRatio;

  return "\t" + to_string(score) + "\t|\t" + to_string(fileSizeRatio) +
         "\t|\t" + to_string(excTimeRatio) + "\t|\t" + to_string(memAccessDiff);
}

/*
 * Compares program 1 to program 2 by ProgramMetrics
 *      Typically: Optimized program vs. Unoptimized program
 *
 * returns a score between -inf and +inf
 *     Where -x indicates that program 1 is  than program 2
 *     Where 0 indicates that program 1 the same as program 2
 *     Where +x indicates that program 1 is better than program 2
 *
 * The score is calculated by the weighted ratio of the metrics.
 * Where execution time is the most important factor, followed by memory access
 * and file size.
 *
 * Include the number of tests to run as the third argument (default is 30)
 * if you want to eliminate even more noise.
 *
 * Example:
 *    ./TIPProgMetrics <program1> <program2> <k> <args>
 * or
 *    ./TIPProgMetrics <program1> <program2>
 */
int main(int argc, char *argv[]) {
  if (argc < 3) {
    cerr << "Usage: " << argv[0]
         << " <program1> <program2> <k> optional number of tests to run"
         << endl;
    return 1;
  }

  int k = (argc >= 4) ? atoi(argv[3]) : 30;

  string args = "";
  if (argc > 4) {
    for (int i = 4; i < argc; i++) {
      args += string(" ") + argv[i];
    }
  }

  string program1 = argv[1];
  string program2 = argv[2];

  cout << comparePrograms(program1, program2, k, args) << endl;

  return 0;
}