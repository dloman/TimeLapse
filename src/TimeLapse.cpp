#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <atomic>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <thread>

std::atomic<bool> gIsRunning(true);

using namespace std::literals;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Interrupt(int)
{
  gIsRunning = false;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main(int argc, const char** argv)
{
  std::string OutputDirectory("");

  if (argc > 1)
  {
    OutputDirectory = argv[1];
  }
  cv::VideoCapture VideoSource;

  VideoSource.open(0);

  if(!VideoSource.isOpened())
  {
    std::cerr << "ERROR: unable to open camera";

    return 1;
  }

  cv::Mat VideoFrame;


  while(gIsRunning)
  {
    VideoSource >> VideoFrame;

    std::vector<int> CompressionParameters{cv::IMWRITE_PNG_COMPRESSION, 9};

    std::time_t Time = std::time(nullptr);
    std::tm LocalTime  = *std::localtime(&Time);


    std::stringstream OutputFilename;

    OutputFilename
      << OutputDirectory
      << std::put_time(&LocalTime, "%F-%H-%M-%S")
      << ".png";

    imwrite(
      OutputFilename.str(),
      VideoFrame,
      {cv::IMWRITE_PNG_COMPRESSION, 9});

    std::this_thread::sleep_for(10s);

  }

  return 0;
}
