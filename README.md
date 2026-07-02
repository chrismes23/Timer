# Timer
A simple Timer desktop app built with Win32 API in C++
The idea is to simulate a kitchen timer/stopwatch
<br>
![Screenshot](https://github.com/chrismes23/Timer/blob/main/res/screenshot1.png?raw=true)<br>
![Screenshot](https://github.com/chrismes23/Timer/blob/main/res/screenshot2.png?raw=true)
## Instructions
To run the program, firstly clone the repository.Then using MinGW compiler on Windows run
```
g++ src/timer.cpp -o timer.exe -lgdi32 -lwinmm
```
<br>

## Usage

### Timer
Press Min and Sec buttons to set the desired time.Press S/S to start the countdown.When time reaches zero, press S/S to stop the alarm or close the window.<br>Time can also be passed as arguments like
counter.exe (minutes) (seconds)

### Stopwatch
Reset the timer with R button (if not already reset) and press S/S to start the stopwatch.