@ECHO OFF
echo Let's assume you have compiled a release build with Visual Studio
del release\*
rmdir asd

mkdir release
copy Project1\Release\*.dll release\
copy Project1\Release\tetris.exe release\
copy Project1\DejaVuSans-Bold.ttf release\
echo Please zip the release-dir in this directory