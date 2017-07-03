#!/bin/bash
cd src
sed -i 's/\(const char \*ssid\s*=\s*"\)\(.*\)";/\1your SSID here";/' *.cpp *.ino
sed -i 's/\(const char \*password\s*=\s*"\)\(.*\)";/\1your password here";/' *.cpp *.ino
