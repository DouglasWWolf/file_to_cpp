@echo off
git add *.cpp
git add *.sln *.vcxproj *.vcxproj.filters
git add README.md push.bat
git commit -m "See History.h for changes"
git push origin main

